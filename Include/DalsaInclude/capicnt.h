//
// Coreco API - Counter module functions.
//

#ifndef _CAPICNT_H_
#define _CAPICNT_H_

#include <capidef.h>
#include <capiacqd.h>

/****************************************************************************
*	Counter Capabilities
****************************************************************************/
#define CORCOUNTER_CAP_FIRST			0
#define CORCOUNTER_CAP( n, size)	    ((((n) + CORCOUNTER_CAP_FIRST) << 16) | (size))
#define 	CORCOUNTER_CAP_BASE_UNITS			CORCOUNTER_CAP( 0x00, 4)
#define 	CORCOUNTER_CAP_DIRECTION			CORCOUNTER_CAP( 0x01, 4)
#define 	CORCOUNTER_CAP_RESOLUTION			CORCOUNTER_CAP( 0x02, 4)
#define 	CORCOUNTER_CAP_DETECTION			CORCOUNTER_CAP( 0x03, 4)
#define 	CORCOUNTER_CAP_FREQ_MAX				CORCOUNTER_CAP( 0x04, 4)
#define 	CORCOUNTER_CAP_STEP					CORCOUNTER_CAP( 0x05, 4)
#define 	CORCOUNTER_CAP_EVENT_TYPE			CORCOUNTER_CAP( 0x06, 4)


/****************************************************************************
*	Counter Parameters
****************************************************************************/
#define CORCOUNTER_PRM_FIRST        0
#define CORCOUNTER_PRM( n, size)	((((n) + CORCOUNTER_PRM_FIRST) << 16) | (size))

#define CORCOUNTER_PRM_LABEL					CORCOUNTER_PRM( 0x00000000, 128)
#define CORCOUNTER_PRM_DEVICE_ID				CORCOUNTER_PRM( 0x00000001, 4)	  
#define CORCOUNTER_PRM_COUNT				CORCOUNTER_PRM( 0x00000002, 4) /*~~must be changed*/	  
#define CORCOUNTER_PRM_BASE_UNITS				CORCOUNTER_PRM( 0x00000003, 4)	  
#define CORCOUNTER_PRM_RESOLUTION				CORCOUNTER_PRM( 0x00000004, 4)	  
#define CORCOUNTER_PRM_DIRECTION				CORCOUNTER_PRM( 0x00000005, 4)	  
#define CORCOUNTER_PRM_DETECTION				CORCOUNTER_PRM( 0x00000006, 4)	  
#define CORCOUNTER_PRM_STEP				CORCOUNTER_PRM( 0x00000007, 4)	  
#define CORCOUNTER_PRM_EVENT_TYPE				CORCOUNTER_PRM( 0x00000008, 4)	  


/***************************************************************************
*	Counter Parameter Values
****************************************************************************/
#define CORCOUNTER_VAL_RISING_EDGE		0x00000001
#define CORCOUNTER_VAL_FALLING_EDGE		0x00000002

#define CORCOUNTER_VAL_DIRECTION_UP		0x00000000
#define CORCOUNTER_VAL_DIRECTION_DOWN	0x00000001

#define CORCOUNTER_VAL_BASE_UNITS_TIME	0x00000000
#define CORCOUNTER_VAL_BASE_UNITS_HS	0x00000001
#define CORCOUNTER_VAL_BASE_UNITS_VS	0x00000002
#define CORCOUNTER_VAL_BASE_UNITS_EXTERNAL 0x00000003

#define CORCOUNTER_VAL_EVENT_TYPE_ELAPSED_TIME 0x00000001

#include "cpackd.h"

typedef union COR_PACK
{
	UINT8	count8;
	UINT16	count16;
	UINT32	count32;
	UINT64	count64;
} CORCOUNT, *PCORCOUNT;

#include "cunpackd.h"

#ifdef __cplusplus
extern "C" {
#endif

// Application programming interface (standard)
CORSTATUS CORAPIFUNC CorCounterResetModule(CORSERVER hServer);

CORSTATUS CORAPIFUNC CorCounterGetHandle(CORSERVER hServer, UINT32 instance, CORCOUNTER *hCounter);
CORSTATUS CORAPIFUNC CorCounterRelease(CORCOUNTER hCounter);
CORSTATUS CORAPIFUNC CorCounterGetCount( CORSERVER hServer, PUINT32 count);
CORSTATUS CORAPIFUNC CorCounterReset(CORCOUNTER hCounter);

CORSTATUS CORAPIFUNC CorCounterGetCap(CORCOUNTER hCounter, UINT32 cap, void *value);
CORSTATUS CORAPIFUNC CorCounterGetPrm(CORCOUNTER hCounter, UINT32 prm, void *value);
CORSTATUS CORAPIFUNC CorCounterSetPrm(CORCOUNTER hCounter, UINT32 prm, UINT32 value);
CORSTATUS CORAPIFUNC CorCounterSetPrmEx(CORCOUNTER hCounter, UINT32 prm, const void  *value);

// Application programming interface (low level)

CORSTATUS CORAPIFUNC CorCounterIncrement(CORCOUNTER hCounter);
CORSTATUS CORAPIFUNC CorCounterRegisterCallback(CORCOUNTER hCounter, UINT32 eventType, UINT32 time,  void *callbackFct, void *context);
CORSTATUS CORAPIFUNC CorCounterStart(CORCOUNTER hCounter);
CORSTATUS CORAPIFUNC CorCounterStop(CORCOUNTER hCounter);
CORSTATUS CORAPIFUNC CorCounterUnregisterCallback(CORCOUNTER hCounter, void *callbackFct);

#ifdef __cplusplus
}
#endif

#endif   // _CAPICNT_H_
