#ifndef _HAIKANGCAMLIB_LIB_H_
#define _HAIKANGCAMLIB_LIB_H_

#include <HaiKangCamLib/HaiKangCamera.h>

//typedef Pylon::CBaslerGigECamera Camera_t;

#define CAM_HAIKANG_BUF_NUM    32

//相机之间用于同步
struct HAIKANGCAMERA_DLLAPI HaiKangSyncSignal
{
	HaiKangSyncSignal()
	{
		//构造函数中创建事件变量
		hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

		bStart = false;   bSetEvent = false;
	}

	~HaiKangSyncSignal()
	{
		//关闭信号量
		CloseHandle(hEvent);

		bStart = FALSE;
	}

	//同步完成，开始采集
	void Start()
	{
		//把指定事件对象的状态设置为不发信号状态
		ResetEvent(hEvent);

		bStart=true;
		bSetEvent=true;
	}

	//停止采集时调用
	void Stop()
	{
		bStart=false;
		bSetEvent=false;
	}

	//初始化完成，触发完成信号
	BOOL Singnal()
	{
		//把指定事件对象的状态设置为发信号状态
		return SetEvent(hEvent);
	}

	bool IsSetEvent()
	{
		return bSetEvent;
	}

	HANDLE hEvent;
	bool   bStart;

private:
	bool bSetEvent;//用于屏蔽多次触发信号
};

class HAIKANGCAMERA_DLLAPI CHaiKangCameraGrab : public CHaiKangGrabBase
{
public:
	CHaiKangCameraGrab();
	virtual ~CHaiKangCameraGrab();

	virtual bool HaiKangOpenCamera();
	virtual bool HaiKangCloseCamera();

	//原始逻辑
	virtual bool HaiKangStartGrab();
	virtual bool HaiKangStopGrab();

	virtual bool HaiKangGrabImage();

	virtual bool HaiKangGrabLine();

public:
	//设置触发方式
	bool SetLineTriggerConf();
	//设置曝光时间
	bool SetExposureTimeConf();
	bool SetGainConf();

	bool IncreaseExpourseTime();
	bool SetFrameRate();
	//设置采集翻转
	bool SetReverseConf();
	//设置图像AOI区域
	bool SetImageAOIConf();

	//设置采集数据的图像格式
	bool SetPixelFormatConf();

	//设置软触发信号
	//bool m_IsSoftTrigger;
	bool SetTriggerSoftware();
	bool GetExposureTimeConf();

	bool GetCameraSerialNumber(char* SerialNumber);

	bool GetCameraNormStatus();

	int GetCameraImg();			// 软触发函数
public:
	HaiKangSyncSignal m_SyncSignal;//各通道同步信号
	HaiKangSyncSignal m_TriggerSyncSignal;

	//统计信息
	DWORD m_nTriggerCount;    //触发信号总数
	DWORD m_nFailedImageNum;  //采集失败总数
	DWORD m_nGrabImageNum;    //采集成功总数

public:     //Dalsa相机的全局采集设备
	//void *m_PtrHaiKangTLayer;
	//void *m_PtrHaiKangCamera;

	void* m_PtrDeviceHandle;   //相机句柄

	//Camera_t::StreamGrabber_t *m_PtrBalserStream;
	//BYTE* m_PtrImageData[CAM_HAIKANG_BUF_NUM];
};

#endif  //_HAIKANGCAMLIB_LIB_H_