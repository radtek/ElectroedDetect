//
// Old Format definitions and conversion macros.
//

#ifndef _FORMATS_H_
#define _FORMATS_H_

#include <capidef.h>

#define FORMAT_VERSION						200

#define CORDATA_OLD_FORMAT_SIGNED		0x01000000
#define CORDATA_OLD_FORMAT_UNSIGNED		0x00000000

#define CORDATA_OLD_FORMAT_MONO      	0x00000000
#define CORDATA_OLD_FORMAT_MONO8     	0x00000008
#define CORDATA_OLD_FORMAT_MONO16    	0x00000010
#define CORDATA_OLD_FORMAT_MONO32    	0x00000020

#define CORDATA_OLD_FORMAT_RGB5551   	0x00000110
#define CORDATA_OLD_FORMAT_RGB565    	0x00000210

#define CORDATA_OLD_FORMAT_RGB888    	0x00000318
#define CORDATA_OLD_FORMAT_RGB8888   	0x00000420
#define CORDATA_OLD_FORMAT_RGB101010 	0x00000520
#define CORDATA_OLD_FORMAT_RGB161616 	0x00000630

#define CORDATA_OLD_FORMAT_UYVY	   	0x00000710	//4:2:2
#define CORDATA_OLD_FORMAT_YUY2	   	0x00000810	//4:2:2
#define CORDATA_OLD_FORMAT_YVYU	   	0x00000910	//4:2:2
#define CORDATA_OLD_FORMAT_YUYV	   	0x00000a10	//4:2:2

#define CORDATA_OLD_FORMAT_Y411	   	0x00000b0c	//4:1:1 also known as Y41P
#define CORDATA_OLD_FORMAT_Y211	   	0x00000c0c	//2:1:1

#define CORDATA_OLD_FORMAT_CCIR422   	0x00000d10
#define CORDATA_OLD_FORMAT_FLOAT     	0x01000e20
#define CORDATA_OLD_FORMAT_COMPLEX   	0x01000f40
#define CORDATA_OLD_FORMAT_POINT     	0x00001040

/* Processing-specific data formats */
#define CORDATA_OLD_FORMAT_INT8			(CORDATA_OLD_FORMAT_SIGNED 		| CORDATA_OLD_FORMAT_MONO8)
#define CORDATA_OLD_FORMAT_UINT8		(CORDATA_OLD_FORMAT_UNSIGNED 	| CORDATA_OLD_FORMAT_MONO8)
#define CORDATA_OLD_FORMAT_INT16		(CORDATA_OLD_FORMAT_SIGNED 		| CORDATA_OLD_FORMAT_MONO16)
#define CORDATA_OLD_FORMAT_UINT16		(CORDATA_OLD_FORMAT_UNSIGNED 	| CORDATA_OLD_FORMAT_MONO16)
#define CORDATA_OLD_FORMAT_INT32		(CORDATA_OLD_FORMAT_SIGNED 		| CORDATA_OLD_FORMAT_MONO32)
#define CORDATA_OLD_FORMAT_UINT32		(CORDATA_OLD_FORMAT_UNSIGNED 	| CORDATA_OLD_FORMAT_MONO32)

typedef struct 
{	
	UINT32 newFormat;
	UINT32 oldFormat;
} _FORMAT_NEW_OLD_;

static _FORMAT_NEW_OLD_  _Format_NEW_OLD_[]=
{
// Monochrome data formats
	{CORDATA_FORMAT_INT8,		CORDATA_OLD_FORMAT_INT8},		// 0
	{CORDATA_FORMAT_UINT8,		CORDATA_OLD_FORMAT_UINT8},		// 1

	{CORDATA_FORMAT_INT16,		CORDATA_OLD_FORMAT_INT16},		// 2
	{CORDATA_FORMAT_UINT16,		CORDATA_OLD_FORMAT_UINT16},	// 3

	{CORDATA_FORMAT_INT24,		(UINT32)-1},						// 4
	{CORDATA_FORMAT_UINT24,		(UINT32)-1},						// 5

	{CORDATA_FORMAT_INT32,		CORDATA_OLD_FORMAT_INT32},		// 6
	{CORDATA_FORMAT_UINT32,		CORDATA_OLD_FORMAT_UINT32},	// 7

	{CORDATA_FORMAT_INT64,		(UINT32)-1},						// 8
	{CORDATA_FORMAT_UINT64,		(UINT32)-1},						// 9

// Color RGB data formats
	{CORDATA_FORMAT_RGB5551,	CORDATA_OLD_FORMAT_RGB5551},		// 10
	{CORDATA_FORMAT_RGB565,		CORDATA_OLD_FORMAT_RGB565},		// 11
	{CORDATA_FORMAT_RGB888,		CORDATA_OLD_FORMAT_RGB888},		// 12
	{CORDATA_FORMAT_RGB8888,	CORDATA_OLD_FORMAT_RGB8888},		// 13
	{CORDATA_FORMAT_RGB101010,	CORDATA_OLD_FORMAT_RGB101010},	// 14
	{CORDATA_FORMAT_RGB161616,	CORDATA_OLD_FORMAT_RGB161616},	// 15
	{CORDATA_FORMAT_RGBP8,		(UINT32)-1},							// 16
	{CORDATA_FORMAT_RGBP16,		(UINT32)-1},							// 17

// Color HSV data formats
	{CORDATA_FORMAT_HSV,			(UINT32)-1},							// 18

// Color YUV data formats
// these 4:2:2
	{CORDATA_FORMAT_UYVY,		CORDATA_OLD_FORMAT_UYVY},			// 19
	{CORDATA_FORMAT_YUY2,		CORDATA_OLD_FORMAT_YUY2},			// 20
	{CORDATA_FORMAT_YVYU,		CORDATA_OLD_FORMAT_YVYU},			// 21
	{CORDATA_FORMAT_YUYV,		CORDATA_OLD_FORMAT_YUYV},			// 22
//4:1:1 also known as Y41P
	{CORDATA_FORMAT_Y411,		CORDATA_OLD_FORMAT_Y411},			// 23
//2:1:1
	{CORDATA_FORMAT_Y211,		CORDATA_OLD_FORMAT_Y211},			// 24
	{CORDATA_FORMAT_YUV,			(UINT32)-1},							// 25

// Other data formats
	{CORDATA_FORMAT_FLOAT,		CORDATA_OLD_FORMAT_FLOAT},			// 26
	{CORDATA_FORMAT_COMPLEX,	CORDATA_OLD_FORMAT_COMPLEX},		// 27
	{CORDATA_FORMAT_POINT,		CORDATA_OLD_FORMAT_POINT},			// 28
	{CORDATA_FORMAT_FPOINT,		(UINT32)-1},							// 29
   {CORDATA_FORMAT_BINARY,    (UINT32)-1},                     // 30
   {CORDATA_FORMAT_HSI,       (UINT32)-1},                     // 31
   {CORDATA_FORMAT_HSIP8,     (UINT32)-1},                     // 32
   {CORDATA_FORMAT_HSIP16,    (UINT32)-1},                     // 33
   {CORDATA_FORMAT_HSVP8,     (UINT32)-1},                     // 34
   {CORDATA_FORMAT_HSVP16,    (UINT32)-1},                     // 35
   {CORDATA_FORMAT_YUVP8,     (UINT32)-1},                     // 36
   {CORDATA_FORMAT_YUVP16,    (UINT32)-1},                     // 37
	{CORDATA_FORMAT_RGB16161616,	(UINT32)-1},	               // 38
   {CORDATA_FORMAT_LAB,		   (UINT32)-1},                     // 39
   {CORDATA_FORMAT_LABP8,     (UINT32)-1},                     // 40
   {CORDATA_FORMAT_LABP16,    (UINT32)-1},                     // 41
	{CORDATA_FORMAT_LAB16161616,	(UINT32)-1},	               // 42
	{CORDATA_FORMAT_LAB101010,	(UINT32)-1},	                  // 43

// Color RGB data format with components ordered as R -> G -> B
   {CORDATA_FORMAT_RGBR888,   (UINT32)-1},                     // 44

   // BICOLOR
   {CORDATA_FORMAT_BICOLOR88,	(UINT32)-1},	                  // 45
	{CORDATA_FORMAT_BICOLOR1616,	(UINT32)-1},	                  // 46

   // Multi-format (RGB-IR)
   {CORDATA_FORMAT_RGB888_MONO8, (UINT32)-1},	                  // 47
	{CORDATA_FORMAT_RGB161616_MONO16, (UINT32)-1},	                  // 48

   // Multi-format (Planar Mono)
   {CORDATA_FORMAT_MONO8P2, (UINT32)-1},	                  // 49
   {CORDATA_FORMAT_MONO8P3, (UINT32)-1},	                  // 50
   {CORDATA_FORMAT_MONO16P2, (UINT32)-1},	                  // 51
	{CORDATA_FORMAT_MONO16P3, (UINT32)-1},	                  // 52
};

#define CVT_OLD_FORMAT_TO_NEW_FORMAT( version, value)\
{\
	if( version <= 100)\
	{\
		UINT32 i;\
		for( i= 0; i < sizeof( _Format_NEW_OLD_)/sizeof( _FORMAT_NEW_OLD_); i++)\
		{\
			if( value == _Format_NEW_OLD_[ i].oldFormat)\
			{\
				value= _Format_NEW_OLD_[ i].newFormat;\
				break;\
			}\
		}\
		if( i == sizeof( _Format_NEW_OLD_)/sizeof( _FORMAT_NEW_OLD_))\
			value= 0;\
	}\
}

#define CVT_INDEX_TO_FORMAT( version, value)\
{\
	if( version < FORMAT_VERSION)\
	{\
		CVT_OLD_FORMAT_TO_NEW_FORMAT( version, value);\
	}\
	else\
	if( value < sizeof( _Format_NEW_OLD_)/sizeof( _FORMAT_NEW_OLD_))\
		value= _Format_NEW_OLD_[ value].newFormat;\
	else\
		value= 0;\
}

#define CVT_FORMAT_TO_INDEX( version, value)\
{\
	UINT32 i;\
	for( i= 0; i < sizeof( _Format_NEW_OLD_)/sizeof( _FORMAT_NEW_OLD_); i++)\
	{\
		if( value == _Format_NEW_OLD_[ i].newFormat)\
		{\
			value= i;\
			break;\
		}\
	}\
	if( i == sizeof( _Format_NEW_OLD_)/sizeof( _FORMAT_NEW_OLD_))\
		value= 0;\
}

#define GET_DEFAULT_FORMAT_INDEX(version)\
   ((version <= 100) ? CORDATA_OLD_FORMAT_UINT8 : 1)

#endif   // _FORMATS_H_
