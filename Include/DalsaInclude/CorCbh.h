//
// Coreco Binary Header Definitions.
//

#ifndef _CORCBH_H_
#define _CORCBH_H_

#include "cordef.h"
#include "cpackd.h"

#define CORECO_CBH_COMMENT_SIZE	128      // Size of Comment in CORECO_CBH_HEADER, including end of string character.
#define CORECO_CBH_SIGNATURE  "CORECO_CBH"   // Header Signature
#define CORECO_CBH_SIGNATURE_SIZE	10

// 
// Size definitions of CBH Header members
//
#define CORECO_CBH_HEADER_VERSION_SIZE							sizeof( UINT8)
#define CORECO_CBH_HEADER_SIZE_SIZE								sizeof( UINT32)
#define CORECO_CBH_CREATION_DATE_MINUTE_SIZE					sizeof( UINT8)
#define CORECO_CBH_CREATION_DATE_HOUR_SIZE					sizeof( UINT8)
#define CORECO_CBH_CREATION_DATE_DAY_SIZE						sizeof( UINT8)
#define CORECO_CBH_CREATION_DATE_MONTH_SIZE					sizeof( UINT8)
#define CORECO_CBH_CREATION_DATE_YEAR_SIZE					sizeof( UINT16)
#define CORECO_CBH_MODIFY_DATE_MINUTE_SIZE					sizeof( UINT8)
#define CORECO_CBH_MODIFY_DATE_HOUR_SIZE						sizeof( UINT8)
#define CORECO_CBH_MODIFY_DATE_DAY_SIZE						sizeof( UINT8)
#define CORECO_CBH_MODIFY_DATE_MONTH_SIZE						sizeof( UINT8)
#define CORECO_CBH_MODIFY_DATE_YEAR_SIZE						sizeof( UINT16)
#define CORECO_CBH_PRODUCT_VERSION_REVISION_SIZE			sizeof( UINT8)
#define CORECO_CBH_PRODUCT_VERSION_BUILD_NUMBER_SIZE		sizeof( UINT16)
#define CORECO_CBH_PRODUCT_VERSION_MINOR_VERSION_SIZE		sizeof( UINT8)
#define CORECO_CBH_PRODUCT_VERSION_MAJOR_VERSION_SIZE		sizeof (UINT8)
#define CORECO_CBH_PRODUCT_ID_SIZE								sizeof( UINT32)
#define CORECO_CBH_COMPONENT_ID_SIZE							sizeof( UINT16)
#define CORECO_CBH_COMPATIBILITY_VERSION_SIZE				sizeof( UINT32)
#define CORECO_CBH_FIRMWARE_ID_SIZE								sizeof( UINT32)
#define CORECO_CBH_FIRMWARE_CHECK_SUM_SIZE					sizeof( UINT32)
#define CORECO_CBH_FIRMWARE_SIZE_SIZE							sizeof( UINT32)
#define CORECO_CBH_OPTION_BIT_SIZE								sizeof( UINT32)
#define CORECO_CBH_COMMMENT_SIZE									CORECO_CBH_COMMENT_SIZE
#define CORECO_CBH_HEADER_CHECKSUM_SIZE						sizeof( UINT32)
#define CORECO_CBH_HEADER_TYPE_SIZE								sizeof( UINT16)
 
// 
// Byte Offset definitions of CBH Header members
//
#define CORECO_CBH_SIGNATURE_OFFSET								0
#define CORECO_CBH_HEADER_VERSION_OFFSET						(CORECO_CBH_SIGNATURE_OFFSET + CORECO_CBH_SIGNATURE_SIZE)
#define CORECO_CBH_HEADER_SIZE_OFFSET							(CORECO_CBH_HEADER_VERSION_OFFSET + CORECO_CBH_HEADER_VERSION_SIZE)
#define CORECO_CBH_CREATION_DATE_MINUTE_OFFSET				(CORECO_CBH_HEADER_SIZE_OFFSET + CORECO_CBH_HEADER_SIZE_SIZE)
#define CORECO_CBH_CREATION_DATE_HOUR_OFFSET					(CORECO_CBH_CREATION_DATE_MINUTE_OFFSET + CORECO_CBH_CREATION_DATE_MINUTE_SIZE)
#define CORECO_CBH_CREATION_DATE_DAY_OFFSET					(CORECO_CBH_CREATION_DATE_HOUR_OFFSET + CORECO_CBH_CREATION_DATE_HOUR_SIZE)
#define CORECO_CBH_CREATION_DATE_MONTH_OFFSET				(CORECO_CBH_CREATION_DATE_DAY_OFFSET + CORECO_CBH_CREATION_DATE_DAY_SIZE)
#define CORECO_CBH_CREATION_DATE_YEAR_OFFSET					(CORECO_CBH_CREATION_DATE_MONTH_OFFSET + CORECO_CBH_CREATION_DATE_MONTH_SIZE)
#define CORECO_CBH_MODIFY_DATE_MINUTE_OFFSET					(CORECO_CBH_CREATION_DATE_YEAR_OFFSET + CORECO_CBH_CREATION_DATE_YEAR_SIZE)
#define CORECO_CBH_MODIFY_DATE_HOUR_OFFSET					(CORECO_CBH_MODIFY_DATE_MINUTE_OFFSET + CORECO_CBH_MODIFY_DATE_MINUTE_SIZE)
#define CORECO_CBH_MODIFY_DATE_DAY_OFFSET						(CORECO_CBH_MODIFY_DATE_HOUR_OFFSET + CORECO_CBH_MODIFY_DATE_HOUR_SIZE)
#define CORECO_CBH_MODIFY_DATE_MONTH_OFFSET					(CORECO_CBH_MODIFY_DATE_DAY_OFFSET + CORECO_CBH_MODIFY_DATE_DAY_SIZE)
#define CORECO_CBH_MODIFY_DATE_YEAR_OFFSET					(CORECO_CBH_MODIFY_DATE_MONTH_OFFSET + CORECO_CBH_MODIFY_DATE_MONTH_SIZE)
#define CORECO_CBH_PRODUCT_VERSION_REVISION_OFFSET		   (CORECO_CBH_MODIFY_DATE_YEAR_OFFSET + CORECO_CBH_MODIFY_DATE_YEAR_SIZE)
#define CORECO_CBH_PRODUCT_VERSION_BUILD_NUMBER_OFFSET	(CORECO_CBH_PRODUCT_VERSION_REVISION_OFFSET + CORECO_CBH_PRODUCT_VERSION_REVISION_SIZE)
#define CORECO_CBH_PRODUCT_VERSION_MINOR_VERSION_OFFSET	(CORECO_CBH_PRODUCT_VERSION_BUILD_NUMBER_OFFSET + CORECO_CBH_PRODUCT_VERSION_BUILD_NUMBER_SIZE)
#define CORECO_CBH_PRODUCT_VERSION_MAJOR_VERSION_OFFSET	(CORECO_CBH_PRODUCT_VERSION_MINOR_VERSION_OFFSET + CORECO_CBH_PRODUCT_VERSION_MINOR_VERSION_SIZE)
#define CORECO_CBH_PRODUCT_ID_OFFSET							(CORECO_CBH_PRODUCT_VERSION_MAJOR_VERSION_OFFSET + CORECO_CBH_PRODUCT_VERSION_MAJOR_VERSION_SIZE)
#define CORECO_CBH_COMPONENT_ID_OFFSET							(CORECO_CBH_PRODUCT_ID_OFFSET + CORECO_CBH_PRODUCT_ID_SIZE)
#define CORECO_CBH_COMPATIBILITY_VERSION_OFFSET				(CORECO_CBH_COMPONENT_ID_OFFSET + CORECO_CBH_COMPONENT_ID_SIZE)
#define CORECO_CBH_FIRMWARE_ID_OFFSET							(CORECO_CBH_COMPATIBILITY_VERSION_OFFSET + CORECO_CBH_COMPATIBILITY_VERSION_SIZE)
#define CORECO_CBH_FIRMWARE_CHECK_SUM_OFFSET					(CORECO_CBH_FIRMWARE_ID_OFFSET + CORECO_CBH_FIRMWARE_ID_SIZE)
#define CORECO_CBH_FIRMWARE_SIZE_OFFSET						(CORECO_CBH_FIRMWARE_CHECK_SUM_OFFSET + CORECO_CBH_FIRMWARE_CHECK_SUM_SIZE)
#define CORECO_CBH_OPTION_BIT_OFFSET							(CORECO_CBH_FIRMWARE_SIZE_OFFSET + CORECO_CBH_FIRMWARE_SIZE_SIZE)
#define CORECO_CBH_COMMENT_OFFSET								(CORECO_CBH_OPTION_BIT_OFFSET + CORECO_CBH_OPTION_BIT_SIZE)
#define CORECO_CBH_HEADER_CHECKSUM_OFFSET						(CORECO_CBH_COMMENT_OFFSET + CORECO_CBH_COMMENT_SIZE)
#define CORECO_CBH_HEADER_TYPE_OFFSET							(CORECO_CBH_HEADER_CHECKSUM_OFFSET + CORECO_CBH_HEADER_CHECKSUM_SIZE)
#define CORECO_CBH_HEADER_STRUCT_SIZE                 	(CORECO_CBH_HEADER_TYPE_OFFSET + CORECO_CBH_HEADER_TYPE_SIZE)
 
//
// Structure to define a DATE
//
typedef struct COR_PACK CBH_DATE
{
   UINT8 minute;
   UINT8 hour;
   UINT8 day;
   UINT8 month;
   UINT16 year;   
} CBH_DATE, *PCBH_DATE;

//
// Structure to define the version of the product.
//
//   Example: 
//         revision = 1;
//         buildNumber = 202;
//         minorVersion = 30;
//         majorVersion = 1;
//
//         Driver Version = 1.30.1.202
//
//
typedef struct COR_PACK CBH_PRODUCT_VERSION
{
   UINT8  revision;     // 0 = Release, 1 = Beta, >=2 = OEM or other.
   UINT16 buildNumber;  // Installation build number
   UINT8  minorVersion; // Minor Version
   UINT8 majorVersion;  // Major Version
} CBH_PRODUCT_VERSION, *PCBH_PRODUCT_VERSION;


//
// Version 1:  First Release
//          
//
#define CORECO_CBH_VERSION_1_SIZE   0xBA  // Size in bytes of the version 1 structure.
#define CORECO_CBH_VERSION_1 1
//
// Version 2:  second Release
//          
//
#define CORECO_CBH_VERSION_2_SIZE   (CORECO_CBH_VERSION_1_SIZE+6)  // Size in bytes of the version 2 structure.
#define CORECO_CBH_VERSION_2 2

#define CORECO_CBH_HEADER_MAX_SIZE (4096)  // Maximum Header Size in bytes

// 
// CBH Header Types
//
#define CORECO_CBH_HEADER_TYPE_UNKNOWN	   0
#define CORECO_CBH_HEADER_TYPE_CONTAINER        1

#ifndef CORECO_CBH_VERSION_TARGET
#define CORECO_CBH_VERSION_TARGET   CORECO_CBH_VERSION_1
#endif

#define CORECO_CBH_VERSION       CORECO_CBH_VERSION_TARGET  // Version number of the CORECO_CBH_HEADER.


#define CORECO_CBH_HEADER_TYPE_UNKNOW		0
#define CORECO_CBH_HEADER_TYPE_CONTAINER	1

#define CORECO_CBH_HEADER_BASE \
   UINT8 signature[CORECO_CBH_SIGNATURE_SIZE];	/* Must be = CORECO_CBH for a valid CBH file */ \
   UINT8 headerVersion;		/* Version of this header. */ \
                           /* Version will start @ 1 and will increase by one everytime a new feature is added. */ \
   UINT32 headerSize;		/* Size of this header in bytes */ \
   CBH_DATE creationDate;  /* Date the header was created and added to a new firmware binary.  */ \
                           /* This field is filled ONLY when the CBH header is created the first time */ \
   CBH_DATE modifyDate;    /*  Date the header was modified last. This field is modified ONLY when the CBH header is modified. */ \
   CBH_PRODUCT_VERSION productVersion; /* Product version the firmware belongs to. */ \
                                       /* This field must match the installation product version. */ \
   UINT32 productId;       /* Identification number specifying which product this firmware is for. */ \
                           /* Usually this will correcpond to the drawing number identified in the Eeprom */ \
	UINT16 componentId;     /* Identification number of component (FPGA, I960, C60 etc): Driver Specific. */ \
                           /* This entry will prevent programming of a device with the wrong firmware. */ \
   UINT32 compatibilityVersion;  /* Driver specific version number used to make sure all components are compatible */ \
                                 /* between each other. It is the responsibility of the driver to test the different component versions */ \
   UINT32 firmwareId;      /* Driver specific ID used to differentiate between different binaries for the same component. */ \
                           /* If the component is an FPGA, the XSM number should be placed here. */ \
   UINT32 firmwareCheckSum;   /* Check Sum of firmware. Simple addition of all the bytes in the firmware. */ \
                              /* Result of addition is kept in a 32-bit value that can roll over. */ \
   UINT32 firmwareSize;       /* Size in bytes of firmware. */ \
   UINT32 optionBit;          /* Option bit field. Driver specific defined. */ \
	BYTE  comment[CORECO_CBH_COMMENT_SIZE];   /* Driver specific comment. */

#define CORECO_CBH_HEADER_EXT_V2 \
	UINT32 headerCheckSum;     /* Check Sum of header. Simple addition of all the bytes in the header. */ \
                              /* Result of addition is kept in a 32-bit value that can roll over. */ \
	UINT16 headerType;         /* 0: Unknown = The payload following the header is only known to the product */ \
										/* 1: Container = The payload following the header consists of a series of CBH Header/Payload.  */ \
	                           /*                To read this CBF file, a user must scan the payload for CBH Header/Payload until the size of the Container payload size is reached. */


typedef struct COR_PACK CORECO_CBH_HEADER_1
{
   CORECO_CBH_HEADER_BASE

} CORECO_CBH_HEADER_1 , *PCORECO_CBH_HEADER_1;



#if CORECO_CBH_VERSION_TARGET ==1
typedef  CORECO_CBH_HEADER_1 CORECO_CBH_HEADER, *PCORECO_CBH_HEADER;
#endif

typedef struct COR_PACK CORECO_CBH_HEADER_2
{
   CORECO_CBH_HEADER_BASE
   CORECO_CBH_HEADER_EXT_V2


} CORECO_CBH_HEADER_2 , *PCORECO_CBH_HEADER_2;

#if CORECO_CBH_VERSION_TARGET ==2
typedef  CORECO_CBH_HEADER_2 CORECO_CBH_HEADER, *PCORECO_CBH_HEADER;
#endif

#include "cunpackd.h"

#endif 	// _CORCBH_H_
