//
// Coreco log manager definitions. 
//

#ifndef _CORLOGID_H_
#define _CORLOGID_H_

#include <corenv.h>
#include "cpackd.h"

#define CORLOG_MAXLOGSIZE	256
#define CORLOG_MAXFILESIZE 	256

#if !COR_NTKERNEL
typedef struct COR_PACK _TIME_FIELDS
{
    short Year;
    short Month;
    short Day;
    short Hour;
    short Minute;
    short Second;
    short Milliseconds;
    short Weekday;
} TIME_FIELDS;
#endif

typedef struct COR_PACK
{
	PVOID          owner;
	TIME_FIELDS   	time;
	unsigned long 	logtype;
	char 			log[ CORLOG_MAXLOGSIZE + 1];
	char 			file[ CORLOG_MAXFILESIZE + 1];
	unsigned long 	line;
} CORLOG, *PCORLOG;

#if !COR_LINUX
typedef struct COR_PACK
{
	VOID *POINTER_32 owner;
	TIME_FIELDS   	time;
	unsigned long 	logtype;
	char 			log[ CORLOG_MAXLOGSIZE + 1];
	char 			file[ CORLOG_MAXFILESIZE + 1];
	unsigned long 	line;
} CORLOG_32, *PCORLOG_32;
#endif

#define CORLOG_TYPE_MAX			4

#define CORLOG_TYPEID_ERR	0	//	ERRORS			
#define CORLOG_TYPEID_FAT	1	//	FATAL ERRORS	
#define CORLOG_TYPEID_WRN	2	//	WARNINGS			
#define CORLOG_TYPEID_INF	3	//	INFORMATIONS	

#include "cunpackd.h"

#endif   // _CORLOGID_H_
