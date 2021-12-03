//
// Coreco API - Display functions.
//

#ifndef _CAPIDISP_H_
#define _CAPIDISP_H_

#include <capidef.h>

/****************************************************************************
*	Display Capabilities (all obsolete)
****************************************************************************/
#define  CORDISPLAY_DEF_FIRST                      0 //5000

#define  CORDISPLAY_CAP_FIRST                      (0 + CORDISPLAY_DEF_FIRST)
#define  CORDISPLAY_CAP( n, size)    					((((n) + CORDISPLAY_CAP_FIRST) << 16) | (size))
/*------------------------------------------------------------------------*/
// CORDISPLAY_CAP_TYPE is now a parameter -> previously CORDISPLAY_CAP(0, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Color space of the display device
#define  CORDISPLAY_CAP_COLOR_SPACE						CORDISPLAY_CAP( 1,4)
#define	CORDISPLAY_VAL_COLOR_SPACE_RGB            0x00000001  // default
#define	CORDISPLAY_VAL_COLOR_SPACE_MONO           0x00000002
#define	CORDISPLAY_VAL_COLOR_SPACE_YUV            0x00000004
#define	CORDISPLAY_VAL_COLOR_SPACE_CMYK           0x00000008
/*------------------------------------------------------------------------*/
// (Obsolete) Brightness Control Supported FALSE/TRUE 
#define  CORDISPLAY_CAP_BRIGHTNESS                 CORDISPLAY_CAP( 2, 4)
// (Obsolete) Minimum for BRIGHTNESS 
#define  CORDISPLAY_CAP_BRIGHTNESS_MIN             CORDISPLAY_CAP( 3, 4)
// (Obsolete) Maximum value for BRIGHTNESS 
#define  CORDISPLAY_CAP_BRIGHTNESS_MAX				   CORDISPLAY_CAP( 4, 4)
// (Obsolete) Step value for BRIGHTNESS 
#define  CORDISPLAY_CAP_BRIGHTNESS_STEP				CORDISPLAY_CAP( 5, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Contrast Control Supported FALSE/TRUE 
#define  CORDISPLAY_CAP_CONTRAST                   CORDISPLAY_CAP( 6, 4)
// (Obsolete) Minimum value for CONTRAST (typically 0) 		
#define  CORDISPLAY_CAP_CONTRAST_MIN					CORDISPLAY_CAP( 7, 4)
// (Obsolete) Maximum value for CONTRAST  
#define  CORDISPLAY_CAP_CONTRAST_MAX				   CORDISPLAY_CAP( 8, 4)
// (Obsolete) Step value for CONTRAST  
#define  CORDISPLAY_CAP_CONTRAST_STEP				   CORDISPLAY_CAP( 9, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Saturation Control Supported FALSE/TRUE 
#define  CORDISPLAY_CAP_SATURATION						CORDISPLAY_CAP(10 ,4)
// (Obsolete) Minimum value for SATURATION
#define  CORDISPLAY_CAP_SATURATION_MIN             CORDISPLAY_CAP(11, 4)
// (Obsolete) Maximum value for SATURATION                                                       
#define  CORDISPLAY_CAP_SATURATION_MAX             CORDISPLAY_CAP(12, 4)
// (Obsolete) Step value for SATURATION                                                          
#define  CORDISPLAY_CAP_SATURATION_STEP				CORDISPLAY_CAP(13, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Hue Control	Supported FALSE/TRUE 
#define  CORDISPLAY_CAP_HUE								CORDISPLAY_CAP(14, 4)
// (Obsolete) Minimum for HUE 
#define  CORDISPLAY_CAP_HUE_MIN							CORDISPLAY_CAP(15, 4)
// (Obsolete) Maximum value for HUE                                                       
#define  CORDISPLAY_CAP_HUE_MAX							CORDISPLAY_CAP(16, 4)
// (Obsolete) Step value for HUE                                                          
#define  CORDISPLAY_CAP_HUE_STEP                   CORDISPLAY_CAP(17, 4)
/*------------------------------------------------------------------------*/
// (All obsolete) zooming for the whole display plane
#define  CORDISPLAY_CAP_ZOOM_HORZ			      	CORDISPLAY_CAP(18, 4)
#define  CORDISPLAY_CAP_ZOOM_HORZ_METHOD	      	CORDISPLAY_CAP(19, 4)
#define  CORDISPLAY_CAP_ZOOM_HORZ_MIN       		CORDISPLAY_CAP(20, 4)
#define  CORDISPLAY_CAP_ZOOM_HORZ_MAX		      	CORDISPLAY_CAP(21, 4)
#define  CORDISPLAY_CAP_ZOOM_HORZ_MULT     			CORDISPLAY_CAP(22, 4)
#define  CORDISPLAY_CAP_ZOOM_HORZ_MIN_FACTOR     	CORDISPLAY_CAP(23, 4)
#define  CORDISPLAY_CAP_ZOOM_HORZ_MAX_FACTOR     	CORDISPLAY_CAP(24, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT		      		CORDISPLAY_CAP(25, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT_METHOD      		CORDISPLAY_CAP(26, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT_MIN      			CORDISPLAY_CAP(27, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT_MAX		      	CORDISPLAY_CAP(28, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT_MULT	      		CORDISPLAY_CAP(29, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT_MIN_FACTOR     	CORDISPLAY_CAP(30, 4)
#define  CORDISPLAY_CAP_ZOOM_VERT_MAX_FACTOR     	CORDISPLAY_CAP(31, 4)

/*------------------------------------------------------------------------*/
// (Obsolete)
#define  CORDISPLAY_CAP_STEREO                     CORDISPLAY_CAP(32, 4)
/*------------------------------------------------------------------------*/
// CORDISPLAY_CAP_MULTI_MONITOR is now obsolete -> CORDISPLAY_CAP(33, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) left edge of DISPLAY must be aligned every X bits relative to source buffer origin
#define  CORDISPLAY_CAP_ALIGN_LEFT                 CORDISPLAY_CAP(34, 4)
// (Obsolete) top edge of DISPLAY must be aligned  every Y bits relative to source buffer origin
#define  CORDISPLAY_CAP_ALIGN_TOP                  CORDISPLAY_CAP(35, 4)
// (Obsolete) width of DISPLAYed region must be a multiple of X bits                            
#define  CORDISPLAY_CAP_ALIGN_WIDTH                CORDISPLAY_CAP(36, 4)
// (Obsolete) width of DISPLAYed region must be a multiple of Y bits                            
#define  CORDISPLAY_CAP_ALIGN_HEIGHT               CORDISPLAY_CAP(37, 4)
// (Obsolete) stride of DISPLAY must be a multiple of Y bits                                    
#define  CORDISPLAY_CAP_ALIGN_STRIDE               CORDISPLAY_CAP(38, 4)
/*------------------------------------------------------------------------*/
// (All obsolete) Maximial and Minimal dimensions
#define  CORDISPLAY_CAP_WIDTH_MIN                  CORDISPLAY_CAP(39, 4)
#define  CORDISPLAY_CAP_WIDTH_MAX                  CORDISPLAY_CAP(40, 4)
#define  CORDISPLAY_CAP_HEIGHT_MIN                 CORDISPLAY_CAP(41, 4)
#define  CORDISPLAY_CAP_HEIGHT_MAX                 CORDISPLAY_CAP(42, 4)
/*------------------------------------------------------------------------*/
#define  CORDISPLAY_CAP_LAST                       ( 43 + CORDISPLAY_CAP_FIRST)


/****************************************************************************
*	Display Parameters
****************************************************************************/
#define  CORDISPLAY_PRM_FIRST                      (0 + CORDISPLAY_DEF_FIRST)
#define  CORDISPLAY_PRM( n, size)    		((((n) + CORDISPLAY_PRM_FIRST) << 16) | (size))
/*------------------------------------------------------------------------*/
// Width in pixels
#define  CORDISPLAY_PRM_WIDTH    						CORDISPLAY_PRM( 0, 4)
/*------------------------------------------------------------------------*/
// Height in pixels
#define  CORDISPLAY_PRM_HEIGHT    						CORDISPLAY_PRM( 1, 4)
/*------------------------------------------------------------------------*/
// Refresh Rate in Hz	
#define  CORDISPLAY_PRM_REFRESH							CORDISPLAY_PRM( 2, 4)
/*------------------------------------------------------------------------*/
// Interlaced TRUE/FALSE	
#define  CORDISPLAY_PRM_INTERLACED						CORDISPLAY_PRM( 3, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Scale image width to this pixel size 
#define  CORDISPLAY_PRM_ZOOM_HORZ						CORDISPLAY_PRM( 4, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Scale image height to this pixel size 
#define  CORDISPLAY_PRM_ZOOM_VERT						CORDISPLAY_PRM( 5, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Brightness 
#define  CORDISPLAY_PRM_BRIGHTNESS						CORDISPLAY_PRM( 6, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Contrast 
#define  CORDISPLAY_PRM_CONTRAST							CORDISPLAY_PRM( 7, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Saturation 
#define  CORDISPLAY_PRM_SATURATION 						CORDISPLAY_PRM( 8, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Hue 
#define  CORDISPLAY_PRM_HUE								CORDISPLAY_PRM( 9, 4)
/*------------------------------------------------------------------------*/
// Pixel depth
#define  CORDISPLAY_PRM_PIXEL_DEPTH						CORDISPLAY_PRM(10, 4)
/*------------------------------------------------------------------------*/
// Label
#define  CORDISPLAY_PRM_LABEL							CORDISPLAY_PRM(11, 128)
/*------------------------------------------------------------------------*/
// Maximial and Minimal dimensions
#define  CORDISPLAY_PRM_PIXEL_TYPE_OFFSCREEN			CORDISPLAY_PRM(12, 128)
#define  CORDISPLAY_PRM_PIXEL_TYPE_OVERLAY				CORDISPLAY_PRM(13, 128)
/*------------------------------------------------------------------------*/
// Primary/secondary display type
#define  CORDISPLAY_PRM_TYPE						      CORDISPLAY_PRM(14, 4)

#define  CORDISPLAY_VAL_TYPE_SYSTEM                0x00000001
#define  CORDISPLAY_VAL_TYPE_DUPLICATE             0x00000002
#define  CORDISPLAY_VAL_TYPE_EXTENDED              0x00000004
#define  CORDISPLAY_VAL_TYPE_INDEPENDENT           0x00000008
/*------------------------------------------------------------------------*/
// Display resource index
#define  CORDISPLAY_PRM_INDEX						      CORDISPLAY_PRM(15, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Linear/physical address of display memory
#define  CORDISPLAY_PRM_ADDRESS					      CORDISPLAY_PRM(16, sizeof(void *))
#define  CORDISPLAY_PRM_PHYS_ADDRESS					CORDISPLAY_PRM(17, sizeof(ULONG_PTR))
/*------------------------------------------------------------------------*/
// (Obsolete) Buffer format corresponding to display depth
#define  CORDISPLAY_PRM_FORMAT					      CORDISPLAY_PRM(18, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) Display pitch
#define  CORDISPLAY_PRM_PITCH					         CORDISPLAY_PRM(19, 4)
/*------------------------------------------------------------------------*/
#define  CORDISPLAY_PRM_LAST							( 20 + CORDISPLAY_PRM_FIRST)

#ifdef __cplusplus
extern "C" {
#endif

// Application programming interface 
CORSTATUS CORAPIFUNC CorDisplayResetModule( CORSERVER server);

CORSTATUS CORAPIFUNC CorDisplayGetCount( CORSERVER server, PUINT32 count);
CORSTATUS CORAPIFUNC CorDisplayGetHandle( CORSERVER server, UINT32 instance, CORDISPLAY *display);
CORSTATUS CORAPIFUNC CorDisplayRelease( CORDISPLAY display);
CORSTATUS CORAPIFUNC CorDisplayReset( CORDISPLAY display);

// cap queries 
CORSTATUS CORAPIFUNC CorDisplayGetCap( CORDISPLAY display, UINT32 cap, void *value);

// parameter queries 
CORSTATUS CORAPIFUNC CorDisplayGetPrm  ( CORDISPLAY display, UINT32 param, void *value);
CORSTATUS CORAPIFUNC CorDisplaySetPrm  ( CORDISPLAY display, UINT32 param, UINT32 value);
CORSTATUS CORAPIFUNC CorDisplaySetPrmEx( CORDISPLAY display, UINT32 param, const void *prm);

#if COR_WIN32
// Access to Windows GDI Display Context
CORSTATUS CORAPIFUNC CorDisplayGetDC( CORDISPLAY hDisplay, HDC *pDC);
CORSTATUS CORAPIFUNC CorDisplayReleaseDC( CORDISPLAY hDisplay);

#if !COR_WIN64
// (Obsolete) Programmable display support
CORSTATUS CORAPIFUNC CorDisplaySetMode(CORSERVER server, UINT32 index, UINT32 width, UINT32 height, UINT32 format, UINT32 refresh);
#endif
#endif

#ifdef  __cplusplus
}
#endif

#endif   //_CAPIDISP_H_
