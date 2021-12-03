#pragma once
#include "pch.h"
#include "ElectrodeDetect2Dlg.h"
#include "HaiKangGrabHander.h"
#include "Analyhander.h"

#include <DTTask/DTUtil.h>
#include <Utility/Utility.h>
#include <LogFile/LogFile.h>

// 相机获取到图片后调用的回调函数
LRESULT __cdecl FunCallBackHaiKangGetImg(ImageUnitBase* PtrImgInfo,int CameraID,void* param)
{
	CElectrodeDetect2Dlg* dlgVision = (CElectrodeDetect2Dlg*)param;

	//if (!dlgVision->m_IsDetecting)
	//{
	//	dlgVision->m_IsDetecting = true;
	//	dlgVision->m_ProductID++;
	//}

	AnalyTask CamAnalyTask;

	CamAnalyTask.Init();

	CamAnalyTask.PtrParaIn = NULL;
	CamAnalyTask.PtrParaOut = NULL;

	CamAnalyTask.PtrParaIn = dlgVision->m_PtrCSIVisionIn2;
	CamAnalyTask.PtrParaOut = dlgVision->m_PtrCSIVisionOut2;

	// ImageUnit表示图像的基本参数：宽、高、格式、图像数据指针
	CamAnalyTask.ImageUnit.m_dwHeight = PtrImgInfo->m_dwHeight;
	CamAnalyTask.ImageUnit.m_dwWidth = PtrImgInfo->m_dwWidth;
	CamAnalyTask.ImageUnit.m_dwImageDataLen = PtrImgInfo->m_dwImageDataLen;
	CamAnalyTask.ImageUnit.m_dwImageFormat = PtrImgInfo->m_dwImageFormat;
	CamAnalyTask.ImageUnit.m_dwImageData = PtrImgInfo->m_dwImageData;

	CamAnalyTask.PictureId = dlgVision->m_CurrTotalNum_HaiKang;

	dlgVision->m_pHaiKangAnalyHander[dlgVision->m_CurrTotalNum_Dalsa % 4]->AddImageTask(&CamAnalyTask);

	dlgVision->m_CurrTotalNum_HaiKang++;

	return TRUE;
}

CHaiKangGrabHander::CHaiKangGrabHander(int cameraIndex, CameraGrabPara* dGrabPara, void* dlgDetection)
{
	m_ExitFlag = false;
	// 将在外面配置好的相机参数赋值给父级真正控制相机的参数对象
	memcpy(m_PtrCameraPara,dGrabPara,sizeof(CameraGrabPara));

	m_dlgDetection = dlgDetection;					// 父窗口，即ElectrodeDetectDlg

	m_cameraIndex = cameraIndex;					// 相机索引
	m_cameraStatus = 0;								// 相机状态

	SetCallBackHaiKangGetImageFun(FunCallBackHaiKangGetImg,dlgDetection);	// 设置获取到图片后调用的函数
}

CHaiKangGrabHander::~CHaiKangGrabHander()
{
	m_ExitFlag = true;

	if (m_cameraStatus != 0 && m_cameraStatus != 4)
		HaiKangCloseCamera();
}

void CHaiKangGrabHander::SetTriModeOn()
{
	SetLineTriggerConf();
}