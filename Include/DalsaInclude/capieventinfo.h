//
// Coreco API - Event information management.
//

#ifndef _CAPIEVENTINFO_H_
#define _CAPIEVENTINFO_H_

#include "capidef.h"


/****************************************************************************
*  Event Parameters
****************************************************************************/

#define COREVENTINFO_PRM_FIRST               0
#define COREVENTINFO_PRM( n, size)           ((((n) + COREVENTINFO_PRM_FIRST) << 16) | (size))

// Common Parameters
#define COREVENTINFO_PRM_EVENT_COUNT         COREVENTINFO_PRM( 0, 4)
#define COREVENTINFO_PRM_EVENT_INDEX         COREVENTINFO_PRM( 1, 4)
#define COREVENTINFO_PRM_EVENT_TYPE          COREVENTINFO_PRM( 2, 4)
#define COREVENTINFO_PRM_HOST_TIME_STAMP     COREVENTINFO_PRM( 3, 8)    // 64-bit value
#define COREVENTINFO_PRM_AUX_TIME_STAMP      COREVENTINFO_PRM( 4, 8)    // 64-bit value

// Unnamed Parameters
#define COREVENTINFO_PRM_GENERIC_0           COREVENTINFO_PRM( 5, 4)
#define COREVENTINFO_PRM_GENERIC_1           COREVENTINFO_PRM( 6, 4)
#define COREVENTINFO_PRM_GENERIC_2           COREVENTINFO_PRM( 7, 4)
#define COREVENTINFO_PRM_GENERIC_3           COREVENTINFO_PRM( 8, 4)

// Custom Parameters
#define COREVENTINFO_PRM_CUSTOM_DATA         COREVENTINFO_PRM( 9, sizeof(void*))
#define COREVENTINFO_PRM_CUSTOM_SIZE         COREVENTINFO_PRM( 10, 4)

#define COREVENTINFO_PRM_EVENT_TYPE64        COREVENTINFO_PRM( 11, 8)

#define COREVENTINFO_PRM_LAST                (COREVENTINFO_PRM_FIRST + 12)

//
// Aliases for already defined parameters
//

// Used by "FeatureValueChanged" and "FeatureInfoChanged" events of CorAcqDevice module
#define COREVENTINFO_PRM_FEATURE_INDEX       COREVENTINFO_PRM_GENERIC_0

// Used by following events of Manager module:
//    CORMAN_VAL_EVENT_TYPE_SERVER_NEW
//    CORMAN_VAL_EVENT_TYPE_SERVER_DISCONNECTED
//    CORMAN_VAL_EVENT_TYPE_SERVER_CONNECTED
//    CORMAN_VAL_EVENT_TYPE_SERVER_NOT_AVAILABLE
//    CORMAN_VAL_EVENT_TYPE_SERVER_AVAILABLE
//    CORMAN_VAL_EVENT_TYPE_SERVER_CONNECTION_DROP
//    CORMAN_VAL_EVENT_TYPE_PRODUCT_SPECIFIC 
#define COREVENTINFO_PRM_SERVER_INDEX        COREVENTINFO_PRM_GENERIC_0

// Used by CORMAN_VAL_EVENT_TYPE_SERVER_ERROR event of Manager module
#define COREVENTINFO_PRM_SERVER_ERROR_INFO   COREVENTINFO_PRM_GENERIC_1

//Used by CORMAN_VAL_EVENT_TYPE_SERVER_FILE
#define COREVENTINFO_PRM_FILE_PERCENT_PROGRESS  COREVENTINFO_PRM_GENERIC_1

// Used by CORMAN_VAL_EVENT_TYPE_PRODUCT_SPECIFIC event of Manager module
#define COREVENTINFO_PRM_PRODUCT_SPECIFIC_EVENT COREVENTINFO_PRM_GENERIC_1
#define COREVENTINFO_PRM_PRODUCT_SPECIFIC_INFO  COREVENTINFO_PRM_GENERIC_2


/****************************************************************************
*	Application programming interface
****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

CORSTATUS CORAPIFUNC CorEventInfoGetPrm(COREVENTINFO eventInfo, UINT32 prm, void *value);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIEVENTINFO_H_
