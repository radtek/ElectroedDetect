//
// Unpacking directive function
//

#include <corenv.h>

#if COR_I960
	#pragma align
#endif

#if COR_WIN32 || COR_NTKERNEL
	#ifdef _MSC_VER
		#pragma pack()
	#endif

	#ifdef __BORLANDC__
      #ifdef COR_BORLANDC64
   		#pragma pack()
      #else
   		#pragma option -a.
      #endif
	#endif
#endif

#ifdef COR_POWERPC
 		#pragma pack() 		
#endif

#if COR_ATMEL_AT91
	#pragma pack()
#endif

#if COR_CYGWIN
	#pragma pack()
#endif
