// Copyright 2006 DT Research Inc. USA, http://www.dtri.com
// @author: Jeff Li

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CESTASK_45092E120177_INCLUDED
#define _INC_CESTASK_45092E120177_INCLUDED

#ifdef ESTASK_EXPORTS
#define ESTASK_API __declspec(dllexport)
#else
#define ESTASK_API __declspec(dllimport)
#endif

#include <DTTask/dtsignage.h>

//const definition to check the return value of wait function
const	DWORD TASK_STOP		=	WAIT_OBJECT_0;
const	DWORD TASK_TIMEOUT	=	WAIT_TIMEOUT;
//const	DWORD TASK_ABNORMAL	=	WAIT_TIMEOUT


//This class encapsulates a Win32 thread in a C++ class:
// 1.  easy to subclass and reuse. besides.
// 2. hides the details of threads from users so they can focus on the project 
//details
// 3. sub classes doesn't need take care of crash report module
//##ModelId=45092E120177
class ESTASK_API CESTask 
{
public:
	//##ModelId=4519E3460232
	CESTask();

	//The returned HANDLE is the handle of the thread created in this function, 
	//it will be used by main thread (WaitForMultipleObjects)
	//
	//before create a new thread, should check value of m_hTaskHandle, if it is 
	//not NULL, should close it at first. In addition, should Reset 
	//m_hStopStartEvent.
	//##ModelId=45092E4F000F
	HANDLE Start();

	//set m_hStopStartEvent, if fWait is TRUE, should signal this event then wait 
	//for m_hStopEndEvent.
	//
	//implementation of Process() should wait m_hStopStartEvent periodically,if 
	//m_hStopStartEvent is released, Process() should set m_hStopendEvent then 
	//exit
	//
	//example code:
	//SetEventm_hStopStartEvent); 
	//if(fWait) return 0;
	//Sleep(1);
	//WaitForSingleObjectm_hStopEndEvent.timeout);
	//if return due to timeout, call TerminateThread
	//SetLiveFlag(FALSE);
	//##ModelId=45092E6A038A
	int Stop(BOOL fWait = TRUE, DWORD dwWaitSeconds = 2);

	//if(!m_fLive) return m_fLive
	//else call GetExitCodeThread(m_hTaskHandle) if the exitcode is not 
	//STILL_ACTIVE return FALSE
	//else return m_fLive;
	//##ModelId=45092E730251
	BOOL IsRuning();

	//f there are errors in thread function which can't continue the process, the 
	//method should be called to set m_csErrMsg
	//##ModelId=450943B9005D
	int SetErrorMessage(const DTString& strMsg);

	//##ModelId=450E146C0280
	BOOL GetErrorMessage(DTString& strMsg);


	//Zhangxq Aug 27, 2008 for bug 12104
	//Add this function to close current thread  in destructor of class.
	//In all classes that derived from class CESTask, we should call this function in destructor.
    void CloseThreadTask();

	//if(IsRuning()) Stop();
	//if(m_hTaskHandle) Close(m_hTaskHandle);
	//if(m_hStopEvent) Cloase(m_hStopEvent);
	//##ModelId=4513A58C0242
	virtual ~CESTask();

protected:
	//m_hStopStartEvent and m_hStopEndEvent are used to communicate between the 
	//class and the thread function when the class want to stop the thread, 
	//they are created in constructor
	//   initial state of m_hStopStartEvent is unsignaled
	//   initial state of m_hStopEndEvent is unsignaled
	//##ModelId=450E12DC03A9
	HANDLE m_hStopStartEvent;

	//m_hStopStartEvent and m_hStopEndEvent are used to communicate between the 
	//class and the thread function when the class want to stop the thread, 
	//they are created in constructor
	//   initial state of m_hStopStartEvent is unsignaled
	//   initial state of m_hStopEndEvent is unsignaled
	//##ModelId=4517650A01B5
	HANDLE m_hStopEndEvent;

	//at the end of every loop of this task, besides waiting for stop event, the 
	//derived class may wait for its own handles, to simplify implementation of 
	//derived class, this member is used in Wait function, so derived class can:
	//1. call AddWaitHandles at first(before loop) if it has other wait handles 
	//besided stop event
	//2. call SetTimeOut to set the time out value
	//3. at end of every loop call Wait
	//4. check return value of Wait, if return TASK_STOP, the thread should exit
	//suppose the maxmum handles won't exceed 10;
	//##ModelId=4546C08103C8
	HANDLE m_pWaitHandles[10];  //suppose the maxmum handles won't exceed 10;

	//thread handle created in Start() function
	//##ModelId=45139B050186
	HANDLE m_hTaskHandle;

	int m_nWaitHandleNum;
	//please refer to comment of m_pWaitHandles for detail
	//##ModelId=4546C0820280
	void AddWaitHandles(HANDLE* pHandles, int nNum);
	//##ModelId=4509FC03008C
	void SetLiveFlag(BOOL fLive);

	//unit:second
	//please refer to comment of m_pWaitHandles for detail
	//##ModelId=4546C0820177
	void SetTimeOut(DWORD dwTimeOutSecond)
	{
		m_dwTimeOut = dwTimeOutSecond*1000;
	}

	void SetTimeOutMicroSecond(DWORD dwTimeOutMicroSecond)
	{
		m_dwTimeOut = dwTimeOutMicroSecond;
	}

	//##ModelId=455150D0006D
	void SetWaitFlag(BOOL fWaitAll = FALSE)
	{
		m_fWaitAll = fWaitAll;
	}

	//the main business is in this function
	//derived classed should override this function
	//##ModelId=450E11F000EA
	virtual DWORD Process();

	//##ModelId=4546C083002E
	virtual DWORD Wait();

	BOOL IsBeingStopped();

private:
	//if there are errors in thread function which can't continue the process, 
	//the error message is updated the exit
	//##ModelId=450943AB00DA
	DTString m_strErrMsg;

	//##ModelId=4509FBDC03C8
	BOOL m_fLive;

	//##ModelId=455150D001D4
	BOOL m_fWaitAll;

	//timeout value passed into WaitForMultipleObjects, the derived class can 
	//call SetTimeOut() to change this value
	//default value: INFINITE
	//##ModelId=4546C0830109
	DWORD m_dwTimeOut;

	//number of valid handles in m_pWaitHandles
	//##ModelId=4546C08301D4

	//this is a static funciton as the main thread entry created in Start() 
	//function
	//
	//
	//the crashReport will be implied on this function:
	//DTES_CRASH_REPORT_START
	//return ((CTask*)(pThis))->Process();
	//DTES_CRASH_REPORT_START(m_pConfig, m_pCommunication, _T("crashed in 
	//CESTask::ThreadProc"))
	//return -1;
	//##ModelId=450E10EF0186
	static DWORD WINAPI ThreadProc(void* pThis);

};

#endif /* _INC_CESTASK_45092E120177_INCLUDED */
