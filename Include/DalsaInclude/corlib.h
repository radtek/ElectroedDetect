//
// Coreco standard library.
//

#ifndef _CORLIB_H_
#define _CORLIB_H_

#include <cordef.h>

// Macros that replace some C run-time string functions.
// By default, these macros resolve to the regular run-time functions.
// See COR_WIN32 below for redefinitions.
#define CorSnprintf  _snprintf
#define CorSprintf_s sprintf_s
#define CorVsnprintf _vsnprintf
#define CorMemcpy_s  memcpy_s
#define CorSscanf    sscanf
#define CorStrcpy_s  strcpy_s
#define CorStrncpy   strncpy
#define CorStrncpy_s   strncpy_s
#define CorStricmp   stricmp
#define CorStrnicmp  strnicmp
#define CorStrncat   strncat
#define CorGetch     getch
#define CorStrtok( strToken, strDelimit, context) (((*(context)) = NULL), (strtok( (strToken), (strDelimit))))
#define CorSplitpath( path, drive, driveSizeInCharacters, dir, dirSizeInCharacters, fname, nameSizeInCharacters,  ext, extSizeInBytes) _splitpath((path), (drive), (dir), (fname), (ext))
#define CorFopen( pFile, filename, mode) (!((*pFile) = fopen( (filename), (mode))))
#define CorItoa( value, buffer, sizeInCharacters, radix) ( _itoa( (value), (buffer), (radix)) ? 0 : 1)
#define CorLocaltime    localtime
#define CorLocaltime64  _localtime64
#define CorStrupr(a,b)       _strupr(a)
#define CorGcvt(buffer, sizeInBytes, value, digits) _gcvt((value), (digits), (buffer))
#define CorMakepath(pathName,n_pathName, tmpModuleDrive, tmpModulePath, s1, s2) _makepath(pathName,tmpModuleDrive, tmpModulePath, s1, s2)
#define CorSpawnlp   spawnlp
#define CorGetpid GetCurrentProcessId
#define CorGettid  GetCurrentThreadId
#define CorProcessIdEquale( _t1, _t2 ) ((_t1) == (_t2)) 

#ifdef __cplusplus
extern "C" {
#endif
void CorSprintf(char *str,int size,char *format, ...);
#if !(COR_LINUX && defined(__KERNEL__))
void CorSwprintf(wchar_t *str,int size,wchar_t *format, ...);
#endif
#ifdef __cplusplus
}
#endif


#if COR_NTKERNEL
	#define CorMalloc( nBytes)				ExAllocatePool( PagedPool, nBytes)
	#define CorFree( p)						ExFreePool(p)
	#define CorCalloc( nItem, nBytes)   CorMalloc( (nItem) * (nBytes))
	#define CorRealloc( p, nBytes)      Not implemented
	#define CorMemcpy(d,s,c)            CorManMemcpy( d, s, c, FALSE)
	#define CorMemcpyAlignSrc(d,s,c)    CorManMemcpy( d, s, c, TRUE)

	#define CorMallocWithTag( nBytes, tag)				ExAllocatePoolWithTag( PagedPool, nBytes, tag)
	#define CorCallocWithTag( nItem, nBytes, tag)   CorMallocWithTag( (nItem) * (nBytes), tag)

#elif COR_95KERNEL
	#define CorMalloc( nBytes)				malloc( nBytes)
	#define CorFree(p)						free( p)
	#define CorCalloc( nItem, nBytes)   calloc( nItem, nBytes)
	#define CorRealloc( p, nBytes)      realloc( p, nBytes)
	#define CorMemcpy(d,s,c)            CorManMemcpy( d, s, c, FALSE)
	#define CorMemcpyAlignSrc(d,s,c)    CorManMemcpy( d, s, c, TRUE)

	#define CorMallocWithTag( nBytes, tag)				CorMalloc( nBytes)
	#define CorCallocWithTag( nItem, nBytes, tag)   CorCalloc( nItem, nBytes)

#elif COR_LINUX && defined(__KERNEL__)
	#include <GDrv_kerneldefs.h>
	#define CorMalloc( nBytes)				vmalloc( nBytes)
	#define CorFree(p)						vfree( p)
	#define CorCalloc( nItem, nBytes)   CorMalloc( (nItem) * (nBytes))
	#define CorRealloc( p, nBytes)		Not implemented
	#define CorMemcpy(d,s,c)            CorManMemcpy( d, s, c, FALSE)
	#define CorMemcpyAlignSrc(d,s,c)    CorManMemcpy( d, s, c, TRUE)

	#define CorMallocWithTag( nBytes, tag)				CorMalloc( nBytes)
	#define CorCallocWithTag( nItem, nBytes, tag)   CorCalloc( nItem, nBytes)

#else
	#include <assert.h>

	#ifndef ASSERT
		#define ASSERT(a) assert((int)a)
	#endif

	#ifdef NOSTANDARD_ALLOC
		void *CorMalloc(UINT32 size);
		void CorFree(void *memblock);

		#define CorMallocWithTag( nBytes, tag)				CorMalloc( nBytes)

	#else
		#include <stdlib.h>
		#if COR_WIN32
			#define CorMalloc(nBytes)        HeapAlloc(GetProcessHeap(), 0, nBytes)
			#define CorFree(p)               HeapFree(GetProcessHeap(), 0,  p)
			#define CorCalloc(nItem, nBytes) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (nItem) * (nBytes))
			#define CorRealloc(p, nBytes)    HeapRealloc(GetProcessHeap(), 0, p, nBytes)
	
			#define CorMallocWithTag( nBytes, tag)				CorMalloc( nBytes)
			#define CorCallocWithTag( nItem, nBytes, tag)   CorCalloc( nItem, nBytes)

		#else
			#define CorMalloc( nBytes)				malloc( nBytes)
			#define CorFree(p)						free( p)
			#define CorCalloc( nItem, nBytes)   calloc( nItem, nBytes)
			#define CorRealloc( p, nBytes)		realloc( p, nBytes)

			#define CorMallocWithTag( nBytes, tag)				CorMalloc( nBytes)
			#define CorCallocWithTag( nItem, nBytes, tag)   CorCalloc( nItem, nBytes)

		#endif
	#endif

	#if COR_WIN32
		#define CorSignalEvent(event)		SetEvent(event)
		#define CorMemcpy(d,s,c)         CorManMemcpy( d, s, c, FALSE)
		#define CorMemcpyAlignSrc(d,s,c) CorManMemcpy( d, s, c, TRUE)

		// With Visual Studio 2005, some regular string functions are marked as deprecated by the compiler.
		// In this case, the macros call the safer/more robust string functions under Win32 and Win64.
		#if defined(_MSC_VER)&& _MSC_VER >= 1400
#pragma warning(push)
#if (_MSC_VER >= 1500) //vs2008
#pragma warning(disable:6387)
#pragma warning(disable:6011)
#endif //end of (_MSC_VER >= 1500)
         //strsafe has a lot of code analysis warnings.
			#include <strsafe.h>
#pragma warning( pop)
			
			#undef  CorSnprintf
			#define CorSnprintf                    StringCbPrintfA
			
			#undef  CorVsnprintf
			#define CorVsnprintf                   StringCbVPrintfA
			
			#undef  CorSscanf
			#define CorSscanf                      sscanf_s
			
			#undef  CorStrncpy
			#define CorStrncpy(dest, src, count)   StringCbCopyA((dest), (count), (src))
			
			#undef  CorStricmp
			#define CorStricmp                     _stricmp
			
			#undef  CorStrnicmp
			#define CorStrnicmp                    _strnicmp
			
			#undef  CorStrncat
			#define CorStrncat(str1, str2, count)  StringCbCatA((str1), (count), (str2))
			
			#undef  CorGetch
			#define CorGetch                       _getch
			
			#undef CorStrtok
			#define CorStrtok                      strtok_s
			
			#undef CorSplitpath
			#define CorSplitpath                   _splitpath_s
			
			#undef CorMakepath
			#define CorMakepath                    _makepath_s
			
			#undef CorFopen
			#define CorFopen                       fopen_s
			
			#undef CorItoa
			#define CorItoa                        _itoa_s
			
			#undef CorLocaltime
			#define CorLocaltime( tm, time)        localtime_s( (tm), (time))
			
			#undef CorLocaltime64
			#define CorLocaltime64( tm, time)      _localtime64_s( (tm), (time))
			
			#undef CorStrupr
			#define CorStrupr                      _strupr_s
			
			#undef CorGcvt
			#define CorGcvt                        _gcvt_s

         #undef CorSpawnlp
         #define CorSpawnlp                     _spawnlp

         #define CorAtomicIncrement( var ) InterlockedIncrement( var )
         #define CorAtomicDecrement( var ) InterlockedDecrement( var )
         #define CorAtomicSwap( prt, comperand, newValue ) InterlockedCompareExchange ( prt, newValue, comperand)

		#else

         #undef CorMemcpy_s
         #define CorMemcpy_s( dst, dstSize, src, count)  memcpy( dst, src, count)

         #undef CorStrcpy_s
         #define CorStrcpy_s( str1, dstSize, str2)        strcpy( str1, str2)

			#undef CorLocaltime
			#define CorLocaltime(tm, time)((tm) = localtime((time)))
		
			#undef CorLocaltime64
			#define CorLocaltime64(tm, time)((tm) = _localtime64((time)))

		#endif
	#endif
	#if COR_C60
		#define CorSignalEvent(event)		CorManSetEvent(event)//_event_set((pointer)event,1)
		#define CorMemcpy(d,s,c)         memcpy( d, s, c, FALSE)
		#define CorMemcpyAlignSrc(d,s,c) memcpy( d, s, c)
	#endif
	#if COR_I960
		#define EVENT_MAGIC_NUMBER 0xCAFECAFE
		#define CorSignalEvent(event)    *(PUINT32)(event)= EVENT_MAGIC_NUMBER
		#define CorMemcpy(d,s,c)         memcpy( d, s, c)
		#define CorMemcpyAlignSrc(d,s,c) memcpy( d, s, c)
	#endif
	#if COR_IOP321
		#define EVENT_MAGIC_NUMBER 0xA55AA55A
		#define CorSignalEvent(event)    *(PUINT32)(event)= EVENT_MAGIC_NUMBER
		#define CorMemcpy(d,s,c)         memcpy( d, s, c)
		#define CorMemcpyAlignSrc(d,s,c) memcpy( d, s, c)
	#endif
	#if COR_LINUX
		#include <sys/syscall.h>
		#undef CorLocaltime
		#define CorLocaltime( tm, time)        ((tm) = localtime((time)))
		#undef CorLocaltime64
		#define CorLocaltime64( tm, time)        ((tm) = localtime((time)))

      #undef  CorSnprintf
      #define CorSnprintf                    snprintf

      #undef  CorSprintf_s
      #define CorSprintf_s                   snprintf

      #undef  CorVsnprintf
      #define CorVsnprintf                   vsnprintf

      #undef CorStrnicmp
      #define CorStrnicmp strncasecmp

      #undef CorStricmp
      #define CorStricmp strcasecmp

      #undef CorMemcpy_s
      #define CorMemcpy_s( dst, dstSize, src, count)  memcpy( dst, src, count)

      #undef CorStrncpy_s
      #define CorStrncpy_s( dst, dstSize, src, count)   strncpy( dst, src, count)

	  #undef CorStrcpy_s
	  #define CorStrcpy_s( dst, dstSize, src) strncpy(dst,src,MIN(dstSize,strlen(src))) // Most close equivalent to strcpy_s using strncpy

      #undef CorGetpid
      #define CorGetpid getpid

      #undef CorGettid
      #define CorGettid()  syscall( SYS_gettid)

      #undef CorProcessIdEquale
      #define CorProcessIdEquale( _t1, _t2 ) ((_t1) == (_t2)) //( pthread_equal((_t1), (_t2)) )
  
      #define CorAtomicIncrement( var ) (__sync_fetch_and_add( var, 1 )+1)
      #define CorAtomicDecrement( var ) (__sync_fetch_and_sub( var, 1 )-1)
      #define CorAtomicSwap( prt, comperand, newValue ) __sync_val_compare_and_swap ( prt, comperand, newValue)


	#endif
	#if defined(POSIX_HOSTPC)
		// For Linux environments with libCorW32.
		#undef  CorSscanf
		#define CorSscanf    cor_sscanf
	#endif

#endif

#endif   // _CORLIB_H_
