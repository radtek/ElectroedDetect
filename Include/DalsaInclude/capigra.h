//
// Coreco API - Graphic functions.
//

#ifndef _CAPIGRA_H_
#define _CAPIGRA_H_

#include <capidef.h>

/****************************************************************************
*	Graphic Capabilities
*
*	Last capability #: 1
****************************************************************************/
#define CORGRAPHIC_CAP_FIRST		0
#define CORGRAPHIC_CAP( n, size)    ((((n) + CORGRAPHIC_CAP_FIRST) << 16) | (size))

#define	CORGRAPHIC_CAP_FILL			CORGRAPHIC_CAP( 0, 4)
#define	CORGRAPHIC_CAP_TEXT			CORGRAPHIC_CAP( 1, 4)

/****************************************************************************
*	Graphic Parameters
*
*	Last parameter #: 5
****************************************************************************/
#define CORGRAPHIC_PRM_FIRST        0
#define CORGRAPHIC_PRM( n, size)	((((n) + CORGRAPHIC_PRM_FIRST) << 16) | (size))

#define CORGRAPHIC_PRM_OPM		    CORGRAPHIC_PRM( 0, 4)
	#define CORGRAPHIC_VAL_OPM_REP	0
	#define CORGRAPHIC_VAL_OPM_XOR	1
	#define CORGRAPHIC_VAL_OPM_AND	2
	#define CORGRAPHIC_VAL_OPM_OR	3
	#define CORGRAPHIC_VAL_OPM_T	0x00008000

#define CORGRAPHIC_PRM_BKCOLOR	  CORGRAPHIC_PRM( 2, sizeof( CORDATA))
#define CORGRAPHIC_PRM_COLOR	  CORGRAPHIC_PRM( 3, sizeof( CORDATA))
#define CORGRAPHIC_PRM_FONTSCALE  CORGRAPHIC_PRM( 4, 4)
#define CORGRAPHIC_PRM_FONTNAME	  CORGRAPHIC_PRM( 5, 128)
#define CORGRAPHIC_PRM_LABEL	  CORGRAPHIC_PRM( 6, 128)
#define CORGRAPHIC_PRM_TEXTALIGN  CORGRAPHIC_PRM( 7, 4)
	#define CORGRAPHIC_VAL_TEXTALIGN_L	0
	#define CORGRAPHIC_VAL_TEXTALIGN_R	1
	#define CORGRAPHIC_VAL_TEXTALIGN_C	2
#define CORGRAPHIC_PRM_CLIP_ENABLE  CORGRAPHIC_PRM( 8, 4)

#ifdef __cplusplus
extern "C" {
#endif

// Application programming interface 

CORSTATUS CORAPIFUNC CorGraphicResetModule( CORSERVER hServer);

/* Gets handle to a graphic device */
CORSTATUS CORAPIFUNC CorGraphicGetCount (CORSERVER hServer, PUINT32 count);
CORSTATUS CORAPIFUNC CorGraphicGetHandle(CORSERVER hServer, UINT32 instance, CORGRAPHIC *hGraphic);

CORSTATUS CORAPIFUNC CorGraphicRelease(CORGRAPHIC hGraphic);
CORSTATUS CORAPIFUNC CorGraphicReset  (CORGRAPHIC hGraphic);

/* Get capabilities */
CORSTATUS CORAPIFUNC CorGraphicGetCap(CORGRAPHIC hGraphic, UINT32 cap, void *value);

/* Get/Set graphic attributes: all graphic attributes have to be saved locally */
CORSTATUS CORAPIFUNC CorGraphicGetPrm  (CORGRAPHIC hGraphic, UINT32 prm, void *value);
CORSTATUS CORAPIFUNC CorGraphicSetPrm  (CORGRAPHIC hGraphic, UINT32 prm, UINT32 value);
CORSTATUS CORAPIFUNC CorGraphicSetPrmEx(CORGRAPHIC hGraphic, UINT32 prm, const void *value);
CORSTATUS CORAPIFUNC CorGraphicSetFont( CORGRAPHIC hGraphic, PCSTR fontName, const void *fontData, UINT32 fontDataSize);

/* Drawing shape functions */
CORSTATUS CORAPIFUNC CorGraphicArc(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y, UINT32 xRadius, UINT32 yRadius, UINT32 startAngle, UINT32 endAngle, UINT32 fill);
CORSTATUS CORAPIFUNC CorGraphicClear(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2);
CORSTATUS CORAPIFUNC CorGraphicDot(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y);
CORSTATUS CORAPIFUNC CorGraphicDots(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y, CORBUFFER dots, UINT32 nPixels);
CORSTATUS CORAPIFUNC CorGraphicDrawVector(CORGRAPHIC hGraphic, CORBUFFER buffer, CORBUFFER vec, INT32 min, INT32 max, UINT32 n);
CORSTATUS CORAPIFUNC CorGraphicFill(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 xSeed, UINT32 ySeed);
CORSTATUS CORAPIFUNC CorGraphicGrid(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2, UINT32 nx, UINT32 ny);
CORSTATUS CORAPIFUNC CorGraphicLine(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2);
CORSTATUS CORAPIFUNC CorGraphicRect(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2, UINT32 fill);
CORSTATUS CORAPIFUNC CorGraphicTarget(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y);
CORSTATUS CORAPIFUNC CorGraphicEllipse(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y, UINT32 xRadius, UINT32 yRadius, UINT32 fill);
CORSTATUS CORAPIFUNC CorGraphicCircle(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y, UINT32 radius, UINT32 fill);

/* Drawing text functions */
CORSTATUS CORAPIFUNC CorGraphicText (CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y, PCSTR text);
CORSTATUS CORAPIFUNC CorGraphicTextEx(CORGRAPHIC hGraphic, CORBUFFER buffer, UINT32 x, UINT32 y, UINT32 angle, PCSTR text);

#ifdef  __cplusplus
}
#endif

#endif   // _CAPIGRA_H_
