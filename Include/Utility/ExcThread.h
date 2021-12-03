
#include "Public.h"

#pragma once

class CExcThreadPool;


//////////////////////////////////////////////////////////////////////////
// CMutexLock
//////////////////////////////////////////////////////////////////////////
class GM_EXPORT CMutexLock
{
public:
	CMutexLock(void);
	~CMutexLock(void);

public:
	void Lock (void);
	void Unlock (void);

private:
	CRITICAL_SECTION  m_lock;
};


//////////////////////////////////////////////////////////////////////////
// CExcThread
//////////////////////////////////////////////////////////////////////////
class GM_EXPORT CExcThread
{
public:   //多线程包括创建、挂起、恢复、终结以及通信工作
	CExcThread(void);
	virtual ~CExcThread(void);

public:
	/*!
		\brief 创建
	 */
	BOOL	CreateExcThread(int priority = THREAD_PRIORITY_NORMAL, DWORD flags = 0);
	/*!
		\brief 挂起
	 */
	DWORD	SuspendExcThread(void);
	/*!
		\brief 重启
	 */
	DWORD	ResumeExcThread(void);
	/*!
		\brief 终止
	 */
	DWORD	TerminateExcThread(void);

	/*!
		\brief 设置优先级
	 */
	BOOL	SetPriorityExcThread(int priority);

	/*!
		\brief 设置ID号
	 */
	void	SetIDForExcThread(int id);

	/*!
		\brief 获取ID号
	 */
	DWORD   GetIDForExcThread(void) const;

	virtual DWORD ThreadProcess(void);

protected:
	static DWORD	_thread_process	(CExcThread *_this);
	virtual BOOL	_enter_instance (void);
	virtual DWORD	_leave_instance (void);

protected:
	HANDLE m_hThread;
	DWORD  m_dwThreadId;

	HANDLE m_hEventSetExit;		// 设置退出事件
	HANDLE m_hEventExited;		// 已经退出事件
	bool   m_isRunning;

	CExcThreadPool  *m_hPool;
};

typedef CExcThread    *HExcThread;
typedef CExcThread   *LPExcThread;


