//
// Design/Configuration Related API for the Pixel Processor.
//

#ifndef _DESIGN_H_
#define _DESIGN_H_

#include <corapi.h>
#include "cpackd.h"

#define CORPPLFUNC

#if COR_WIN32
	#undef CORPPLFUNC

	#if CORPPL_DEFINE_EXPORT
		#define CORPPLFUNC      __declspec(dllexport) __stdcall
	#else
		#define CORPPLFUNC      __declspec(dllimport) __stdcall
	#endif
#endif

#define CORPPL_NB_DESIGN	5		// Number of designs available through the API

/***************************************************************************
*	Bank ID definitions
****************************************************************************/
#define CORPPL_FRAME_BUFFER_BANK0		0x00000001
#define CORPPL_FRAME_BUFFER_BANK1		0x00000002
#define CORPPL_LINE_BUFFER_BANK0			0x00000004
#define CORPPL_LINE_BUFFER_BANK1			0x00000008

/***************************************************************************
*	Port ID definitions
****************************************************************************/
#define CORPPL_PORT_INPUT0					0x00000001
#define CORPPL_PORT_OUTPUT0				0x00000002
#define CORPPL_PORT_BANK					0x00000004

/***************************************************************************
*	Function IDs definitions
****************************************************************************/
#define CORPPL_FCT_PASSTHROUGH				0
#define CORPPL_FCT_INVERT_IMAGE				1
#define CORPPL_FCT_REF_IMAGE					2
#define CORPPL_FCT_ABS_IMAGE_SUB				3
#define CORPPL_FCT_UNDERFLOW_IMAGE_SUB		4
#define CORPPL_FCT_WEIGHTED_AVG				5
#define CORPPL_FCT_INTEGRATE_SCALE			6

#define CORPPL_FCT_LAST							CORPPL_FCT_INTEGRATE_SCALE


/***************************************************************************
*	Port definition
****************************************************************************/
typedef struct COR_PACK
{
	UINT32 portId;					// Port Identification: Input, Output, Memory Bank
	UINT32 bankId;					// Memory Bank Identification: Frame Buffer, Line Buffer
	UINT32 bufferId;				// Buffer Identification: location in memory bank
	UINT32 format;					// Data format of the Port
	UINT32 width;					// Width in pixels of image
	UINT32 height;					// Height in lines of image
	UINT32 frame;					// Frame Type: Interlace/Non-Interlace 
	UINT32 fieldOrder;			// Field Order of the frame
	UINT32 snapCount;				// Number of frames needed to perform an operation
} CORPPL_PORT, *PCORPPL_PORT;


/***************************************************************************
*	Function Properties definition
****************************************************************************/
typedef struct COR_PACK
{
	BOOLEAN fAvailable;						// TRUE if function is availble
	UINT32  bankId;							// Memory Bank where operation can be performed
} CORPPL_FCT_PROP, *PCORPPL_FCT_PROP;


/***************************************************************************
*	Pixel Member definition
****************************************************************************/
typedef struct COR_PACK
{
	char label[16];
	UINT32 nbBytes;
	UINT32 format;
} CORPPL_PIXEL_MEMBER, *PCORPPL_PIXEL_MEMBER;



/***************************************************************************
*	On-Demand Command definition
****************************************************************************/
typedef struct COR_PACK
{
	UINT32 fpgaId;
	UINT32 pageId;
	UINT32 regId;
	UINT32 accessType;
	UINT32 value;
} CORPPL_ON_DEMAND_COMMAND, *PCORPPL_ON_DEMAND_COMMAND;


#ifdef __cplusplus
extern "C" {
#endif

//
// Design/Configuration Related API
//
CORSTATUS CORPPLFUNC CorPplReadDesign(const char *filename);
CORSTATUS CORPPLFUNC CorPplLoadDesign( CORPIXPRO hPixPro);
CORSTATUS CORPPLFUNC CorPplProgramConfiguration( CORPIXPRO hPixPro, UINT32 configId, UINT32 inputWidth, UINT32 inputHeight);
CORSTATUS CORPPLFUNC CorPplProgramConfigurationEx( CORPIXPRO hPixPro, UINT32 configId, PCORPPL_PORT pPort);
CORSTATUS CORPPLFUNC CorPplGetDesignName(char *name);
CORSTATUS CORPPLFUNC CorPplGetDesignNumber(UINT32 *number);
CORSTATUS CORPPLFUNC CorPplGetConfigurationCount(UINT32 *count);
CORSTATUS CORPPLFUNC CorPplGetConfigName(UINT32 configId, char *name, UINT32 size);
CORSTATUS CORPPLFUNC CorPplGetConfigInputFormat(UINT32 configId, UINT32 *format);
CORSTATUS CORPPLFUNC CorPplGetConfigInputHeight(UINT32 configId, UINT32 *height);
CORSTATUS CORPPLFUNC CorPplGetConfigInputWidth(UINT32 configId, UINT32 *width);
CORSTATUS CORPPLFUNC CorPplGetConfigInputFrame(UINT32 configId, UINT32 *frame);
CORSTATUS CORPPLFUNC CorPplGetConfigInputFieldOrder(UINT32 configId, UINT32 *fieldOrder);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferCount(UINT32 configId, UINT32 *count);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputFormat(UINT32 configId, UINT32 *format);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferInfo(UINT32 configId, UINT32 bufferId, CORPIXPRO_OUTPUT_BUFFER_INFO *info);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferODCCount(UINT32 configId, UINT32 bufferId, UINT32 *count);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferODCList(UINT32 configId, UINT32 bufferId, CORPPL_ON_DEMAND_COMMAND *list);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferPixelSize(UINT32 configId, UINT32 bufferId, UINT32 *size);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferPMCount(UINT32 configId, UINT32 bufferId, UINT32 *count);
CORSTATUS CORPPLFUNC CorPplGetConfigOutputBufferPMList(UINT32 configId, UINT32 bufferId, CORPPL_PIXEL_MEMBER *list);
CORSTATUS CORPPLFUNC CorPplGetConfigSnapCount(UINT32 configId, UINT32 *count);
CORSTATUS CORPPLFUNC CorPplGetDefaultConfigNumber(UINT32 *number);
CORSTATUS CORPPLFUNC CorPplGetDesignVersion(UINT32 *version);
CORSTATUS CORPPLFUNC CorPplExecuteCommand(CORPIXPRO hPixPro, CORPPL_ON_DEMAND_COMMAND *pOnDemandCmdList, UINT32 count);

//
// Low-Level Pixel Processing API
//
CORSTATUS CORPPLFUNC CorPplInquireFctLL( CORPIXPRO hPixPro, UINT32 designNumber, UINT32 functionId, PCORPPL_FCT_PROP properties, UINT32 propSize);

CORSTATUS CORPPLFUNC CorPplAbsImageSubLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput1, PCORPPL_PORT pplInput2, PCORPPL_PORT pplOutput, UINT32 nbOutput);
CORSTATUS CORPPLFUNC CorPplIntegrateScaleLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput1, PCORPPL_PORT pplInput2, PCORPPL_PORT pplOutput, UINT32 nbOutput, UINT32 integrateCount, UINT32 scaleFactor);
CORSTATUS CORPPLFUNC CorPplInvertImageLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput, PCORPPL_PORT pplOutput, UINT32 nbOutput);
CORSTATUS CORPPLFUNC CorPplPassthroughLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput, PCORPPL_PORT pplOutput);
CORSTATUS CORPPLFUNC CorPplRefImageLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput, PCORPPL_PORT pplOutput, UINT32 nbOutput);
CORSTATUS CORPPLFUNC CorPplUnderflowImageSubLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput1, PCORPPL_PORT pplInput2, PCORPPL_PORT pplOutput, UINT32 nbOutput);
CORSTATUS CORPPLFUNC CorPplWeightedAvgLL( CORPIXPRO hPixPro, PCORPPL_PORT pplInput1, PCORPPL_PORT pplInput2, PCORPPL_PORT pplOutput, UINT32 nbOutput, UINT32 factor);


//
// High 
//
CORSTATUS CORPPLFUNC CorPplInquireFctHL( CORPIXPRO hPixPro, UINT32 designNumber, UINT32 functionId, PCORPPL_FCT_PROP properties, UINT32 propSize);

CORSTATUS CORPPLFUNC CorPplAbsImageSubHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst, UINT32 bankId);
CORSTATUS CORPPLFUNC CorPplIntegrateScaleHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst, UINT32 bankId, UINT32 integrateCount, UINT32 scaleFactor);
CORSTATUS CORPPLFUNC CorPplInvertImageHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst);
CORSTATUS CORPPLFUNC CorPplPassthroughHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst);
CORSTATUS CORPPLFUNC CorPplRefImageHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst, UINT32 bankId);
CORSTATUS CORPPLFUNC CorPplUnderflowImageSubHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst, UINT32 bankId);
CORSTATUS CORPPLFUNC CorPplWeightedAvgHL( CORPIXPRO hPixPro, CORHANDLE hSrc, CORHANDLE hDst, UINT32 bankId, UINT32 factor);

#ifdef  __cplusplus
}
#endif

#include "cunpackd.h"

#endif   // _DESIGN_H_
