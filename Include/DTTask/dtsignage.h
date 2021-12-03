/*****************************************************************************
* File:		DTSinage.h
*
* Purpose:  DT General definition used in DT E-Sinage Client.
*
* Author:	Cavan Joe
*
* Created:	2007-02-26
*
* Updated:  2007-10-30 Cavan
*
* Home:		http://www.dtri.com/
*
* History:
* 2007-11-21 Cavan Joe
* Add "DTMOTYPE" definition.
*
* COPYRIGHT(C) 1995-2008 DT RESEARCH,INC. ALL RIGHTS RESERVED.
*****************************************************************************/
#ifndef _DTSINAGE__
#define _DTSINAGE__

#pragma once

///Import general neutral C++ definition
#include <tchar.h>
#include "DTDefine.h"

///Here we import platform information
#ifdef WIN32
#ifndef _WINDOWS_
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif
#define PATH_SOLIDUS_CHAR _T('\\')
#define PATH_SOLIDUS_STR _T("\\")
#else
#include "dtwintype.h"
#define PATH_SOLIDUS_CHAR _T('/')
#define PATH_SOLIDUS_STR _T("/")
#endif
#define	USE_DTMSGQUEUE	TRUE

//////////////////////////////////////////////////////////////////////////////
///The Program Publish Client will issue message DTWM_PUBLISHREADY message to
///DT Media Player that a new publish occur.
#define DTWM_PUBLISHREADY	WM_USER+1

///WPARAM
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///|8bits DTPOMEDIATYPE|1bit disk space flag|3bits(DTPO_PUBLISH or DTPO_PREVIEW)|20bits duration|
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum _tagPublishObjectMediaType
{
    DTPO_INVALID	         =	0,	///<RESERVED! It represents invalid publish type.
	DTPO_MINIMUM	         =	0,	///<RESERVED! It represents minimum publish type.
    DTPO_PROGRAM	         =	1,	///<The new publish/preview is PROGRAM
	DTPO_UTK		         =	2,	///<The new publish/preview is URGENT CAST
    DTPO_PLAYLIST	         =	3,	///<The new publish/preview is PLAYLIST
	DTPO_RESERVED	         =	4,	///<NOT USED!!! DONOT USE.    
    DTPO_TICKER	             =	5,	///<The new publish/preview is TICKER    
    DTPO_WEBSERVICE	         =	6,	///<The new publish/preview is DYNAMIC OBJECT
    DTPO_SCHEDULE	         =	7,	///<The new publish/preview is SCHEDULE
    DTPO_LOCALIMAGE          =  8,  ///<The new publish/preview is LOCAL IMAGE
    DTPO_REMOTEIMAGE         =  9,  ///<The new publish/preview is REMOTE IMAGE
    DTPO_LOCALSOUND          =  10, ///<The new publish/preview is LOCAL SOUND
    DTPO_REMOTESOUND         =  11, ///<The new publish/preview is REMOTE SOUND
    DTPO_LOCALMULTIMEDIA     =  12, ///<The new publish/preview is LOCAL OBJECT
    DTPO_REMOTEMULTIMEDIA    =  13, ///<The new publish/preview is REMOTE OBJECT
    DTPO_LOCALREALTIMEVIDEO  =  14, ///<The new publish/preview is LOCAL REAL TIME VIDEO
    DTPO_REMOTEREALTIMEVIDEO =  15, ///<The new publish/preview is REMOTE REAL TIME VIDEO
	DTPO_TVTUNNER			 =  16, ///<The new publish/preview is TV TUNNER
	DTPO_EXECUTABLE			 =	17, ///<The new publish/preview is EXECUTABLE MEDIA
	DTPO_MULTIFILE			 =	18, ///<The new publish/preview is MULTIPLE-FILE MEDIA
	DTPO_COMBOLIST			 =	19, ///<The new preview/default is COMBOLIST
	DTPO_SLIVERLIGHT		 =	20,	///<The new publish/preview is SliverLight  
	DTPO_MAXIMUM	         =	21	///<RESERVED! It represents maximum publish type.

}DTPOMEDIATYPE;

//special type used for preload sysimage and update patch
//2009.1.23  Jeff
#define			DTPO_SYSIMAGE				1000
#define			DTPO_PLAYERPATCH			1001


//definition of different type player
//how to calculate the number:
//	macro name--->md5-->add every char-->*111+3
//2009.4.27  Jeff
#define			DT_LEGAL_PLAYER				207906	 //after liscense check passed, this player can be this type
#define			DT_PREVIEW_PLAYER			205686	//only can play preview tasks
#define			DT_PCEVAL_PLAYER			202578		
#define			DT_PC_CLIENT				214122  //only can play uc
#define			DT_TRIAL_PLAYER				205353		
#define			DT_OFFLINE_TOOL				207795		


typedef enum _tagPublishObjectType
{
    DTPO_PUBLISH    = 0x01, ///<It is normal PUBLISH
    DTPO_PREVIEW    = 0x02  ///<It is PREVIEW
}DTPOTYPE;

#define GET_POMEDIATYPE(WParam) ((WParam & 0xFF000000) >> 24)
#define OUT_OF_SPACE_MASK		0x00800000
#define OUT_OF_ES_SPACE_MASK	0x00400000
#define IS_OUT_OF_SPACE(WParam) (1 == ((WParam & OUT_OF_SPACE_MASK) >> 23))
#define IS_OUT_OF_ES_SPACE(WParam) (1 == ((WParam & OUT_OF_ES_SPACE_MASK) >> 22))
#define GET_POTYPE(WParam)      ((WParam & 0x00300000) >> 20)
#define GET_DURATION(WParam)    (WParam & 0x000FFFFF)

///LPARAM
///+++++++++++++++++++++
///|32bits MEDIA ID    |
///+++++++++++++++++++++

//////////////////////////////////////////////////////////////////////////////
///Some notice need DTPlayer cooperation
#define DTWM_NOTICEPLAYER WM_USER+2
///WPARAM
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///|8bits DTPOMEDIATYPE|16bits reserved            | 8bits DTNOTICEID        |
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum _tagNoticeID
{
    ///Do nothing, reserved.
    DTNOTIFY_NORMAL             = 0x00,
    ///Clear all schedule, preview, urgent ticker, everything. LPARAM - NA
    DTNOTIFY_CLEAR              = 0x01,
    ///Remove program. LPARAM - 32 bits program ID
    DTNOTIFY_CLEARSCHEDULE      = 0x02,
    ///The running hardware is not DT. LPARAM - NA
    DTNOTIFY_PIRACY             = 0x03,
    ///DTMP will clear current log files when site change. LPARAM - NA
    DTNOTIFY_SITECHANGE         = 0x04,
    ///The message notice DTMP to show or hide mouse cursor.LPARAM - 1 to show
    ///cursor or 0 to hide cursor
    DTNOFITY_MOUSECURSOR        = 0x05,
    ///The message notice DTMP show downloading tip. The highest 8bits WPARAM 
    ///is DTPUBLISHTYPE. LPARAM is the 32bits Media ID.
    DTNOTIFY_DOWNLOADTIP        = 0x06,
    ///Clear downloading tips. The highest 8bits WPARAM is DTPUBLISHTYPE;
	///LPARAM is the 32bits Media ID; if the Media ID is -1, then all download
	///tips are removed.
    DTNOTIFY_CLEARDOWNLOADTIP   = 0x07,
	///Inform the render the default play list or new wall paper
	DTNOTIFY_DEFAULTPLAYLIST	= 0x08,
	///Inform the render to clean up default play list or new wall paper
	DTNOTIFY_CLEARDEFAULT	= 0x09,
	///Inform the render stop playing urgent cast
	DTNOTIFY_STOPURGENTCAST		= 0x0A,
	//inform the render to change logLevel
	//lPARAM: 0-----normal  1-----debug
	//2009.9.25  Jeff
	DTNOTIFY_CHANGELOGLEVEL		= 0x0B,
	///inform preview manager stop preview, only use in preview player
	DTNOTIFY_STOPPREVIEW       = 0x0C
}DTNOTICEID;
///Macro to get notice ID
#define GET_NOTICE_ID(WParam) (WParam & 0x000000FF)
///LPARAM
/// Depends on DTNOTICEPLAYER

//////////////////////////////////////////////////////////////////////////////
///The action when watch dog receive an alive message.
typedef enum _tagWatchDogAction
{
    ///User click cancel button when registration
    DT_EXIT_WATCHDOG        = 0,
    ///Restart download engine
    DT_RESTART_APPLICATION  = 1,
    ///Hardware reset
    DT_RESTART_MACHINE      = 2,
	//notify watchdog after register/login
	DT_REGISTER_OK			= 3,
	//if timezone is changed from one command, the message will be sent by the monitor
	//2009.1.4  Jeff
	DT_TIMEZONE_CHANGED		= 4,
	// after apply screen settings, the render process needs to restart, otherwise the size is not fit for 
	// the screen. 2009.7.28 YuPeng
	DT_RESTART_RENDER		= 5
}DTWDOGACTION;

//////////////////////////////////////////////////////////////////////////////
///This message is used by render process to post alive message to watchdog
///process.
#define DTWM_RENDER_ALIVE	WM_USER+3
///WPARAM
/// DTWDOGACTION
///LPARAM
/// LPARAM is the time when post message (time_t)

//////////////////////////////////////////////////////////////////////////////
///This message is used by download process to post alive message to watchdog
///process.
#define DTWM_MONITOR_ALIVE	WM_USER+4
///WPARAM
/// DTWDOGACTION
///LPARAM
/// LPARAM is the time when post message (time_t)
//if the user click cancel button when register, this message is posted to tell watchdog process exit with LPARAM equal to 0

//this message is used by watchmasterplayer process to post alive message to watchdog process
//2007.11.4  Jeff
#define DTWM_COPIER_ALIVE  WM_USER+5

//this message is used by edgeserver agent process to post alive message to watchdog process
//2008.3.21  Jeff
#define DTWM_ESAGENT_ALIVE  WM_USER+6

#define DTWM_ESAPACHELOG_ALIVE  WM_USER+9

//The message is sent if there are medias of published program being downloading
//this message is also sent when try to download the ever failed objects
//WPARAM: the number which have been downloaded; LPARAM:the total number which should be downloaded
//if WPARAM is not 0 but the LPARAM is 0, should stop showing this message
//if WPARAM and LPARAM is always 0, only show this message withough progress indication
//2008.1.7  Jeff (for 2.1 patch)
#define DTWM_SCHEDULEDOWNLOAD WM_USER+7

//This message(DTWM_SCHEDULEDOWNLOADCONFIG) is used to tell the render what is the current config for showing schedule downloading message.
//WPARAM is the config value:
//3:show schedule downloading message always
//2: show schedule downloading message only when idle
//1: never show schedule downloading message
const	unsigned long	SHOW_SCHEDULE_DOWNLOADING_ALWAYS	=	3;
const	unsigned long	SHOW_SCHEDULE_DOWNLOADING_IDLE		=	2;
const	unsigned long	SHOW_SCHEDULE_DOWNLOADING_NEVER		=	1;
#define DTWM_SCHEDULEDOWNLOADCONFIG WM_USER+8

//////////////////////////////////////////////////////////////////////////////
///The supported media object type, 16 bits.
typedef enum _tagMOType
{
	///NA
	DTMO_OTHER		    =	0,
	///Program Item.
	DTMO_PROGRAM        =   1,
	///Schedule Item.
	DTMO_SCHEDULE       =   2,
	///ComboList item
	DTMO_COMBOLIST		=	3,
	///Play list item.
	DTMO_PLAYLIST       =   4,
	///Urgent Ticker item, its limit duration is in priority, user preset or
	///default duration in configuration.
	DTMO_URGENTTICKER	=	5,
	///DirectShow image object, its limit duration is, in priority, user preset
	///or default duration from configuration.
	DTMO_IMAGE		    =	6,
	///DirectShow audio object, its limit duration is, in priority, user preset,
	///audio file length, or default duration from configuration.
	DTMO_AUDIO		    =	7,
	///DirectShow video object, its limit duration is, in priority, user preset,
	///video file length, or default duration from configuration.
	DTMO_VIDEO		    =	8,
	///Flash, implemented by exe flash render.
	DTMO_FLASH		    =	9,
	///PPT Viewer process, its limit is, in priority, user preset or default
	///duration from configuration.
	DTMO_PPT		    =	10,
	///HTML ActiveX Window, its limit  is, in priority, user preset or default
	///duration from configuration.
	DTMO_HTML		    =	11,
	///Windows Media Player compatible item, its limit duration is, in priority,
	///user preset, file length or default duration from configuration.
	DTMO_WMP		    =	12,
	///Ticker item, its limit duration is in priority, user preset, or if it is
	///Ticker under PLAYLIST, then its duration is same as PLAYLIST; if it is
	///under PROGRAM then it is default duration from configuration.
	DTMO_TICKER		    =	13,
	///The Video in item. The render show video in context through RF or SVideo.
	DTMO_VIDEOIN        =   14,
	///The TV tuner item. The render show TV Program by specified channel.
	DTMO_TVTUNNER       =   15,
	///The application media file.
	DTMO_EXECUTABLE     =   16,
	///The multiple-file item. The render show multiple-file by a specified html file.
	DTMO_MULTIFILE		=	17,
	///The sliverlight item. 
	DTMO_SLIVERLIGHT	=	18,
	///Tip item.
	DTMO_TIP			=	19
	///Flash, implemented by Flash OCX object, its limit duration is, in priority, user preset, flash
	///file total frame divide frame rate, or default duration from configuration.
	//DTMO_FLASH_BASE		=	19
}DTMOTYPE;

//this customer message is used to replace WM_COPYDATA if we use DTMessageQueue
//2008.4.9  Jeff
#define DTWM_SHOWSITEINFO WM_USER+10

//This customer message is used to DT SDK
//2009.5.18 nren
#define DTWM_DTSDK WM_USER+11

//////////////////////////////////////////////////////////////////////////////
///When define user message please use DTWM_USER instead of WM_USER.
#define DTWM_USER WM_USER+12

//////////////////////////////////////////////////////////////////////////
///define our own notice tip message.
#define DTWM_NOTICETIP DTWM_USER+1
///WPARAM
///the tip type.same TIP_TYPE define in Class CDTipManager.
///LPARAM
///the notice tip's duration.

//////////////////////////////////////////////////////////////////////////////
/// notice render there is a event happens.
#define DTWM_RENDEREVENTDATA DTWM_USER+2

#define DTWM_MAINTHREAD_ALIVE DTWM_USER + 1024

//////////////////////////////////////////////////////////////////////////////
///Module inside windows message
#define DTWM_WMQ_NOTICEPLAYER DTWM_USER + 2048

#define DTWM_SHOWMAINWINDOW DTWM_USER + 2049

#define DTWM_HIDEMAINWINDOW DTWM_USER + 2050

#define DTWM_LOCKSCREEN DTWM_USER + 2051

#define DTWM_RELEASESCREEN DTWM_USER + 2052

//////////////////////////////////////////////////////////////////////////////
///When the free disk size is not enough, the event is signaled to ask cleanup
///task to do disk cleanup
#define DTES_CLEANUP_EVENT_NAME			DTSTR("__DTESCLEANUP__")

//////////////////////////////////////////////////////////////////////////////
///When some downloading tasks need to stop, the event is signaled
#define DTES_ABORT_EVENT_NAME           DTSTR("__DTESABORT__")

//////////////////////////////////////////////////////////////////////////////
///For player,if there is media being played, the event is signaled, if there
///is nothing to play, reset this event; for download process, when send
///heartbeat request, check the status of that event, if it is signaled, pass
///mediaID as 1, otherwise pass mediaID as 0
#define DTES_PLAYER_STATUS_EVENT_NAME	DTSTR("__DTESPLAYERSTATUS__")

//////////////////////////////////////////////////////////////////////////////
///When the player is launched by watchdog, watchdog will set this event to
///inform download process, download process will check the status of this
///event, if it is signaled, it will post messages to render process to let
///the player play those tasks which haven't played yet
#define DTES_PLAYER_START_EVENT_NAME	DTSTR("__DTESSTARTPLAYER__")

//if this event is in signal status, should move the log content in ram disk to the local disk
//2008.5.8  Jeff
#define DTES_FLUSH_LOG_EVENT_NAME		DTSTR("__DTESFLUSHLOGEVENT__")

//if want to invoke the timetask of the monitor process, set this event
//2009.1.13  Jeff
#define DTES_START_TIMETASK_EVENT_NAME	DTSTR("__DTES_START_TIMETASK_EVENT__")

//if want to read config again, set this event
//2012.5.15  Zhangxq
#define DTES_READ_COMM_CONFIGURATION_AGAIN_EVENT	DTSTR("__DTES_READ_COMM_CONFIGURATION_AGAIN_EVENT__")
//////////////////////////////////////////////////////////////////////////////
///Add this line to prevent multiple processes of essendcrashreport.exe
///2007.7.23  Jeff
#define DTES_SEND_CRASHREPORT_MUTEX		DTSTR("__DTES_SEND_CRASHREPORT_MUTEX__")

//if player using proxy to communicate with the PS, the proxy host, user name and password are saved into registry
#define DTES_REGISTRY_PROXY_HOST		DTSTR("proxyhost")
#define DTES_REGISTRY_PROXY_USER		DTSTR("proxyusername")
#define DTES_REGISTRY_PROXY_PASSWORD	DTSTR("proxypassword")

//this file is used to save the registry information of our application
#define DTES_REGISTRY_BACKUPFILE	DTSTR("__backreg__.xml")
#define DTES_REGISTRY_BACKUPFILE2	DTSTR("__backreg2__.xml")

//If there is not anything to be downloaded and there are not new tasks
//an empty file whose name is DTES_MPDOWNLOADED_FILENAME will be created
//under work folder
//add to support master player implementation
//2007.10.31  Jeff
#define DTES_MPDOWNLOADED_FILENAME	DTSTR("__downloaded__.dat")

//after the player is copied, this file will be created under work folder
#define DTES_COPIED_FILENAME		DTSTR("__wcmcopied__.dat")


//before copy player from the sharefolder or the USB disk, copy player class set this event
//to ask watchdog stop the download process
//after copied, start download process again
//2007.11.4  Jeff
#define DTES_PLAYER_COPYSTART_EVENT_NAME	DTSTR("__dtescopyplayerstart__")

#define DTES_EXITWATCHDOG_EVENT_NAME    DTSTR("__DTESEXITWATCHDOG__")

//if one item can't befound when render try to play it, the download process and copyplayer process are
//notified to try to get it from PS or copy from edge server again
//the two semaphores are used to inform the two processes
//2007.12.11 Jeff
#define DTES_PLAYER_FAILOBJ_COPY_SEMAPHORE	DTSTR("__dtesfailojbcopy__")
#define DTES_PLAYER_FAILOBJ_DOWNLOAD_SEMAPHORE	DTSTR("__dtesfailojbdownload__")
#define FAIL_SEMAPHORE_MAX_COUNT	10000

//when crash, if the current used mem percent is more than a predefined value which is saved in registry
//one mail should be sent to PS
#define CRASH_HIGH_MEM			DTSTR("~dtmem~.txt")
#define REG_MEM_THRESHOLD		DTSTR("maxMemPercent")

#define DTWM_NOTIFYICON	WM_USER + 1
#define DTWM_CLOSEDLG	WM_USER + 2
#define DTWM_FRAME_READY	WM_USER + 3
#define DTWM_SUBFRAME_READY	WM_USER + 4
#define DTWM_LOST_LINE	WM_USER + 5
#define DTWM_REFRESH_MSG	WM_USER + 6
#define DTWM_TOOLBAR_MSG	WM_USER + 7
#define DTWM_BASESTOP_MSG	WM_USER + 8

const int DEVICE_COUNT_MAX = 2;

#endif