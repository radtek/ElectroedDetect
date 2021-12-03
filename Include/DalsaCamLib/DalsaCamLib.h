#ifndef _DALSACAMLIB_LIB_H_
#define _DALSACAMLIB_LIB_H_

#include <DalsaCamLib/DalsaCamera.h>

#include "SapClassBasic.h"

#define CAM_BUF_NUM    12

//相机之间用于同步
struct DALSACAMERA_DLLAPI CameraSyncSignal
{
	CameraSyncSignal()
	{
		//构造函数中创建事件变量
		hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

		bStart = false;   bSetEvent = false;
	}

	~CameraSyncSignal()
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


class DALSACAMERA_DLLAPI CDalseCameraGrab : public CCameraGrabBase
{
public:
	CDalseCameraGrab();
	virtual ~CDalseCameraGrab();

	void InitImageBuffer();

	virtual bool DalsaOpenCamera();
	virtual bool DalsaCloseCamera();

	//原始逻辑
	virtual bool DalsaStartGrab();
	virtual bool DalsaStopGrab();

	virtual bool DalsaGrabImage();

public:
	//设置触发方式
	bool setLineTriggerConf();
	//设置曝光时间
	bool setExposureTimeConf();
	//设置采集翻转
	bool setReverseXConf();

	//设置图像灰度是否翻转
	bool setNegativeImageConf();
	//设置图像AOI区域
	bool setImageAOIConf();

	//设置采集数据的图像格式
	bool setPixelFormatConf();

	//设置相机的采集帧率
	bool setAcquistionFrameRate();

	//设置相机的白平衡
	//bool setPixelBalanceConf();

	bool setTriggerSoftware();

	bool getCameraSerialNumber(char* SerialNumber);

public:
	CameraSyncSignal m_SyncSignal;//各通道同步信号
	CameraSyncSignal m_TriggerSyncSignal;

	//统计信息
	DWORD m_nTriggerCount;  //触发信号总数
	DWORD m_nFailedImageNum;//采集失败总数
	DWORD m_nGrabImageNum;  //采集成功总数

	DWORD m_nGrabLineImageNum;//采集线扫图像数目

	int   m_nCurrLineIndex;   //当前线条序号

public:     //Dalsa相机的全局采集设备
	SapLocation*     m_SapLocation;
	SapAcqDevice*    m_SapAcqDevice;
	SapBuffer*       m_SapBuffers;
	SapTransfer*     m_SapTransfer;
};

#endif  //_DAHUACAMLIB_LIB_H_