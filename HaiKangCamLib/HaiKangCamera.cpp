#include <HaiKangCamLib/HaiKangCamera.h>

CHaiKangGrabBase::CHaiKangGrabBase()
{
	m_PtrImageUnit = new ImageUnitBase();
	m_PtrCameraPara = new CameraGrabPara();

	m_bHaiKangPauseGrab = false;
	m_bHaiKangConnected = false;

	m_bHaiKangGrabbing = false;

	//采集图像相关参数
	m_PtrHaiKangFunOnGetImage = NULL;
	m_PtrHaiKangFunOnGetImageParam = NULL;

	//相机更新相关参数
	m_PtrHaiKangFunOnCameraEvent = NULL;
	m_PtrHaiKangFunOnCameraEventParam = NULL;
}

CHaiKangGrabBase::~CHaiKangGrabBase()
{
	delete m_PtrImageUnit;
	m_PtrImageUnit = NULL;

	delete m_PtrCameraPara;
	m_PtrCameraPara = NULL;
}

void CHaiKangGrabBase::SetCallBackHaiKangGetImageFun(HaiKangFunOnGetImage PtrHaiKangFunOnGetImage, void* param)
{
	m_PtrHaiKangFunOnGetImage = PtrHaiKangFunOnGetImage;		// 获取图片的回调函数
	m_PtrHaiKangFunOnGetImageParam = param;						// 父窗口
}

void CHaiKangGrabBase::SetCallBackHaiKangCameraEventFun(HaiKangFunOnCameraEvent PtrHaiKangFunOnCameraEvent, void* param)
{
	m_PtrHaiKangFunOnCameraEvent = PtrHaiKangFunOnCameraEvent;
	m_PtrHaiKangFunOnCameraEventParam = param;
}

bool CHaiKangGrabBase::HaiKangOpenCamera()
{
	m_bHaiKangConnected = true;

	HaiKangCameraChangeEvent(ceOpen);

	return true;
}

bool CHaiKangGrabBase::HaiKangCloseCamera()
{
	m_bHaiKangConnected = false;

	HaiKangCameraChangeEvent(ceClose);

	return true;
}

bool CHaiKangGrabBase::HaiKangStartGrab()
{
	//m_bBalserGrabbing = true;

	HaiKangCameraChangeEvent(ceStart);

	return true;
}

bool CHaiKangGrabBase::HaiKangStopGrab()
{
	HaiKangCameraChangeEvent(ceStop);
	HaiKangCameraChangeEvent(ceIdle);

	m_bHaiKangGrabbing = false;

	return true;
}

void CHaiKangGrabBase::HaiKangPauseGrab(bool bPause)
{
	m_bHaiKangPauseGrab = bPause;

	if (bPause)
		HaiKangCameraChangeEvent(cePause);
	else
		HaiKangCameraChangeEvent(ceNoPause);
}

bool CHaiKangGrabBase::IsHaiKangPauseGrab()
{
	return m_bHaiKangPauseGrab;
}

bool CHaiKangGrabBase::IsHaiKangConnected()
{
	return m_bHaiKangConnected;
}

bool CHaiKangGrabBase::IsHaiKangGrabbing()
{
	return m_bHaiKangGrabbing;
}

void CHaiKangGrabBase::HaiKangCameraChangeEvent(CameraEvent CamEvent)
{
	HKGrabStatus GrabStatus;

	unsigned char ucStatus = 0;

	BYTE ucBit = 255;
	BYTE ucValue = 0;
	switch (CamEvent)
	{
	case ceOpen:
		ucBit = 254;
		ucValue = 1;
		GrabStatus.bIsOpen = true;
		break;
	case ceClose:
		ucBit = 254;
		GrabStatus.bIsOpen = false;
		break;
	case ceStart:
		ucBit = 253;
		ucValue = 2;
		GrabStatus.bIsStart = true;
		break;
	case ceStop:
		ucBit = 253;
		GrabStatus.bIsStart = false;
		break;
	case ceGrabbing:
		ucBit = 251;
		ucValue = 4;
		GrabStatus.bIsGrabbing = true;
		break;
	case ceIdle:
		ucBit = 251;
		GrabStatus.bIsGrabbing = false;
		break;
	case cePause:
		ucBit = 247;
		ucValue = 8;
		GrabStatus.bIsPause = true;
		break;
	case ceNoPause:
		ucBit = 247;
		GrabStatus.bIsPause = false;
		break;
	}

	ucStatus &= ucBit;
	ucStatus += ucValue;

	if (CamEvent == ceOpen) //设置为ceStop 和ceIdle
	{
		ucBit = 253;
		ucStatus &= ucBit;
		ucBit = 251;
		ucStatus &= ucBit;
		GrabStatus.bIsStart = false;
		GrabStatus.bIsGrabbing = false;
	}
	else if (CamEvent == ceStop) //设置为ceIdle
	{
		ucBit = 251;
		ucStatus &= ucBit;
		GrabStatus.bIsGrabbing = false;
	}

	if (m_PtrHaiKangFunOnCameraEvent != NULL)
		m_PtrHaiKangFunOnCameraEvent(CamEvent, m_PtrHaiKangFunOnCameraEventParam);
}

bool CHaiKangGrabBase::GetImageInfo(ImageUnitBase *PtrImageInfo)
{
	(*PtrImageInfo) = *m_PtrImageUnit;

	return true;
}

bool CHaiKangGrabBase::SetImageInfo(const ImageUnitBase *PtrImageInfo)
{
	(*m_PtrImageUnit) = *PtrImageInfo;

	return true;
}