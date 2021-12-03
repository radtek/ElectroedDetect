//
// Coreco API - Files parameters control functions.
//

#ifndef _CAPIPARAM_H_
#define _CAPIPARAM_H_

#include <capidef.h>


/****************************************************************************
*	Files Parameters Capabilities
*
*	Last capability #: 0
****************************************************************************/
#define CORPARAM_CAP_FIRST					0
#define CORPARAM_CAP( n, size)				((((n) + CORPARAM_CAP_FIRST) << 16) | (size))

/****************************************************************************
*
*	Files Parameters Parameters
*
****************************************************************************/
#define CORPARAM_PRM_FIRST					0
#define CORPARAM_PRM( n, size)				((((n) + CORPARAM_PRM_FIRST) << 16) | (size))

//--------------------------------------------------------------------------
//		CAB Module
#define CORPARAM_CAB_MODULE					CORSTATUS_MODULE_CAB
#define CORPARAM_PRM_CAB( n, size)			CORPARAM_PRM( n | (CORPARAM_CAB_MODULE << 8), size)

#define CORPARAM_PRM_CAB_TEMPLATE_VERSION	CORPARAM_PRM_CAB(0,1)
#define CORPARAM_PRM_CAB_TRANSFER_MODE		CORPARAM_PRM_CAB(1,4)
#define CORPARAM_PRM_CAB_BLOCK_SIZE			CORPARAM_PRM_CAB(2,4)
#define CORPARAM_PRM_CAB_CHANNEL_PORT0		CORPARAM_PRM_CAB(3,4)
#define CORPARAM_PRM_CAB_CHANNEL_PORT1		CORPARAM_PRM_CAB(4,4)
#define CORPARAM_PRM_CAB_CHANNEL_PORT2		CORPARAM_PRM_CAB(5,4)
#define CORPARAM_PRM_CAB_CHANNEL_PORT3		CORPARAM_PRM_CAB(6,4)


/****************************************************************************
*
*	Files Parameters Value
*
****************************************************************************/
#define CORPARAM_VAL_MODULE_CAB				CORSTATUS_MODULE_CAB


#ifdef __cplusplus
extern "C" {
#endif

/* Application programming interface */

/* Object creation and destruction */
CORSTATUS CORAPIFUNC CorParamFree		( CORPARAM hParam);
CORSTATUS CORAPIFUNC CorParamNew			( CORSERVER hServer, UINT32 module, CORPARAM *pParam);

/* Load/Save from/to file */
CORSTATUS CORAPIFUNC CorParamLoad		( CORPARAM hParam, PCSTR section, PCSTR filename);
CORSTATUS CORAPIFUNC CorParamSave		( CORPARAM hParam, PCSTR section, PCSTR filename);

/*Management function*/
CORSTATUS CORAPIFUNC CorParamCopy		( CORPARAM hParamSrc, CORPARAM hParamDst);

/* Modify a  Parameters	*/
CORSTATUS CORAPIFUNC CorParamGetPrm  	( CORPARAM hParam, UINT32 param, void *value); 
CORSTATUS CORAPIFUNC CorParamSetPrm  	( CORPARAM hParam, UINT32 param, UINT32 value); 
CORSTATUS CORAPIFUNC CorParamSetPrmEx	( CORPARAM hParam, UINT32 prm, const void *value);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIPARAM_H_
