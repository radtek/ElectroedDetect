#ifndef _DTLINUXTOOL_
#define _DTLINUXTOOL_
#include "dtsignage.h"
#include <windows.h>

#define PRINTDEBUGINFO

void GetLocaleString(char *pLocale);

bool DT2ATC(WCHAR **pDest, int &iDestLen, const char *pSrc , const char *pLocale);

bool DTCT2A(char **pDest, int &iDestLen, const WCHAR *pSrc,const char *pLocale);

bool DT2ATC(CHAR **pDest, int &iDestLen, const char *pSrc , const char *pLocale);

bool DTCT2A(char **pDest, int &iDestLen, const CHAR *pSrc,const char *pLocale);

bool DT2ATC(WCHAR **pDest, int &iDestLen, const char *pSrc);

bool DTCT2A(char **pDest, int &iDestLen, const WCHAR *pSrc);

bool DT2ATC(CHAR **pDest, int &iDestLen, const char *pSrc);

bool DTCT2A(char **pDest, int &iDestLen, const CHAR *pSrc);

void DTSleep(DWORD dwMilliSecond);

int DTATOI(const TCHAR *sInteger);

long DTATOL(const TCHAR *sInteger);

void DebugInfo(const char *pszStr, ...);

bool DTToLower(TCHAR *pStr, const char *pLocale = "");

bool DTToUpper(TCHAR *pStr, const char *pLocale = "");
BOOL DTGetExeFileName(DTString &sFileName);
BOOL DTGetExeFilePath(DTString &sFilePath);
BOOL IsFileExist(const DTString& strFilePath, time_t* pLastModifyTime);
int DTNCMPCaseInsensitive(const TCHAR* strLeft, const TCHAR *strRight, int iCount = 0);
#endif
