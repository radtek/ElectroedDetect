//
// Coreco standard status definitions.
//

#ifndef _CORSTAT_H_
#define _CORSTAT_H_

#include "cordef.h"
#include "corlogid.h"

/*
 status format

	status ID:	8 bits - a CORSTATUS_... constant
	info:		  12 bits - a CORSTATUS_INFO_... constant
	level:		2 bits - a CORSTATUS_LEVEL_... constant	
	module:		6 bits - a CORSTATUS_MODULE_... constant	
|------------------|-------------------|-------------|-------------|-----------------|
|31   reserved   28|27   module ID   22|21  level  20|19   info   8|7   status ID   0|     
|------------------|-------------------|-------------|-------------|-----------------|
*/

#define CORSTATUS		UINT32


// Status format location definitions
#define CORSTATUS_MODULE_BIT_OFFSET	22
#define CORSTATUS_LEVEL_BIT_OFFSET	20
#define CORSTATUS_INFO_BIT_OFFSET	8
#define CORSTATUS_STATUS_BIT_OFFSET	0

// Status format size definitions
#define CORSTATUS_MODULE_BIT_MASK	0x3f
#define CORSTATUS_LEVEL_BIT_MASK		0x03
#define CORSTATUS_INFO_BIT_MASK		0xfff
#define CORSTATUS_STATUS_BIT_MASK	0xff

// level
#define CORSTATUS_LEVEL(status)	(((status) >> CORSTATUS_LEVEL_BIT_OFFSET) & CORSTATUS_LEVEL_BIT_MASK)

#define CORSTATUS_LEVEL_FAT	CORLOG_TYPEID_FAT	//	fatal errors	
#define CORSTATUS_LEVEL_ERR	CORLOG_TYPEID_ERR	//	general errors	
#define CORSTATUS_LEVEL_WRN	CORLOG_TYPEID_WRN	//	warnings			
#define CORSTATUS_LEVEL_INF	CORLOG_TYPEID_INF	//	informations	

// module
#define CORSTATUS_MODULE(status)	(((status) >> CORSTATUS_MODULE_BIT_OFFSET) & CORSTATUS_MODULE_BIT_MASK)

#define CORSTATUS_MODULE_ACQ		0x01	//	1:	Acquisition module
#define CORSTATUS_MODULE_BUFFER	0x02	//	2:	Buffer module
#define CORSTATUS_MODULE_CAB		0x03	//	3:	CAB module
#define CORSTATUS_MODULE_CAM		0x04	//	4:	Camera parameters module
#define CORSTATUS_MODULE_DISPLAY	0x05	//	5:	Display module
#define CORSTATUS_MODULE_FONT		0x06	//	6:	Font module
#define CORSTATUS_MODULE_GRAPHIC	0x07	//	7:	Graphic module
#define CORSTATUS_MODULE_HOST		0x08	//	8:	Host module
#define CORSTATUS_MODULE_KERNEL	0x09	//	9:	Kernel module
#define CORSTATUS_MODULE_LOG		0x0A	//	10:Log module
#define CORSTATUS_MODULE_LUT		0x0B	//	11:Lut module
#define CORSTATUS_MODULE_MANAGER	0x0C	// 12:API control module 
#define CORSTATUS_MODULE_MEMORY	0x0D	//	13:Memory management module
#define CORSTATUS_MODULE_PCI		0x0E	//	14:PCI module
#define CORSTATUS_MODULE_PORT		0x0F	//	15:Port module 
#define CORSTATUS_MODULE_PRO		0x10	//	16:Processing module
#define CORSTATUS_MODULE_VIC		0x11	//	17:Vic module
#define CORSTATUS_MODULE_VIEW		0x12	//	18:View module
#define CORSTATUS_MODULE_XFER		0x13	//	19:Transfer module
#define CORSTATUS_MODULE_VDI		0x14	//	20:Video display interface module
#define CORSTATUS_MODULE_SERVER	0x15	// 21:Server module
#define CORSTATUS_MODULE_PIXPRO	0x16	// 22:Pixel Processor module
#define CORSTATUS_MODULE_FILE 	0x17	// 23:File module
#define CORSTATUS_MODULE_C60     0x18  // 24:C60 module
#define CORSTATUS_MODULE_GIO	0x19		// 25:General IO module
#define CORSTATUS_MODULE_COUNTER	0x1a	// 26:Counter module
#define CORSTATUS_MODULE_OBJECT	0x1b	//	27:Object module
#define CORSTATUS_MODULE_ARRAY	CORSTATUS_MODULE_OBJECT	//	Obsolete
#define CORSTATUS_MODULE_STREAM	0x1c	//	28:Object module
#define CORSTATUS_MODULE_PARAM	0x1D	//	29:Param module
#define CORSTATUS_MODULE_SERIAL	0x1E	//	30:Serial module
#define CORSTATUS_MODULE_UTIL	   0x1F	//	31:Utility module
#define CORSTATUS_MODULE_EVENTINFO 0x20   // 32: Event information module
#define CORSTATUS_MODULE_FEATURE 0x21  // 33: Feature module
#define CORSTATUS_MODULE_ACQDEVICE  0x22  // 34: Acquisition device module

// also use in info in proper context

// info index
#define CORSTATUS_INFO(status)	(((status) >> CORSTATUS_INFO_BIT_OFFSET) & CORSTATUS_INFO_BIT_MASK)

#define CORSTATUS_ID(status)		((status) & CORSTATUS_STATUS_BIT_MASK)

#define CORSTATUS_OK									0x00
#define CORSTATUS_INVALID_HANDLE					0x01	// + module ID -> info 

// only user-accessible objects
#define CORSTATUS_INCOMPATIBLE_ACQ				0x0A	//(10)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_BUFFER			0x0B	//(11)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_CAB				0x0C	//(12)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_CAM				0x0D	//(13)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_DISPLAY			0x0E	//(14)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_GRAPHIC			0x0F	//(15)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_KERNEL			0x10	//(16)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_LUT				0x11	//(17)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_MANAGER			0x12	//(18)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_PRO				0x13	//(19)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_VIC				0x14	//(20)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_VIEW				0x15	//(21)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_XFER				0x16	//(22)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_STRING			0x17	//(23)	+ To be determined -> info
#define CORSTATUS_INCOMPATIBLE_OBJECT			0x18	//(24)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_ARRAY			CORSTATUS_INCOMPATIBLE_OBJECT	// Obsolete
#define CORSTATUS_INCOMPATIBLE_STREAM			0x19	//(25)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_FILE				0x1A	//(26)	+ PRM number -> info
#define CORSTATUS_INCOMPATIBLE_FEATURE       0x1B  //(27) + PRM number -> info
#define CORSTATUS_INCOMPATIBLE_ACQDEVICE     0x1C  //(28) + PRM number -> info

// API capabilities
#define CORSTATUS_CAP_INVALID						0x1E	//(30)
#define CORSTATUS_CAP_NOT_AVAILABLE				0x1F	//(31)	+ CORCAP_GETID( cap) -> info

// API Feature
#define CORSTATUS_FEATURE_INVALID      		0x20	//(32)   
#define CORSTATUS_FEATURE_NOT_ACCESSIBLE		0x21	//(33) 
#define CORSTATUS_FEATURE_LOCKED             0x22	//(34) 
#define CORSTATUS_FEATURE_READ_ONLY  		   0x23	//(35)
#define CORSTATUS_FEATURE_WRITE_ONLY  		   0x24	//(36)
#define CORSTATUS_FEATURE_INVALID_VALUE  		0x25	//(37)

// API parameters
#define CORSTATUS_PRM_INVALID						0x28	//(40)
#define CORSTATUS_PRM_NOT_AVAILABLE				0x29	//(41)
#define CORSTATUS_PRM_OUT_OF_RANGE				0x2A	//(42)	+ CORPRM_GETID( prm) -> info
#define CORSTATUS_PRM_INVALID_VALUE				0x2B	//(43)
#define CORSTATUS_PRM_READ_ONLY					0x2C	//(44)
#define CORSTATUS_PRM_MUTUALLY_EXCLUSIVE		0x2D	//(45)

// user-passed arguments
#define CORSTATUS_ARG_INVALID                0x32	//(50)
#define CORSTATUS_ARG_OUT_OF_RANGE				0x33	//(51)	+ number of arg (obj handle = arg #1) -> info
#define CORSTATUS_ARG_INCOMPATIBLE				0x34	//(52)
#define CORSTATUS_ARG_INVALID_VALUE				0x35	//(53)
#define CORSTATUS_ARG_NULL						0x36	//(54)	NULL pointer not expected 

#define CORSTATUS_FILE_OPTIONS_ERROR     		0x39	//(57)
#define CORSTATUS_FILE_OPEN_MODE_INVALID		0x3A	//(58)
#define CORSTATUS_FILE_SEEK_ERROR				0x3B	//(59)
#define CORSTATUS_FILE_CREATE_ERROR				0x3C	//(60)
#define CORSTATUS_FILE_OPEN_ERROR				0x3D	//(61)
#define CORSTATUS_FILE_READ_ERROR				0x3E	//(62)
#define CORSTATUS_FILE_WRITE_ERROR				0x3F	//(63)
#define CORSTATUS_FILE_CLOSE_ERROR				0x40	//(64)
#define CORSTATUS_FILE_FORMAT_UNKNOWN 	        0x41	//(65)
#define CORSTATUS_FILE_FIELD_VALUE_NOT_SUPPORTED  0x42	//(66)
#define CORSTATUS_FILE_GET_FIELD_ERROR			0x43	//(67)
#define CORSTATUS_FILE_READ_ONLY				0x44	//(68)
#define CORSTATUS_FILE_WRITE_ONLY				0x45	//(69)

#define CORSTATUS_NOT_IMPLEMENTED				0x46	//(70)
#define CORSTATUS_NO_MEMORY						0x47	//(71)
#define CORSTATUS_CLIPPING_OCCURED				0x48	//(72)
#define CORSTATUS_HARDWARE_ERROR					0x49	//(73)
#define CORSTATUS_SERVICE_NOT_AVAILABLE		0x4A	//(74)	NT service only
#define CORSTATUS_NOT_ACCESSIBLE					0x4B	//(75)
#define CORSTATUS_NOT_AVAILABLE					0x4C	//(76)
#define CORSTATUS_ROUTING_NOT_IMPLEMENTED		0x4D	//(77)
#define CORSTATUS_ROUTING_NOT_AVAILABLE		0x4E	//(78)
#define CORSTATUS_ROUTING_IN_USE					0x4F	//(79)
#define CORSTATUS_INCOMPATIBLE_SIZE				0x50	//(80)	ideally precision ->info
#define CORSTATUS_INCOMPATIBLE_FORMAT			0x51	//(81)	ideally precision ->info
#define CORSTATUS_RESOURCE_INVALID           0x52  //(82)   A specified resource is invalid, does not exist.
#define CORSTATUS_INCOMPATIBLE_LOCATION		0x53	//(83)	e.g. link between modules from different servrs not permitted 
#define CORSTATUS_RESOURCE_IN_USE				0x54	//(84)	e.g. when handle #x already 'gotten'
#define CORSTATUS_RESOURCE_LINKED				0x55	//(85)	
#define CORSTATUS_SOFTWARE_ERROR					0x56	//(86)	Internal Software error
#define CORSTATUS_PARAMETERS_LOCKED				0x57	//(87)
#define CORSTATUS_XFER_NOT_CONNECTED 	      0x58	//(88)
#define CORSTATUS_XFER_EMPTY_LIST		   	0x59	//(89)
#define CORSTATUS_XFER_CANT_CYCLE  			   0x5A	//(90)
#define CORSTATUS_ROUTING_NOT_SPECIFIED		0x5B	//(91)
#define CORSTATUS_TRANSFER_IN_PROGRESS			0x5D	//(93)
#define CORSTATUS_API_NOT_LOCKED					0x5E	//(94)
#define CORSTATUS_SERVER_NOT_FOUND				0x5F	//(95)
#define CORSTATUS_CANNOT_SIGNAL_EVENT			0x60	//(96)
#define CORSTATUS_NO_MESSAGE						0x61	//(97)
#define CORSTATUS_TIMEOUT							0x62	//(98)	info (1 -> XFER, 2 -> CAB, 3 -> COMM)
#define CORSTATUS_INVALID_ALIGNMENT				0x63	//(99)
#define CORSTATUS_DDRAW_256_COLORS				0x64	//(100)
#define CORSTATUS_PCI_IO_ERROR					0x65	//(101)
#define CORSTATUS_PCI_CANNOT_ACCESS_DEVICE	0x66	//(102)
#define CORSTATUS_EVENT_CREATE_ERROR         0x67	//(103)
#define CORSTATUS_BOARD_NOT_READY				0x68	//(104)
#define CORSTATUS_XFER_MAX_SIZE              0x69  //(105)
#define CORSTATUS_PROCESSING_ERROR	         0x6A  //(106)
#define CORSTATUS_RESOURCE_LOCKED            0x6B  //(107)	e.g. when parameter LOCKED of the corresponding module is ON.
#define CORSTATUS_NO_MESSAGING_MEMORY		   0x6C //(108)
#define CORSTATUS_DDRAW_NOT_AVAILABLE        0x6D //(109)
#define CORSTATUS_DDRAW_ERROR                0x6E //(110)
#define CORSTATUS_RESOURCE_NOT_LOCKED        0x6F //(111)
#define CORSTATUS_DISK_ON_CHIP_ERROR        	0x70 //(112)
#define CORSTATUS_NOT_COMPLETED       	      0x71 //(113) internal use only, leave undocumented
#define CORSTATUS_AUTHENTIFICATION_FAILED    0x72 //(114)
#define CORSTATUS_INSUFFICIENT_BANDWIDTH     0x73 //(115)
#define CORSTATUS_FILE_TELL_ERROR				0x74 //(116)
#define CORSTATUS_MAX_PROCESS_EXCEEDED       0x75 //(117)
#define CORSTATUS_XFER_COUNT_MULT_SRC_FRAME_COUNT  0x76  //(118)
#define CORSTATUS_ACQ_CONNECTED_TO_XFER		0x77 //(119)
#define CORSTATUS_INSUFFICIENT_BOARD_MEMORY  0x78 //(120)
#define CORSTATUS_INSUFFICIENT_RESOURCES     0x79 // (121)
#define CORSTATUS_MISSING_RESOURCE           0x7A  // (122): Used when a DLL cannot be loaded.
#define CORSTATUS_NO_DEVICE_FOUND            0x7B  // (123): Used when no devices (ie. boards) are found for a driver
#define CORSTATUS_RESOURCE_NOT_CONNECTED     0x7C  //(124) + module ID -> info
#define CORSTATUS_SERVER_DATABASE_FULL       0x7D  //(125)
#define CORSTATUS_IN_PROGRESS                0x7E  //(126) internal use only, leave undocumented
#define CORSTATUS_DEVICE_NOT_CONNECTED       0x7F  //(127)Device is not connected, unplugged.
#define CORSTATUS_RESOURCE_ACCESS            0x80  //(128)Resource is not accessible. 
#define CORSTATUS_DEVICE_NOT_RESPONDING      0x81  //(129)Remote device is not responding.
#define CORSTATUS_DATA_INVALID               0x82  //(130)Data expected is invalid.
#define CORSTATUS_RESOURCE_READ              0x83  //(131)Error reading from resource.
#define CORSTATUS_RESOURCE_WRITE             0x84  //(132)Error writing to resource     
#define CORSTATUS_CONNECTION_DROPPED         0x85  //(133)Logical connection with device was lost.
#define CORSTATUS_EVALUATION_PERIOD_EXPIRED  0x86  //(134)Sapera LT evaluation period has expired
#define CORSTATUS_EXTERNAL_POWER_NO_PRESENT  0x87  //(135)The external power is not connected to the board
#define CORSTATUS_CAMERA_POWER_ERROR         0x88  //(136)The external power is connected but a short curcuit occur when apply to the camera
#define CORSTATUS_REBOOT_REQUIRED            0x89  //(137)A reboot of the computer is required. Usually this can happen after a reset of the board is done.
#define CORSTATUS_INCOMPATIBLE_FIRMWARE      0x8A  //(138)The firmware cannot be loaded on that board
#define CORSTATUS_INCOMPATIBLE_SERVER        0x8B  //(139)
#define CORSTATUS_DEVICE_CONTEXTUAL_ERROR    0x8C  //(140)Error from a device (rich contextual info)
//^^^^ Don't forget to add the new CORSTATUS_XXXXXX string in ApiStatus.c ^^^^

// level first so that it be visible instantly
#define CORSTATUS_BUILD( level, id, info, module)	((id) | (((info) & CORSTATUS_INFO_BIT_MASK)<<CORSTATUS_INFO_BIT_OFFSET) | (((level) & CORSTATUS_LEVEL_BIT_MASK)<<CORSTATUS_LEVEL_BIT_OFFSET) | (((module) & CORSTATUS_MODULE_BIT_MASK)<<CORSTATUS_MODULE_BIT_OFFSET))

/* Macros for adding single fields to status */
#define CORSTATUS_ADD_ID( status, id)				((status) | ((id) & CORSTATUS_STATUS_BIT_MASK))
#define CORSTATUS_ADD_INFO( status, info)			((status) | (((info) & CORSTATUS_INFO_BIT_MASK)<<CORSTATUS_INFO_BIT_OFFSET))
#define CORSTATUS_ADD_LEVEL( status, level)		((status) | (((level) & CORSTATUS_LEVEL_BIT_MASK)<<CORSTATUS_LEVEL_BIT_OFFSET))
#define CORSTATUS_ADD_MODULE( status, module)	((status) | (((module) & CORSTATUS_MODULE_BIT_MASK)<<CORSTATUS_MODULE_BIT_OFFSET))

/* Macros for adding module to status */
#define CORSTATUS_ACQ(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_ACQ)
#define CORSTATUS_BUFFER(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_BUFFER)
#define CORSTATUS_CAB(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_CAB)
#define CORSTATUS_PIXPRO(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_PIXPRO)
#define CORSTATUS_CAM(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_CAM)
#define CORSTATUS_DISPLAY(status)	CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_DISPLAY)
#define CORSTATUS_FONT(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_FONT)
#define CORSTATUS_GRAPHIC(status)	CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_GRAPHIC)
#define CORSTATUS_HOST(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_HOST)
#define CORSTATUS_KERNEL(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_KERNEL)
#define CORSTATUS_LOG(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_LOG)
#define CORSTATUS_LUT(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_LUT)
#define CORSTATUS_MANAGER(status)	CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_MANAGER)
#define CORSTATUS_MEMORY(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_MEMORY)
#define CORSTATUS_PCI(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_PCI)
#define CORSTATUS_PORT(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_PORT)
#define CORSTATUS_PRO(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_PRO)
#define CORSTATUS_VIC(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_VIC)
#define CORSTATUS_VIEW(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_VIEW)
#define CORSTATUS_XFER(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_XFER)
#define CORSTATUS_VDI(status)			CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_VDI)
#define CORSTATUS_FILE( status)     CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_FILE)
#define CORSTATUS_C60( status)      CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_C60)
#define CORSTATUS_GIO(status)	      CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_GIO)
#define CORSTATUS_OBJECT(status)	   CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_OBJECT)
#define CORSTATUS_COUNTER(status)   CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_COUNTER)
#define CORSTATUS_STREAM(status)    CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_STREAM)
#define CORSTATUS_PARAM(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_PARAM)
#define CORSTATUS_SERIAL(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_SERIAL)
#define CORSTATUS_UTIL(status)		CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_UTIL)
#define CORSTATUS_EVENTINFO(status)	CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_EVENTINFO)
#define CORSTATUS_FEATURE(status)	CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_FEATURE)
#define CORSTATUS_ACQDEVICE(status) CORSTATUS_ADD_MODULE(status, CORSTATUS_MODULE_ACQDEVICE)

/* Macros for adding module/info to status */
#define CORSTATUS_ACQ_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_ACQ)
#define CORSTATUS_BUFFER_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_BUFFER)
#define CORSTATUS_CAB_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_CAB)
#define CORSTATUS_PIXPRO_INFO(status, info) 	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_PIXPRO)
#define CORSTATUS_CAM_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_CAM)
#define CORSTATUS_DISPLAY_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_DISPLAY)
#define CORSTATUS_FONT_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_FONT)
#define CORSTATUS_GRAPHIC_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_GRAPHIC)
#define CORSTATUS_HOST_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_HOST)
#define CORSTATUS_KERNEL_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_KERNEL)
#define CORSTATUS_LOG_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_LOG)
#define CORSTATUS_LUT_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_LUT)
#define CORSTATUS_MANAGER_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_MANAGER)
#define CORSTATUS_MEMORY_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_MEMORY)
#define CORSTATUS_PCI_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_PCI)
#define CORSTATUS_PORT_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_PORT)
#define CORSTATUS_PRO_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_PRO)
#define CORSTATUS_VIC_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_VIC)
#define CORSTATUS_VIEW_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_VIEW)
#define CORSTATUS_XFER_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_XFER)
#define CORSTATUS_VDI_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_VDI)
#define CORSTATUS_FILE_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_FILE)
#define CORSTATUS_C60_INFO(status, info)		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_C60)
#define CORSTATUS_GIO_INFO(status, info) 		CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_GIO)
#define CORSTATUS_COUNTER_INFO(status, info) CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_COUNTER)
#define CORSTATUS_OBJECT_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_OBJECT)
#define CORSTATUS_STREAM_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_STREAM)
#define CORSTATUS_PARAM_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_PARAM)
#define CORSTATUS_SERIAL_INFO(status, info)	CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_SERIAL)
#define CORSTATUS_UTIL_INFO(status, info)	   CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_UTIL)
#define CORSTATUS_EVENTINFO_INFO(status, info)  CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_EVENTINFO)
#define CORSTATUS_FEATURE_INFO(status, info)	   CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_FEATURE)
#define CORSTATUS_ACQDEVICE_INFO(status, info)  CORSTATUS_ADD_MODULE(CORSTATUS_ADD_INFO(status, info), CORSTATUS_MODULE_ACQDEVICE)

/* Macro for converting WITPRO error code to SAPERA error status */
#define CORSTATUS_WIT_TO_SAP_ERR(status)		((status) == COR_OP_OK ? CORSTATUS_OK : CORSTATUS_PROCESSING_ERROR)

#endif   //_CORSTAT_H_
