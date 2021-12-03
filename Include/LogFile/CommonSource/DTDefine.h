/*****************************************************************************
* File:		DTDefine.h
*
* Purpose:  DT General definition used in various application. This file
*           must pure C/C++ and OS neutral.
*           1. Unify ANSI and Unicode difference. If UNICODE or _UNICODE is
*              defined, then UNICODE is used by default.
*           2. Also provide simple debug macro.
*
* Author:	Cavan Joe
*
* Created:	2007-02-26
*
* Updated:  2007-10-30 Cavan
*
* Home:		http://www.dtri.com/
*
* COPYRIGHT(C) 1995-2008 DT RESEARCH,INC. ALL RIGHTS RESERVED.
*****************************************************************************/
#ifndef _DTDEFINE__
#define _DTDEFINE__

#pragma once

//Disable warning message "'function': was declared deprecated".
#pragma warning(disable:4996)

///
///Let current running break right now. In general the application will pop
///up a dialog box to prompt user continue or not.
#define DTDebugBreak()	_asm int 3


#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT		0x0501  //Windows XP
#endif

#if !defined(WINVER)
#define WINVER		0x0501  //Windows XP
#endif


///
///The memory leak and overwriting detection. The global operator new is
///substituted by CRT debug API.
#ifdef _DEBUG
    //Maps the base heap functions to their debug version counterparts.
    //The #include statements must be in the order shown here. If you change
    //the order, the functions you will use may not work properly. 
	//don't define this macro any more, it may cause some compile errors when using boost, etc.  2009.9.17  Jeff
    //#define _CRTDBG_MAP_ALLOC  
    #include <stdlib.h>
    #include <malloc.h>
    #include <crtdbg.h>
    
    #define DTASSERT(X)	_ASSERT(X)
#else //NDEBUG
    #define DTASSERT(X)	__noop
#endif //_DEBUG

#include <exception>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>

#if defined(UNICODE) || defined(_UNICODE)
	typedef std::wstring DTString;
	typedef std::wstringstream DTStringStream;
    #define DTSTRING_RAW(s)  L ## s

#else
	typedef std::string DTString;
	typedef std::stringstream DTStringStream;
    #define DTSTRING_RAW(s)  s    
#endif

///This macro is used to output Unicode __FILE__, __FUNCTION__ macro string.
#define DTSTR(s) DTSTRING_RAW(s)

typedef std::vector<DTString> DTStringArray;

///Define 64 bits time value. 0 represents midnight, January 1, 1970.
typedef time_t DTTIME;
#define DTTIME_INVALID DTTIME(-1)

///Define DT FILETIME, unit is 100 ns
typedef unsigned __int64 DTFILETIME;

///Define 64 bits nanosecond unit, one unit is 100 nanosecond
typedef __int64 DTNANOSECOND;


///The keyword used to force C++ compiler not generate vtable.
#define DT_NO_VTABLE __declspec(novtable)

#endif