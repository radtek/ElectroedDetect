#ifndef _BALSERCAMERA_LIB_H_
#define _BALSERCAMERA_LIB_H_

#ifdef BALSERCAMERA_EXPORTS
#define BALSERCAMERA_DLLAPI __declspec(dllexport)
#else
#define BALSERCAMERA_DLLAPI __declspec(dllimport)
#endif

#include "CSIItemStruct.h"
/**********************************************************
获取相机运行事件回调函数
EventID,相机状态改变事件ID
ucStatus,相机当前状态，按位操作
HGFEDCBA     
A-> 1-相机打开(ceOpen) 0-相机关闭(ceClose)
B-> 1-采集线程启动(ceStart) 0-采集线程关闭(ceStop)
C-> 1-采集暂停(cePause) 0-采集正常
D-> 1-正在采集(ceGrabbing) 0-未采集，空闲(ceIdle)
EFGH保留，全0
**********************************************************/
typedef struct BALSERCAMERA_DLLAPI tagBLGrabStatus
{
	bool bIsOpen;
	bool bIsStart;
	bool bIsPause;
	bool bIsGrabbing;
}BLGrabStatus;

//获取相机数据回调函数
typedef LRESULT(__cdecl *BalserFunOnGetImage)(ImageUnitBase *PtrImageInfo, int CameraID, void* param);

//相机采集的相关事宜
typedef LRESULT (__cdecl *BalserFunOnCameraEvent)(CameraEvent EventID, void* param);

class BALSERCAMERA_DLLAPI CBalserGrabBase
{
public:
	//相机采集初始化
	CBalserGrabBase();
	virtual ~CBalserGrabBase();

	/**********************************************************
	* 设置相机图像数据获取的回调函数，用于多个相机情况下异步取数
	* pDHFunOnGetImage 相机获取图像回调函数
	* param            回调函数参数
    * 返回值 TRUE-成功 FALSE-失败
    ************************************************************/
	void SetCallBackBalserGetImageFun(BalserFunOnGetImage PtrBalserFunOnGetImage, void* param);

	/*********************************************************
	* 设置相机运行触发事件回调函数
	* pDHFunOnCameraEvent   相机事件回调函数
	* param                 回调函数参数
	***********************************************************/
	void SetCallBackBalserCameraEventFun(BalserFunOnCameraEvent PtrBalserFunOnCameraEvent,void* param);
	
	/*********************************************************
	* 暂停采集
	* bPause TRUE-暂停 FALSE-继续
    ***********************************************************/
	void BalserPauseGrab(bool bPause);

	/**********************************************************
	* 读取是否暂停采集标志
	* 返回值 TRUE-暂停 FALSE-继续
	***********************************************************/
	bool IsBalserPauseGrab();

	/**********************************************************
	* 返回相机是否连接正常 
	* 返回值 TRUE-运行 FALSE-未运行
	**********************************************************/
	bool IsBalserConnected();

	bool IsBalserGrabbing();

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
	virtual bool BalserOpenCamera() = 0;
	
	/**********************************************
	* 关闭相机连接
    *返回值 TRUE-成功 FALSE-失败,派生类成功后需调用基类该函数
	************************************************/
	virtual bool BalserCloseCamera() = 0;

	/*********************************************
	* 启动采集线程开始进行连续采集
	* sOption 采集选项，见类CGrabOption介绍
    *返回值 TRUE-成功，启动采集线程，按照sOption设置条件进行采集 FALSE-失败
	********************************************/
	virtual bool BalserStartGrab() = 0;
	
	/**********************************************
	* 停止图像采集线程
	* 返回值 TRUE-成功 FALSE-失败
	***********************************************/
	virtual bool BalserStopGrab() = 0;
	
	/***************************************************
	* 相机采集数据，用于同步采集，一次采集一张图片
	* pBuffer-out，数据内存指针，用于存放返回的数据
	* dwBufferSize-inout，内存大小，防止溢出,返回实际数据大小
	* pImageInfo-out,采集到的图像信息
    * 返回值 0-成功，其余值失败, 10-重新连接相机
	***************************************************/
	virtual bool BalserGrabImage() = 0;

	virtual bool BalserGrabLine() = 0;

public:
	//数据接收回调函数
	BalserFunOnGetImage m_PtrBalserFunOnGetImage;
	void*               m_PtrBalserFunOnGetImageParam;
	//获取相机运行事件回调函数
	BalserFunOnCameraEvent m_PtrBalserFunOnCameraEvent;
	void*                  m_PtrBalserFunOnCameraEventParam;
	
	//修改相机状态，子类可调用此函数改变状态
	void BalserCameraChangeEvent(CameraEvent CamEvent);

	//相机参数指针---相机采集参数
	CameraGrabPara* m_PtrCameraPara;
	//图像信息指针---图像信息参数
	ImageUnitBase*  m_PtrImageUnit;

public:
	//暂停采集标志
	bool    m_bBalserPauseGrab;

	//相机连接正常标志
	bool    m_bBalserConnected;

	bool    m_bBalserGrabbing;
	bool    m_IsNormCameraStatus;
};


#endif  //_BALSERCAMERA_LIB_H_