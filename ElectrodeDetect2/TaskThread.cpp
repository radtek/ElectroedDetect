#include "pch.h"
#include "TaskThread.h"
#include "FileHander.h"
#include "ElectrodeDetect2Dlg.h"

#include <LogFile/LogFile.h>
#include <Utility/Utility.h>

extern CLogFile m_LogFile;

CPollingThread::CPollingThread()
{
	m_bThreadIdle = true;

	m_param = NULL;  m_ptrFun = NULL;

	m_timeInterval = 50;
}

CPollingThread::~CPollingThread()
{
	CloseThreadTask();
}

void CPollingThread::SetCallBackFun(CallBackFun PtrFun, void* param, int TimeInterval)
{
	m_ptrFun = PtrFun;
	m_param = param;
	m_timeInterval = TimeInterval;
}

bool CPollingThread::IsThreadIdle()
{
	return m_bThreadIdle;
}

DWORD CPollingThread::Process()
{
	SetTimeOutMicroSecond(0);

	m_bThreadIdle = true; 
	
	while (true)
	{
		if (Wait() == TASK_STOP)
			break;

		m_bThreadIdle = false;

		if (m_ptrFun != NULL)
		{
			m_ptrFun(m_param);
		}
		Sleep(m_timeInterval);

		m_bThreadIdle = true;
	}

	return 0;
}

/* 保存CSV文件的线程 */
CSaveCsvFileThread::CSaveCsvFileThread(CElectrodeDetect2Dlg* Parent)
{
	m_bThreadIdle = true;

	m_param = NULL;  m_ptrFileFun = NULL;

	m_timeInterval = 5;

	m_pParent = Parent;
}

CSaveCsvFileThread::~CSaveCsvFileThread()
{
	CloseThreadTask();
}

void CSaveCsvFileThread::SetCallBackFileFun(CallBackFileFun PtrFun, void* param, int TimeInterval)
{
	m_ptrFileFun = PtrFun;
	m_param = param;
	m_timeInterval = TimeInterval;
}

bool CSaveCsvFileThread::IsThreadIdle()
{
	return m_bThreadIdle;
}

DWORD CSaveCsvFileThread::Process()
{
	SetTimeOutMicroSecond(0);

	FileTask* PtrFileTask = NULL;

	while (true)
	{
		if (Wait() == TASK_STOP)
			break;

		if (m_pParent->m_PtrFileHander != NULL)
		{
			if (m_pParent->m_PtrFileHander->GetFileTask(&PtrFileTask))
			{
				if (m_ptrFileFun != NULL)
				{
					m_ptrFileFun(PtrFileTask, m_param);
				}
			}
		}
		Sleep(m_timeInterval);
	}
	return 0;
}
