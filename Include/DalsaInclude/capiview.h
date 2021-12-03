//
// Coreco API - View port functions.
//

#ifndef _CAPIVIEW_H_
#define _CAPIVIEW_H_

#include <capidef.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
*	View Capabilities
****************************************************************************/
#define CORVIEW_DEF_FIRST							0x0000

#define CORVIEW_CAP_FIRST							(  0 + CORVIEW_DEF_FIRST)
#define CORVIEW_CAP( n, size)						((((n) + CORVIEW_CAP_FIRST) << 16) | (size)) 
/*------------------------------------------------------------------------*/

//CORVIEW_CAP_KEYER_TYPE is obsolete, left in api to be bkwd compatible
//replaced by CORVIEW_CAP_OVERLAY_MODE
#define CORVIEW_CAP_KEYER_TYPE						CORVIEW_CAP( 0, 4) //**obsolete
#define CORVIEW_VAL_KEYER_TYPE_COLOR				0x00000001  //**obsolete
#define CORVIEW_VAL_KEYER_TYPE_CHROMA				0x00000002  //**obsolete
#define CORVIEW_VAL_KEYER_TYPE_ALPHA				0x00000004  //**obsolete

/*------------------------------------------------------------------------*/
// Number of lookup table available
#define CORVIEW_CAP_LUTS							CORVIEW_CAP( 1, 4)
/*------------------------------------------------------------------------*/
// Sequence in the list of overlaid views
#define CORVIEW_CAP_ZORDER							CORVIEW_CAP( 2, 4)
/*------------------------------------------------------------------------*/
#define CORVIEW_CAP_FLIP							CORVIEW_CAP( 3, 4)

#define CORVIEW_VAL_FLIP_X							0x00000001
#define CORVIEW_VAL_FLIP_Y							0x00000002
/*------------------------------------------------------------------------*/
// CAP 4 was used for CORVIEW_CAP_SIGNAL (now available)

#define CORVIEW_VAL_SIGNAL_START					0x00000001   
#define CORVIEW_VAL_SIGNAL_END						0x00000002   
/*------------------------------------------------------------------------*/
// ability to change color space when VIEWing an image
#define CORVIEW_CAP_COLOR_SPACE_CONVERT				CORVIEW_CAP( 5, 4)
/*------------------------------------------------------------------------*/
#define CORVIEW_CAP_ROTATE							CORVIEW_CAP( 6, 4)

#define CORVIEW_VAL_ROTATE_ANY						0x00000001 
#define CORVIEW_VAL_ROTATE_90						0x00000002 
/*------------------------------------------------------------------------*/
// 'displ level' X BITS OUT OF Y 
#define CORVIEW_CAP_RANGE							CORVIEW_CAP( 7, 4)
// (Obsolete) mask certain bits from VIEWing
#define CORVIEW_CAP_MASK							CORVIEW_CAP( 8, 4)
/*------------------------------------------------------------------------*/
// source rectangle may be defined in buffer
#define CORVIEW_CAP_ROI_SRC							CORVIEW_CAP( 9, 4)
// destination rectangle may be defined on the diaplay plane
#define CORVIEW_CAP_ROI_DST							CORVIEW_CAP(10, 4)
// For backward compatibility
#define CORVIEW_CAP_WIN_SRC							CORVIEW_CAP_ROI_SRC
#define CORVIEW_CAP_WIN_DST							CORVIEW_CAP_ROI_DST
/*------------------------------------------------------------------------*/
// zooming for the particular view only!
#define CORVIEW_CAP_ZOOM_HORZ						CORVIEW_CAP(11, 4)
#define CORVIEW_CAP_ZOOM_HORZ_METHOD				CORVIEW_CAP(12, 4)
#define CORVIEW_CAP_ZOOM_HORZ_MIN					CORVIEW_CAP(13, 4)
#define CORVIEW_CAP_ZOOM_HORZ_MAX					CORVIEW_CAP(14, 4)
#define CORVIEW_CAP_ZOOM_HORZ_MULT					CORVIEW_CAP(15, 4)
#define CORVIEW_CAP_ZOOM_HORZ_MIN_FACTOR			CORVIEW_CAP(16, 4)
#define CORVIEW_CAP_ZOOM_HORZ_MAX_FACTOR			CORVIEW_CAP(17, 4)
#define CORVIEW_CAP_ZOOM_VERT						CORVIEW_CAP(18, 4)
#define CORVIEW_CAP_ZOOM_VERT_METHOD				CORVIEW_CAP(19, 4)
#define CORVIEW_CAP_ZOOM_VERT_MIN					CORVIEW_CAP(20, 4)
#define CORVIEW_CAP_ZOOM_VERT_MAX					CORVIEW_CAP(21, 4)
#define CORVIEW_CAP_ZOOM_VERT_MULT					CORVIEW_CAP(22, 4)
#define CORVIEW_CAP_ZOOM_VERT_MIN_FACTOR			CORVIEW_CAP(23, 4)
#define CORVIEW_CAP_ZOOM_VERT_MAX_FACTOR			CORVIEW_CAP(24, 4)

#define CORVIEW_VAL_ZOOM_METHOD_SIMPLE				0x00000001
#define CORVIEW_VAL_ZOOM_METHOD_INTERPOLATION		0x00000002
#define CORVIEW_VAL_ZOOM_METHOD_POW2				0x00000004
#define CORVIEW_VAL_ZOOM_METHOD_INTEGER				0x00000008
/*------------------------------------------------------------------------*/
// (Obsolete) Weather no tearing mechanism in this view
#define CORVIEW_CAP_NO_TEARING						CORVIEW_CAP(25, 4)
#define CORVIEW_CAP_NOTEARING						CORVIEW_CAP_NO_TEARING
/*------------------------------------------------------------------------*/
// TRUE is output Lookup Tables can be enabled/disabled, FALSE otherwise
#define CORVIEW_CAP_LUT_ENABLE					   	CORVIEW_CAP(26, 4)

// TRUE if output Look-Up Tables are available, FALSE otherwise
#define CORVIEW_CAP_LUT 					      	CORVIEW_CAP( 27, 4)
// TRUE if VGA adapter can toggle between buffers at end of frame automatically
#define CORVIEW_CAP_AUTO_SHOW				      	CORVIEW_CAP( 28, 4)

// (Obsolete) Alpha blending modes supported
#define CORVIEW_CAP_ALPHA_BLEND_MODE				CORVIEW_CAP( 29, 4)

// (Obsolete) Alpha keying modes supported
#define CORVIEW_CAP_ALPHA_KEY_MODE					CORVIEW_CAP( 30, 4)

// (Obsolete) step that will cause a change in the alpha blending factor
#define CORVIEW_CAP_ALPHA_BLEND_STEP				CORVIEW_CAP( 31, 4)

//Overlay modes that are supported 
#define CORVIEW_CAP_OVERLAY_MODE 					CORVIEW_CAP( 32, 4)

//Maximum value for CORVIEW_PRM_RANGE
#define CORVIEW_CAP_RANGE_MAX 					   CORVIEW_CAP( 33, 4)

/*------------------------------------------------------------------------*/
#define CORVIEW_CAP_LAST  /* last valid + 1 */		( 34 + CORVIEW_CAP_FIRST)
 
/****************************************************************************
*	View Parameters
****************************************************************************/

#define CORVIEW_PRM_FIRST							( 0 + CORVIEW_DEF_FIRST)
#define CORVIEW_PRM( n, size)						((((n) + CORVIEW_PRM_FIRST) << 16) | (size))
/*------------------------------------------------------------------------*/
#define CORVIEW_PRM_KEYER_TYPE						CORVIEW_PRM( 0, 4)  //replaced by CORVIEW_PRM_OVERLAY_MODE
/*------------------------------------------------------------------------*/
#define CORVIEW_PRM_KEYER_COLOR_RED					CORVIEW_PRM( 1, 4)
#define CORVIEW_PRM_KEYER_COLOR_GREEN				CORVIEW_PRM( 2, 4)
#define CORVIEW_PRM_KEYER_COLOR_BLUE				CORVIEW_PRM( 3, 4)
#define CORVIEW_PRM_KEYER_COLOR_PALETTE				CORVIEW_PRM( 4, 4)
#define CORVIEW_PRM_KEYER_CHROMA_LO					CORVIEW_PRM( 5, 4)
#define CORVIEW_PRM_KEYER_CHROMA_HI					CORVIEW_PRM( 6, 4)
#define CORVIEW_PRM_KEYER_ALPHA						CORVIEW_PRM( 7, 4)   //**obsolete
/*------------------------------------------------------------------------*/
// CORVIEW_PRM(8,4) to CORVIEW_PRM(11,4) have been removed (KEYER_RECTMASK)

#if COR_WIN32
#define CORVIEW_PRM_HWND							CORVIEW_PRM(12, sizeof(HWND))
#else
#define CORVIEW_PRM_HWND							CORVIEW_PRM(12, 4)
#endif
/*------------------------------------------------------------------------*/
// Look-Up Table number (0 to CORDISPLAY_LUT_MAX-1) 
#define CORVIEW_PRM_LUT_NUMBER						CORVIEW_PRM(13, 4)
/*------------------------------------------------------------------------*/
#define CORVIEW_PRM_FLIP_X							CORVIEW_PRM(14, 4)
#define CORVIEW_PRM_FLIP_Y							CORVIEW_PRM(15, 4)
/*------------------------------------------------------------------------*/
// rotation in degrees
#define CORVIEW_PRM_ROTATE							CORVIEW_PRM(16, 4)
/*------------------------------------------------------------------------*/
// Precedence of the view in the Z dir compared to others on the same display
#define CORVIEW_PRM_ZORDER							CORVIEW_PRM(17, 4)
/*------------------------------------------------------------------------*/
// 'displ level' X BITS OUT OF Y 
#define CORVIEW_PRM_RANGE							CORVIEW_PRM(18, 4)
/*------------------------------------------------------------------------*/
// (Obsolete) mask certain bits to VIEW
#define CORVIEW_PRM_MASK							CORVIEW_PRM(19, 4)
/*------------------------------------------------------------------------*/
// these by default set to full buffer size and full display area at creation 
// source window
#define CORVIEW_PRM_ROI_SRC_LEFT					CORVIEW_PRM(20, 4)
#define CORVIEW_PRM_ROI_SRC_TOP						CORVIEW_PRM(21, 4)

// CORVIEW_PRM(21, 4) missing

#define CORVIEW_PRM_ROI_SRC_HEIGHT					CORVIEW_PRM(23, 4)
#define CORVIEW_PRM_ROI_SRC_WIDTH					CORVIEW_PRM(24, 4)
// destination window
#define CORVIEW_PRM_ROI_DST_LEFT                CORVIEW_PRM(25, 4)
#define CORVIEW_PRM_ROI_DST_TOP                 CORVIEW_PRM(26, 4)
#define CORVIEW_PRM_ROI_DST_HEIGHT              CORVIEW_PRM(27, 4)
#define CORVIEW_PRM_ROI_DST_WIDTH               CORVIEW_PRM(28, 4)

// For backward compatibility
#define CORVIEW_PRM_WIN_SRC_LEFT                CORVIEW_PRM_ROI_SRC_LEFT
#define CORVIEW_PRM_WIN_SRC_TOP						CORVIEW_PRM_ROI_SRC_TOP
#define CORVIEW_PRM_WIN_SRC_HEIGHT					CORVIEW_PRM_ROI_SRC_HEIGHT
#define CORVIEW_PRM_WIN_SRC_WIDTH					CORVIEW_PRM_ROI_SRC_WIDTH
#define CORVIEW_PRM_WIN_DST_LEFT                CORVIEW_PRM_ROI_DST_LEFT
#define CORVIEW_PRM_WIN_DST_TOP						CORVIEW_PRM_ROI_DST_TOP
#define CORVIEW_PRM_WIN_DST_HEIGHT					CORVIEW_PRM_ROI_DST_HEIGHT
#define CORVIEW_PRM_WIN_DST_WIDTH					CORVIEW_PRM_ROI_DST_WIDTH
/*-----------------------------------------------------------------------*/
// (Obsolete) Turn on mechanism to prevent tearing on this display	
#define CORVIEW_PRM_STOP_TEARING					CORVIEW_PRM(29, 4)
// for backwards compatibility
#define CORVIEW_PRM_STOPTEARING						CORVIEW_PRM_STOP_TEARING
/*------------------------------------------------------------------------*/
#define CORVIEW_PRM_LUT_MAX							CORVIEW_PRM(30, 4)
#define CORVIEW_PRM_LUT_ENABLE						CORVIEW_PRM(31, 4)
#define CORVIEW_PRM_LUT_FORMAT						CORVIEW_PRM(32, 4)
/*------------------------------------------------------------------------*/
//#define CORVIEW_PRM_VIDEO_MEMORY_AVAILABLE			CORVIEW_PRM(33, 4)
/*------------------------------------------------------------------------*/
// View mode
#define CORVIEW_PRM_MODE                        CORVIEW_PRM(33, 4)
#define CORVIEW_VAL_MODE_AUTO_DETECT            0x00000000
#define CORVIEW_VAL_MODE_KEYER                  0x00000002
#define CORVIEW_VAL_MODE_OVERLAY                CORVIEW_VAL_MODE_KEYER
#define CORVIEW_VAL_MODE_DIB                    0x00000004            
#define CORVIEW_VAL_MODE_BLT                    0x00000008  

/*------------------------------------------------------------------------*/
// Behaviour when refreshing display of overlay
#define CORVIEW_PRM_OVERLAY_MODE						CORVIEW_PRM(34, 4)
#define CORVIEW_VAL_OVERLAY_MODE_ALWAYS_ON_TOP			0x00000001
#define CORVIEW_VAL_OVERLAY_MODE_AUTO_COLOR_KEYING		0x00000002
#define CORVIEW_VAL_OVERLAY_MODE_MANUAL_COLOR_KEYING	0x00000004
// (Next 3 are obsolete)
#define CORVIEW_VAL_OVERLAY_MODE_ALPHA_BLENDING			0x00000008
#define CORVIEW_VAL_OVERLAY_MODE_ALPHA_KEYING			0x00000010
#define CORVIEW_VAL_OVERLAY_MODE_ALPHA_KEYING_BLENDING  0x00000020

//The following modes are obsolete, they are left here to be bkwd compatible.
#define CORVIEW_VAL_OVERLAY_MODE_DIRECT         0x00000001		//**obsolete replaced by CORVIEW_VAL_OVERLAY_MODE_WINDOW_ON_TOP
#define CORVIEW_VAL_OVERLAY_MODE_AUTO_KEYING    0x00000002		//**obsolete by CORVIEW_VAL_OVERLAY_MODE_AUTO_COLOR_KEYING
#define CORVIEW_VAL_OVERLAY_MODE_MANUAL_KEYING  0x00000003		//**obsolete by CORVIEW_VAL_OVERLAY_MODE_MANUAL_COLOR_KEYING

/*------------------------------------------------------------------------*/
// Title of window created when CORVIEW_PRM_HWND is set to -1
#define CORVIEW_PRM_HWND_TITLE                  CORVIEW_PRM(35, 128)
/*------------------------------------------------------------------------*/

//*-----------------------------------------------------------------------*/
// Sets the alpha blending feature
// Alpha blending is enabled from CORVIEW_PRM_OVERLAY_MODE
// (Obsolete)
//*-----------------------------------------------------------------------*/
#define CORVIEW_PRM_ALPHA_BLEND_CONST           CORVIEW_PRM(36, 8)
#define CORVIEW_PRM_ALPHA_BLEND_MODE            CORVIEW_PRM(37, 4)
#define CORVIEW_VAL_ALPHA_BLEND_SRC_CONST       0x00000001
#define CORVIEW_VAL_ALPHA_BLEND_DST_CONST       0x00000002

//*-----------------------------------------------------------------------*/
// Sets the alpha keying features
// Alpha keying is enabled from CORVIEW_PRM_OVERLAY_MODE
// (Obsolete)
//*-----------------------------------------------------------------------*/
#define CORVIEW_PRM_ALPHA_KEY_MODE              CORVIEW_PRM(38, 4)
#define CORVIEW_PRM_ALPHA_KEY_VALUE             CORVIEW_PRM(39, 4)
#define CORVIEW_VAL_ALPHA_KEY_SRC_NOT_EQUAL	    0x00000001
#define CORVIEW_VAL_ALPHA_KEY_DST_NOT_EQUAL     0x00000002

//*-----------------------------------------------------------------------*/
// Zoom method ( horizontal and vertical)
//*-----------------------------------------------------------------------*/
#define CORVIEW_PRM_ZOOM_HORZ_METHOD				CORVIEW_PRM( 40, 4)
#define CORVIEW_PRM_ZOOM_VERT_METHOD				CORVIEW_PRM( 41, 4)

#define CORVIEW_PRM_LAST   /* last valid + 1 */		( 42 + CORVIEW_PRM_FIRST)
/*------------------------------------------------------------------------*/

// CORVIEW_MODE_KEYER has been changed to the more descriptive CORVIEW_MODE_OVERLAY
// (mc) keep it for backward compatibility
#define CORVIEW_MODE_AUTO_DETECT                CORVIEW_VAL_MODE_AUTO_DETECT	
#define CORVIEW_MODE_KEYER                      CORVIEW_VAL_MODE_KEYER			
#define CORVIEW_MODE_OVERLAY                    CORVIEW_VAL_MODE_OVERLAY		
#define CORVIEW_MODE_DIB                        CORVIEW_VAL_MODE_DIB            
#define CORVIEW_MODE_BLT                        CORVIEW_VAL_MODE_BLT			


// constants used for "ops" parameter of CorViewBlit and CorViewShowAlt function
#define CORVIEW_OPS_SRC_ROI				0x0001
#define CORVIEW_OPS_DST_ROI				0x0002
#define CORVIEW_OPS_ROTATION           0x0004
#define CORVIEW_OPS_MIRROR_UP_DOWN		0x0008
#define CORVIEW_OPS_MIRROR_LEFT_RIGHT	0x0010
#define CORVIEW_OPS_COLOR_FILL			0x0020
#define CORVIEW_OPS_SRC_KEY_COLOR		0x0040
#define CORVIEW_OPS_DST_KEY_COLOR		0x0080

// Blit parameters structure
typedef struct
{
	UINT32 roi_src_left;
	UINT32 roi_src_top;
	UINT32 roi_src_height;
	UINT32 roi_src_width;
	UINT32 roi_dst_left;
	UINT32 roi_dst_top;
	UINT32 roi_dst_height;
	UINT32 roi_dst_width;
	UINT32 rotation_angle;
	UINT32 color_fill;
	UINT32 dst_key_color;		// reserved
	UINT32 src_key_color;		// reserved
} CORVIEW_BLIT_DESC, *PCORVIEW_BLIT_DESC;  // (mc) should be the same as CVDI_BLIT_DESC in cvditypes.h

// (Obsolete) alpha blending constants
typedef struct
{
	UINT32  srcConstant;
	UINT32  dstConstant;
} CORVIEW_ALPHA_BLEND_CONSTS, *PCORVIEW_ALPHA_BLEND_CONSTS;

// Application programming interface 

CORSTATUS CORAPIFUNC CorViewNew( CORSERVER server, CORDISPLAY display, CORBUFFER buffer, UINT32 mode, CORVIEW *view);
CORSTATUS CORAPIFUNC CorViewFree( CORVIEW view);

CORSTATUS CORAPIFUNC CorViewGetCap( CORVIEW view, UINT32 cap, void *value);

CORSTATUS CORAPIFUNC CorViewGetPrm( CORVIEW view, UINT32 param, void *value);
CORSTATUS CORAPIFUNC CorViewSetPrm( CORVIEW view, UINT32 param, UINT32 value);
CORSTATUS CORAPIFUNC CorViewSetPrmEx( CORVIEW view, UINT32 param, const void *prm);

CORSTATUS CORAPIFUNC CorViewGetLut( CORVIEW view, CORLUT hLut, UINT32 lutNumber);
CORSTATUS CORAPIFUNC CorViewSetLut( CORVIEW view, CORLUT hLut, UINT32 lutNumber);

CORSTATUS CORAPIFUNC CorViewShow( CORVIEW view);
CORSTATUS CORAPIFUNC CorViewUpdatePos( CORVIEW view);
CORSTATUS CORAPIFUNC CorViewOnMove( CORVIEW view);
CORSTATUS CORAPIFUNC CorViewOnSize( CORVIEW view);
CORSTATUS CORAPIFUNC CorViewOnPaint( CORVIEW view);
CORSTATUS CORAPIFUNC CorViewHide( CORVIEW view);

CORSTATUS CORAPIFUNC CorViewBlit(CORVIEW source, CORVIEW dest, UINT32 ops, CORVIEW_BLIT_DESC *parameters);
CORSTATUS CORAPIFUNC CorViewShowWithOps(CORVIEW view, UINT32 ops, CORVIEW_BLIT_DESC *parameters);

CORSTATUS CORAPIFUNC CorViewSetBuffer( CORVIEW view, CORBUFFER buffer);

#ifdef __cplusplus
}
#endif

#endif   //_CAPIVIEW_H_
