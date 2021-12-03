#ifndef _SAPCLASSBASICDEF_H_
#define _SAPCLASSBASICDEF_H_

//	SapClassBasicDef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Export definitions

#if !defined(POSIX_HOSTPC)
	#if defined SAPCLASSBASIC
		#define SAPCLASSBASIC_VAR		__declspec(dllexport)
		#define SAPCLASSBASIC_CLASS	__declspec(dllexport)
	#else
		#define SAPCLASSBASIC_VAR		__declspec(dllimport)
		#define SAPCLASSBASIC_CLASS	__declspec(dllimport)
	#endif
   #ifdef COR_BORLANDC64
		#undef WINAPI
		#define WINAPI __stdcall
   #endif
#else
	// Posix/Linux -> undo Win32'isms
	#include <corenv.h>
	#include <sys/param.h>
	#define SAPCLASSBASIC_VAR
	#define SAPCLASSBASIC_CLASS
	#ifndef WINAPI
		#define WINAPI
	#endif
	#ifndef __stdcall
		#define __stdcall
	#endif
	#ifndef CALLBACK
		#define CALLBACK
	#endif
	#ifndef MAX_PATH
		#define MAX_PATH MAXPATHLEN
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// New definitions using existing ones in Sapera

#define SAPSTATUS CORSTATUS

/////////////////////////////////////////////////////////////////////////////
// Helper macros for frequently used source code constructs

#define SAP_FREE_POINTER(ptr) \
   {                          \
      if (ptr != NULL)        \
      {                       \
         delete ptr;          \
         ptr = NULL;          \
      }                       \
   }

#define SAP_FREE_ARRAY(array) \
   {                          \
      if (array != NULL)      \
      {                       \
         delete [] array;     \
         array = NULL;        \
      }                       \
   }

#endif	// _SAPCLASSBASICDEF_H_

