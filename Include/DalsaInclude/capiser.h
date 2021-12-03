//
// Coreco API - Serial port module functions
//

#ifndef _CAPISER_H_
#define _CAPISER_H_

#include <capidef.h>

/******************************************************************************
*	Serial port related capabilities
******************************************************************************/

#define CORSERIAL_CAP_FIRST      0
#define CORSERIAL_CAP(n, size)   ((((n) + CORSERIAL_CAP_FIRST) << 16) | (size))

#define CORSERIAL_CAP_BAUD_RATE        CORSERIAL_CAP(0x00, 4)
#define CORSERIAL_CAP_DATA_BITS        CORSERIAL_CAP(0x01, 4)
#define CORSERIAL_CAP_PARITY           CORSERIAL_CAP(0x02, 4)
#define CORSERIAL_CAP_STOP_BITS        CORSERIAL_CAP(0x03, 4)
#define CORSERIAL_CAP_FLOW_CONTROL     CORSERIAL_CAP(0x04, 4)

#define CORSERIAL_CAP_LAST             (CORSERIAL_CAP_FIRST + 0x07)


/******************************************************************************
*	Serial port related parameters
******************************************************************************/

#define CORSERIAL_PRM_FIRST      0
#define CORSERIAL_PRM(n, size)   ((((n) + CORSERIAL_PRM_FIRST) << 16) | (size))

// Read/write parameters
#define CORSERIAL_PRM_BAUD_RATE        CORSERIAL_PRM(0x00, 4)
#define CORSERIAL_PRM_DATA_BITS        CORSERIAL_PRM(0x01, 4)
#define CORSERIAL_PRM_PARITY           CORSERIAL_PRM(0x02, 4)
#define CORSERIAL_PRM_STOP_BITS        CORSERIAL_PRM(0x03, 4)
#define CORSERIAL_PRM_FLOW_CONTROL     CORSERIAL_PRM(0x04, 4)
// Read-only parameter
#define CORSERIAL_PRM_DEVICE_HANDLE    CORSERIAL_PRM(0x05, 4)
// Private to serial port module
#define CORSERIAL_PRM_COM_ID           CORSERIAL_PRM(0x06, 4)

#define CORSERIAL_PRM_LAST             (CORSERIAL_PRM_FIRST + 0x07)


/******************************************************************************
*	Serial port related values
******************************************************************************/

// Baud Rate
#define CORSERIAL_VAL_BAUD_RATE_110          0x00000001
#define CORSERIAL_VAL_BAUD_RATE_300          0x00000002
#define CORSERIAL_VAL_BAUD_RATE_600          0x00000004
#define CORSERIAL_VAL_BAUD_RATE_1200         0x00000008
#define CORSERIAL_VAL_BAUD_RATE_2400         0x00000010
#define CORSERIAL_VAL_BAUD_RATE_4800         0x00000020
#define CORSERIAL_VAL_BAUD_RATE_9600         0x00000040
#define CORSERIAL_VAL_BAUD_RATE_19200        0x00000080
#define CORSERIAL_VAL_BAUD_RATE_38400        0x00000100
#define CORSERIAL_VAL_BAUD_RATE_57600        0x00000200
#define CORSERIAL_VAL_BAUD_RATE_115200       0x00000400
#define CORSERIAL_VAL_BAUD_RATE_230400       0x00000800
#define CORSERIAL_VAL_BAUD_RATE_460800       0x00001000
#define CORSERIAL_VAL_BAUD_RATE_921600       0x00002000
#define CORSERIAL_VAL_BAUD_RATE_MASK         0x00003fff

// Number of data bits
#define CORSERIAL_VAL_DATA_BITS_4            0x00000001
#define CORSERIAL_VAL_DATA_BITS_5            0x00000002
#define CORSERIAL_VAL_DATA_BITS_6            0x00000004
#define CORSERIAL_VAL_DATA_BITS_7            0x00000008
#define CORSERIAL_VAL_DATA_BITS_8            0x00000010
#define CORSERIAL_VAL_DATA_BITS_MASK         0x0000001f

// Parity method
#define CORSERIAL_VAL_PARITY_NONE            0x00000001
#define CORSERIAL_VAL_PARITY_EVEN            0x00000002
#define CORSERIAL_VAL_PARITY_ODD             0x00000004
#define CORSERIAL_VAL_PARITY_MARK            0x00000008
#define CORSERIAL_VAL_PARITY_SPACE           0x00000010
#define CORSERIAL_VAL_PARITY_MASK            0x0000001f

// Number of stop bits
#define CORSERIAL_VAL_STOP_BITS_1            0x00000001
#define CORSERIAL_VAL_STOP_BITS_1_5          0x00000002
#define CORSERIAL_VAL_STOP_BITS_2            0x00000004
#define CORSERIAL_VAL_STOP_BITS_MASK         0x00000007

// Flow control method
#define CORSERIAL_VAL_FLOW_CONTROL_NONE      0x00000001
#define CORSERIAL_VAL_FLOW_CONTROL_XON_XOFF  0x00000002
#define CORSERIAL_VAL_FLOW_CONTROL_HARDWARE  0x00000004
#define CORSERIAL_VAL_FLOW_CONTROL_MASK      0x00000007


/******************************************************************************
*	Application programming interface
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

CORSTATUS CORAPIFUNC CorSerialGetCount(CORSERVER hMainServer, CORSERVER hPortServer, PUINT32 count);
CORSTATUS CORAPIFUNC CorSerialResetModule(CORSERVER hServer);
CORSTATUS CORAPIFUNC CorSerialGetHandle(CORSERVER hMainServer, CORSERVER hPortServer, UINT32 index, PCORSERIAL hSerial);
CORSTATUS CORAPIFUNC CorSerialGetHandleByOwner(CORSERVER hServer, CORACQ hAcq, PCORSERIAL hSerial);
CORSTATUS CORAPIFUNC CorSerialGetHandleByName(CORSERVER hServer, const char *name, PCORSERIAL hSerial);
CORSTATUS CORAPIFUNC CorSerialRelease(CORSERIAL hSerial);
CORSTATUS CORAPIFUNC CorSerialReset(CORSERIAL hSerial);

CORSTATUS CORAPIFUNC CorSerialGetCap(CORSERIAL hSerial, UINT32 cap, void *value);
CORSTATUS CORAPIFUNC CorSerialGetPrm(CORSERIAL hSerial, UINT32 prm, void *value);
CORSTATUS CORAPIFUNC CorSerialSetPrm(CORSERIAL hSerial, UINT32 prm, UINT32 value);
CORSTATUS CORAPIFUNC CorSerialSetPrmEx(CORSERIAL hSerial, UINT32 prm, const void  *value);

CORSTATUS CORAPIFUNC CorSerialRead(CORSERIAL hSerial, void *array, UINT32 size, PUINT32 bytesRead, BOOLEAN wait);
CORSTATUS CORAPIFUNC CorSerialWrite(CORSERIAL hSerial, const void *array, UINT32 size, PUINT32 bytesWritten, BOOLEAN wait);

#ifdef __cplusplus
}
#endif

#endif   // _CAPISER_H_
