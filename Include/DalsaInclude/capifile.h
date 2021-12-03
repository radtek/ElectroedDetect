//
// Coreco API - File functions.
//

#ifndef _CAPIFILE_H_
#define _CAPIFILE_H_

#include <capidef.h>

/****************************************************************************
*	File Capabilities
*
*	Last capability #: 0
****************************************************************************/
#define CORFILE_CAP_FIRST			0
#define CORFILE_CAP( n, size)		((((n) + CORFILE_CAP_FIRST) << 16) | (size))

#define CORFILE_CAP_COMPRESSION		CORFILE_CAP( 0, 4)

/****************************************************************************
*	File Parameters
*
*	Last parameter #: 5
****************************************************************************/
#define CORFILE_PRM_FIRST			0
#define CORFILE_PRM( n, size)		((((n) + CORFILE_PRM_FIRST) << 16) | (size))

#define CORFILE_PRM_FORMAT			CORFILE_PRM( 0, 4)
#define CORFILE_PRM_DATAFORMAT		CORFILE_PRM( 1, 4)
#define CORFILE_PRM_DATASIZE		CORFILE_PRM( 2, 4)
#define CORFILE_PRM_DATADEPTH		CORFILE_PRM( 3, 4)
#define CORFILE_PRM_XMIN			CORFILE_PRM( 4, 4)
#define CORFILE_PRM_YMIN			CORFILE_PRM( 5, 4)
#define CORFILE_PRM_WIDTH			CORFILE_PRM( 6, 4)
#define CORFILE_PRM_HEIGHT			CORFILE_PRM( 7, 4)
#define CORFILE_PRM_MEM_WIDTH		CORFILE_PRM( 8, 4)
#define CORFILE_PRM_MEM_HEIGHT		CORFILE_PRM( 9, 4)
#define CORFILE_PRM_SIGNED			CORFILE_PRM( 10, 4)
#define CORFILE_PRM_COMPRESSION     CORFILE_PRM( 11, 4)
#define CORFILE_PRM_LUT             CORFILE_PRM( 12, 768)
#define CORFILE_PRM_SIZE            CORFILE_PRM( 13, 4)
#define CORFILE_PRM_NUM_FRAMES      CORFILE_PRM( 14, 4)
#define CORFILE_PRM_FRAMERATE		CORFILE_PRM( 15, 4)
#define CORFILE_PRM_NAME		    CORFILE_PRM( 16, 128)
#define CORFILE_PRM_ACCESS		    CORFILE_PRM( 17, 4)

/* Codec supported for readind and/or writing files */
#define CORFILE_VAL_COMPRESSION_NONE      0x00000000	/* dump mode */
#define CORFILE_VAL_COMPRESSION_RLE       0x00000001	/* CCITT modified Huffman RLE */
#define CORFILE_VAL_COMPRESSION_LZW	   	0x00000002	/* Lempel-Ziv  & Welch */
#define CORFILE_VAL_COMPRESSION_JPEG   	0x00000004	/* JPEG DCT compression */
#define CORFILE_VAL_COMPRESSION_I263   	0x00000008	/* Intel H.263 */
#define CORFILE_VAL_COMPRESSION_CVID	   0x00000010	/* Radius Cinepack codec */
#define CORFILE_VAL_COMPRESSION_IV32	   0x00000020	/* Intel Indeo 3.2 */
#define CORFILE_VAL_COMPRESSION_MSVC	   0x00000040	/* Microsoft Video 1 */
#define CORFILE_VAL_COMPRESSION_IV50	   0x00000080	/* Intel Indeo 5.0 */
#define CORFILE_VAL_COMPRESSION_JPEG_2000	0x00000100  /* JPEG DCT compression */
#define CORFILE_VAL_COMPRESSION_UNKNOWN	0x80000000

/* File Formats */
#define	CORFILE_VAL_FORMAT_BMP		   CORDATA_FILEFORMAT_BMP
#define	CORFILE_VAL_FORMAT_TIF		   CORDATA_FILEFORMAT_TIF
#define	CORFILE_VAL_FORMAT_TIFF		   CORDATA_FILEFORMAT_TIFF
#define	CORFILE_VAL_FORMAT_CRC		   CORDATA_FILEFORMAT_CRC
#define	CORFILE_VAL_FORMAT_RAW		   CORDATA_FILEFORMAT_RAW
#define	CORFILE_VAL_FORMAT_JPEG		   CORDATA_FILEFORMAT_JPEG
#define	CORFILE_VAL_FORMAT_JPG	   	CORDATA_FILEFORMAT_JPG
#define	CORFILE_VAL_FORMAT_AVI		   CORDATA_FILEFORMAT_AVI
#define	CORFILE_VAL_FORMAT_JPEG_2000	CORDATA_FILEFORMAT_JPEG_2000
#define	CORFILE_VAL_FORMAT_LAST		   CORDATA_FILEFORMAT_JPEG_2000
#define	CORFILE_VAL_FORMAT_UNKNOWN	CORDATA_FILEFORMAT_UNKNOWN

/* File Access */
#define	CORFILE_VAL_ACCESS_RDONLY	0
#define	CORFILE_VAL_ACCESS_RDWR 	1
#define	CORFILE_VAL_ACCESS_WRONLY	2

/* Old File Formats (for backward compatibility only) */
#define	CORFILE_FORMAT_BMP		   CORDATA_FILEFORMAT_BMP
#define	CORFILE_FORMAT_TIF		   CORDATA_FILEFORMAT_TIF
#define	CORFILE_FORMAT_TIFF		   CORDATA_FILEFORMAT_TIFF
#define	CORFILE_FORMAT_CRC		   CORDATA_FILEFORMAT_CRC
#define	CORFILE_FORMAT_RAW		   CORDATA_FILEFORMAT_RAW
#define	CORFILE_FORMAT_JPEG		   CORDATA_FILEFORMAT_JPEG
#define	CORFILE_FORMAT_JPG		   CORDATA_FILEFORMAT_JPG
#define	CORFILE_FORMAT_AVI		   CORDATA_FILEFORMAT_AVI
#define	CORFILE_FORMAT_JPEG_2000	CORDATA_FILEFORMAT_JPEG_2000
#define	CORFILE_FORMAT_COLOR_CORRECTION CORDATA_FILEFORMAT_COLOR_CORRECTION
#define	CORFILE_FORMAT_LAST		   CORFILE_FORMAT_COLOR_CORRECTION
#define	CORFILE_FORMAT_UNKNOWN	   CORDATA_FILEFORMAT_UNKNOWN

/* File seek method */
#define	CORFILE_BEGIN		FILE_BEGIN
#define	CORFILE_CURRENT		FILE_CURRENT
#define	CORFILE_END  		FILE_END

#ifdef __cplusplus
extern "C" {
#endif

/* Application programming interface */

/* File creation and destruction */
CORSTATUS CORAPIFUNC CorFileNew( CORSERVER server, const char filename[], const char mode[], CORFILE *hFile);
CORSTATUS CORAPIFUNC CorFileFree( CORFILE hFile);

/* Read/Write/Copy/Seek */
CORSTATUS CORAPIFUNC CorFileRead( CORFILE hFile, void *array, UINT32 nItem, UINT32 itemSize);
CORSTATUS CORAPIFUNC CorFileReadEx( CORFILE hFile, void *array, UINT32 nItem, UINT32 itemSize, UINT32 *nRead);
CORSTATUS CORAPIFUNC CorFileWrite( CORFILE hFile, const void *array, UINT32 nItem, UINT32 itemSize);
CORSTATUS CORAPIFUNC CorFileCopy( CORFILE hSrc, CORFILE hDst);
CORSTATUS CORAPIFUNC CorFileSeek( CORFILE hFile, INT32 offset, INT32 origin);

/* Load/Save */
CORSTATUS CORAPIFUNC CorFileLoad( CORFILE hFile, CORHANDLE hDst, PCSTR options);
CORSTATUS CORAPIFUNC CorFileSave( CORFILE hFile, CORHANDLE hSrc, PCSTR options);

CORSTATUS CORAPIFUNC CorFileLoadSequence( CORFILE hFile, CORHANDLE *hDst, UINT32 nFrames, 
										  UINT32 startFrame, PCSTR options);
CORSTATUS CORAPIFUNC CorFileSaveSequence( CORFILE hFile, CORHANDLE *hSrc, UINT32 nFrames,
										  FLOAT frameRate, PCSTR options);
CORSTATUS CORAPIFUNC CorFileAddSequence( CORFILE hFile, CORHANDLE *hSrc, UINT32 nFrames,
										  FLOAT frameRate, PCSTR options);

/* Get attributes */
CORSTATUS CORAPIFUNC CorFileGetCap( CORFILE hFile, UINT32 cap, void *value);
CORSTATUS CORAPIFUNC CorFileGetPrm( CORFILE hFile, UINT32 prm, void *value);
CORSTATUS CORAPIFUNC CorFileSetPrm( CORFILE hFile, UINT32 prm, UINT32 value);
CORSTATUS CORAPIFUNC CorFileSetPrmEx( CORFILE hFile, UINT32 prm, const void *value);

#ifdef  __cplusplus
}
#endif

#endif   // _CAPIFILE_H_
