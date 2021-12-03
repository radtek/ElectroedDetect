#include "stdafx.h"
#include "dttool.h"
#include <locale>
#include <assert.h>
#include <io.h>
#include <tchar.h>

void DebugInfo(const char *pszStr, ...)
{
#ifndef PRINTDEBUGINFO
  return;
#endif	
	va_list				arglist;
	va_start(arglist, pszStr);
	char sz[2096];
	vsprintf(sz, pszStr, arglist);
	printf(sz);
	va_end(arglist);
}

void GetLocaleString(char *pLocale)
{
 	    strcpy(pLocale, "english");
    	LANGID langId = GetSystemDefaultLangID();
	    if (PRIMARYLANGID(langId) == LANG_CHINESE && SUBLANGID(langId) == SUBLANG_CHINESE_SIMPLIFIED)
    	{
    	    strcpy(pLocale, "chinese-simplified");
    	}
	    else if(PRIMARYLANGID(langId) == LANG_CHINESE && SUBLANGID(langId) == SUBLANG_CHINESE_TRADITIONAL)
    	{
    	    strcpy(pLocale, "chinese-traditional");
    	}
	    else if(PRIMARYLANGID(langId) == LANG_JAPANESE)
    	{
    	    strcpy(pLocale, "japanese");
    	}
	    else if(PRIMARYLANGID(langId) == LANG_GERMAN)
    	{
    	    strcpy(pLocale, "german");
    	}
    	else if (PRIMARYLANGID(langId) == LANG_FRENCH)
	    {
    	    strcpy(pLocale, "french");
    	}
	    else if (PRIMARYLANGID(langId) == LANG_SPANISH)
    	{
    	    strcpy(pLocale, "spanish");
    	}
	    else if (PRIMARYLANGID(langId) == LANG_PORTUGUESE)
    	{
    	    strcpy(pLocale, "portuguese");
    	}
	    else if (PRIMARYLANGID(langId) == LANG_KOREAN)
    	{
    	    strcpy(pLocale, "korean");
    	}
    	return ;
}

bool DT2ATC(WCHAR **pDest, int &iDestLen, const char *pSrc , const char *pLocale)
{
	assert(pSrc!=NULL);
	setlocale(LC_ALL, pLocale);
	size_t iSrcSize = mbstowcs(NULL, pSrc, 0) + 1;
	if (*pDest==NULL)
	{
		iDestLen=0;
	}
	if (iDestLen!=0)
	{
		if ((int)iSrcSize > iDestLen) return false;
	}
	else
	{
		*pDest=new WCHAR[iSrcSize];
	}
	size_t iSize = mbstowcs(*pDest, pSrc, iSrcSize);
	if (iSize == (size_t) (-1))
	{
		if (iDestLen==0)
		{
			delete []*pDest;
			*pDest=NULL;
		}
		return false;
	}
	iDestLen=iSize;
	return true;
}


bool DTCT2A(char **pDest, int &iDestLen, const WCHAR *pSrc,const char *pLocale)
{
	assert(pSrc!=NULL);
	setlocale(LC_ALL, pLocale);
	size_t iSrcSize = wcstombs(NULL, pSrc, 0) + 1;
	if (*pDest==NULL)
	{
		iDestLen=0;   
	}
	if (iDestLen!=0)
	{
		if ((int)iSrcSize > iDestLen) return false;
	}
	else
	{
		*pDest=new char[iSrcSize];
	}
	size_t iSize = wcstombs(*pDest, pSrc, iSrcSize);
	if (iSize == (size_t) (-1))
	{
		if (iDestLen==0)
		{
            delete []*pDest;
			*pDest=NULL;
		}
		return false;
	}
	iDestLen=iSize;
	return true;
}

bool DT2ATC(CHAR **pDest, int &iDestLen, const char *pSrc , const char *pLocale)
{
	assert(pSrc!=NULL);
	size_t iSrcSize = strlen(pSrc) + 1;
	if (*pDest==NULL)
	{
		iDestLen=0;
	}
	if (iDestLen!=0)
	{
		if ((int)iSrcSize > iDestLen) return false;
	}
	else
	{
		*pDest=new CHAR[iSrcSize];
	}
	strcpy(*pDest, pSrc);
	iDestLen=iSrcSize-1;
	return true;
}


bool DTCT2A(char **pDest, int &iDestLen, const CHAR *pSrc,const char *pLocale)
{
	assert(pSrc!=NULL);
	size_t iSrcSize =strlen(pSrc) + 1;
	if (*pDest==NULL)
	{
		iDestLen=0;   
	}
	if (iDestLen!=0)
	{
		if ((int)iSrcSize > iDestLen) return false;
	}
	else
	{
		*pDest=new char[iSrcSize];
	}
	strcpy(*pDest, pSrc);
	iDestLen=iSrcSize-1;
	return true;
}

bool DT2ATC(WCHAR **pDest, int &iDestLen, const char *pSrc)
{
	char szLocale[100];
	GetLocaleString(szLocale);
	return DT2ATC(pDest, iDestLen, pSrc, szLocale);
}

bool DTCT2A(char **pDest, int &iDestLen, const WCHAR *pSrc)
{
	char szLocale[100];
	GetLocaleString(szLocale);
	return DTCT2A(pDest, iDestLen, pSrc, szLocale);
}

bool DT2ATC(CHAR **pDest, int &iDestLen, const char *pSrc)
{
	char szLocale[100];
	GetLocaleString(szLocale);
	return DT2ATC(pDest, iDestLen, pSrc, szLocale);
}

bool DTCT2A(char **pDest, int &iDestLen, const CHAR *pSrc)
{
	char szLocale[100];
	GetLocaleString(szLocale);
	return DTCT2A(pDest, iDestLen, pSrc, szLocale);
}

void DTSleep(DWORD dwMilliSecond)
{
	Sleep(dwMilliSecond);
}

int DTATOI(const TCHAR *sInteger)
{
	int iRet=0;
#if defined(UNICODE) || defined(_UNICODE)
	iRet=_wtoi(sInteger);  
#else
	iRet=atoi(sInteger);  
#endif
	return iRet;
}

long DTATOL(const TCHAR *sInteger)
{
	long lRet=0;
#if defined(UNICODE) || defined(_UNICODE)
	lRet=_wtol(sInteger);  
#else
	lRet=atol(sInteger);  
#endif
	return lRet;
}

bool DTToLower(TCHAR *pStr, const char *pLocale)
{
	size_t iLen=_tcslen(pStr);
	std::locale loc(pLocale);
	for (size_t i=0;i<iLen;i++)
	{
		if (isupper(pStr[i],loc))
		{
			pStr[i]=tolower(pStr[i],loc);
		}
	}
	return true;
}

bool DTToUpper(TCHAR *pStr, const char *pLocale)
{
	size_t iLen=_tcslen(pStr);
	std::locale loc("");
	for (size_t i=0;i<iLen;i++)
	{
		if (islower(pStr[i],loc))
		{
			pStr[i]=toupper(pStr[i],loc);
		}
	}
	return true;
}
BOOL DTGetExeFileName(DTString &sFileName)
{
    sFileName.clear();
	TCHAR sAppPath[2048];
	if(GetModuleFileName(NULL, sAppPath, 2047) > 0)
	{
		sFileName.append(sAppPath);
		size_t nn = sFileName.rfind(PATH_SOLIDUS_CHAR);
		if(nn != DTString::npos)
		{
			sFileName.erase(0, nn + 1);  
		}
	}
	else
		return FALSE;
	return TRUE;
}


BOOL DTGetExeFilePath(DTString &sFilePath)
{
	sFilePath.clear();
	TCHAR sAppPath[2048];
	if(GetModuleFileName(NULL, sAppPath, 2047) > 0)
	{
		sFilePath.append(sAppPath);
		size_t nn = sFilePath.rfind(PATH_SOLIDUS_CHAR);
		if(nn != DTString::npos)
		{
			sFilePath.erase(nn + 1);  
		}
	}
	else
		return FALSE;
	return TRUE;
}

BOOL IsFileExist(const DTString& strFilePath, time_t* pLastModifyTime)
{	
	BOOL fRet = FALSE;
	if(NULL == pLastModifyTime)
	{
		if( (_taccess(strFilePath.c_str(), 0 )) == 0) fRet = TRUE;
	}
	else
	{
		fRet=FALSE;
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = FindFirstFile(strFilePath.c_str(), &FindFileData);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			SYSTEMTIME systm;
			if(FileTimeToSystemTime(&(FindFileData.ftLastWriteTime), &systm))
			{
				tm time;
				time.tm_year = systm.wYear - 1900;
				time.tm_mon = systm.wMonth - 1;
				time.tm_mday = systm.wDay;
				time.tm_hour = systm.wHour;
				time.tm_min = systm.wMinute;
				time.tm_sec = systm.wSecond;
				time.tm_wday = systm.wDayOfWeek;

				time_t now, utcnow;
				::time(&now);
				tm tmp;
				if(gmtime_s(&tmp, &now) == 0)
				{
					utcnow = mktime(&tmp);
					time_t duc = now - utcnow;
					*pLastModifyTime = mktime(&time) + duc;
				}
				fRet = TRUE;
			}
			FindClose(hFind);
		}
	}	
	return fRet;
}

int DTNCMPCaseInsensitive(const TCHAR* strLeft, const TCHAR *strRight, int iCount)
{
	int iRet=0;
	if (iCount>0)
	{
		iRet=_tcsnicmp(strLeft, strRight, iCount);
	}
	else
	{
		iRet=_tcsicmp(strLeft, strRight);
	}
	return iRet;
}
