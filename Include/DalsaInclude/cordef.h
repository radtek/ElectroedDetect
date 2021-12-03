//
// Coreco standard definitions.
//

#ifndef _CORDEF_H_
#define _CORDEF_H_

#include "corenv.h"

#if !COR_LINUX
#if !COR_WIN64 && defined(_WIN64)
#define COR_WIN64    1
#endif
#if defined(__BORLANDC__) && defined(__clang__)
#define COR_BORLANDC64
#endif
#endif

#define CORPROCESS_MAX_NUMBER			32	
#define CORECO_VENDORID					0x11ec

#ifndef MIN
#define MIN( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX( a, b ) ( ( (a) > (b) ) ? (a) : (b) )
#endif

// Default definitions
#define CCONV
#define CORKEVENT								UINT32
#define CorIsBadReadPtr(ptr, size)		0
#define CorIsBadWritePtr(ptr, size)		0
#define CorIsBadStringPtr(ptr, size)	0

#define ASSERT_PTR(ptr) ASSERT( ((ptr) != NULL))

///////////////////////////////////////////////////////////////////////////////////////
// Windows 32 user level definitions
#if COR_WIN32 || COR_ARMV4I
   // Disable Visual Studio level 4 warnings
   //    4100 -> 'identifier' : unreferenced formal parameter
   #ifdef _MSC_VER
   #pragma warning(disable: 4100)
   #endif

   #if _MSC_VER && !defined(_LIB)
      #if (_DEBUG && !_MT)
         #error The project option "C/C++ | Code Generation | Use run-time library" must either be "Debug Multithreaded" or "Debug Multithreaded DLL"
      #elif (!_DEBUG && !_MT)
         #error The project option "C/C++ | Code Generation | Use run-time library" must either be "Multithreaded" or "Multithreaded DLL"
      #endif
   #endif

   // Allow access to features from Windows 2000 and up
   #ifndef _WIN32_WINNT
   #define _WIN32_WINNT 0x0500
   #endif
   #ifndef WINVER
   #define WINVER _WIN32_WINNT
   #endif

	#include <windows.h>
	#include <Limits.h>


   #ifndef IS_HANDLE_VALID
   #define IS_HANDLE_VALID( handle) ( ( handle != NULL) && ( handle != INVALID_HANDLE_VALUE))
   #endif

	#undef  CORKEVENT
	#define CORKEVENT       HANDLE

#if !defined(_WIN64)
	#undef  CCONV
	#define CCONV           __stdcall
#endif

	#undef  CorIsBadReadPtr
	#define CorIsBadReadPtr(ptr, size)		IsBadReadPtr(ptr, size)
	#undef  CorIsBadWritePtr
	#define CorIsBadWritePtr(ptr, size)		IsBadWritePtr(ptr, size)
	#undef  CorIsBadStringPtr
	#define CorIsBadStringPtr(ptr, size)	IsBadStringPtr(ptr, size)

	typedef signed char     INT8;
	typedef unsigned char   UINT8;
	typedef short           INT16;
	typedef unsigned short  UINT16;
	typedef float           FLOAT;
	typedef int             BOOL;
	typedef double				DOUBLE;

	#ifndef _BASETSD_H_     // New in Visual C++ 6.0
		typedef long            INT32;
		typedef unsigned long   UINT32;

		// needed for C++ Builder
		typedef __int64		   UINT64;
	#endif

// With Visual Studio 2012, the following are already defined in stdint.h
#if defined(_MSC_VER) && _MSC_VER < 1700
   #define INT8_MAX             CHAR_MAX
   #define INT8_MIN             CHAR_MIN
   #define UINT8_MAX            UCHAR_MAX
   #define INT16_MAX            SHRT_MAX
   #define INT16_MIN            SHRT_MIN
   #define UINT16_MAX           USHRT_MAX
   #define INT32_MAX            LONG_MAX
   #define INT32_MIN            LONG_MIN
   #define UINT32_MAX           ULONG_MAX
#else
   #include <stdint.h>
#endif
   #define PVOID_MAX            ((PVOID)ULONG_MAX)

   // There is no definition for ULONG_PTR in Visual Studio 6.0, unless a recent Platform SDK is installed.
   // In the latter case, the new typedef for ULONG_PTR is compatible with the one in the Platform SDK.
   #if defined(_MSC_VER) && _MSC_VER <= 1200
      typedef ULONG ULONG_PTR;
      typedef ULONG *PULONG_PTR;
   #endif
   
   typedef LONG COR_ATOMIC_VARIABLE;

///////////////////////////////////////////////////////////////////////////////////////
// Windows 95 kernel level definitions
#elif COR_95KERNEL

	#include <vtoolsc.h>

	typedef long   			*LPLONG;
	typedef unsigned int	UINT;
	typedef signed char     INT8;
	typedef unsigned char   UINT8;
	typedef short           INT16;
	typedef unsigned short  UINT16;
	typedef long            INT32;
	typedef unsigned long   UINT32;
	typedef float           FLOAT;
	typedef int             BOOL;
	typedef double			   DOUBLE;

///////////////////////////////////////////////////////////////////////////////////////
// Windows NT kernel level definitions
#elif COR_NTKERNEL
	#include <ntddk.h>


	#undef  CORKEVENT
	#define CORKEVENT       PKEVENT

	typedef long   			*LPLONG;
	typedef unsigned int	UINT;
	typedef signed char     INT8;
	typedef unsigned char   UINT8;
	typedef short           INT16;
	typedef unsigned short  UINT16;

	#ifndef _BASETSD_H_     // DDK 2000
		typedef long            INT32;
		typedef unsigned long   UINT32;
		typedef __int64         UINT64;
		typedef unsigned __int64 INT64;
      typedef unsigned long ULONG_PTR;
      typedef unsigned long* PULONG_PTR;
      typedef unsigned long SIZE_T;
      typedef unsigned long* PSIZE_T;
      typedef long SSIZE_T;
      __inline unsigned long PtrToUlong(ULONG_PTR p)
      {
       return((unsigned long) p );
      }
      __inline ULONG_PTR UlongToPtr( unsigned long l)
      {
         return ((ULONG_PTR) l);
      }
	#endif

   // Usefull for converting addresses from a pointer to a ULONG as long as the pointer
   // is in the 1st 4GB of memory. 
   #define UlongPtrToUlong( p)   PtrToUlong( (PVOID)(p))

	typedef float           FLOAT;
	typedef int             BOOL;

///////////////////////////////////////////////////////////////////////////////////////
// C6x firmware definitions
#elif COR_C60
	#include <Limits.h>
   
	#define INVALID_HANDLE_VALUE    0
	#ifndef TRUE
		#define TRUE                    1
		#define FALSE                   0
	#endif

	typedef char           CHAR;
	typedef char           INT8;
	typedef unsigned char  UINT8;
	typedef short          INT16;
	typedef unsigned short UINT16;
	typedef int            INT32;
	typedef unsigned int   UINT32;

#include "cpackd.h"
	typedef struct
	{
		UINT32 LowDWord;
		UINT32 HiDWord;
	}       UINT64;
#include "cunpackd.h"

	typedef long				INT40;
	typedef unsigned long	UINT40;
	typedef float				FLOAT;
	typedef unsigned int		HANDLE;
	typedef int					BOOL;
	typedef unsigned int		UINT;
	typedef int					INT;
	typedef char            *PSTR;
	typedef double				DOUBLE;
//	typedef unsigned int *LPLONG;

   #define INT8_MAX		CHAR_MAX
   #define INT8_MIN		CHAR_MIN
   #define UINT8_MAX		UCHAR_MAX
   #define INT16_MAX		SHRT_MAX
   #define INT16_MIN		SHRT_MIN
   #define UINT16_MAX	USHRT_MAX
   #define INT32_MAX		INT_MAX
   #define INT32_MIN		INT_MIN
   #define UINT32_MAX	UINT_MAX

///////////////////////////////////////////////////////////////////////////////////////
// i960 firmware definitions
#elif COR_I960
	#include <Limits.h>
   
	#define INVALID_HANDLE_VALUE    0
	#define TRUE                    1
	#define FALSE                   0

	typedef char            CHAR;
   typedef unsigned char   *PUCHAR;
	typedef char            INT8;
	typedef unsigned char   UINT8;
	typedef short           INT16;
	typedef unsigned short  UINT16;
	typedef long            INT32;
	typedef unsigned long   UINT32;

#include "cpackd.h"
	typedef struct
	{
		UINT32  LowDWord;
		UINT32  HiDWord;
	}       UINT64;
#include "cunpackd.h"

	typedef float           FLOAT;
	typedef int             BOOL;
	typedef unsigned int    HANDLE;
	typedef unsigned int    UINT;
	typedef int             INT;
	typedef long   			*LPLONG;
	typedef char            *PSTR;
	typedef double          DOUBLE;
   
   #define INT8_MAX             CHAR_MAX
   #define INT8_MIN             CHAR_MIN
   #define UINT8_MAX            UCHAR_MAX
   #define INT16_MAX            SHRT_MAX
   #define INT16_MIN            SHRT_MIN
   #define UINT16_MAX           USHRT_MAX
   #define INT32_MAX            LONG_MAX
   #define INT32_MIN            LONG_MIN
   #define UINT32_MAX           ULONG_MAX
////////////////////////////////////////////////////////
#elif COR_IOP321


	#define INVALID_HANDLE_VALUE    0
	#define TRUE                    1
	#define FALSE                   0

	typedef char            CHAR;
   typedef unsigned char   *PUCHAR;
	typedef char            INT8;
	typedef unsigned char   UINT8;
	typedef short           INT16;
	typedef unsigned short  UINT16;
	typedef long            INT32;
	typedef unsigned long   UINT32;

   typedef unsigned long ULONG_PTR;
   typedef unsigned long* PULONG_PTR;
   typedef unsigned long SIZE_T;
   typedef unsigned long* PSIZE_T;

	typedef UINT8		*PUCHAR;

	typedef unsigned int*   UINT_PTR;

   //inline is not defined for xscale compiler
   #define _inline 

#include "cpackd.h"
	typedef struct
	{
		UINT32  LowDWord;
		UINT32  HiDWord;
	}       UINT64;
#include "cunpackd.h"

	typedef float           FLOAT;
	typedef int             BOOL;
	typedef unsigned int    HANDLE;
	typedef unsigned int    UINT;
	typedef int             INT;
	typedef long   			*LPLONG;
	typedef char            *PSTR;
	typedef double          DOUBLE;
   
   #define INT8_MAX             CHAR_MAX
   #define INT8_MIN             CHAR_MIN
   #define UINT8_MAX            UCHAR_MAX
   #define INT16_MAX            SHRT_MAX
   #define INT16_MIN            SHRT_MIN
   #define UINT16_MAX           USHRT_MAX
   #define INT32_MAX            LONG_MAX
   #define INT32_MIN            LONG_MIN
   #define UINT32_MAX           ULONG_MAX


///////////////////////////////////////////////////////////////////////////////////////
// C165 firmware definitions
#elif COR_C165
	#define TRUE            1
	#define FALSE           0

	typedef char            CHAR;
	typedef char            INT8;
	typedef unsigned char   UINT8;
	typedef int             INT16;
	typedef unsigned int    UINT16;
	typedef long            INT32;
	typedef unsigned long   UINT32;

#include "cpackd.h"
	typedef struct
	{
		UINT32 LowDWord;
		UINT32 HiDWord;
	}       UINT64;
#include "cunpackd.h"

	typedef int             BOOL;
	typedef unsigned int    UINT;
	typedef int             INT;
	typedef char            *PSTR;
	typedef unsigned int		HANDLE;
	typedef float           FLOAT;
	
///////////////////////////////////////////////////////////////////////////////////////
// PowerPC definitions
#elif COR_POWERPC

	#define INVALID_HANDLE_VALUE    0
	#ifndef TRUE					
		#define TRUE                    1
		#define FALSE                   0
	#endif

	typedef char           CHAR;
	typedef char           INT8;
	typedef unsigned char  UINT8;
	typedef short          INT16;
	typedef unsigned short UINT16;
	typedef int            INT32;
	typedef unsigned int   UINT32;

   typedef unsigned long ULONG_PTR;
   typedef unsigned long* PULONG_PTR;
   typedef unsigned long SIZE_T;
   typedef unsigned long* PSIZE_T;
   
	typedef UINT8		*PUCHAR;
   typedef  char*     PCHAR;

	typedef unsigned int*   UINT_PTR;
	
#include "cpackd.h"
	typedef struct
	{
		UINT32 LowDWord;
		UINT32 HiDWord;
	}       UINT64;

typedef union _LARGE_INTEGER {
    struct {
        UINT32 LowPart;
        UINT32 HighPart;
    };
    struct {
        UINT32 LowPart;
        UINT32 HighPart;
    } u;
    UINT64 QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

#include "cunpackd.h"

	typedef long				INT40;
	typedef unsigned long	UINT40;
	typedef float				FLOAT;
	typedef unsigned int		HANDLE;
	typedef int					BOOL;
	typedef unsigned int		UINT;
	typedef int					INT;
	typedef char            *PSTR;
	typedef double				DOUBLE;
//	typedef unsigned int *LPLONG;

   #define INT8_MAX		CHAR_MAX
   #define INT8_MIN		CHAR_MIN
   #define UINT8_MAX		UCHAR_MAX
   #define INT16_MAX		SHRT_MAX
   #define INT16_MIN		SHRT_MIN
   #define UINT16_MAX	USHRT_MAX
   #define INT32_MAX		INT_MAX
   #define INT32_MIN		INT_MIN
   #define UINT32_MAX	UINT_MAX

///////////////////////////////////////////////////////////////////////////////////////
// TI's DSP DM642
#elif COR_TI_DM642
	#include <Limits.h>
   
	#define INVALID_HANDLE_VALUE    0
	#ifndef TRUE
		#define TRUE                    1
		#define FALSE                   0
	#endif

	typedef char           CHAR;
	
#ifndef _C_USERTYPE_INC		// defined in DM642 NDK header file
	typedef char           INT8;
	typedef unsigned char  UINT8;
	typedef short          INT16;
	typedef unsigned short UINT16;
	typedef int            INT32;
	typedef unsigned int   UINT32;
	typedef unsigned int		HANDLE;	
#endif	

   typedef unsigned long ULONG_PTR;
   typedef unsigned long* PULONG_PTR;
   typedef unsigned long SIZE_T;
   typedef unsigned long* PSIZE_T;

	typedef UINT8		*PUCHAR;

	typedef unsigned int*   UINT_PTR;

   typedef union
   {
   	struct
   	{
		   UINT32 lo;
		   UINT32 hi;	
	   } uint32;

      struct
      {
         UINT16 word0;
         UINT16 word1;
         UINT16 word2;
         UINT16 word3;
      } uint16;

      struct
      {
         UINT8 byte0;
         UINT8 byte1;
         UINT8 byte2;
         UINT8 byte3;
         UINT8 byte4;
         UINT8 byte5;
         UINT8 byte6;
         UINT8 byte7;
      } uint8;

   } UINT64;

	typedef float				FLOAT;	
	typedef int					BOOL;
	typedef unsigned int		UINT;
	typedef int					INT;
	typedef char            *PSTR;
	typedef double				DOUBLE;

   #define INT8_MAX		CHAR_MAX
   #define INT8_MIN		CHAR_MIN
   #define UINT8_MAX		UCHAR_MAX
   #define INT16_MAX		SHRT_MAX
   #define INT16_MIN		SHRT_MIN
   #define UINT16_MAX	USHRT_MAX
   #define INT32_MAX		INT_MAX
   #define INT32_MIN		INT_MIN
   #define UINT32_MAX	UINT_MAX
   #define PVOID_MAX    ((PVOID)UINT_MAX)

/******************************************************************************/
/*                                                                            */
/*                      XILINX MICROBLAZE DEFINITIONS                         */
/*                                                                            */
/******************************************************************************/
#elif COR_NIOS2_GCC
	#include <limits.h>
   
	#define INVALID_HANDLE_VALUE        0
	#ifndef TRUE
		#define TRUE                     1
		#define FALSE                    0
	#endif

	typedef float			               FLOAT;
	typedef double			               DOUBLE;
	typedef char                        CHAR;
	typedef char                        INT8;
	typedef unsigned char               UINT8;
	typedef short                       INT16;
	typedef unsigned short              UINT16;
	typedef int                         INT32;
	typedef unsigned int                UINT32;
	typedef unsigned int		            HANDLE;

   typedef union
   {
   	struct
   	{
		   UINT32 lo;
		   UINT32 hi;	
	   } uint32;

      struct
      {
         UINT16 word0;
         UINT16 word1;
         UINT16 word2;
         UINT16 word3;
      } uint16;

      struct
      {
         UINT8 byte0;
         UINT8 byte1;
         UINT8 byte2;
         UINT8 byte3;
         UINT8 byte4;
         UINT8 byte5;
         UINT8 byte6;
         UINT8 byte7;
      } uint8;

   } UINT64;

	typedef int					BOOL;
	typedef unsigned int		UINT;
	typedef int					INT;
	typedef char            *PSTR;

#ifndef BOOLEAN_DEFINED
   typedef UINT8  BOOLEAN;
   #define BOOLEAN_DEFINED
#endif

   typedef unsigned long   ULONG_PTR;
   typedef unsigned long*  PULONG_PTR;
   typedef unsigned long   SIZE_T;
   typedef unsigned long*  PSIZE_T;

   #define INT8_MAX		CHAR_MAX
   #define INT8_MIN		CHAR_MIN
   #define UINT8_MAX		UCHAR_MAX
   #define INT16_MAX		SHRT_MAX
   #define INT16_MIN		SHRT_MIN
   #define UINT16_MAX	USHRT_MAX
   #define INT32_MAX		INT_MAX
   #define INT32_MIN		INT_MIN
   #define UINT32_MAX	UINT_MAX
   #define SIZE_MAX     ULONG_MAX

// Don't know whois the one who use min instead of MIN !!!  But
// min and max are required by CorFirmwareUtil.c and CorCbhUtil.c !!
#ifndef min
#define min( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
#endif

#ifndef max
#define max( a, b ) ( ( (a) > (b) ) ? (a) : (b) )
#endif

/******************************************************************************/
/*                                                                            */
/*                            CYGWIN DEFINITIONS                              */
/*                                                                            */
/******************************************************************************/
#elif COR_CYGWIN
	#include <Limits.h>
   
	#define INVALID_HANDLE_VALUE        0
	#ifndef TRUE
		#define TRUE                     1
		#define FALSE                    0
	#endif

	typedef float			               FLOAT;
	typedef double			               DOUBLE;
	typedef char                        CHAR;
	typedef char                        INT8;
	typedef unsigned char               UINT8;
	typedef short                       INT16;
	typedef unsigned short              UINT16;
	typedef int                         INT32;
	typedef unsigned int                UINT32;
	typedef unsigned int		            HANDLE;

   typedef union
   {
   	struct
   	{
		   UINT32 lo;
		   UINT32 hi;	
	   } uint32;

      struct
      {
         UINT16 word0;
         UINT16 word1;
         UINT16 word2;
         UINT16 word3;
      } uint16;

      struct
      {
         UINT8 byte0;
         UINT8 byte1;
         UINT8 byte2;
         UINT8 byte3;
         UINT8 byte4;
         UINT8 byte5;
         UINT8 byte6;
         UINT8 byte7;
      } uint8;

   } UINT64;

	typedef int					BOOL;
	typedef unsigned int		UINT;
	typedef int					INT;
	typedef char            *PSTR;
   typedef  char*     PCHAR;

   typedef unsigned long ULONG_PTR;
   typedef unsigned long* PULONG_PTR;


// Don't know whois the one who use min instead of MIN !!!  But
// min and max are required by CorFirmwareUtil.c and CorCbhUtil.c !!
#ifndef min
#define min( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
#endif

#ifndef max
#define max( a, b ) ( ( (a) > (b) ) ? (a) : (b) )
#endif

/******************************************************************************/
/*                                                                            */
/*                      MSP430 TI MICROPROCESSOR DEFINITIONS                */
/*                                                                            */
/******************************************************************************/
#elif COR_MSP430_TI
   
	#define INVALID_HANDLE_VALUE        0
	#ifndef TRUE
		#define TRUE                     1
		#define FALSE                    0
	#endif

	typedef char                        CHAR;
	typedef char                        INT8;
	typedef unsigned char               UINT8;
	typedef int                         INT16;
	typedef unsigned int                UINT16;
	typedef long int                    INT32;
	typedef unsigned long int           UINT32;
	typedef unsigned long int		      HANDLE;

	typedef long int					      BOOL;
	typedef unsigned long int		      UINT;
	typedef long int					      INT;
	typedef char                        *PSTR;

#ifndef BOOLEAN_DEFINED
   typedef UINT8  BOOLEAN;
   #define BOOLEAN_DEFINED
#endif

// Don't know whois the one who use min instead of MIN !!!  But
// min and max are required by CorFirmwareUtil.c and CorCbhUtil.c !!
#ifndef min
#define min( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
#endif

#ifndef max
#define max( a, b ) ( ( (a) > (b) ) ? (a) : (b) )
#endif


/******************************************************************************/
/*                                                                            */
/*                      ATMEL AT91 MICROPROCESSOR DEFINITIONS                 */
/*                                                                            */
/******************************************************************************/
#elif COR_ATMEL_AT91
   
   #include <stdint.h>
   
	#ifndef TRUE
		#define TRUE         1
		#define FALSE        0
	#endif

   typedef char            INT8;
   typedef unsigned char   UINT8;
   typedef short           INT16;
   typedef unsigned short  UINT16;
   typedef int             INT32;
   typedef unsigned int    UINT32;
   typedef unsigned int	   HANDLE;	
   typedef int					BOOL;
   typedef union
   {
      struct
      {
         UINT32 lo;
         UINT32 hi;  
      } uint32;

      struct
      {
         UINT16 word0;
         UINT16 word1;
         UINT16 word2;
         UINT16 word3;
      } uint16;

      struct
      {
         UINT8 byte0;
         UINT8 byte1;
         UINT8 byte2;
         UINT8 byte3;
         UINT8 byte4;
         UINT8 byte5;
         UINT8 byte6;
         UINT8 byte7;
      } uint8;
   } UINT64;

   typedef float           FLOAT;

///////////////////////////////////////////////////////////////////////////////////////
// Linux definitions
#elif COR_LINUX


#ifdef __KERNEL__
#include <linux/types.h>
	typedef s8      CHAR;
	typedef s8      INT8;
	typedef u8      UINT8;
	typedef s16     INT16;
	typedef u16     UINT16;
	typedef s32     INT32;
	typedef u32     UINT32;
	typedef s64     INT64;
	typedef u64     UINT64;
	typedef void *  HANDLE, *PHANDLE;
	#define PEPROCESS HANDLE
	//typedef u32  ULONG;
	//typedef u32  *PULONG;
#include "posixcmn.h"

#else

#include <stddef.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
	typedef char    CHAR;    // 'int8_t' replaced with 'char', GCC doesnt allow conversion from 'signed char' to 'char' and CHAR is used as a 'char'
   typedef int8_t    INT8;
	typedef u_int8_t  UINT8;
	typedef int16_t   INT16;
	typedef u_int16_t   UINT16;
	typedef int32_t   INT32;
	typedef u_int32_t   UINT32;
	typedef long long   INT64;
	typedef long long   _int64;
    typedef long long   __int64;
	typedef u_int64_t   UINT64;
    typedef INT64      *PINT64;
    typedef UINT64     *PUINT64;

   #ifndef IS_HANDLE_VALID
   #define IS_HANDLE_VALID( handle) ( ( handle != NULL) && ( handle != INVALID_HANDLE_VALUE))
   #endif
	//typedef INT32   LONG;
	//typedef UINT32  ULONG;
	//typedef UINT32  *PULONG;

#if CORPOSIX_OFF
   #include <stdio.h>
   #include <pthread.h>
   #include <semaphore.h>
   #include <signal.h>
   #include <dlfcn.h>
   #include <unistd.h>
   #ifndef TRUE
      #define TRUE                    1
      #define FALSE                   0
   #endif
#else
   #include "corposix.h"

	#undef  CORKEVENT
	#define CORKEVENT       HANDLE

#endif
   typedef int COR_ATOMIC_VARIABLE;


#endif

	typedef float			FLOAT;
	typedef unsigned int	UINT;
	typedef unsigned int	*PUINT;
	typedef int				INT;
   typedef int          *PINT;
	typedef char			*PSTR, *LPSTR, *LPTSTR; //, *LPCSTR, *LPCTSTR;
	typedef const char 	*LPCSTR, *LPCTSTR;
	typedef double		DOUBLE;
	typedef UINT8		UCHAR;
	typedef UINT8		*PUCHAR;
	typedef INT16		SHORT;
	typedef UINT16		USHORT;
//	typedef INT32		LONG;
//	typedef UINT32		ULONG;
	typedef UINT32    *PDWORD;
	typedef INT32     LRESULT;

	typedef UINT32		NTSTATUS;
	typedef void		VOID;
	typedef unsigned long   ULONG_PTR, *PULONG_PTR;
	typedef ULONG_PTR       DWORD_PTR, *PDWORD_PTR;
	typedef unsigned long   SIZE_T;
	typedef unsigned long*  PSIZE_T;
	typedef long            SSIZE_T;
	static __inline unsigned long _PtrToUlong(ULONG_PTR p)
	{
		return((unsigned long) p );
	}
	static __inline ULONG_PTR _UlongToPtr( unsigned long l)
	{
		return ((ULONG_PTR) l);
	}

   // Usefull for converting addresses from a pointer to a ULONG as long as the pointer
   // is in the 1st 4GB of memory. 
   #define PtrToUlong( p)      _PtrToUlong( (ULONG_PTR)(p))
   #define UlongToPtr( p)      _UlongToPtr( (ULONG)(p))
   #define UlongPtrToUlong( p) _PtrToUlong( (ULONG_PTR)(p))
   
   // Supporty Windows WOW64 marker
   #define POINTER_32
   #define POINTER_64

#ifdef __KERNEL__
   #define INT8_MAX		CHAR_MAX
   #define INT8_MIN		CHAR_MIN
   #define UINT8_MAX		UCHAR_MAX
   #define INT16_MAX		SHRT_MAX
   #define INT16_MIN		SHRT_MIN
   #define UINT16_MAX		USHRT_MAX
   #define INT32_MAX		INT_MAX
   #define INT32_MIN		INT_MIN
   #define UINT32_MAX		UINT_MAX
#else
   #include <stdint.h>
#endif

#ifdef COR_ARM

   typedef  long  LONG;
   typedef  int   BOOL;

   // Don't know whois the one who use min instead of MIN !!!  But
   // min and max are required by...
   #ifndef min
      #define min( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
   #endif

   #ifndef max
      #define max( a, b ) ( ( (a) > (b) ) ? (a) : (b) )
   #endif

#endif // COR_ARM

#endif // COR_LINUX

///////////////////////////////////////////////////////////////////////////////////////
// General definitions

#ifndef NULL
	#define NULL            0
#endif

#ifndef far
	#define far
#endif

// Maximum length of full pathname 
#if !COR_POWERPC
#ifndef _MAX_PATH
	#define _MAX_PATH     260                 
#endif
#endif
#ifndef _MAX_DRIVE
	#define _MAX_DRIVE      3
#endif
#ifndef _MAX_DIR
	#define _MAX_DIR        256
#endif
#ifndef _MAX_FNAME
	#define _MAX_FNAME      256
#endif
#ifndef _MAX_EXT
	#define _MAX_EXT        256
#endif

typedef INT8            *PINT8;
#if COR_TI_DM642 || COR_NIOS2_GCC
typedef PINT8 PCHAR;
#endif
typedef UINT8           *PUINT8;
typedef INT16           *PINT16;
typedef UINT16          *PUINT16;
typedef INT32           *PINT32;
typedef UINT32          *PUINT32;

typedef char            BOOL8;
typedef BOOL8           *PBOOL8;
typedef INT16           BOOL16;
typedef BOOL16          *PBOOL16;
typedef INT32           BOOL32;
typedef BOOL32          *PBOOL32;

#if !COR_95KERNEL && !COR_MSP430_TI
	typedef UINT64          *PUINT64;
#endif

#if !COR_C165 && !COR_MSP430_TI
	typedef FLOAT           *PFLOAT;
#endif

#if COR_LINUX
typedef UINT32   DWORD;
#else
typedef unsigned long   DWORD;
typedef BOOL            *PBOOL;
#endif

#if !COR_C60 && !COR_LINUX
	#if (COR_I960 || ((_MSC_VER > 0 && _MSC_VER < 1200)) ||  COR_NTKERNEL  || COR_IOP321 ||  COR_POWERPC)
		#ifndef _BASETSD_H_     // DDK 2000
			typedef INT32           LONG;
			typedef UINT32          ULONG;
			typedef UINT32          *PULONG;
		#endif
		typedef UINT32          *PDWORD;
		typedef INT32           LRESULT;
	#endif
#endif

typedef const char      *PCSTR;
typedef UINT8           *PBYTE;
typedef UINT8           *LPBYTE;

#if !COR_95KERNEL && !COR_NIOS2_GCC
	typedef UINT8           *PBOOLEAN;
#endif

#if !COR_NIOS2_GCC
   typedef UINT8           *LPBOOLEAN;
#endif

typedef UINT16          *PWORD;

#if !COR_95KERNEL && !COR_ATMEL_AT91 && !COR_NIOS2_GCC && !COR_MSP430_TI
	typedef UINT8           BOOLEAN; 
#endif
typedef UINT8           BYTE;
typedef UINT16          WORD;
typedef void            *LPVOID, *PVOID;

typedef char            CORSTR[ 256];

#if !COR_TI_DM642 && !COR_NIOS2_GCC && !COR_MSP430_TI
#include "cpackd.h"

// Scatter/Gather memory structure shared between user, kernel, and firmware drivers.
typedef struct COR_PACK _CORSGENTRY
{
	ULONG_PTR	address;	// Physical Address for segment.(*)
	UINT32		length;	// Length (in bytes) of the segment.
} CORSGENTRY, *PCORSGENTRY;

// Scatter/Gather memory structure shared between user, kernel, and firmware drivers.
// supports WOW64
typedef struct COR_PACK _CORSGENTRY_64
{
	UINT64	address;	// Physical Address for segment.(*)
	UINT32	length;	// Length (in bytes) of the segment.
} CORSGENTRY_64, *PCORSGENTRY_64;

#include "cunpackd.h"
#endif // COR_TI_DM642

#if COR_I960
	// Already defined for i960 (in intel types.h)
	#include <types.h>
#elif COR_C165
#elif COR_TI_DM642
#else
#if !COR_LINUX
	typedef unsigned int		uint;
	typedef unsigned short	ushort;
	typedef unsigned char	uchar;
	typedef unsigned long	ulong;
#endif
#endif

// volatile definitions
typedef UINT8 volatile  VUINT8;
typedef UINT8 volatile  *PVUINT8;

typedef UINT8 volatile  VBYTE;
typedef UINT8 volatile  *PVBYTE;

typedef UINT16 volatile VUINT16;
typedef UINT16 volatile *PVUINT16;

typedef UINT16 volatile VWORD;
typedef UINT16 volatile *PVWORD;

typedef UINT32 volatile VUINT32;
typedef UINT32 volatile *PVUINT32;

typedef UINT32 volatile VDWORD;
typedef UINT32 volatile *PVDWORD;

#if !COR_95KERNEL && !COR_MSP430_TI
	typedef UINT64 volatile VUINT64;
	typedef UINT64 volatile *PVUINT64;
#endif


// Ethernet-related definitions
typedef struct 
{
   UINT8 i1;
   UINT8 i2;
   UINT8 i3;
   UINT8 i4;
} CORIP_ADDRESS;



#endif   // _CORDEF_H_
