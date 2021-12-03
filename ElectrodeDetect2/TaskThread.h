/************************************************
     所有与线程有关的操作均在该文件中
*************************************************/
#ifndef _TASK_THREAD_H_
#define _TASK_THREAD_H_

#include "Public.h"
#include "ZcStruct.h"
#include "CameraPara.h"
#include "GlobalDefine.h"

#include <DTTask/CESTask.h>

class CElectrodeDetect2Dlg;

typedef LRESULT(__cdecl* CallBackFun)(void* param);

class CPollingThread : public CESTask
{
public:
	CPollingThread();
	~CPollingThread();

	bool IsThreadIdle();

	void SetCallBackFun(CallBackFun PtrFun, void* param, int TimeInterval);
protected:
	virtual DWORD Process();
private:
	bool  m_bThreadIdle;

	int   m_timeInterval;
	void* m_param;

	CallBackFun m_ptrFun;
};

typedef LRESULT(__cdecl* CallBackFileFun)(FileTask* PtrFileTask, void* param);

// 保存Csv文件的线程
class CSaveCsvFileThread : public CESTask
{
public:
	CSaveCsvFileThread(CElectrodeDetect2Dlg* Parent);
	~CSaveCsvFileThread();

	bool IsThreadIdle();

	void SetCallBackFileFun(CallBackFileFun PtrFun, void* param, int TimeInterval);

protected:
	virtual DWORD Process();
private:
	bool  m_bThreadIdle;

	int   m_timeInterval;
	void* m_param;

	CElectrodeDetect2Dlg* m_pParent;

	CallBackFileFun m_ptrFileFun;
};

#endif//_TASK_THREAD_H_