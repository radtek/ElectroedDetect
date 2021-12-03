
#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include "Public.h"

#define MAX_MSG_SIZE	4096
#define LOG_BUF			MAX_MSG_SIZE

#define LOG_DEBUG 0
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERROR 3
#define LOG_CRIT  4
#define LOG_FATAL 5
#define LOG_NULL  6

//typedef void (*PFunLog)(char * szMsg);

class GM_EXPORT CLogFile  
{
public:
	CLogFile();
	~CLogFile();

	BOOL LogMessage(const char* szPath, const char *szMsg,  const char *szMsg1 = NULL);
	BOOL LogFormat(const char* szPath, int logLevel, const char *fmt, ...);
	
	//BOOL LogMessage(const char *szMsg,  const char *szMsg1 = NULL);
	//BOOL LogFormat(int logLevel, const char *fmt, ...);

	static int CreateMultiDir(char* szPath);
	//PFunLog m_pfunLog;
	static void TraceMessage(const char *fmt, ...);
private:
	FILE *m_File;
	char szLogFilePath[MAX_PATH];
	char szMessage[MAX_MSG_SIZE];
	CRITICAL_SECTION cs;
	bool bFirst;

protected:
	time_t nowTime, yesTime;
	char szNowTime[MAX_PATH];
	char szYesTime[MAX_PATH];
	char szDT[MAX_PATH];
	char szDelLogFile[MAX_PATH];
	char szLogFile[MAX_PATH];
	tm tmTemp, tmNow, tmYes;
};

#endif