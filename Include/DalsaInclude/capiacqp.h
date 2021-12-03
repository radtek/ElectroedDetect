//
// Coreco API - Acquisition control functions.
//

#ifndef _CAPIACQP_H_
#define _CAPIACQP_H_

#include <capidef.h>
#include <capiacqd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Application programming interface */
CORSTATUS CORAPIFUNC CorAcqResetModule( CORSERVER hServer);

CORSTATUS CORAPIFUNC CorAcqGetCount(CORSERVER hServer, PUINT32 count);
CORSTATUS CORAPIFUNC CorAcqGetHandle(CORSERVER hServer, UINT32 index, CORACQ *hAcq);
CORSTATUS CORAPIFUNC CorAcqRelease(CORACQ hAcq);
CORSTATUS CORAPIFUNC CorAcqReset (CORACQ hAcq);

CORSTATUS CORAPIFUNC CorAcqGetCap( CORACQ hAcq, UINT32 cap, void *value );

CORSTATUS CORAPIFUNC CorAcqGetPrm  ( CORACQ hAcq, UINT32 prm, void *value );
CORSTATUS CORAPIFUNC CorAcqSetPrm  ( CORACQ hAcq, UINT32 prm, UINT32 value );
CORSTATUS CORAPIFUNC CorAcqSetPrmEx( CORACQ hAcq, UINT32 prm, const void *value );

CORSTATUS CORAPIFUNC CorAcqUnlock( CORACQ hAcq, CORVIC hVic, CORCAM hCam );

CORSTATUS CORAPIFUNC CorAcqGetPrms( CORACQ hAcq, CORVIC hVic, CORCAM hCam, UINT32 toLock );
CORSTATUS CORAPIFUNC CorAcqSetPrms( CORACQ hAcq, CORVIC hVic, CORCAM hCam, UINT32 toUnlock );

CORSTATUS CORAPIFUNC CorAcqGetLut( CORACQ hAcq, CORLUT hLut, UINT32 lutNumber );
CORSTATUS CORAPIFUNC CorAcqSetLut( CORACQ hAcq, CORLUT hLut, UINT32 lutNumber );

CORSTATUS CORAPIFUNC CorAcqCustomCmd( CORACQ acq, UINT32 cmd, const void *inData, UINT32 inSize, void *outData, UINT32 outSize);
CORSTATUS CORAPIFUNC CorAcqInternalCmd( CORACQ acq, UINT32 cmd, const void *inData, UINT32 inSize, void *outData, UINT32 outSize);

CORSTATUS CORAPIFUNC CorAcqRegisterCallback( CORACQ hAcq, UINT32 eventType, PCORCALLBACK callback, void *context);
CORSTATUS CORAPIFUNC CorAcqRegisterCallbackEx( CORACQ hAcq, UINT64 eventType, PCOREVENTINFOCALLBACK callback, void *context);
CORSTATUS CORAPIFUNC CorAcqUnregisterCallback( CORACQ hAcq, PCORCALLBACK callback);
CORSTATUS CORAPIFUNC CorAcqUnregisterCallbackEx( CORACQ hAcq, PCOREVENTINFOCALLBACK callback);

CORSTATUS CORAPIFUNC CorAcqGetCamIoControl( CORACQ hAcq, PCSTR label, UINT32 *value);
CORSTATUS CORAPIFUNC CorAcqSetCamIoControl( CORACQ hAcq, PCSTR label, UINT32 value);

CORSTATUS CORAPIFUNC CorAcqSoftwareTrigger( CORACQ hAcq, UINT32 triggerType);

CORSTATUS CORAPIFUNC CorAcqDetectSync( CORACQ hAcq, PCORACQ_DETECT_SYNC detectSync);

CORSTATUS CORAPIFUNC CorAcqNewFlatfield( CORACQ hAcq, UINT32 *flatfieldNumber);
CORSTATUS CORAPIFUNC CorAcqFreeFlatfield(CORACQ hAcq, UINT32 flatfieldNumber);
CORSTATUS CORAPIFUNC CorAcqGetFlatfield( CORACQ hAcq, UINT32 flatfieldNumber, CORBUFFER hBufferGain, CORBUFFER hBufferOffset);
CORSTATUS CORAPIFUNC CorAcqSetFlatfield( CORACQ hAcq, UINT32 flatfieldNumber, CORBUFFER hBufferGain, CORBUFFER hBufferOffset);
CORSTATUS CORAPIFUNC CorAcqGetSerialPortName( CORACQ hAcq, UINT32 portNameLengthMax, char* szSerialPortName);

CORSTATUS CORAPIFUNC CorAcqNewDynamicLut( CORACQ hAcq, UINT32 *lutNumber);
CORSTATUS CORAPIFUNC CorAcqFreeDynamicLut(CORACQ hAcq, UINT32 lutNumber);
CORSTATUS CORAPIFUNC CorAcqGetDynamicLut( CORACQ hAcq, UINT32 lutNumber, CORLUT hLut);
CORSTATUS CORAPIFUNC CorAcqSetDynamicLut( CORACQ hAcq, UINT32 lutNumber, CORLUT hLut);

CORSTATUS CORAPIFUNC CorAcqSetImageFilter( CORACQ hAcq, UINT32 imageFilterNumber, CORBUFFER hBufferKernel);
CORSTATUS CORAPIFUNC CorAcqGetImageFilter( CORACQ hAcq, UINT32 imageFilterNumber, CORBUFFER hBufferKernel);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIACQP_H_
