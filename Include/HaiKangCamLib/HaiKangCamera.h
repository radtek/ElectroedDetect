#ifndef _HAIKANGCAMERA_LIB_H_
#define _HAIKANGCAMERA_LIB_H_

#ifdef HAIKANGCAMERA_EXPORTS
#define HAIKANGCAMERA_DLLAPI __declspec(dllexport)
#else
#define HAIKANGCAMERA_DLLAPI __declspec(dllimport)
#endif

#include "CameraPara.h"

#include <string>
#include <malloc.h>
#include <string.h>
#include <vector>
#include <atltime.h>
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <iostream>

//#include "Public.h"

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
typedef struct HAIKANGCAMERA_DLLAPI tagHKGrabStatus
{
	bool bIsOpen;
	bool bIsStart;
	bool bIsPause;
	bool bIsGrabbing;
}HKGrabStatus;

//获取相机数据回调函数
typedef LRESULT(__cdecl *HaiKangFunOnGetImage)(ImageUnitBase *PtrImageInfo, int CameraID, void* param);

//相机采集的相关事宜
typedef LRESULT(__cdecl *HaiKangFunOnCameraEvent)(CameraEvent EventID, void* param);

class HAIKANGCAMERA_DLLAPI CHaiKangGrabBase
{
public:
	//相机采集初始化
	CHaiKangGrabBase();
	virtual ~CHaiKangGrabBase();

	/**********************************************************
	* 设置相机图像数据获取的回调函数，用于多个相机情况下异步取数
	* pDHFunOnGetImage 相机获取图像回调函数
	* param            回调函数参数
    * 返回值 TRUE-成功 FALSE-失败
    ************************************************************/
	void SetCallBackHaiKangGetImageFun(HaiKangFunOnGetImage PtrHaiKangFunOnGetImage, void* param);

	/*********************************************************
	* 设置相机运行触发事件回调函数
	* pDHFunOnCameraEvent   相机事件回调函数
	* param                 回调函数参数
	***********************************************************/
	void SetCallBackHaiKangCameraEventFun(HaiKangFunOnCameraEvent PtrHaiKangFunOnCameraEvent, void* param);
	
	/*********************************************************
	* 暂停采集
	* bPause TRUE-暂停 FALSE-继续
    ***********************************************************/
	void HaiKangPauseGrab(bool bPause);

	/**********************************************************
	* 读取是否暂停采集标志
	* 返回值 TRUE-暂停 FALSE-继续
	***********************************************************/
	bool IsHaiKangPauseGrab();

	/**********************************************************
	* 返回相机是否连接正常 
	* 返回值 TRUE-运行 FALSE-未运行
	**********************************************************/
	bool IsHaiKangConnected();

	bool IsHaiKangGrabbing();

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
	virtual bool HaiKangOpenCamera() = 0;
	
	/**********************************************
	* 关闭相机连接
    *返回值 TRUE-成功 FALSE-失败,派生类成功后需调用基类该函数
	************************************************/
	virtual bool HaiKangCloseCamera() = 0;

	/*********************************************
	* 启动采集线程开始进行连续采集
	* sOption 采集选项，见类CGrabOption介绍
    *返回值 TRUE-成功，启动采集线程，按照sOption设置条件进行采集 FALSE-失败
	********************************************/
	virtual bool HaiKangStartGrab() = 0;
	
	/**********************************************
	* 停止图像采集线程
	* 返回值 TRUE-成功 FALSE-失败
	***********************************************/
	virtual bool HaiKangStopGrab() = 0;
	
	/***************************************************
	* 相机采集数据，用于同步采集，一次采集一张图片
	* pBuffer-out，数据内存指针，用于存放返回的数据
	* dwBufferSize-inout，内存大小，防止溢出,返回实际数据大小
	* pImageInfo-out,采集到的图像信息
    * 返回值 0-成功，其余值失败, 10-重新连接相机
	***************************************************/
	virtual bool HaiKangGrabImage() = 0;

	virtual bool HaiKangGrabLine() = 0;

public:
	//数据接收回调函数
	HaiKangFunOnGetImage m_PtrHaiKangFunOnGetImage;
	void*                m_PtrHaiKangFunOnGetImageParam;
	//获取相机运行事件回调函数
	HaiKangFunOnCameraEvent m_PtrHaiKangFunOnCameraEvent;
	void*                   m_PtrHaiKangFunOnCameraEventParam;
	
	//修改相机状态，子类可调用此函数改变状态
	void HaiKangCameraChangeEvent(CameraEvent CamEvent);

	//相机参数指针---相机采集参数
	CameraGrabPara* m_PtrCameraPara;
	//图像信息指针---图像信息参数
	ImageUnitBase*  m_PtrImageUnit;

public:
	//暂停采集标志
	bool    m_bHaiKangPauseGrab;

	//相机连接正常标志
	bool    m_bHaiKangConnected;

	bool    m_bHaiKangGrabbing;

	bool    m_IsNormCameraStatus;
};


#endif  //_HAIKANGCAMERA_LIB_H_