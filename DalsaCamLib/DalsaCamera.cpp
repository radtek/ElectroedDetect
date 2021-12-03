#pragma once
#include <DalsaCamLib/DalsaCamera.h>

CCameraGrabBase::CCameraGrabBase()
{
	m_pImageUnit = new ImageUnitBase();
	m_pCameraPara = new CameraGrabPara();

	m_bDalsaPauseGrab = false;
	m_bDalsaConnected = false;

	m_bDalsaGrabbing = false;

	//采集图像相关参数
	m_pDalsaFunOnGetImage = NULL;
	m_pDalsaFunOnGetImageParam = NULL;

	//相机更新相关参数
	m_pDalsaFunOnCameraEvent = NULL;
	m_pDalsaFunOnCameraEventParam = NULL;

	//图像保存相关函数
	m_pDalsaFunBeforeSaveImage = NULL;
	m_pDalsaFunBeforeSaveImageParam = NULL;
}

CCameraGrabBase::~CCameraGrabBase()
{
	delete m_pImageUnit;
	m_pImageUnit = NULL;

	delete m_pCameraPara;
	m_pCameraPara = NULL;
}

void CCameraGrabBase::SetCallBackGetImageFun(DalsaFunOnGetImage pDalsaFunOnGetImage, void* param)
{
	m_pDalsaFunOnGetImage = pDalsaFunOnGetImage;
	m_pDalsaFunOnGetImageParam = param;
}

void CCameraGrabBase::SetCallBackBeforeSaveImageFun(DalsaFunBeforeSaveImage pDalsaFunBeforeSaveImage, void* param)
{
	m_pDalsaFunBeforeSaveImage = pDalsaFunBeforeSaveImage;
	m_pDalsaFunBeforeSaveImageParam = param;
}

void CCameraGrabBase::SetCallBackCameraEventFun(DalsaFunOnCameraEvent pDalsaFunOnCameraEvent, void* param)
{
	m_pDalsaFunOnCameraEvent = pDalsaFunOnCameraEvent;
	m_pDalsaFunOnCameraEventParam = param;
}

bool CCameraGrabBase::DalsaOpenCamera()
{
	m_bDalsaConnected = true;

	DalsaCameraChangeEvent(ceOpen);

	return true;
}

bool CCameraGrabBase::DalsaCloseCamera()
{
	m_bDalsaConnected = false;

	DalsaCameraChangeEvent(ceClose);

	return true;
}

bool CCameraGrabBase::DalsaStartGrab()
{
	m_bDalsaGrabbing = true;

	DalsaCameraChangeEvent(ceStart);

	return true;
}

bool CCameraGrabBase::DalsaStopGrab()
{
	DalsaCameraChangeEvent(ceStop);
	DalsaCameraChangeEvent(ceIdle);

	m_bDalsaGrabbing = false;

	return true;
}

void CCameraGrabBase::DalsaPauseGrab(bool bPause)
{
	m_bDalsaPauseGrab = bPause;

	if (bPause)
		DalsaCameraChangeEvent(cePause);
	else
		DalsaCameraChangeEvent(ceNoPause);
}

bool CCameraGrabBase::IsDalsaPauseGrab()
{
	return m_bDalsaPauseGrab;
}

bool CCameraGrabBase::IsDalsaConnected()
{
	return m_bDalsaConnected;
}

bool CCameraGrabBase::IsDalsaGrabbing()
{
	return m_bDalsaGrabbing;
}

void CCameraGrabBase::DalsaCameraChangeEvent(CameraEvent CamEvent)
{
	DHGrabStatus GrabStatus;

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

	if (m_pDalsaFunOnCameraEvent != NULL)
		m_pDalsaFunOnCameraEvent(CamEvent, m_pDalsaFunOnCameraEventParam);
}

bool CCameraGrabBase::GetImageInfo(ImageUnitBase* pImageInfo)
{
	(*pImageInfo) = *m_pImageUnit;

	return true;
}

bool CCameraGrabBase::SetImageInfo(const ImageUnitBase* pImageInfo)
{
	(*m_pImageUnit) = *pImageInfo;

	return true;
}