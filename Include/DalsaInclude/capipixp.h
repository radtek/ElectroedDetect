//
// Coreco API - Pixel Processor module functions.
//

#ifndef _CAPIPIXP_H_
#define _CAPIPIXP_H_

#include <capidef.h>
#include <capiacqd.h>

/****************************************************************************
*	Pixel Processor Capabilities
****************************************************************************/
#define CORPIXPRO_CAP_FIRST			0
#define CORPIXPRO_CAP( n, size)	    ((((n) + CORPIXPRO_CAP_FIRST) << 16) | (size))

#define CORPIXPRO_CAP_FRAME_BUFFER_BASE_ADDRESS_BANK0			CORPIXPRO_CAP( 0, 4)
#define CORPIXPRO_CAP_FRAME_BUFFER_BASE_ADDRESS_BANK1			CORPIXPRO_CAP( 1, 4)
#define CORPIXPRO_CAP_LINE_BUFFER_BASE_ADDRESS_BANK0			CORPIXPRO_CAP( 2, 4)
#define CORPIXPRO_CAP_LINE_BUFFER_BASE_ADDRESS_BANK1			CORPIXPRO_CAP( 3, 4)

#define CORPIXPRO_CAP_FRAME_BUFFER_SIZE_BANK0					CORPIXPRO_CAP( 4, 4)
#define CORPIXPRO_CAP_FRAME_BUFFER_SIZE_BANK1					CORPIXPRO_CAP( 5, 4)
#define CORPIXPRO_CAP_LINE_BUFFER_SIZE_BANK0					CORPIXPRO_CAP( 6, 4)
#define CORPIXPRO_CAP_LINE_BUFFER_SIZE_BANK1					CORPIXPRO_CAP( 7, 4)
#define CORPIXPRO_CAP_EVENT_TYPE          						CORPIXPRO_CAP( 8, 4)

#define CORPIXPRO_CAP_FPGA_CORE_SPEED							CORPIXPRO_CAP( 9, 4)
#define CORPIXPRO_CAP_FPGA_CTRL_SPEED							CORPIXPRO_CAP(10, 4)

#define CORPIXPRO_CAP_FPGA_CORE_ID								CORPIXPRO_CAP(11, 4)
#define CORPIXPRO_CAP_FPGA_CTRL_ID								CORPIXPRO_CAP(12, 4)
#define CORPIXPRO_CAP_COMPONENTS_REVISION  						CORPIXPRO_CAP(13, 4)

#define CORPIXPRO_CAP_FRAME_BUFFER_SIZE_BANK2					CORPIXPRO_CAP(14, 4)
#define CORPIXPRO_CAP_FRAME_BUFFER_SIZE_BANK3					CORPIXPRO_CAP(15, 4)
#define CORPIXPRO_CAP_LINE_BUFFER_SIZE_BANK2					CORPIXPRO_CAP(16, 4)
#define CORPIXPRO_CAP_LINE_BUFFER_SIZE_BANK3					CORPIXPRO_CAP(17, 4)
#define CORPIXPRO_CAP_FPGA_CORE_DEVICE							CORPIXPRO_CAP(18, 32)
#define CORPIXPRO_CAP_FPGA_CTRL_DEVICE							CORPIXPRO_CAP(19, 32)
#define CORPIXPRO_CAP_FPGA_CORE_FAMILY							CORPIXPRO_CAP(20, 4)
#define CORPIXPRO_CAP_FPGA_CTRL_FAMILY							CORPIXPRO_CAP(21, 4)

#define CORPIXPRO_CAP_MESSAGE_PRIORITY							CORPIXPRO_CAP(22, 4)
#define CORPIXPRO_CAP_MESSAGE_FLAG  							CORPIXPRO_CAP(23, 4)


/****************************************************************************
*	Pixel Processor Parameters
****************************************************************************/
#define CORPIXPRO_PRM_FIRST        0
#define CORPIXPRO_PRM( n, size)	((((n) + CORPIXPRO_PRM_FIRST) << 16) | (size))

#define CORPIXPRO_PRM_DESIGN_NUMBER					CORPIXPRO_PRM( 0x00000000, 4)
#define CORPIXPRO_PRM_DESIGN_NAME					CORPIXPRO_PRM( 0x00000001, 128)	  
#define CORPIXPRO_PRM_LABEL							CORPIXPRO_PRM(	0x00000002, 128)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK0_FORMAT			CORPIXPRO_PRM( 0x00000003, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK0_WIDTH			CORPIXPRO_PRM( 0x00000004, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK0_HEIGHT			CORPIXPRO_PRM( 0x00000005, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK0_FRAME			CORPIXPRO_PRM( 0x00000006, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK0_FIELD_ORDER	CORPIXPRO_PRM( 0x00000007, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK1_FORMAT			CORPIXPRO_PRM( 0x00000008, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK1_WIDTH			CORPIXPRO_PRM( 0x00000009, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK1_HEIGHT			CORPIXPRO_PRM( 0x0000000a, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK1_FRAME			CORPIXPRO_PRM( 0x0000000b, 4)
#define CORPIXPRO_PRM_FRAME_BUFFER_BANK1_FIELD_ORDER	CORPIXPRO_PRM( 0x0000000c, 4)
#define CORPIXPRO_PRM_INPUT_PORT0_SNAP_COUNT		CORPIXPRO_PRM( 0x0000000d, 4)
#define CORPIXPRO_PRM_INPUT_PORT0_FORMAT			CORPIXPRO_PRM( 0x0000000e, 4)
#define CORPIXPRO_PRM_INPUT_PORT0_WIDTH				CORPIXPRO_PRM( 0x0000000f, 4)
#define CORPIXPRO_PRM_INPUT_PORT0_HEIGHT			CORPIXPRO_PRM( 0x00000010, 4)
#define CORPIXPRO_PRM_INPUT_PORT0_FRAME				CORPIXPRO_PRM( 0x00000011, 4)
#define CORPIXPRO_PRM_INPUT_PORT0_FIELD_ORDER		CORPIXPRO_PRM( 0x00000012, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_FORMAT			CORPIXPRO_PRM( 0x00000013, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_WIDTH			CORPIXPRO_PRM( 0x00000014, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_HEIGHT			CORPIXPRO_PRM( 0x00000015, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_FRAME			CORPIXPRO_PRM( 0x00000016, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_FIELD_ORDER		CORPIXPRO_PRM( 0x00000017, 4)
#define CORPIXPRO_PRM_INTERRUPT						CORPIXPRO_PRM( 0x00000018, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_LABEL			CORPIXPRO_PRM( 0x00000019, 16)
#define CORPIXPRO_PRM_OUTPUT_PORT0_LENGTH			CORPIXPRO_PRM( 0x0000001a, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_BUFFER_COUNT		CORPIXPRO_PRM( 0x0000001b, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_BUFFER_INDEX		CORPIXPRO_PRM( 0x0000001c, 4)
#define CORPIXPRO_PRM_OUTPUT_PORT0_BUFFER_INFO		CORPIXPRO_PRM( 0x0000001d, CORPIXPRO_VAL_MAX_OUTPUT_BUFFER_INFO*sizeof(CORPIXPRO_OUTPUT_BUFFER_INFO))
#define CORPIXPRO_PRM_EVENT_TYPE					CORPIXPRO_PRM( 0x0000001e, 4)
#define CORPIXPRO_PRM_WAIT_STATE					CORPIXPRO_PRM( 0x0000001f, 4)
#define CORPIXPRO_PRM_ACQ_CLOCK_MULTIPLY	 		CORPIXPRO_PRM( 0x00000020, 4)
#define CORPIXPRO_PRM_DEMAND_MODE			 		CORPIXPRO_PRM( 0x00000021, 4)

/***************************************************************************
*	Pixel Processor Parameter Values
****************************************************************************/
#define CORPIXPRO_VAL_FRAME_INTERLACED		  		CORACQ_VAL_FRAME_INTERLACED
#define CORPIXPRO_VAL_FRAME_NON_INTERLACED  		CORACQ_VAL_FRAME_NON_INTERLACED
#define CORPIXPRO_VAL_FRAME_PROGRESSIVE			CORACQ_VAL_FRAME_PROGRESSIVE

#define CORPIXPRO_VAL_FIELD_ORDER_ODD_EVEN  		CORACQ_VAL_FIELD_ORDER_ODD_EVEN
#define CORPIXPRO_VAL_FIELD_ORDER_EVEN_ODD 		CORACQ_VAL_FIELD_ORDER_EVEN_ODD
#define CORPIXPRO_VAL_FIELD_ORDER_NEXT_FIELD		CORACQ_VAL_FIELD_ORDER_NEXT_FIELD

#define CORPIXPRO_VAL_LENGTH_FIX						0x00000001
#define CORPIXPRO_VAL_LENGTH_VARIABLE				0x00000002

// Standard events
#define CORPIXPRO_VAL_EVENT_TYPE_START_OF_FRAME		0x00000001
#define CORPIXPRO_VAL_EVENT_START_OF_FRAME			CORPIXPRO_VAL_EVENT_TYPE_START_OF_FRAME	// For backward compatibility
#define CORPIXPRO_VAL_EVENT_TYPE_END_OF_FRAME 		0x00000002
#define CORPIXPRO_VAL_EVENT_END_OF_FRAME 				CORPIXPRO_VAL_EVENT_TYPE_END_OF_FRAME		// For backward compatibility

// Design specific events
#define CORPIXPRO_VAL_EVENT_TYPE_INTERRUPT0			0x00010000
#define CORPIXPRO_VAL_EVENT_INTERRUPT0					CORPIXPRO_VAL_EVENT_TYPE_INTERRUPT0			// For backward compatibility
#define CORPIXPRO_VAL_EVENT_TYPE_CTRL_INTERRUPT0	0x00010000
#define CORPIXPRO_VAL_EVENT_CTRL_INTERRUPT0			CORPIXPRO_VAL_EVENT_TYPE_CTRL_INTERRUPT0	// For backward compatibility
#define CORPIXPRO_VAL_EVENT_TYPE_CORE_INTERRUPT0	0x00020000
#define CORPIXPRO_VAL_EVENT_CORE_INTERRUPT0			CORPIXPRO_VAL_EVENT_TYPE_CORE_INTERRUPT0	// For backward compatibility

#define CORPIXPRO_VAL_EVENT_TYPE_MASK           0x00030003

#define CORPIXPRO_VAL_MAX_OUTPUT_BUFFER_INFO		32

/***************************************************************************
*	FPGA ID definitions
****************************************************************************/
#define CORPIXPRO_FPGA_CTRL	0
#define CORPIXPRO_FPGA_CORE	1

/***************************************************************************
*	DPT ID definitions
****************************************************************************/
#define CORPIXPRO_DPT_CONTINUOUS	(-1L)

#define CORPIXPRO_DPT_0		0
#define CORPIXPRO_DPT_1		1
#define CORPIXPRO_DPT_2		2
#define CORPIXPRO_DPT_3		3
#define CORPIXPRO_DPT_4		4
#define CORPIXPRO_DPT_5		5
#define CORPIXPRO_DPT_6		6

/***************************************************************************
*	Write Register Block Mode definitions
****************************************************************************/
#define CORPIXPRO_REGISTER_AUTO_INCREMENT		0x00000001
#define CORPIXPRO_REGISTER_NO_INCREMENT		0x00000002

/***************************************************************************
*	Write Register Block accessType definitions
****************************************************************************/
#define CORPIXPRO_REGISTER_ACCESS_TYPE_UINT8		1
#define CORPIXPRO_REGISTER_ACCESS_TYPE_UINT16	2
#define CORPIXPRO_REGISTER_ACCESS_TYPE_UINT32	4
#define CORPIXPRO_REGISTER_ACCESS_TYPE_UINT32_UINT8	8 //access a 32 bits register as four 8 bits registers

/***************************************************************************
* Write Memory access types.
****************************************************************************/
#define CORPIXPRO_MEMACCESS_AUTO_ADDRESS_INCREMENT		1
#define CORPIXPRO_MEMACCESS_NO_ADDRESS_INCREMENT	   2

/***************************************************************************
*	FPGA type and speed
****************************************************************************/
#define CORPIXPRO_VAL_FPGA_ID_UNKNOWN				0x00000000
#define CORPIXPRO_VAL_FPGA_SPEED_UNKNOWN			0x00000000
/***************************************************************************
*	Register Page Default Values
****************************************************************************/
#define CORPIXPRO_REGISTER_PAGE_DEFAULT	15
#define CORPIXPRO_REGISTER_PAGE_LUT			15

/***************************************************************************
*	Components revison values
****************************************************************************/
#define CORPIXPRO_VAL_COMPONENTS_REVISION_DEFAULT			0
#define CORPIXPRO_VAL_COMPONENTS_REVISION_NO_CTRL			1


/***************************************************************************
*	message priority values
****************************************************************************/
#define CORPIXPRO_VAL_MESSAGE_PRIORITY_LOW						0x0004
#define CORPIXPRO_VAL_MESSAGE_PRIORITY_NORMAL					0x0020
#define CORPIXPRO_VAL_MESSAGE_PRIORITY_HIGH						0x0100

/***************************************************************************
*	message flag values
****************************************************************************/
#define CORPIXPRO_VAL_MESSAGE_FLAG_SYNCHRONOUS              0x0001
#define CORPIXPRO_VAL_MESSAGE_FLAG_ASYNCHRONOUS             0x0002       

#include "cpackd.h"

typedef struct COR_PACK
{
	UINT32 fpgaId;
	UINT32 pageId;
	UINT32 regId;
	UINT32 accessType;
	UINT32 value;
} CORPIXPRO_ON_DEMAND_COMMAND, *PCORPIXPRO_ON_DEMAND_COMMAND;

typedef struct COR_PACK
{
	UINT32 regId;
	UINT32 value;
} CORPIXPRO_REG_SET, *PCORPIXPRO_REG_SET;

typedef struct COR_PACK
{
	UINT32 startAddress;
	UINT32 countA;
	UINT32 countB;
	INT32  pitchB;
	UINT32 countC;
	INT32  pitchC;
	UINT32 countD;
	INT32  pitchD;
} CORPIXPRO_DPT, *PCORPIXPRO_DPT;


//
// WARNING: This structure cannot be modified as it will create an incompatibility
//          with drivers compiled with a different size.
//
typedef struct COR_PACK
{
	char  	label[16];
	UINT32	width;
	UINT32	height;
	UINT32	format;	
	UINT32	frame;
	UINT32	fieldOrder;
	UINT32	length;
	} CORPIXPRO_OUTPUT_BUFFER_INFO, *PCORPIXPRO_OUTPUT_BUFFER_INFO;

#include "cunpackd.h"

#ifdef __cplusplus
extern "C" {
#endif

// Application programming interface (standard)
CORSTATUS CORAPIFUNC CorPixProResetModule( CORSERVER hServer);

CORSTATUS CORAPIFUNC CorPixProGetHandle(CORSERVER hServer, UINT32 instance, CORPIXPRO *hPixPro);
CORSTATUS CORAPIFUNC CorPixProRelease(CORPIXPRO hPixPro);
CORSTATUS CORAPIFUNC CorPixProGetCount( CORSERVER hServer, PUINT32 count);
CORSTATUS CORAPIFUNC CorPixProReset(CORPIXPRO hPixPro);

CORSTATUS CORAPIFUNC CorPixProGetCap  (CORPIXPRO hPixPro, UINT32 cap, void *value);
CORSTATUS CORAPIFUNC CorPixProGetPrm  (CORPIXPRO hPixPro, UINT32 prm, void *value);
CORSTATUS CORAPIFUNC CorPixProSetPrm  (CORPIXPRO hPixPro, UINT32 prm, UINT32 value);
CORSTATUS CORAPIFUNC CorPixProSetPrmEx(CORPIXPRO hPixPro, UINT32 prm, const void  *value);

CORSTATUS CORAPIFUNC CorPixProRegisterCallback( CORPIXPRO hPixPro, UINT32 eventType, PCORCALLBACK callback, void *context);
CORSTATUS CORAPIFUNC CorPixProUnregisterCallback( CORPIXPRO hPixPro, PCORCALLBACK callback);

CORSTATUS CORAPIFUNC CorPixProRegisterCallbackEx( CORPIXPRO hPixPro, UINT32 eventType, PCOREVENTINFOCALLBACK callback, void *context);
CORSTATUS CORAPIFUNC CorPixProUnregisterCallbackEx( CORPIXPRO hPixPro, PCOREVENTINFOCALLBACK callback);

// Application programming interface (low level)
CORSTATUS CORAPIFUNC CorPixProMemoryAlloc(CORPIXPRO hPixPro, UINT32 bankId, UINT32 size, UINT32 *address);
CORSTATUS CORAPIFUNC CorPixProMemoryFree(CORPIXPRO hPixPro, UINT32 address);
CORSTATUS CORAPIFUNC CorPixProWriteDPT(CORPIXPRO hPixPro, UINT32 dptId, CORPIXPRO_DPT *dpt);
CORSTATUS CORAPIFUNC CorPixProWriteRegisters(CORPIXPRO hPixPro, UINT32 fpgaId, CORPIXPRO_REG_SET *set, UINT32 size);
CORSTATUS CORAPIFUNC CorPixProWriteRegisterBlock(CORPIXPRO hPixPro, UINT32 fpgaId, UINT32 pageId, UINT32 regId, UINT32 accessType, UINT8 *values, UINT32 size, UINT32 mode);
CORSTATUS CORAPIFUNC CorPixProReadRegisterBlock(CORPIXPRO hPixPro, UINT32 fpgaId, UINT32 pageId, UINT32 regId, UINT32 accessType, UINT8 *values, UINT32 size, UINT32 mode);
CORSTATUS CORAPIFUNC CorPixProReadRegisters(CORPIXPRO hPixPro, UINT32 fpgaId, CORPIXPRO_REG_SET *set, UINT32 size);
CORSTATUS CORAPIFUNC CorPixProLoadFpga(CORPIXPRO hPixPro, UINT32 fpgaId, PUINT8 bitStream, UINT32 size);
CORSTATUS CORAPIFUNC CorPixProLoadFpgaFromFile(CORPIXPRO hPixPro, UINT32 fpgaId, const char *filename);
CORSTATUS CORAPIFUNC CorPixProStartDPT(CORPIXPRO hPixPro, UINT32 dptId, UINT32 count);
CORSTATUS CORAPIFUNC CorPixProStopDPT(CORPIXPRO hPixPro, UINT32 dptId);
CORSTATUS CORAPIFUNC CorPixProExecuteCommand(CORPIXPRO hPixPro, CORPIXPRO_ON_DEMAND_COMMAND *cmdList ,UINT32 count);
CORSTATUS CORAPIFUNC CorPixProInternalCmd(CORPIXPRO hPixPro, UINT32 cmd, void *inData, UINT32 inDataSize, void *outData, UINT32 outDataSize);
CORSTATUS CORAPIFUNC CorPixProLoadFirmwareFromFile(CORPIXPRO hPixPro, UINT32 firmwareId, const char *filename);

CORSTATUS CORAPIFUNC CorPixProWriteMemory( CORPIXPRO hPixPro, UINT32  fpgaId, UINT32  address, void *pData, UINT32  dataSizeBytes, UINT32 flags);
CORSTATUS CORAPIFUNC CorPixProReadMemory( CORPIXPRO hPixPro, UINT32  fpgaId, UINT32  address, void *pData, UINT32  dataSizeBytes, UINT32 flags);

// pixpro communications.
CORSTATUS CORAPIFUNC CorPixProSendMessage( CORPIXPRO hPixPro, UINT32 cmd, UINT32 priority,  UINT32 flag, UINT32 maxWaitTimeMs, void *inData, UINT32 inDataSize, void *outData, UINT32 outDataSize);
CORSTATUS CORAPIFUNC CorPixProRegisterMsgCallback( CORPIXPRO hPixPro, PCORMSGCALLBACK msgCallback, void* context);
CORSTATUS CORAPIFUNC CorPixProUnregisterMsgCallback( CORPIXPRO hPixPro);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIPIXP_H_
