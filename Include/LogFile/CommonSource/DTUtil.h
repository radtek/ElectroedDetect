
#ifndef _INC_DTCOMMONWINUTIL_INCLUDED
#define _INC_DTCOMMONWINUTIL_INCLUDED


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the WINUTIL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// WINUTIL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#include <atlbase.h>
#ifdef DTUTIL_EXPORTS
#define DTUTIL_API __declspec(dllexport)
#else
#define DTUTIL_API __declspec(dllimport)
#endif

#include "dtsignage.h"
#include <map>
using namespace std;

#define ESUTIL_NS_BEGIN namespace esutil{
#define ESUTIL_NS_END }
#define	ESUTIL_NS esutil


const DTString FAKE_PREFIX = _T("tmp_");

const DTString UPDATEIMG_RESULT_LOG_FILE = _T("D:\\boot\\grub\\FirmwareUpdateResult.log");
const DTString UPDATEIMG_FIRMWAREUPDATE_FULLPATHNAME = _T("C:\\Program Files\\WebDT RemoteManager\\Client\\FirmwareUpdate.exe");
const DTString UPDATEIMG_FIRMWAREUPDATE_FILENAME = _T("FirmwareUpdate.exe");
const DTString UPDATEIMG_ERROR_LOG_FILE = _T("D:\\boot\\grub\\errorlog");
const DTString UPDATEIMG_BOOT_FOLDER = _T("D:\\boot\\");
const DTString UPDATEIMG_BOOT_FOLDER_BACKUP = _T("D:\\bootbak\\");
const DTString UPDATEIMG_CHECK_FILE = _T("DTRI\\log\\FileWillBeRemove");
const DTString UPDATEIMG_UPDATE_FLAG_FILE = _T("D:\\boot\\grub\\flagos");

//struct for timezone information
//maliqiang 2008.03.19
struct TIME_ZONE_INFO
{
    LONG Bias;
    LONG StandardBias;
    LONG DaylightBias;
    SYSTEMTIME StandardDate;
    SYSTEMTIME DaylightDate;
    TIME_ZONE_INFO(){
		Bias =0;
		StandardBias=0;
		DaylightBias=0;
		memset(&StandardDate,0,sizeof(SYSTEMTIME));
		memset(&DaylightDate,0,sizeof(SYSTEMTIME));
    }
};
struct TIME_ZONE{
	DTString strTimeZoneName;
	DTString strDisplayName;
	TCHAR daylightName[ 32 ];
	//DTString strDlt;
	DWORD dwIndex;
	DTString strMapID;
	TCHAR standardName[ 32 ];
	//DTString strStd;
	TIME_ZONE_INFO tzi;
	TIME_ZONE(){
		strTimeZoneName = _T("");
		strDisplayName = _T("");
		memset(daylightName,0,32*sizeof(TCHAR));
		dwIndex = (DWORD)-1;
		strMapID = _T("");
		memset(standardName,0,32*sizeof(TCHAR));
	}

	TIME_ZONE(const TIME_ZONE &tz){
		strTimeZoneName = tz.strTimeZoneName;
		strDisplayName = tz.strDisplayName;
		_tcscpy(daylightName,tz.daylightName);
		dwIndex = tz.dwIndex;
		strMapID = tz.strMapID;
		_tcscpy(standardName,tz.standardName);
		tzi=tz.tzi;//fix the bug 19034,added by Maliqiang 2009.02.12
	}
	//overload operator "=", maybe fix the bug 18780
	//added by Maliqiang 2009.02.03
	TIME_ZONE& operator=(const TIME_ZONE &tz){
		strTimeZoneName = tz.strTimeZoneName;
		strDisplayName = tz.strDisplayName;
		_tcscpy(daylightName,tz.daylightName);
		dwIndex = tz.dwIndex;
		strMapID = tz.strMapID;
		_tcscpy(standardName,tz.standardName);
		tzi=tz.tzi;//fix the bug 19034,added by Maliqiang 2009.02.12
		return *this;
	}
	
};
struct MAC_IP_INFO
{
	DTString strIp;
	DTString strMac;
	BOOL bWireless;
};

struct WIFI_INFO 
{
	DTString ssid;
	DTString key_material;
};


struct IPPORT
{
	DTString ip;
	DTString port;
};
struct OBJECT_INFO
{
	int nObjectId;
	int nObjectType;
	DTString strExtension;
	DTString strLastModifyTime;
	time_t timeLatModifyTime;

	int nFlag;//one flag. you can use it  according your need.

	OBJECT_INFO& operator=(const OBJECT_INFO &object_info)
	{
		nObjectId = object_info.nObjectId;
		nObjectType = object_info.nObjectType;
		strExtension = object_info.strExtension;
		strLastModifyTime = object_info.strLastModifyTime;
		timeLatModifyTime = object_info.timeLatModifyTime;
		nFlag = object_info.nFlag;
		return *this;
	}
};

struct DOWNLOAD_STATUS
{
	DWORD dwType;
	DWORD dwId;
	DWORD dwStatus;
	DWORD dwTotal;
	DWORD dwCompleted;
};

ESUTIL_NS_BEGIN
// Get the folder of "My Document"
// "C:\Documents and Settings\UserName\My Documents"
// where UserName is the name of current user, and the actual drive may not be "C:"
DTUTIL_API BOOL GetMyDocumentFolder(DTString& wsPathName, LPCWSTR pwszAppName = NULL);
DTUTIL_API BOOL GetAppDataFolder(DTString& wsPathName, LPCWSTR pwszAppName = NULL);
DTUTIL_API BOOL IsFileExist(const DTString& strFilePath, time_t* pLastModifyTime = NULL);
DTUTIL_API DTString GetFileExtent(const DTString& strFilePath);

//similar to the api GetModuleFileName, but only return the folder path, end by '\'
DTUTIL_API BOOL GetModuleFilePath(HMODULE hMod, DTString& path);

//a wrapper of GetDiskFreeSpaceEx
//get free space of a disk which contains the passed path, 
	//if the path is empty, get free space of the disk wich contains "Documents and Settings" directory 
//return value is in MB unit
DTUTIL_API DWORD ESGetDiskFreeSpace(const DTString& strOnePath, DWORD dwKeptMB = 3, BOOL fKBUnit = FALSE);

DTUTIL_API BOOL IsThereUSBDisk();

DTUTIL_API time_t  local_time(time_t *local_timer);

//convert between time_t and local time string
DTUTIL_API void  Time2StringLocal(time_t time, DTString& strTime);
DTUTIL_API time_t  String2TimeLocal(const DTString& strTime);

//convert between time_t and GMT time string
//add when fix bug20300  Jeff 2009.8.28
DTUTIL_API void  Time2StringGMT(time_t time, DTString& strTime);
DTUTIL_API time_t  String2TimeGMT(const DTString& strTime);



//synchronize the time with the time server
//serverHost is the host name of the time server
//return TRUE is success


#if 0
DTUTIL_API BOOL ReadFile2Str(LPCWSTR pwszFilePath, std::wstring& wsStr);
DTUTIL_API BOOL WriteStr2File(LPCWSTR pwszFilePath, LPCWSTR pwszStr);
#endif

DTUTIL_API BOOL TestandCreateDirectory(const DTString& strPath);
DTUTIL_API int DeleteDirectory(const DTString& strDir, BOOL fRecursiveIfFailed = FALSE);
DTUTIL_API int DeleteFiles(const DTString& strDir, const DTString& strFileName, BOOL fRecur = TRUE);
DTUTIL_API int DeleteDirectoryRecur(const DTString& strDir);

//search the dirctory strDir, and return all the file paths whose ext name is strExt.
//    if want to find all files pass strExt as "*"
//if you want exclude some folders, pass the folder names into pExcludeFolders
//if you want exclude some files, pass the file names into pExcludeFiles
//the returned files paths are put into files
//fRecur indicate whether should search all sub direcotries or not
//the caller should never pass the parameters fFirst (make it always true)
//return the number of the found files
//2008.10.9  Jeff
DTUTIL_API int FindFiles(const DTString& strDir, const DTString& strExt, BOOL fRecur, 
						 vector<DTString>& files, 
						 vector<DTString>* pExcludeFolders = NULL, vector<DTString>* pExcludeFiles = NULL,
						 BOOL fFirst = TRUE);

//get the last USB disk (type is DRIVE_REMOVABLE), the output path contains the back slash,for example: "e:\"
//if there is error, return value < 0
//if there is not any USB disk, return 1
//return 0 if successful
//2007.11.5  Jeff
DTUTIL_API int GetLastRemoveableDisk(DTString&  strPath);


#define  ZIP_FILE		2
#define  ZIP_FOLDER	4
DTUTIL_API BOOL CompressFiles(const std::vector<DTString>& strInputFiles, const DTString& strOutFile, UINT unFlag = ZIP_FILE, DWORD* pOutErrCode = NULL);

//a wrapper of API FlushFileBuffers
DTUTIL_API BOOL ForceFileContentToDisk(const DTString& strFile);

//pass hFileHandle NULL if get version of the exe file
//return FALSE indicate there isnot version information
DTUTIL_API BOOL GetProductVersion(DTString *psFullPathFileName, DTString& strVersion, BOOL f4BAlign = TRUE);
DTUTIL_API BOOL GetWholeProductVersion(DTString *psFullPathFileName, DTString& strVersion, DTString sHeaderNumber, BOOL f4BAlign = TRUE);

/*
the version string:a1a2a3a4.b1b2b3b4.c1c2c3c4.d1d2d3d4
when a player receives a broadcast message from one edge server:
1. if d1 is different, return FALSE, otherwise goto step2
2. compare a1a2a3a4 and d1d2d3d4, if the value of strVersion is less than what of the player, return FALSE, otherwise, goto step3
This means current can only accept the remote which version is equal to or above current's.
3. return TRUE

Parameters: 
version: The current player/es version. Should be get from esutil::GetProductVersion().
strVersion: The version got from broadcast message which indicates a remote ES's version.
Return Values:
TRUE: if version is less or equal to strVersion. Otherwise, FALSE
*/
DTUTIL_API BOOL CheckProductVersion(const DTString& version, const DTString& strVersion);

/*
@FunctionName:ES_ITOA
@Description:convert DWORD to DTString 
@Parameters:dwID,(in)
@ReturnValue: the string value of dwID
*/
DTUTIL_API DTString ES_ITOA(DWORD dwId) ;

/*
@FunctionName:ES_ATOI
@Description:convert DTString to DWORD
@Parameters:strID,(in)
@ReturnValue: the DWORD value of strID
*/
DTUTIL_API DWORD  ES_ATOI(DTString strId) ;

//share the passed folder wrapper of the api function NetShareAdd
//value of dwSharePermission:ACCESS_READ, ACCESS_WRITE, etc.
//2007.11.5  Jeff
//DTUTIL_API int ShareFolder(const DTString&  strPath, const DTString& strShareName, DWORD dwSharePermission);

DTUTIL_API BOOL SetProxySetting(const DTString& proxyList,const DTString& bypassList = _T(""));

/*
	Parameter: nFlag
	0 (when getting MAC or IP,we don't enable the disabled wired NIC)
	1 (when getting MAC or IP,we first enable the wired NIC which is disabled; after getting MAC or IP,then disable it again)

	the parameter "nFlag" is suitable for the functions "GetMAC()","GetIPAdress()" and "GetAllMACAndIP()".
	//modified by maliqiang 2008.05.06
*/
DTUTIL_API void GetMAC(std::vector<DTString> &macs,int nFlag = 1, bool bUseWirelessMacWiredLost = true, bool bUseVirtualMacWiredLost = true);

DTUTIL_API void GetIPAdress(DTString& ip, int nFlag = 1);

DTUTIL_API void GetAllMACAndIP(std::vector<MAC_IP_INFO> &MacsAndIps,int nFlag = 1);//Get all macs and ips

#define GIP_WIRED		1
#define GIP_WIRELESS	2
DTUTIL_API void GetIPAddressWithPriority(DTString& ip, int nFlag, int priority = GIP_WIRED);

//get pure host name or ip address from one URL string
//for example:
// if strURL = "http://192.168.0.2/ps" or "http://192.168.0.2/ps"					then strRet = "192.168.0.2"
// if strURL = "http://192.168.0.2:888/ps" and fWithPort=true						then strRet = "192.168.0.2:888"
// if strURL = "http://192.168.0.2:888/ps" and fWithPort=false						then strRet = "192.168.0.2"
// if strURL = "www.dtri.com/index"													then strRet = "www.dtri.com"
// if strURL = "www.dtri.com/index?...."											then strRet = "www.dtri.com"
// if strURL = "www.dtri.com/index;JESSIONID=...."									then strRet = "www.dtri.com"
//2009.2.19  Jeff
DTUTIL_API void GetIPAndPortFromURL(const DTString& strURL, DTString& strRet, DTString &strPort, const DTString &strDefaultPort=_T("80"));

DTUTIL_API int GetLocalTime(DTString& strLocalTime);

DTUTIL_API int GetScreenRotationMode();//get screen rotation mode

/*
	Function: get the time zone information by time zone index
	Return: 0(successful),or -1(failed)
	Record: 1.added by maliqiang 2008.07.14
*/
DTUTIL_API int GetTimezoneInfo(DWORD dwTimezoneIndex,TIME_ZONE & time_zone);

//This function return the time zone index of the current timezone setting.
//maliqiang 2008.03.18
DTUTIL_API DWORD GetCurrentTimezoneIndex();
//set the system time zone
//maliqiang 2008.03.20
DTUTIL_API int SetTimeZone(DWORD dwIndex);
//synchronize time
//parameter:1.strTimeServer (time server,format as:"time.nist.gov");2.nPort (port number,used for communicate with time server,such as "37")
//maliqiang 2008.03.25
//DTUTIL_API int SynchronizeTime(DTString strTimeServer,int nPort);
//unzip folder
//maliqiang 2008.03.31
DTUTIL_API BOOL UnzipFile(const DTString& zipfilePath, const DTString& unzipFolder,DWORD dwFlag);
//Function: check if the given file is OS's wallpaper.
//Return: TRUE(OS's wallpaper),FALSE(not OS's wallpaper)
//maliqiang 2008.04.24
DTUTIL_API BOOL CheckIsOSWallpaper(DTString strFileName);
//set OS desktop wall paper with given picture
//maliqiang 2008.06.04
DTUTIL_API BOOL SetOsWallPaper(DTString strWallPaper);
/*Start a process by command line 
params: cmdline:input,command line to execute
        hprocess:output, if success, handle of the new created process
        pPID:output, if not NULL, return the new created process id.
*/
DTUTIL_API int StartProgram(const DTString &cmdline, HANDLE &hprocess, DWORD* pPID = NULL, bool bWait = false);

/**Start a process by command line, this process CANNOT terminated by TerminateProcess() or from TaskManager
until it stops normally.
params: cmdline:input, command line to execute
		phProcess:output, handle of process, optional
		pPID:output, ID of process, optional
*/
DTUTIL_API int StartUnterminatedProgram(const DTString &cmdline, PHANDLE phProcess = NULL, PDWORD pPID = NULL);
/*Restart os system
params: None
*/
DTUTIL_API BOOL RestartOSSystem();


/*Get the type of current player 
params: 
return value: 1-DTPlayer
              2-EdgeServer
			  other-illegal
*/
#define		WCM_PLAYER			1
#define		WCM_EDGESERVER		2
DTUTIL_API int GetPlayerType(); 
/*Synchronize time with time server, this is the final synchronizing function 
params: sIP:input, IP address of time server
        fSynchronizeDiff:input,synchronize time  only when time difference is greater than this value. Default is 0.0    
return value: true-Success
              false-failure
*/

DTUTIL_API bool SynchronizeTimeNew(const DTString &sIP, float fSynchronizeDiff = 0.0);

/*Get the handle of a process by its executive name 
params: szProcessName: input,the executive name
return value: handle of process.
              NULL if fail
*/
DTUTIL_API HANDLE GetProcessHandle(const TCHAR* szProcessName);

extern "C" DTUTIL_API HINSTANCE GetDtrApiHandle();

/*Get the language id of the current system
params: m_langId:out, Language id, m_sLangid:out, string corresponding to language id
return value:always return 0.
*/
//DTUTIL_API DTString GetLangID();
/*Get a file name with full path, this file is a temp file during downloading.
params: realname: input, the real name after file is downloaded.
return value: temp file name during downloading.
              empry if fail
*/
DTUTIL_API DTString ProduceFakeName(const DTString& realname);
/*
	Function: Get wired NIC status, Disabled or Enabled
	Return: -1(error), 0(Disabled), 1(Enabled)
	Record: 1. added by Maliqiang 2008.04.29
*/

    /*
    @FunctionName:RemoveAllFilesInAFolder
    @Description:Remove all files in a folder with full path.
    @Parameters:sFolderPath:(in)the folder path 
    @ReturnValue:0-Success
                -1-fail to delete files in folder
    */
DTUTIL_API    int RemoveAllFilesInAFolder(const DTString &sFolderPath);
    /*
    @FunctionName:RemoveAFolderN
    @Description:another function to remove a folder. The folder may has many sub-folders.
    @Parameters:sFolderPath:(in)the folder path 
    @ReturnValue:0-Success
                -1-fail to delete files in folder
			    -2-fail to delete a folder
			    -4-fail to set attribute of a folder
    */
DTUTIL_API    int RemoveAFolderN(const DTString &sFolderPath);
DTUTIL_API int CreateFlagFile(const DTString &sFileName);
DTUTIL_API bool CheckIfItself(const DTString &sIP);

DTUTIL_API const short GetWiredNetworkAdapterStatus();
DTUTIL_API bool ScanForHardwareChange();
DTUTIL_API const bool DoesNetCardExist();
DTUTIL_API DWORD getWiredNICStatus();

/*
	Function: Enable wired NIC
*/
DTUTIL_API BOOL EnableWiredNIC();

/*
	Function: Disable wired NIC
*/
DTUTIL_API BOOL DisableWiredNIC();

/*
	Function: parse the given string strUC ,then get the urgent cast detail info. then save the detail info to map "m_UCDetail"
	parameter:m_UCDetail (key --->urgent cast id,value --->last modified time)
		    strUC (formated as: "34|2008-05-21 15:03:45,36|2008-05-21 17:03:45,38|2008-05-21 19:03:55")
*/
DTUTIL_API void GetUrgentCastDetail(std::map<DWORD,time_t> &m_UCDetail,DTString strUC);


DTUTIL_API BOOL EncryptString(const DTString& strInput, DTString& strOutput);
DTUTIL_API BOOL DecryptString(const DTString& strInput, DTString& strOutput);
DTUTIL_API int SimpleEncrypt(const char *szInPass, char *szOutPass, int len);
DTUTIL_API int SimpleDecrypt(const char* szInPass, char* szOutPass, int len);
DTUTIL_API BOOL EncryptStringMD5(const DTString& strInput, DTString& strOutput);
DTUTIL_API BOOL EncodeTxtFileByLinesMD5(const DTString& strInFile, const DTString& strOutFile);
DTUTIL_API BOOL EncodeBinFileMD5(const DTString &strInFile,DTString &MD5Code,
								 int nAdditionalDataLen = 0, unsigned char* pAdditionalData = NULL);

//convert a string to another string which is an array of char values seperated by ','
//for example, 
//convert "ljf" to "108,106,102,"
//convert "123<汗渍>\abc" to "49,50,51,60,27735,28173,62,92,97,98,99,"
//2009.2.25  Jeff
DTUTIL_API BOOL EncodeString2Digit(const DTString& strInput, DTString& strOutput);
DTUTIL_API BOOL DecodeDigit2String(const DTString& strInput, DTString& strOutput);


DTUTIL_API int StopService(const DTString& strServiceName, BOOL fWait = FALSE, BOOL fRestart = FALSE);
DTUTIL_API DWORD GetServiceStatus(const DTString& strServiceName);
DTUTIL_API BOOL ShutdownSystem();//shutdown the system

// This function will first get the handle of playerutil module or edgeserverutil module.
// Then call the corresponding functions of playerutil or edgeserverutil.
DTUTIL_API BOOL GetRegistryString(TCHAR* subSection, const TCHAR* key, DTString& strValue, TCHAR* lcmSection = NULL);
DTUTIL_API UINT GetRegistryInt(	TCHAR*		subSection,		
									const TCHAR*		key,
									UINT		defaultValue,
									TCHAR*  lcmSection = NULL,
									BOOL*	pfExist = NULL);
DTUTIL_API BOOL SetRegistryInt(TCHAR*		subSection,	
								 const TCHAR*		key,
								 DWORD		dwValue);
DTUTIL_API BOOL SetRegistryString(TCHAR*		subSection,		
									const TCHAR*		key,
									const DTString&		strValue); 
DTUTIL_API BOOL GetWorkFolder(DTString& sRet);
DTUTIL_API BOOL GetLibFolder(DTString& sRet);

// Check whether strUrl in no-proxy-list or not. The out-parameter fInNoProxy shows the result.
// Return 0 means success, -1 means fail.
// Before compare, the function will trim the strUrl to remove all before :// and after : or /
// Then compare only ip or host whether in no-proxy-list or not.
// Example: no-proxy-list: "1.2.3.4; 11.11.11.11;" Url: "https://1.2.3.4:8080/abcd/efgh/a.jpg"
// Result is TRUE;
DTUTIL_API int CheckByPass(const DTString &strUrl, BOOL &fInNoProxy);


// Check the response code has ES failure information or not.
// If the failure information exist, return true, otherwise, false instead.
// The parameter nHttpCode is valid only the function return a TRUE value. Otherwise, it's meaningless.
// At present, the error node is different from error code key. Example: <esHeartbeatCGIResponse siteId="50000" playerId="50000" code="2086" localIp="169.254.202.254" >
DTUTIL_API BOOL CheckIfESFailure(const DTString& strResponse, const DTString& strErrorNodeKey, const DTString& strErrorCodeKey, int& nHttpCode);
// Check the response code has PS failure information or not.
// If the failure information exist, return true, otherwise, false instead.
// The parameter nHttpCode is valid only the function return a TRUE value. Otherwise, it's meaningless.
// At present, the error node key is the same as error code key. Example: __$$dtdownloaderrorcode$$__:23.
DTUTIL_API BOOL CheckIfPSFailure(const DTString& strResponse, const DTString& strErrorNodeKey, const DTString& strErrorCodeKey, int& nHttpCode);

//Function Name:SetRemoteDesktop
//Parameters:nFlag (0--disable Remote Desktop,1--enable Remote Desktop)
//return:TRUE--success
//		 FALSE--fail
//Description:Enable or Disable OS's Remote Desktop property
DTUTIL_API BOOL SetRemoteDesktop(int nFlags = 0);

//Function Name:GetRemoteDesktopStatus
//Parameters:nFlag (in/out)
//return:TRUE--success
//		 FALSE--fail
//Description:Get OS's Remote Desktop status
DTUTIL_API BOOL GetRemoteDesktopStatus(int &nFlag);


//*************************************************used specially for WebDT Signage Player  Start********************************

//Function Name:GetPreloadMediaDetail
//Parameters:
//			strPreloadMedia (Strings which includes preload media info, 
//							formated as "ptype,Objectid,objecttype, lastmodifytime | ptype,objectid,objecttype, lastmodifytime")
//			vMediaDetail (it includes OBJECT_INFO variables
//								struct OBJECT_INFO
//																{
//																	int nObjectId;
//																	int nObjectType;
//																	DTString strExtension;
//																	DTString strLastModifyTime;
//																	int nFlag;//one flag. you can use it  according your need.
//																}
//								save ptype to OBJECT_INFO.nFlag.
//return:no
//Description:get preload media detailed info,
DTUTIL_API void GetPreloadMediaDetail(DTString strPreloadMedia,vector<struct OBJECT_INFO> &vMediaDetail);

//get uc logo information parse String "mediaId|extension|lastmodifytime"
DTUTIL_API int GetUCLogoDetail(DTString strUCLogo,OBJECT_INFO &object_info);
DTUTIL_API int ESBeep(DWORD dwMilliseconds, DWORD dwFreHz = 500);
DTUTIL_API void GetSystemImageBuildVersion(DTString& version);

//get EDID of the display monitor
DTUTIL_API BOOL GetMonitorType(DTString& type);

//before/after do autoregister, call the below two functions
DTUTIL_API void BeforeAutoregister();
DTUTIL_API void AfterAutoregister();
//check if the player/edgeserver is autoregistering or not
DTUTIL_API BOOL IsAutoregistering();

DTUTIL_API int SelectBestURL(const std::vector<IPPORT> items, DTString& strURL);


//*************************************************used specially for WebDT Signage Player  End********************************


/*
//Zhangxq Mar 11, 2009 
//Add some functions about disk/folder protection.

//Function Name: ProtectVolume
//Parameters:  sDisk, in, e.g. _T("C:"),_T("C:\\")
//             bReallyDo, out, if protected volume actually, this variable is true, in this case, os should restart to let modification take effect, otherwise, false.
//             bRebootAfterSet, in, default false. if true, after protect volume, reboot os.
//return: true-success false-failure.
//Description: This function is used to protect the whole disk, if disk has been protected, still return true, but paremeter bReallyDo will be false.
DTUTIL_API bool ProtectVolume(const DTString &sDisk, bool &bReallyDo, bool bRebootAfterSet=false);
//Function Name: UnprotectVolume
//Parameters:  sDisk, in, e.g. _T("C:"),_T("C:\\")
//             bReallyDo, out, if protected volume actually, this variable is true, in this case, os should restart to let modification take effect, otherwise, false.
//             bRebootAfterSet, in, default false. if true, after protect volume, reboot os.
//return: true-success false-failure.
//Description: This function is used to unprotect the whole disk, if disk has been unprotected, still return true, but paremeter bReallyDo will be false.
DTUTIL_API bool UnprotectVolume(const DTString &sDisk, bool &bReallyDo, bool bRebootAfterSet=false);
//Function Name: IsVolumeProtected
//Parameters:  sDisk, in, e.g. _T("C:"),_T("C:\\")
//return: true-protected false-unprotected.
//Description: This function is used to check the protection option of a disk.
DTUTIL_API bool IsVolumeProtected(const DTString &sDisk);
//Function Name: IsFolderProtected
//Parameters:  sFolder, in, full path string. e.g. _T("C:\\aaa\\bbb\\ccc"),_T("C:\\aaa\\bbb\\ccc\\")
//return: true-protected false-unprotected.
//Description: This function is used to check the protection option of a folder. if the folder parameter is a disk string, call function IsVolumeProtected directly.
DTUTIL_API bool IsFolderProtected(const DTString &FullPath);
//Function Name: IsFilterEnabled
//Parameters:  None
//return: true-enabled false-disabled.
//Description: This function is used to check if filter option is opened or not.
DTUTIL_API bool IsFilterEnabled();
//Function Name: UnprotectFolder
//Parameters:  sFullPath, in, ,full path string. e.g. _T("C:\\aaa\\bbb\\ccc"),_T("C:\\aaa\\bbb\\ccc\\")
//             bReallyDo, out, if unprotected folder actually, this variable is true, in this case, os should restart to let modification take effect, otherwise, false.
//             bRebootAfterSet, in, default false. if true, after unprotect folder, reboot os.
//return: true-success false-failure.
//Description: This function is used to unprotect a folder, if folder has been unprotected, still return true, but paremeter bReallyDo will be false.
//             if the folder parameter is a disk string, call function UnprotectVolume directly.  
DTUTIL_API bool UnprotectFolder(const DTString &sFullPath, bool &bReallyDo, bool bRebootAfterSet=false);
//Function Name: ProtectFolder
//Parameters:  sFullPath, in, ,full path string. e.g. _T("C:\\aaa\\bbb\\ccc"),_T("C:\\aaa\\bbb\\ccc\\")
//             bReallyDo, out, if protected folder actually, this variable is true, in this case, os should restart to let modification take effect, otherwise, false.
//             bRebootAfterSet, in, default false. if true, after protect folder, reboot os.
//return: true-success false-failure.
//Description: This function is used to protect a folder, if folder has been protected, still return true, but paremeter bReallyDo will be false.
//             if the folder parameter is a disk string, call function ProtectVolume directly.  
DTUTIL_API bool ProtectFolder(const DTString &sFullPath, bool &bReallyDo, bool bRebootAfterSet=false);
*/
//add several utility functions about display device  2009.5.21  Jeff
	//fOnlyConnecting=false return the max number of the display output (max screens which can be connected with this machine)
	//fOnlyConnecting=true return the number of the screen being used (Number of display monitors on the desktop)
DTUTIL_API int GetDisplayScreenNum(bool fOnlyConnecting = false);
	//return the display card number connected currently
	//return -1 means error
DTUTIL_API int GetDisplayAdapterNum();

DTUTIL_API bool GetWholeScreenResolution(int& width, int& height);
DTUTIL_API bool GetPrimaryScreenResolution(int& width, int& height);

DTUTIL_API time_t FileTimeToGMT(LPFILETIME pft);
DTUTIL_API time_t GetFileModifyTime(const DTString& filename, DWORD *pdwErrCode);
DTUTIL_API void GMTToFileTime(time_t t, LPFILETIME pft);
DTUTIL_API bool RefreshModifyTime(const DTString& filename, time_t modtime); 
//////////////////////////////////////////////////////////////////////////
// Used for screen rotation/resolution

DTUTIL_API int ScreenRotate(int rotation, int width, int height);
DTUTIL_API int CheckOrApplyScreenSettings(const DTString& file);
DTUTIL_API bool GetCurrentScreenSettings(int& rotation, int& width, int& height);
//////////////////////////////////////////////////////////////////////////
//Zhangxq Sep 23, 2009 for bug 23550
//add this function to conver the url to an uniform style before save into configuration file.
DTUTIL_API enum URL_TYPE {utPS};
DTUTIL_API DTString FormatURL(URL_TYPE urlType, const DTString &sURL);
//Zhangxq Oct 15, 2009
//Check if it's time to updating a patch.
DTUTIL_API BOOL IsPatchUpdating();

// Makes a case-sensitive comparison of two url strings.
// Return true if two strings are the same, apart from a trailing '\' character if fIgnoreSlash is set to TRUE.
// Otherwise, return false.
DTUTIL_API bool IsSameUrl(const DTString& url1, const DTString& url2, BOOL fIgnoreSlash = TRUE);

// If URL has no scheme information, set HTTP as default
// for bug 21582, 2009.9.9, yantao
DTUTIL_API void CheckAndAddUrlScheme(DTString &strPSUrl);

DTUTIL_API int SplitString(const DTString sSrc, DTString sDel, DTString *pString);

DTUTIL_API BOOL IsNumberCode(char ch);

DTUTIL_API void Log(LPCWSTR pwszStr, ...);
DTUTIL_API void Log2File(const TCHAR *strLog, BOOL fWithTime);
DTUTIL_API int GetFileSize(const DTString sFile);
//sTitle(in)-浏览对话框中的提示文字 
//sFolder(out)--用户选择的目录
DTUTIL_API BOOL SelectAFolder(const DTString &sTitle, DTString &sFolder);
DTUTIL_API void SplitAMsgStr(const DTString &sStr, std::vector<DTString> &v_Item, std::vector<DTString> &v_Value);

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

//#define		 LOG_INFO			2
//#define		 LOG_WARN			1
//#define		 LOG_ERR			0
//#define		 LOG_FORCE			0
//
//#define  DEBUGLOG_EVENT_NAME		_T("Global\\__DTESDEBUGLOGEVENT__")
//#define  NORMALLOG_EVENT_NAME		_T("Global\\__DTESNORMALLOGEVENT__")
//
//class DTUTIL_API CAPPLog
//{
//	public:
//		static void Log(int nLogLevel, LPCWSTR pwszStr, ...);
//		static void Log(int nLogLevel, const char *pszStr, ...);
//		//static void Log(int nLogLevel, LPCWSTR pwszStr, va_list);
//		//static void Log(int nLogLevel, const char *pszStr, va_list);
//		static void Log(const char *pszStr, int nLogLevel = LOG_INFO, BOOL fWithTime = TRUE);
//		static void Log(LPCWSTR pwszStr, int nLogLevel = LOG_INFO);
//		static void DumpBinData(const unsigned char *buf, int size, int nLogLevel = LOG_INFO);
//		static void SetLogFile(const char *pszPath, BOOL fDefaultSet = FALSE);
//		static void GetDefaultLogFolder(DTString& folder);
//		static void SetLogLevel(int nLevel);
//		static void SetMaxLogFileSize(DWORD dwSize);
//		static void SetFlushOption(const DTString& strRAMDisk, DWORD dwFlushInterval);
//		static void ForceFlushLogOnRAMDisk();
//	protected:
//		CAPPLog(){};
//		~CAPPLog(){};
//		static void Log2File(const char *strLog, BOOL fWithTime = TRUE);
//		static void CheckRAMDisk();
//		static FILE* GetFileHandle();
//		static FILE* GetRAMFileHandle();
//		static BOOL CreateOldFile(FILE** ppLogFile);
//		static void CreateOneLog();
//		static DWORD WINAPI WatchFlushEvent(void* p);
//		//Zhangxq Aug 05, 2008
//        static DTString GetFileNameInTempPath();
//		static time_t GetLastFlushTime();
//		static void SetLastFlushTime(time_t &flushtime);
//	private:
//		static int   s_nLogLevel;
//
//		//max size of one log file, the unit is KB
//		static DWORD s_dwMaxFileSize;
//		static char* s_pstrLogFile;
//		static char* s_pstrRAMLogFile; //the path which under a RAM disk
//		static DTString s_strRamDisk;
//		static HANDLE  s_hFlushEvent;
//		static DWORD  s_dwFlushIntervalMin;
//		static HANDLE s_hLogMutex;
//		//Zhangxq Aug 05, 2008
//		//save the execute file name, this name will create a key in registry.
//		static DTString s_strExeName;
//};

#endif