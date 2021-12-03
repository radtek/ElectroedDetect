
#ifndef _INC_DTCOMMONWINUTIL_INCLUDED
#define _INC_DTCOMMONWINUTIL_INCLUDED

#define ESUTIL_NS_BEGIN namespace esutil{
#define ESUTIL_NS_END }
#define	ESUTIL_NS esutil

ESUTIL_NS_BEGIN

class LockMutex
{
public:
	//##ModelId=45360C25006D
	LockMutex(HANDLE hMutex, DWORD dwTimeoutSecond)
	{
		m_hMutex = NULL;
		m_bLock = false;
		m_bTimeout = false;
		DWORD dwWaitResult=0;
		if (hMutex!=NULL)
		{
		    dwWaitResult = WaitForSingleObject( 
									 hMutex,   // handle to mutex
									 (dwTimeoutSecond == INFINITE)? dwTimeoutSecond = INFINITE : dwTimeoutSecond * 1000);   // 1min time-out interval
		}
		switch (dwWaitResult)
		{
			case WAIT_OBJECT_0:
			case WAIT_ABANDONED:
				m_hMutex = hMutex;
    			m_bLock = true;
				break;
			case WAIT_TIMEOUT:
				m_bTimeout = true;
				break;
		}
	}
	//##ModelId=45360C25006F
	~LockMutex()
	{
		if(m_hMutex != NULL)
		{
			ReleaseMutex(m_hMutex);
		}
	}
	bool IsLocked()
	{
		return m_bLock;  
	}
	bool IsTimeout()
	{
		return m_bTimeout;  
	}
private:
	//##ModelId=45360C250070
	BOOL fOwn;
	//##ModelId=45360C2500AB
	HANDLE m_hMutex;
	bool m_bLock;
	bool m_bTimeout;
};

class LockCritSect
{
public:
	LockCritSect(CRITICAL_SECTION* pCritSect){
		EnterCriticalSection(pCritSect) ;
		m_pCritSect = pCritSect ;
	}
	~LockCritSect() {
		LeaveCriticalSection(m_pCritSect) ;
	}

private:
	CRITICAL_SECTION* m_pCritSect ;
};

ESUTIL_NS_END

#endif