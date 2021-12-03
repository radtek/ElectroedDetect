#ifndef _BALSERCAMLIB_LIB_H_
#define _BALSERCAMLIB_LIB_H_

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigECamera.h>

#include <BalserCamLib/BalserCamera.h>

typedef Pylon::CBaslerGigECamera Camera_t;

#define CAM_BALSER_BUF_NUM    32

//相机之间用于同步
struct BALSERCAMERA_DLLAPI BalserSyncSignal
{
	BalserSyncSignal()
	{
		//构造函数中创建事件变量
		hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

		bStart = false;   bSetEvent = false;
	}

	~BalserSyncSignal()
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

class BALSERCAMERA_DLLAPI CBalserCameraGrab : public CBalserGrabBase
{
public:
	CBalserCameraGrab();
	virtual ~CBalserCameraGrab();

	virtual bool BalserOpenCamera();
	virtual bool BalserCloseCamera();

	//原始逻辑
	virtual bool BalserStartGrab();
	virtual bool BalserStopGrab();

	virtual bool BalserGrabImage();

	virtual bool BalserGrabLine();

public:
	bool IsBalserGigeConnect();

	//设置触发方式
	bool setLineTriggerConf();
	//设置曝光时间
	bool setExposureTimeConf();
	//设置采集翻转
	bool setReverseConf();
	//设置图像AOI区域
	bool setImageAOIConf();

	//设置采集数据的图像格式
	bool setPixelFormatConf();

	//设置相机的采集帧率
	bool setAcquistionFrameRate();

	//设置相机的白平衡
	bool setPixelBalanceConf();

	//设置软触发信号
	//bool m_IsSoftTrigger;
	bool setTriggerSoftware();

	bool getCameraSerialNumber(char* SerialNumber);

	bool GetCameraNormStatus();

public:
	BalserSyncSignal m_SyncSignal;//各通道同步信号
	BalserSyncSignal m_TriggerSyncSignal;

	//统计信息
	DWORD m_nTriggerCount;    //触发信号总数
	DWORD m_nFailedImageNum;  //采集失败总数
	DWORD m_nGrabImageNum;    //采集成功总数

public:     //Dalsa相机的全局采集设备
	void *m_PtrBalserTLayer;
	void *m_PtrBalserCamera;

	Camera_t::StreamGrabber_t *m_PtrBalserStream;
	BYTE* m_PtrImageData[CAM_BALSER_BUF_NUM];
};

#endif  //_BALSERCAMLIB_LIB_H_