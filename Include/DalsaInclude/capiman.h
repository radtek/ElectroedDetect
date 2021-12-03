//
// Coreco API - Manager functions.
//

#ifndef _CAPIMAN_H_
#define _CAPIMAN_H_

#include <capidef.h>
#include <capimsg.h>

#define CORMAN_CORECO_CMD		0x80000000
#define CORMAN_USER_CMD			0xa0000000

// Internal use (file and line are implicit)
#define CorManLogEx( logtype, log) _CorManLogEx( logtype, log, __FILE__, __LINE__)
#define CorManLog( status)         _CorManLog( status, __FILE__, __LINE__)

// External use (allows specifying user file and line)
#define CorManLogMessage   _CorManLogEx
#define CorManLogStatus    _CorManLog

#if COR_WIN32
   #define CORMANLOG_AND_RETURN(status) { CorManLog(status); return status; }
#define CORMANLOG_AND_RETURN_CONTEXT(status, msg) { CorManSetStatusContext(status, msg); CORMANLOG_AND_RETURN(status); }
#else
	#define CORMANLOG_AND_RETURN(status) { return status; }
#endif

/* Version Manager Value */
#define CORMAN_VAL_VERSION_TYPE_MASK			0x0000FFFF
#define CORMAN_VAL_VERSION_ONBOARD				0x00010000
#define CORMAN_VAL_VERSION_SAPERA				0x00000001
#define CORMAN_VAL_VERSION_ONBOARD_SAPERA	 	(CORMAN_VAL_VERSION_SAPERA | CORMAN_VAL_VERSION_ONBOARD)
#define CORMAN_VAL_VERSION_DRIVER				0x00000002
#define CORMAN_VAL_VERSION_ONBOARD_DRIVER	 	(CORMAN_VAL_VERSION_DRIVER | CORMAN_VAL_VERSION_ONBOARD)

/* Version Manager macro */
#define CORMAN_VERSION_MAJOR(value)		((value & 0xFFC00000) >> 22)
#define CORMAN_VERSION_MINOR(value)		((value & 0x003FFC00) >> 10)
#define CORMAN_VERSION_BETA(value)		(value & 0x000003FF)


//
// Component Version Related Definitions
//
#define CORMAN_COMPONENT_ID_SAPERA_DRIVER		0x1000	// driverS.dll version
#define CORMAN_COMPONENT_ID_CXM_DRIVER		   0x1001   // driverX.cxm version
#define CORMAN_COMPONENT_ID_LOW_LEVEL_DRIVER	0x1002	// driverL.dll version
#define CORMAN_COMPONENT_ID_KERNEL_DRIVER		0x1003	// driver.sys version
#define CORMAN_COMPONENT_ID_SAPERA_LIBRARY   0x1004   // corapi.dll version
#define CORMAN_COMPONENT_ID_USER_DEFINED		0x0000	// device dependent for on-device firmware.

#define CORMAN_COMPONENT_ID_VERSION_TYPE_OLD 0  // Only Version Information is available in the format of Major/Minor/Beta as 
                                                // defined by the obsolete function CorManGetVersion.
#define CORMAN_COMPONENT_ID_VERSION_TYPE_NEW 1  // Only Version Information is available in the format of Major/Minor/Release/Build
                                                // that follows the CBH_PRODUCT_VERSION data structure.
#define CORMAN_COMPONENT_ID_VERSION_TYPE_CBN 2  // CBN Information is available
#define CORMAN_COMPONENT_ID_VERSION_TYPE_CBH 3  // CBH Information is available

#define CORMAN_COMPONENT_VERSION_INFO_VERSION_OFFSET  0
#define CORMAN_COMPONENT_VERSION_INFO_TYPE_OFFSET     1
#define CORMAN_COMPONENT_VERSION_INFO_NAME_OFFSET     2
#define CORMAN_COMPONENT_VERSION_INFO_DATA            66

#define CORMAN_COMPONENT_VERSION_OLD_MAJOR(value)		((value & 0xFFC00000) >> 22)
#define CORMAN_COMPONENT_VERSION_OLD_MINOR(value)		((value & 0x003FFC00) >> 10)
#define CORMAN_COMPONENT_VERSION_OLD_BETA(value)		   (value & 0x000003FF)

#define CORMAN_COMPONENT_STATUS_NOT_FOUND         0x00000000  // HW Component & Firmware are not present.
#define CORMAN_COMPONENT_STATUS_HW_DEVICE_PRESENT 0x00000001  // HW device is present.
#define CORMAN_COMPONENT_STATUS_PRESENT           0x00000002  // Component/Firmware is present
#define CORMAN_COMPONENT_STATUS_ACTIVE            0x00000004  // Component/Firmware is active (ie. loaded)
#define CORMAN_COMPONENT_STATUS_LOCKED            0x00000008  // Component/Firmware is locked (usually in flash memory).
#define CORMAN_COMPONENT_STATUS_NOT_LOCKED        0x00000010  // Component/Firmware is not locked (usually in flash memory)
#define CORMAN_COMPONENT_STATUS_NOT_ACTIVE        0x00000020  // Component/Firmware is not active (ie. loaded)

#define CORMAN_COMPONENT_VERSION_STRUCTURE   1     // Version 1, first version.

typedef struct
{
   UINT32 version;      // Version of this structure
   UINT32 type;         // Type of version information returned
   UINT32 status;       // Status of component
   UINT32 reserved[8];  // For Future use.
   char   name[64];     // Name of component
} CORMAN_COMPONENT_VERSION, *PCORMAN_COMPONENT_VERSION;


//
// Sapera LT Version Information Related Definitions
//
#define CORMAN_VAL_SAPERA_LICENSE_RUNTIME   0x01
#define CORMAN_VAL_SAPERA_LICENSE_EVAL      0x02
#define CORMAN_VAL_SAPERA_LICENSE_SDK       0x04

typedef struct
{
   // Version number = major.minor.revision.build (e.g., 6.12.01.0712)
   UINT32 major;
   UINT32 minor;
   UINT32 revision;
   UINT32 build;
   UINT32 licenseType;        // License type = runtime or evaluation or full SDK
   UINT32 evalDaysRemaining;  // Number of days left for evaluation version
} CORMAN_SAPERA_VERSION_INFO, *PCORMAN_SAPERA_VERSION_INFO;

//
// Definitions related to new callback mechanism
//
typedef struct
{
   // Standard fields
   UINT32 eventCount;
   UINT32 numEventIndexes;    // If event was registered using an index, otherwise 0
   UINT32 eventType;          // If event was registered using bit fields, otherwise 0
   UINT64 hostTimeStamp;
   UINT64 auxTimeStamp;       // For example, a hardware generated time stamp
   UINT32 eventTypeEx;        // If module requires more than 32 event in the bitfield.

   // For future expansion of the standard fields
   UINT32 reserved1;
   UINT32 reserved2;
   UINT32 reserved3;

   // Can be used freely by drivers
   UINT32 generic0;           // Example: featureIndex for 'Feature Change' event
   UINT32 generic1;
   UINT32 generic2;
   UINT32 generic3;

   UINT32 customSize;         // Number of bytes of additional custom fields
} CALLBACK_EXTRA_INFO, *PCALLBACK_EXTRA_INFO;

#define CORMAN_CALLBACK_TYPE_UNDEFINED    0
#define CORMAN_CALLBACK_TYPE_ACQDEVICE    1
#define CORMAN_CALLBACK_TYPE_MANAGER      2


//
// Event types for CorManRegisterCallbackEx
// Note that RESOURCE_INFO_CHANGED is only meaningful for Sapera++
//
#define CORMAN_VAL_EVENT_TYPE_SERVER_NEW              0x00000001
#define CORMAN_VAL_EVENT_TYPE_SERVER_DISCONNECTED     0x00000002
#define CORMAN_VAL_EVENT_TYPE_SERVER_CONNECTED        0x00000004
#define CORMAN_VAL_EVENT_TYPE_SERVER_DATABASE_FULL    0x00000008
#define CORMAN_VAL_EVENT_TYPE_RESOURCE_INFO_CHANGED   0x00000010
#define CORMAN_VAL_EVENT_TYPE_SERVER_NOT_AVAILABLE    0x00000020
#define CORMAN_VAL_EVENT_TYPE_SERVER_AVAILABLE        0x00000040
#define CORMAN_VAL_EVENT_TYPE_SERVER_CONNECTION_DROP  0x00000080
#define CORMAN_VAL_EVENT_TYPE_SERVER_ERROR            0x00000100
#define CORMAN_VAL_EVENT_TYPE_PRODUCT_SPECIFIC        0x00000200
#define CORMAN_VAL_EVENT_TYPE_SERVER_FILE             0x00000400

#define CORMAN_VAL_EVENT_TYPE_MASK                    0x000007ff

// Obsolete event types
#define CORMAN_VAL_EVENT_TYPE_SERVER_NOT_ACCESSIBLE   CORMAN_VAL_EVENT_TYPE_SERVER_DISCONNECTED
#define CORMAN_VAL_EVENT_TYPE_SERVER_ACCESSIBLE       CORMAN_VAL_EVENT_TYPE_SERVER_CONNECTED

//
// State definitions for CorManGetServerState
//
#define CORMAN_VAL_SERVER_STATE_AVAILABLE       0x00000001
#define CORMAN_VAL_SERVER_STATE_DISCONNECTED    0x00000002
#define CORMAN_VAL_SERVER_STATE_USED            0x00000004
#define CORMAN_VAL_SERVER_STATE_CONNECTION_DROP 0x00000008
#define CORMAN_VAL_SERVER_STATE_ERROR           0x00000010

//
// Resource type definitions for CorManIsResourceAvailable and CorManGetResourceName
//
#define CORMAN_VAL_RESOURCE_TYPE_ACQ         0
#define CORMAN_VAL_RESOURCE_TYPE_DISPLAY     1
#define CORMAN_VAL_RESOURCE_TYPE_CAB         2
#define CORMAN_VAL_RESOURCE_TYPE_PIXPRO      3
#define CORMAN_VAL_RESOURCE_TYPE_RTPRO       CORMAN_VAL_RESOURCE_TYPE_PIXPRO
#define CORMAN_VAL_RESOURCE_TYPE_DSP         4
#define CORMAN_VAL_RESOURCE_TYPE_GRAPHIC     5
#define CORMAN_VAL_RESOURCE_TYPE_GIO         6
#define CORMAN_VAL_RESOURCE_TYPE_COUNTER     7
#define CORMAN_VAL_RESOURCE_TYPE_ACQDEVICE   8

//
// 'Server Type' definitions for CorManDetectAllServers
//
#define CORMAN_VAL_DETECTION_SERVER_TYPE_GENCP  0x00000001
#define CORMAN_VAL_DETECTION_SERVER_TYPE_ALL    0x00000001

#ifdef __cplusplus
extern "C" {
#endif

/* Application programming interface */
CORSTATUS CORAPIFUNC CorManAllocCallbackQueue( UINT32 size);
CORSTATUS CORAPIFUNC CorManFreeCallbackQueue( void);

CORSTATUS CORAPIFUNC CorManRegisterCallback( CORSERVER hServer, PCORMANCALLBACK manCallback);
CORSTATUS CORAPIFUNC CorManUnregisterCallback( CORSERVER hServer);

CORSTATUS CORAPIFUNC CorManRegisterCallbackEx( UINT32 eventType, PCOREVENTINFOCALLBACK callback, void *context);
CORSTATUS CORAPIFUNC CorManUnregisterCallbackEx( void);

CORSTATUS CORAPIFUNC CorManUserCmd( CORSERVER hServer, UINT32 cmd, void *inData, UINT32 inDataSize, void *outData, UINT32 outDataSize);
CORSTATUS CORAPIFUNC CorManControl( CORSERVER hServer, UINT32 cmd, void *inData, UINT32 inDataSize, void *outData, UINT32 outDataSize);
CORSTATUS CORAPIFUNC CorManInternalCmd( CORSERVER hServer, UINT32 cmd, void *inData, UINT32 inDataSize, void *outData, UINT32 outDataSize);

CORSTATUS CORAPIFUNC CorManCallback( CORSERVER hServer, CAPIMSG_ADDRESS from, PCORCALLBACK callback, void *context, UINT32 eventType, UINT32 eventCount);
CORSTATUS CORAPIFUNC CorManCallbackEx( CORSERVER hServer, CAPIMSG_ADDRESS from, PCOREVENTINFOCALLBACK callback, void *context, UINT32 callbackType, PCALLBACK_EXTRA_INFO extraInfo, PUINT32 eventIndexBuf, const void *customBuf);
CORSTATUS CORAPIFUNC CorManMsgCallback( CORSERVER hServer, CAPIMSG_ADDRESS from, PCORMSGCALLBACK callback, void *context, UINT32 cmd, void *inData, UINT32 inDataSize, void *outData, UINT32 outDataSize);

CORSTATUS CORAPIFUNC CorManQueueCallback( CORSERVER hServer, CAPIMSG_ADDRESS from, PCORCALLBACK callback, void *context, UINT32 eventType, UINT32 eventCount);
CORSTATUS CORAPIFUNC CorManExecuteCallback( void);

CORSTATUS CORAPIFUNC _CorManLogEx ( UINT32 logtype, PCSTR log, PCSTR module, UINT32 line);
CORSTATUS CORAPIFUNC _CorManLog   ( CORSTATUS status, PCSTR module, UINT32 line);

CORSTATUS CORAPIFUNC CorManGetHandleByIndex( CORSERVER hServer, UINT32 index, PCORHANDLE pHandle);
CORSTATUS CORAPIFUNC CorManGetHandleByName( CORSERVER hServer, PSTR name, PCORHANDLE pHandle);

CORSTATUS CORAPIFUNC CorManGetVersion(CORSERVER hBoard, UINT32 item, void *value );
CORSTATUS CORAPIFUNC CorManGetComponentVersion(CORSERVER hServer, UINT32 componentID, PVOID pVersionInfo, UINT32 infoSize, PUINT32 pInfoSizeResult);
CORSTATUS CORAPIFUNC CorManGetSaperaVersionInfo(PCORMAN_SAPERA_VERSION_INFO pVersionInfo);

CORSTATUS CORAPIFUNC CorManGetInstallationDirectory( CORSERVER hServer, PSTR pInstalDir, UINT32 strSize);

CORSTATUS CORAPIFUNC CorManOpen(void);
CORSTATUS CORAPIFUNC CorManClose(void);

CORSTATUS CORAPIFUNC CorManConnect(CORSERVER server);
CORSTATUS CORAPIFUNC CorManDisconnect(CORSERVER server);

CORSTATUS CORAPIFUNC CorManGetServerState(CORSERVER server, PUINT32 state, PUINT32 extraInfo);
CORSTATUS CORAPIFUNC CorManIsResourceAvailable(CORSERVER server, UINT32 resourceType, UINT32 resourceIndex, PUINT32 isAvailable);
CORSTATUS CORAPIFUNC CorManGetResourceName(CORSERVER server, UINT32 resourceType, UINT32 resourceIndex, PSTR resourceName, UINT32 nameSize);

CORSTATUS CORAPIFUNC CorManIsBufferTypeSupported(CORSERVER server, UINT32 bufType, PUINT32 isSupported);
CORSTATUS CORAPIFUNC CorManWriteFile(CORSERVER hServer, PCSTR localFileName, UINT32 deviceFileIndex);

CORSTATUS CORAPIFUNC CorManDetectAllServers(UINT32 serverType);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIMAN_H_
