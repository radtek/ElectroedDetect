#pragma once
#include <LogFile/LogFile.h>
#include <DalsaCamLib/DalsaCamLib.h>

CLogFile  m_LogFile;

//统计信息
//DWORD m_gTriggerCount;  //触发信号总数
//DWORD m_gFailedImageNum;//采集失败总数
//DWORD m_gGrabImageNum;  //采集成功总数

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 CDHCameraGrab.h
CDalseCameraGrab::CDalseCameraGrab()
{
	m_nTriggerCount = 0;
	m_nGrabImageNum = 0;
	m_nFailedImageNum = 0;

	m_nGrabLineImageNum = 0;  m_nCurrLineIndex = 0;
}

void CDalseCameraGrab::InitImageBuffer()
{
	if (m_pCameraPara->m_uLineHeight > 0)   //LineHeight  大于0   表示针对线扫相机
	{
		int iPixelSize = 0, dwImageLen = 0;

		if (m_pCameraPara->m_uImageChannel == 3)
			iPixelSize = 2;
		else
			iPixelSize = 1;

		dwImageLen = m_pCameraPara->m_uImageWidth * m_pCameraPara->m_uImageHeight * iPixelSize;

		m_pImageUnit->m_dwHeight = m_pCameraPara->m_uImageHeight;
		m_pImageUnit->m_dwWidth = m_pCameraPara->m_uImageWidth;
		m_pImageUnit->m_dwImageFormat = m_pCameraPara->m_uImageChannel;

		m_pImageUnit->m_dwImageDataLen = dwImageLen;

		m_pImageUnit->m_dwImageData = (unsigned char*)malloc(dwImageLen * sizeof(unsigned char));
		memset(m_pImageUnit->m_dwImageData, 0, dwImageLen * sizeof(unsigned char));
	}
}

CDalseCameraGrab::~CDalseCameraGrab()
{
	if (m_pCameraPara->m_uLineHeight > 0)   //LineHeight  大于0   表示针对线扫相机
	{
		free(m_pImageUnit->m_dwImageData);
		m_pImageUnit->m_dwImageData = NULL;
	}
}


bool CDalseCameraGrab::setLineTriggerConf()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//设置信号触发源  Software  为软触发
	if (m_pCameraPara->m_iTriggerMode == 0)   //外部触发
	{
		//判断当前变量是否有效ei
		IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerSelector", &IsAvaiablePara);

		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("TriggerSelector", "LineStart"/*"FrameStart"*/))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger source fail.\n");

				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger source fail.\n");

			return false;
		}

		//判断当前变量是否有效
		IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerMode", &IsAvaiablePara);

		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("TriggerMode", "On"))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger mode fail.\n");

				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger mode fail.\n");

			return false;
		}

		//判断当前变量是否有效
		IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerSource", &IsAvaiablePara);

		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("TriggerSource", "rotaryEncoder1"/*"Line1"*/))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger source fail.\n");

				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger source fail.\n");

			return false;
		}

		//IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerOverlap",&IsAvaiablePara);

		//if (IsAvaiablePara && IsAvaiableResult)
		//{
		//	if(!m_SapAcqDevice->SetFeatureValue("TriggerOverlap", "previousLine"))
		//	{
		//		m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger overlap fail.\n");
		//		return false;
		//	}
		//}
		//else
		//{
		//	m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger activation fail.\n");
		//	return false;
		//}
		//判断当前变量是否有效
		//IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerActivation",&IsAvaiablePara);

		//if (IsAvaiablePara && IsAvaiableResult)
		//{
		//	if(!m_SapAcqDevice->SetFeatureValue("TriggerActivation", "RisingEdge"))
		//	{
		//		m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger activation fail.\n");
		//		return false;
		//	}
		//}
		//else
		//{
		//	m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger activation fail.\n");
		//	return false;
		//}
	}
	else
	{
		//判断当前变量是否有效
		IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerSelector", &IsAvaiablePara);

		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("TriggerSelector", "FrameStart"))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger source fail.\n");

				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger source fail.\n");

			return false;
		}

		//判断当前变量是否有效
		IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("TriggerMode", &IsAvaiablePara);

		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("TriggerMode", "Off"))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger mode fail.\n");

				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "set trigger mode fail.\n");

			return false;
		}
	}

	return true;
}

//设置相机的采集帧率
bool CDalseCameraGrab::setAcquistionFrameRate()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("AcquisitionLineRate", &IsAvaiablePara);

	if (IsAvaiablePara && IsAvaiableResult)
	{
		if (!m_SapAcqDevice->SetFeatureValue("AcquisitionLineRate", (double)m_pCameraPara->m_iFrameRate))
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "AcquisitionLineRate  getMaxVal fail.\n");
			return false;
		}
	}
	else
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "AcquisitionLineRate  getMaxVal fail.\n");
		return false;
	}

	return true;
}

//设置曝光时间
bool CDalseCameraGrab::setExposureTimeConf()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("ExposureTime", &IsAvaiablePara);

	if (IsAvaiablePara && IsAvaiableResult)
	{
		if (!m_SapAcqDevice->SetFeatureValue("ExposureTime", (double)m_pCameraPara->m_uExposureTime))
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "ExposureTime  getMaxVal fail.\n");
			return false;
		}
	}
	else
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "ExposureTime  getMaxVal fail.\n");
		return false;
	}

	return true;
}

bool CDalseCameraGrab::setReverseXConf()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("ReverseX", &IsAvaiablePara);

	//写入相关翻转参数
	if (m_pCameraPara->m_bReverseX == 0)
	{
		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("ReverseX", FALSE))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "reverseX  setValue fail.\n");
				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "reverseX  setValue fail.\n");
			return false;
		}
	}
	else
	{
		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("ReverseX", TRUE))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "reverseX  setValue fail.\n");
				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "reverseX  setValue fail.\n");
			return false;
		}
	}

	return true;
}

bool CDalseCameraGrab::setNegativeImageConf()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("NegativeImage", &IsAvaiablePara);

	//写入相关翻转参数
	if (m_pCameraPara->m_bReverseY == 0)
	{
		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("NegativeImage", FALSE))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "NegativeImage  setValue fail.\n");
				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "NegativeImage  setValue fail.\n");
			return false;
		}
	}
	else
	{
		if (IsAvaiablePara && IsAvaiableResult)
		{
			if (!m_SapAcqDevice->SetFeatureValue("NegativeImage", TRUE))
			{
				m_LogFile.LogFormat(NULL, LOG_INFO, "NegativeImage  setValue fail.\n");
				return false;
			}
		}
		else
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "NegativeImage  setValue fail.\n");
			return false;
		}
	}

	return true;
}

bool CDalseCameraGrab::setImageAOIConf()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("Width", &IsAvaiablePara);

	if (IsAvaiablePara && IsAvaiableResult)
	{
		if (!m_SapAcqDevice->SetFeatureValue("Width", m_pCameraPara->m_uImageWidth))
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "Width setValue fail.\n");
			return false;
		}
	}
	else
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "Width setValue fail.\n");
		return false;
	}

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("OffsetX", &IsAvaiablePara);

	if (IsAvaiablePara && IsAvaiableResult)
	{
		if (!m_SapAcqDevice->SetFeatureValue("OffsetX", m_pCameraPara->m_uXOffset))
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "Width setValue fail.\n");
			return false;
		}
	}
	else
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "Width setValue fail.\n");
		return false;
	}

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("Height", &IsAvaiablePara);

	if (IsAvaiablePara && IsAvaiableResult)
	{
		if (!m_SapAcqDevice->SetFeatureValue("Height", m_pCameraPara->m_uLineHeight))
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "Height setValue fail.\n");
			return false;
		}
	}
	else
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "Height setValue fail.\n");
		return false;
	}

	return true;
}

bool CDalseCameraGrab::setPixelFormatConf()
{
	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("PixelFormat", &IsAvaiablePara);

	if (IsAvaiablePara && IsAvaiableResult)
	{
		if (!m_SapAcqDevice->SetFeatureValue("PixelFormat", "Mono8"))
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "PixelFormat setValue fail.\n");

			return false;
		}
	}
	else
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "PixelFormat setValue fail.\n");

		return false;
	}

	return true;
}

void SapTransferCallback(SapXferCallbackInfo* pInfo)
{
	CDalseCameraGrab* ptrGrabCamera = (CDalseCameraGrab*)pInfo->GetContext();

	if (ptrGrabCamera->m_pDalsaFunOnGetImage != NULL)
	{
		//m_gGrabImageNum++;

		//m_gTriggerCount = m_gGrabImageNum + m_gFailedImageNum;

		int iPixelSize = 0, dwImageLen = 0;
		if (ptrGrabCamera->m_pCameraPara->m_uImageChannel == 3)
			iPixelSize = 2;
		else
			iPixelSize = 1;

		unsigned char* TempGrabData = NULL, * ResultGrabData = NULL;

		//当前图像序号
		if (ptrGrabCamera->m_nCurrLineIndex < ptrGrabCamera->m_pCameraPara->m_uImageHeight)
		{
			dwImageLen = ptrGrabCamera->m_nCurrLineIndex * ptrGrabCamera->m_pImageUnit->m_dwWidth * iPixelSize;
			TempGrabData = ptrGrabCamera->m_pImageUnit->m_dwImageData + dwImageLen * sizeof(unsigned char);

			//ResultGrabData = (unsigned char *)pFrame.getImage();

			ptrGrabCamera->m_SapBuffers->GetAddress((void**)&ResultGrabData);

			dwImageLen = ptrGrabCamera->m_pCameraPara->m_uLineHeight * ptrGrabCamera->m_pImageUnit->m_dwWidth * iPixelSize;
			memcpy(TempGrabData, ResultGrabData, dwImageLen * sizeof(unsigned char));

			ptrGrabCamera->m_nCurrLineIndex += ptrGrabCamera->m_pCameraPara->m_uLineHeight;
		}

		//当图像行数满足图像要求
		if (ptrGrabCamera->m_nCurrLineIndex >= ptrGrabCamera->m_pCameraPara->m_uImageHeight)
		{
			ptrGrabCamera->m_nCurrLineIndex = 0;
			ptrGrabCamera->m_nGrabLineImageNum++;

			//ptrGrabCamera->m_nFailedImageNum = m_gFailedImageNum;  
			ptrGrabCamera->m_nGrabImageNum++;// = m_gGrabImageNum;  
			ptrGrabCamera->m_nTriggerCount = ptrGrabCamera->m_nFailedImageNum + ptrGrabCamera->m_nGrabImageNum;

			ptrGrabCamera->m_pImageUnit->m_dwHeight = ptrGrabCamera->m_pCameraPara->m_uImageHeight;
			ptrGrabCamera->m_pImageUnit->m_dwWidth = ptrGrabCamera->m_pCameraPara->m_uImageWidth;

			dwImageLen = ptrGrabCamera->m_pCameraPara->m_uImageHeight * ptrGrabCamera->m_pImageUnit->m_dwWidth * iPixelSize;
			ptrGrabCamera->m_pImageUnit->m_dwImageDataLen = dwImageLen;

			if (ptrGrabCamera->m_pCameraPara->m_iPixelFormat == 1)
				ptrGrabCamera->m_pImageUnit->m_dwImageFormat = 1;
			else
				ptrGrabCamera->m_pImageUnit->m_dwImageFormat = 3;

			//函数指针为数据指针
			ptrGrabCamera->m_pDalsaFunOnGetImage(ptrGrabCamera->m_pImageUnit,
				ptrGrabCamera->m_pCameraPara->m_iCamID,
				ptrGrabCamera->m_pDalsaFunOnGetImageParam);
		}
	}

	ptrGrabCamera->DalsaCameraChangeEvent(ceGrabbing);

	return; //true;
}

bool CDalseCameraGrab::DalsaOpenCamera()
{
	bool IsFindCarema = false;

	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	char SerialNumber[64] = { '\0' }, ServerName[256] = { '\0' }, CameraName[256] = { '\0' };

	int  SerialNameIndex = 0, CameraNameIndex = 0;

	/**************************************************
			设备搜索---确定相机对象指针
	***************************************************/
	SapManager::Open();   //Manager  管理Open

	//代表显卡数目
	int iServerCount = SapManager::GetServerCount();

	SapManager::SetDisplayStatusMode(SapManager::StatusLog);

	if (iServerCount == 0)
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "No device found!\n");

		return FALSE;
	}

	SapManager::DetectAllServers(SapManager::DetectServerAll);

	SapLocation* TempLocation = NULL;	SapAcqDevice* TempAcqDevice = NULL;

	for (int iDeviceIndex = 0; iDeviceIndex < iServerCount; iDeviceIndex++)
	{
		// when m_serverCategory is ServerAcqDevice, 
		//show only servers that have only one resource that is an acqdevice and no acq
		int iAcqDeviceNum = SapManager::GetResourceCount(iDeviceIndex, SapManager::ResourceAcqDevice);
		//int iAcqNum       =  SapManager::GetResourceCount(iDeviceIndex, SapManager::ResourceAcq);

		if (iAcqDeviceNum == 0)// && iAcqNum == 0)
			continue;

		//获取网卡名称
		if (!SapManager::GetServerName(iDeviceIndex, ServerName, sizeof(ServerName)))
			continue;

		int iCameraNum = SapManager::GetResourceCount(ServerName, SapManager::ResourceAcqDevice);

		/*遍历该Server下所有的采集卡*/
		for (int iCameraIndex = 0; iCameraIndex < iCameraNum; iCameraIndex++)
		{
			/*获取相机名称*/
			if (!SapManager::GetResourceName(ServerName, SapManager::ResourceAcqDevice, iCameraIndex, CameraName, sizeof(CameraName)))
				continue;

			TempLocation = new SapLocation(iDeviceIndex, iCameraIndex);

			TempAcqDevice = new SapAcqDevice(*TempLocation, false);
			TempAcqDevice->Create();

			//判断当前变量是否有效
			IsAvaiableResult = TempAcqDevice->IsFeatureAvailable("DeviceSerialNumber", &IsAvaiablePara);

			if (!IsAvaiableResult || !IsAvaiablePara)
			{
				TempAcqDevice->Destroy();
				delete TempAcqDevice;

				delete TempLocation;

				continue;
			}

			if (!TempAcqDevice->GetFeatureValue("DeviceSerialNumber", SerialNumber, 64))
			{
				TempAcqDevice->Destroy();
				delete TempAcqDevice;

				delete TempLocation;

				continue;
			}

			//确认序列号和相机名称是否一致
			if (!strcmp(SerialNumber, m_pCameraPara->m_szSerialNum) == 0
				|| !strcmp(CameraName, m_pCameraPara->m_szCamName) == 0)
			{
				TempAcqDevice->Destroy();
				delete TempAcqDevice;

				delete TempLocation;

				continue;
			}

			IsFindCarema = true;

			CameraNameIndex = iCameraIndex;
			SerialNameIndex = iDeviceIndex;

			TempAcqDevice->Destroy();
			delete TempAcqDevice;

			delete TempLocation;

			break;
		}
	}

	SapManager::Close();

	if (!IsFindCarema)
	{
		m_LogFile.LogFormat(NULL, LOG_INFO,
			"CDHCameraGrab::OpenCamera->Error, didn't find the camera:%s",
			m_pCameraPara->m_szSerialNum);

		return false;
	}

	/**************************************************
		  根据设备搜索设备名称，确定相机对象指针
	***************************************************/
	m_SapLocation = new SapLocation(SerialNameIndex, CameraNameIndex);

	//创建设备采集对象
	m_SapAcqDevice = new SapAcqDevice(*m_SapLocation, false);

	if (m_SapAcqDevice && !*m_SapAcqDevice && !m_SapAcqDevice->Create())
	{
		if (m_SapAcqDevice && *m_SapAcqDevice)
			m_SapAcqDevice->Destroy();

		return false;
	}

	m_SapBuffers = new SapBufferWithTrash(2, m_SapAcqDevice);

	//注册采集函数的回调函数
	m_SapTransfer = new SapAcqDeviceToBuf(m_SapAcqDevice, m_SapBuffers, SapTransferCallback, this);

	/**************************************************
			相机外部参数设置---外部触发设置
	***************************************************/
	//设置图像AOI区域
	if (!setImageAOIConf())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "set ImageAOI config fail.\n");

		//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
		return false;
	}

	if (!m_SapBuffers->Create())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "Create Buffer Failed!\n");

		return FALSE;
	}

	if (!m_SapTransfer->Create())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "Create Transfer Failed!\n");

		return FALSE;
	}

	//设置外部触发配置
	if (!setLineTriggerConf())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "set Line trigger config fail.\n");
		//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
		return false;
	}

	//设置图像翻转和AOI裁剪区域
	if (!setReverseXConf())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "set reversex config fail.\n");
		//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
		return false;
	}

	//设置图像翻转和AOI裁剪区域
	if (!setNegativeImageConf())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "set NegativeImage config fail.\n");
		//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
		return false;
	}

	//设置曝光时间
	if (!setExposureTimeConf())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "set exposuretime config fail.\n");
		//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
		return false;
	}

	//设置相机采集帧率
	if (!setAcquistionFrameRate())
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "set FrameRate config fail.\n");

		//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
		return false;
	}

	m_nTriggerCount = 0;	m_nGrabImageNum = 0;	m_nFailedImageNum = 0;

	m_nGrabLineImageNum = 0; m_nCurrLineIndex = 0;

	/*m_SapAcqDevice->SetFeatureValue("UserSetSelector", "UserSet1");
	m_SapAcqDevice->SetFeatureValue("UserSetSave", TRUE);*/

	/*Dahua::GenICam::IUserSetControlPtr ptrUserSetControl = systemObj.createUserSetControl(m_ptrICamera);
	ptrUserSetControl->setCurrentUserSet(Dahua::GenICam::IUserSetControl::EConfigSet::userSet1);
	ptrUserSetControl->saveUserSet();*/

	m_SapTransfer->Connect();

	/**************************************************
			相机外部参数设置---外部触发设置
	***************************************************/
	m_pImageUnit->m_dwHeight = m_pCameraPara->m_uImageHeight;
	m_pImageUnit->m_dwWidth = m_pCameraPara->m_uImageWidth;

	m_pImageUnit->m_dwImageFormat = m_pCameraPara->m_uImageChannel;

	int iPixelSize = (m_pCameraPara->m_iPixelFormat == 0) ? 2 : 1;

	m_pImageUnit->m_dwImageDataLen = m_pImageUnit->m_dwHeight * m_pImageUnit->m_dwWidth * iPixelSize;

	CCameraGrabBase::DalsaOpenCamera();

	return true;
}

bool CDalseCameraGrab::DalsaCloseCamera()
{
	if (m_SapTransfer->IsConnected())
	{
		if (!m_SapTransfer->Disconnect())
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "disConnect camera fail.\n");

			return false;
		}
	}

	if (m_SapTransfer && *m_SapTransfer)
	{
		m_SapTransfer->Destroy();

		delete m_SapTransfer;
	}

	// Destroy buffer object
	if (m_SapBuffers && *m_SapBuffers)
	{
		m_SapBuffers->Destroy();

		delete m_SapBuffers;
	}

	// Destroy acquisition object
	if (m_SapAcqDevice && *m_SapAcqDevice)
	{
		m_SapAcqDevice->Destroy();

		delete m_SapAcqDevice;
	}

	m_LogFile.LogFormat(NULL, LOG_INFO, "CDHCameraGrab::CloseCamera->leave");

	CCameraGrabBase::DalsaCloseCamera();

	m_bDalsaConnected = false;

	return true;
}


//将采集参数移到类内部，数据线程逻辑转移到初始化相机时
//数据线程用于初始化相机，用于解决在遇到异常时，恢复相机
bool CDalseCameraGrab::DalsaStartGrab()
{
	if (!m_SapTransfer->IsConnected())
		m_SapTransfer->Connect();

	//组册异常事件回调函数
	if (m_pCameraPara->m_iTriggerMode == 0)   //表示外部触发
	{
		bool issubscribeSucess = m_SapTransfer->Grab();

		if (!issubscribeSucess)
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "StartGrabbing  fail.\n");

			//实际应用中应及时释放相关资源，如diconnect相机等，不宜直接return
			return  false;
		}
	}
	else
	{
		m_SapTransfer->Grab();
	}

	m_nGrabLineImageNum = 0; m_nCurrLineIndex = 0;

	CCameraGrabBase::DalsaStartGrab();

	return true;
}

bool CDalseCameraGrab::DalsaStopGrab()
{
	m_LogFile.LogFormat(NULL, LOG_INFO, "CDHCameraGrab::StopGrab->enter");

	if (m_pCameraPara->m_iTriggerMode == 0)   //表示外部触发
	{
		//停止相机拉流
		bool isStopGrabbingSuccess = m_SapTransfer->Freeze();

		if (!isStopGrabbingSuccess)
		{
			m_LogFile.LogFormat(NULL, LOG_INFO, "StopGrabbing  fail.\n");
		}
	}

	CCameraGrabBase::DalsaStopGrab();

	return true;
}

bool CDalseCameraGrab::DalsaGrabImage()
{
	DWORD dwRet = 1;

	int iPixelSize;

	if (m_pCameraPara->m_uImageChannel == 3)
		iPixelSize = 2;
	else
		iPixelSize = 1;

	DWORD dwImageLen = m_pCameraPara->m_uImageWidth * m_pCameraPara->m_uImageHeight * iPixelSize;

	//if (!IsDaHuaConnected())
	//	return false;

	////对同步信号置位---即进入采集函数开始进行同步信号
	//if(!m_SyncSignal.IsSetEvent())
	//	m_SyncSignal.Singnal();

	//Dahua::GenICam::CFrame TempFrame;

	////设置获取数据的时间限制
	//if (m_ptrDaHuaStream->getFrame(TempFrame, 1))
	//{
	//	if (TempFrame.valid() == true)
	//	{
	//		//unsigned char *pImageBuffer = (unsigned char *)TempFrame.getImage();

	//		if (m_pDHFunOnGetImage != NULL)
	//		{
	//			m_pImageUnit->m_dwHeight = TempFrame.getImageHeight();
	//			m_pImageUnit->m_dwWidth = TempFrame.getImageWidth();

	//			m_pImageUnit->m_dwPaddingX = TempFrame.getImagePadddingX();
	//			m_pImageUnit->m_dwPaddingY = TempFrame.getImagePadddingY();

	//			m_pImageUnit->m_dwImageFormat = TempFrame.getImagePixelFormat();

	//			m_pImageUnit->m_dwImageDataLen = TempFrame.getImageSize();
	//			m_pImageUnit->m_dwImageData = (unsigned char *)TempFrame.getImage();

	//			m_gGrabImageNum++;

	//			m_gTriggerCount = m_gGrabImageNum + m_gFailedImageNum;

	//			//函数指针为数据指针
	//			m_pDHFunOnGetImage(m_pImageUnit, m_pCameraPara->m_iCamID, m_pDHFunOnGetImageParam);
	//		}

	//		DaHuaCameraChangeEvent(ceGrabbing);					

	//		TempFrame.reset();

	//		dwRet = 0;				
	//	}
	//	else
	//	{
	//		m_LogFile.LogFormat(NULL, LOG_INFO, "CDHCameraGrab::Frame Invalid!"); 
	//	}
	//}
	//else
	//{
	//	//m_LogFile.LogFormat(NULL, LOG_INFO, "CDHCameraGrab::GetFrame Invalid!");
	//}

	//m_nFailedImageNum = m_gFailedImageNum;  
	//m_nGrabImageNum = m_gGrabImageNum;  
	//m_nTriggerCount = m_gTriggerCount;

	return dwRet;
}

bool CDalseCameraGrab::setTriggerSoftware()
{
	DWORD dwRet = 1;

	if (!IsDalsaConnected())
		return dwRet;

	bool issubscribeSucess = m_SapTransfer->Snap();

	if (issubscribeSucess == false)
	{
		m_LogFile.LogFormat(NULL, LOG_INFO, "CDalseCameraGrab::SnapImage->Error");

		return false;
	}

	return true;
}

bool CDalseCameraGrab::getCameraSerialNumber(char* SerialNumber)
{
	if (!IsDalsaConnected())
		return false;

	BOOL IsAvaiablePara = FALSE, IsAvaiableResult = FALSE;

	//判断当前变量是否有效
	IsAvaiableResult = m_SapAcqDevice->IsFeatureAvailable("DeviceSerialNumber", &IsAvaiablePara);

	if (!IsAvaiableResult || !IsAvaiablePara)
		return false;

	if (!m_SapAcqDevice->GetFeatureValue("DeviceSerialNumber", SerialNumber, 64))
		return false;

	return true;
}