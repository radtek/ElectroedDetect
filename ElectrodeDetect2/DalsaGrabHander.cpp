#include "pch.h"
#include "DalsaGrabHander.h"
#include "Analyhander.h"
#include "ElectrodeDetect2Dlg.h"
#include "FileHander.h"

#include <DTTask/DTUtil.h>
#include <Utility/Utility.h>

LRESULT __cdecl FunCallBackDalsaGetImg(ImageUnitBase* PtrImgInfo, int CameraID, void* param)
{
	CElectrodeDetect2Dlg* dlgVision = (CElectrodeDetect2Dlg*)param;

	// 获取到图片
	if (!dlgVision->m_IsDetecting)
	{
		dlgVision->m_IsDetecting = true;
		dlgVision->m_ProductID++;
		dlgVision->m_CurrTotalNum_Dalsa = 0;
		dlgVision->m_CurrTotalNum_HaiKang = 0;

		dlgVision->m_NCam1_Sum = 0;
		dlgVision->m_NCam1_Pass = 0;
		dlgVision->m_NCam1_Fail = 0;
	}

	AnalyTask CamAnalyTask;

	CamAnalyTask.Init();

	CamAnalyTask.PtrParaIn = dlgVision->m_PtrCSIVisionIn;
	CamAnalyTask.PtrParaOut = dlgVision->m_PtrCSIVisionOut;

	// ImageUnit表示图像的基本参数：宽、高、格式、图像数据指针
	CamAnalyTask.ImageUnit.m_dwHeight = PtrImgInfo->m_dwHeight;
	CamAnalyTask.ImageUnit.m_dwWidth = PtrImgInfo->m_dwWidth;
	CamAnalyTask.ImageUnit.m_dwImageDataLen = PtrImgInfo->m_dwImageDataLen;
	CamAnalyTask.ImageUnit.m_dwImageFormat = PtrImgInfo->m_dwImageFormat;
	CamAnalyTask.ImageUnit.m_dwImageData = PtrImgInfo->m_dwImageData;

	CamAnalyTask.PictureId = dlgVision->m_CurrTotalNum_Dalsa;

	dlgVision->m_pDalsaAnalyHander[dlgVision->m_CurrTotalNum_Dalsa % 4]->AddImageTask(&CamAnalyTask);

	dlgVision->m_CurrTotalNum_Dalsa++;

	return TRUE;
}

CDalsaGrabHander::CDalsaGrabHander(int cameraIndex, CameraGrabPara* dGrabPara, void* dlgDetection)
{
	m_ExitFlag = false;
	// 将在外面配置好的相机参数赋值给父级真正控制相机的参数对象
	memcpy(m_pCameraPara, dGrabPara, sizeof(CameraGrabPara));

	m_dlgDetection = dlgDetection;					// 父窗口，即ElectrodeDetectDlg

	m_cameraIndex = cameraIndex;					// 相机索引
	m_cameraStatus = 0;								// 相机状态

	SetCallBackGetImageFun(FunCallBackDalsaGetImg, dlgDetection);	// 设置获取到图片后调用的函数
	
	if (m_pCameraPara->m_uImageChannel == 1)
		pTempBuffer = NULL;
	else
		pTempBuffer = (unsigned char*)malloc(m_pCameraPara->m_uImageHeight * m_pCameraPara->m_uImageWidth * 3);
}

CDalsaGrabHander::~CDalsaGrabHander()
{
	m_ExitFlag = true;

	if (m_cameraStatus != 0 && m_cameraStatus != 4)
		DalsaCloseCamera();
}
