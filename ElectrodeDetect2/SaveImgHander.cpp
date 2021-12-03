#include "pch.h"
#include "SaveImgHander.h"
#include "TaskThread.h"
#include "Analyhander.h"
#include <DTTask/DTUtil.h>
#include <Utility/Utility.h>
#include "ElectrodeDetect2Dlg.h"


LRESULT __cdecl FunCallBackSaveImgThread(void* param)
{
	CSaveImgHander* hander = (CSaveImgHander*)param;
	
	if (hander->IsQueueEmpty())			
		return TRUE;

	AnalyTask analyTask;

	if (!hander->GetImageTask(&analyTask))
		return TRUE;

	CElectrodeDetect2Dlg* parent = hander->m_pParent;

	//  线程功能
	int CameraIndex = hander->m_CameraIndex;

	// 获取图片数据
	cv::Mat GrayImage(cvSize(analyTask.ImageUnit.m_dwWidth, analyTask.ImageUnit.m_dwHeight), CV_8U);
	memcpy(GrayImage.data,
		analyTask.ImageUnit.m_dwImageData,
		analyTask.ImageUnit.m_dwWidth * analyTask.ImageUnit.m_dwHeight);

	int index = analyTask.PictureId % 4;

	//  保存
	CUtility uti;
	COleDateTime CurTime(COleDateTime::GetCurrentTime());
	char FilePath[1024] = { '\0' }, DataPath[1024] = { '\0' }, TimePath[1024] = { '\0' }, imigPath[1024] = { '\0' };

	uti.Utility_getDayStr(DataPath);
	uti.Utility_GetCurTimeIndexFormat(TimePath);


	//***********指定文件夹\\OKNG\\班别\\日期文件夹***********//
	if (CameraIndex == 0)		// Dalsa相机保存图片
	{
		if (parent->m_IsSaveOKData && parent->m_IsSaveNGData)
		{
			if (analyTask.DetectResult == TRUE)
				sprintf_s(FilePath, "%s\\%s\\相机1\\OK\\", parent->m_strSaveImagePath,DataPath);
			else if (analyTask.DetectResult == FALSE)
				sprintf_s(FilePath, "%s\\%s\\相机1\\NG\\", parent->m_strSaveImagePath, DataPath);
			else
				return false;
		}
		else if (parent->m_IsSaveOKData)
		{
			if (analyTask.DetectResult == TRUE)
				sprintf_s(FilePath, "%s\\%s\\相机1\\OK\\", parent->m_strSaveImagePath, DataPath);
			else
				return false;
		}
		else if (parent->m_IsSaveNGData)
		{
			if (analyTask.DetectResult == FALSE)
				sprintf_s(FilePath, "%s\\%s\\相机1\\NG\\", parent->m_strSaveImagePath, DataPath);
			else
				return false;
		}
		else
			return false;

		uti.Utility_CreateDirByPath(FilePath);
		sprintf_s(imigPath, "%s%s-%d.bmp", FilePath, TimePath, analyTask.PictureId);
		imwrite(imigPath, GrayImage);
	}
	else if(CameraIndex == 1)	// 海康相机保存图片
	{
		if (parent->m_IsSaveOKData && parent->m_IsSaveNGData)
		{
			if (((VisionParaOut*)analyTask.PtrParaOut)->DetectResult == TOOL_PASS)
				sprintf_s(FilePath, "%s\\%s\\相机2\\OK\\", parent->m_strSaveImagePath, DataPath);
			else if (analyTask.DetectResult == TOOL_ERROR)
				sprintf_s(FilePath, "%s\\%s\\相机2\\NG\\", parent->m_strSaveImagePath, DataPath);
			else
				return false;
		}
		else if (parent->m_IsSaveOKData)
		{
			VisionParaOut* p_temp = (VisionParaOut*)analyTask.PtrParaOut;
			if (((VisionParaOut*)analyTask.PtrParaOut)->DetectResult == TOOL_PASS)
				sprintf_s(FilePath, "%s\\%s\\相机2\\OK\\", parent->m_strSaveImagePath, DataPath);
			else
				return false;
		}
		else if (parent->m_IsSaveNGData)
		{
			if (((VisionParaOut*)analyTask.PtrParaOut)->DetectResult == TOOL_ERROR)
				sprintf_s(FilePath, "%s\\%s\\相机2\\NG\\", parent->m_strSaveImagePath, DataPath);
			else
				return false;
		}
		else
			return false;

		uti.Utility_CreateDirByPath(FilePath);
		sprintf_s(imigPath, "%s%s-%d.jpg", FilePath, TimePath, analyTask.PictureId);
		imwrite(imigPath, GrayImage);
	}

	return true;
}

CSaveImgHander::CSaveImgHander(int CameraIndex, CElectrodeDetect2Dlg* Parent)
{
	m_pParent = Parent;
	m_CameraIndex = CameraIndex;

	std::queue<AnalyTask> emptyQueue;
	m_Task.swap(emptyQueue);

	m_pThread = new CPollingThread();
	m_pThread->SetCallBackFun(FunCallBackSaveImgThread, this, 10);

	HANDLE handle;
	handle = m_pThread->Start();
}

bool CSaveImgHander::AddImageTask(AnalyTask* Task)
{
	m_Task.push(*Task);

	return true;
}

bool CSaveImgHander::IsQueueEmpty()
{
	if (m_Task.size() <= 0)
		return true;

	return false;
}

CSaveImgHander::~CSaveImgHander()
{
	if (m_pThread->IsRuning())
		m_pThread->Stop();

	delete m_pThread;
	m_pThread = NULL;

	std::queue<AnalyTask> emptyQueue;
	m_Task.swap(emptyQueue);
}


bool CSaveImgHander::GetImageTask(AnalyTask* Task)
{
	if (m_Task.size() <= 0)
		return false;

	*Task = m_Task.front();
	m_Task.pop();

	return true;
}