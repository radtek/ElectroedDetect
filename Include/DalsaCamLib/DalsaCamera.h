#ifndef _DALSACAMERA_LIB_H_
#define _DALSACAMERA_LIB_H_

#ifdef DALSACAMERA_EXPORTS
#define DALSACAMERA_DLLAPI __declspec(dllexport)
#else
#define DALSACAMERA_DLLAPI __declspec(dllimport)
#endif

#include "ZcStruct.h"

typedef struct DALSACAMERA_DLLAPI tagDHGrabStatus
{
	bool bIsOpen;
	bool bIsStart;
	bool bIsPause;
	bool bIsGrabbing;
}DHGrabStatus;

//获取相机数据回调函数
typedef LRESULT (__cdecl *DalsaFunOnGetImage)(ImageUnitBase *pImageInfo, int cameraID, void* param);

//保存图片前的回调函数 返回TRUE则保存图片，否则不保存图片
typedef LRESULT (__cdecl *DalsaFunBeforeSaveImage)(ImageUnitBase *pImageInfo, void* param);

//相机采集的相关事宜
typedef LRESULT (__cdecl *DalsaFunOnCameraEvent)(CameraEvent EventID, void* param);

class DALSACAMERA_DLLAPI CCameraGrabBase
{
public:
	//相机采集初始化
	CCameraGrabBase();
	virtual ~CCameraGrabBase();

	/**********************************************************
	* 设置相机图像数据获取的回调函数，用于多个相机情况下异步取数
	* pDHFunOnGetImage 相机获取图像回调函数
	* param            回调函数参数
    * 返回值 TRUE-成功 FALSE-失败
    ************************************************************/
	void SetCallBackGetImageFun(DalsaFunOnGetImage pDalsaFunOnGetImage, void* param);

	/**********************************************************
	* 设置相机图像数据获取的回调函数，用于多个相机情况下异步取数
	* pDHFunBeforeSaveImage	保存图像前的回调函数
	* param					回调函数参数
    *返回值 TRUE-成功 FALSE-失败
    ***********************************************************/
	void SetCallBackBeforeSaveImageFun(DalsaFunBeforeSaveImage pDalsaFunBeforeSaveImage, void* param);

	/*********************************************************
	* 设置相机运行触发事件回调函数
	* pDHFunOnCameraEvent   相机事件回调函数
	* param                 回调函数参数
	***********************************************************/
	void SetCallBackCameraEventFun(DalsaFunOnCameraEvent pDalsaFunOnCameraEvent,void* param);
	
	/*********************************************************
	* 暂停采集
	* bPause TRUE-暂停 FALSE-继续
    ***********************************************************/
	void DalsaPauseGrab(bool bPause);

	/**********************************************************
	* 读取是否暂停采集标志
	* 返回值 TRUE-暂停 FALSE-继续
	***********************************************************/
	bool IsDalsaPauseGrab();

	/**********************************************************
	* 返回相机是否连接正常 
	* 返回值 TRUE-运行 FALSE-未运行
	**********************************************************/
	bool IsDalsaConnected();

	bool IsDalsaGrabbing();

	/*********************************************************
	* 读取图像参数
	* pImageInfo 图像参数
    * 返回值 TRUE-成功 FALSE-失败
	***********************************************************/
	bool GetImageInfo(ImageUnitBase *pImageInfo);

	/*********************************
	* 设置图像参数
	* pImageInfo 图像参数
    * 返回值 TRUE-成功 FALSE-失败
	************************************/
	bool SetImageInfo(const ImageUnitBase *pImageInfo);

public:
	/********************************************
	* 开启相机连接 
    *返回值 TRUE-成功 FALSE-失败,派生类成功后需调用基类该函数
	***********************************************/
	virtual bool DalsaOpenCamera() = 0;
	
	/**********************************************
	* 关闭相机连接
    *返回值 TRUE-成功 FALSE-失败,派生类成功后需调用基类该函数
	************************************************/
	virtual bool DalsaCloseCamera() = 0;

	/*********************************************
	* 启动采集线程开始进行连续采集
	* sOption 采集选项，见类CGrabOption介绍
    *返回值 TRUE-成功，启动采集线程，按照sOption设置条件进行采集 FALSE-失败
	********************************************/
	virtual bool DalsaStartGrab() = 0;
	
	/**********************************************
	* 停止图像采集线程
	* 返回值 TRUE-成功 FALSE-失败
	***********************************************/
	virtual bool DalsaStopGrab() = 0;
	
	/***************************************************
	* 相机采集数据，用于同步采集，一次采集一张图片
	* pBuffer-out，数据内存指针，用于存放返回的数据
	* dwBufferSize-inout，内存大小，防止溢出,返回实际数据大小
	* pImageInfo-out,采集到的图像信息
    * 返回值 0-成功，其余值失败, 10-重新连接相机
	***************************************************/
	virtual bool DalsaGrabImage() = 0;

public:
	//数据接收回调函数
	DalsaFunOnGetImage m_pDalsaFunOnGetImage;
	void*              m_pDalsaFunOnGetImageParam;
	//图片保存前回调函数
	DalsaFunBeforeSaveImage m_pDalsaFunBeforeSaveImage;
	void*                   m_pDalsaFunBeforeSaveImageParam;
	//获取相机运行事件回调函数
	DalsaFunOnCameraEvent m_pDalsaFunOnCameraEvent;
	void*                 m_pDalsaFunOnCameraEventParam;
	
	//修改相机状态，子类可调用此函数改变状态
	void DalsaCameraChangeEvent(CameraEvent CamEvent);

	//相机参数指针---相机采集参数
	CameraGrabPara* m_pCameraPara;
	//图像信息指针---图像信息参数
	ImageUnitBase*  m_pImageUnit;

public:
	//暂停采集标志
	bool    m_bDalsaPauseGrab;

	//相机连接正常标志
	bool    m_bDalsaConnected;

	bool    m_bDalsaGrabbing;
};


#endif  //_DALSACAMERA_LIB_H_