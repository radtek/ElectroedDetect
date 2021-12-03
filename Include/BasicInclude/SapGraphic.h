#ifndef _SAPGRAPHIC_H_
#define _SAPGRAPHIC_H_

// SapGraphic.h : header file
//

#include "SapClassBasicDef.h"


//
// SapGraphic class declaration
//

class SAPCLASSBASIC_CLASS SapGraphic : public SapManager
{
public:
   // Drawing modes
   typedef int DrawMode;
   enum _DrawMode
   {
      ModeReplace = CORGRAPHIC_VAL_OPM_REP,
      ModeAnd     = CORGRAPHIC_VAL_OPM_AND,
      ModeOr      = CORGRAPHIC_VAL_OPM_OR,
      ModeXor     = CORGRAPHIC_VAL_OPM_XOR
   };

   // Text alignment
   typedef int TextAlign;
   enum _TextAlign
   {
      TextLeft   = CORGRAPHIC_VAL_TEXTALIGN_L,
      TextCenter = CORGRAPHIC_VAL_TEXTALIGN_C,
      TextRight  = CORGRAPHIC_VAL_TEXTALIGN_R
   };

public:
   // Constructor/Destructor
   SapGraphic(SapLocation loc = SapLocation::ServerSystem);
   SapGraphic(const SapGraphic &graph);
   virtual ~SapGraphic();

   SapGraphic &operator=(const SapGraphic &graph);

   // Module create/destroy
   virtual BOOL Create();
   virtual BOOL Destroy();

   // Access to implementation
   CORHANDLE GetHandle()     const { return m_hGraphic; }
   SapLocation GetLocation() const { return m_Location; }

   DrawMode GetDrawMode()   const { return m_DrawMode; }
   BOOL GetTransparency()   const { return m_IsTransparent; }
   SapData GetColor()       const { return m_Color; }
   SapData GetBackColor()   const { return m_BackColor; }
   TextAlign GetTextAlign() const { return m_TextAlign; }

   BOOL SetLocation(SapLocation location);
   virtual BOOL SetDrawMode(DrawMode drawMode);
   virtual BOOL SetTransparency(BOOL isTransparent);
   virtual BOOL SetColor(SapData color);
   virtual BOOL SetBackColor(SapData backColor);
   virtual BOOL SetTextAlign(TextAlign textAlign);
   virtual BOOL SetBatchMode(BOOL batchMode, SapView *pView);

   virtual BOOL IsCapabilityValid(int cap);
   virtual BOOL GetCapability(int cap, void *pValue);

   virtual BOOL IsParameterValid(int param);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   // Drawing methods
   BOOL Circle(SapBuffer *pBuffer, int x, int y, int radius, BOOL fill = FALSE);
   BOOL Circle(SapView *pView, int x, int y, int radius, BOOL fill = FALSE);
   BOOL Clear(SapBuffer *pBuffer);
   BOOL Clear(SapView *pView);
   BOOL Dot(SapBuffer *pBuffer, int x, int y);
   BOOL Dot(SapView *pView, int x, int y);
   BOOL Ellipse(SapBuffer *pBuffer, int x, int y, int xRadius, int yRadius, BOOL fill = FALSE);
   BOOL Ellipse(SapView *pView, int x, int y, int xRadius, int yRadius, BOOL fill = FALSE);
   BOOL Line(SapBuffer *pBuffer, int x1, int y1, int x2, int y2);
   BOOL Line(SapView *pView, int x1, int y1, int x2, int y2);
   BOOL Rectangle(SapBuffer *pBuffer, int x1, int y1, int x2, int y2, BOOL fill = FALSE);
   BOOL Rectangle(SapView *pView, int x1, int y1, int x2, int y2, BOOL fill = FALSE);
   BOOL Text(SapBuffer *pBuffer, int x, int y, const char *text);
   BOOL Text(SapView *pView, int x, int y, const char *text);
   BOOL Flush(SapView *pView, int x1 = 0, int y1 = 0, int x2 = -1, int y2 = -1);

protected:
   // Utility methods
   void Construct(SapLocation loc, DrawMode drawMode, SapData color, SapData backColor, TextAlign textAlign);
   BOOL EnableBatchMode(SapView *pView);
   BOOL DisableBatchMode();
   BOOL InitSapDrawing(SapView *pView);
   BOOL InitGDIDrawing(SapView *pView, BOOL fill);
   BOOL InitGDITextDrawing(SapView *pView);
   BOOL EndGDIDrawing(SapView *pView);
   HDC GetDrawingDC() { return m_BatchMode ? m_hBatchDC : m_hDC; }

protected:
   SapLocation m_Location;
   CORGRAPHIC  m_hGraphic;

   // Parameters
   DrawMode  m_DrawMode;         // Drawing mode between foreground color and destination
   BOOL      m_IsTransparent;    // TRUE if transparent drawing (background remains unchanged)
   SapData   m_Color;            // Foreground drawing color
   SapData   m_BackColor;        // Background drawing color
   TextAlign m_TextAlign;        // Text alignment
   BOOL      m_IsNewColor;       // TRUE when foreground color value has changed

   // Windows GDI objects used for drawing on the image overlay
   HFONT   m_hFont;
   HGDIOBJ m_hOldFont;        // Initial font for device context
   HBRUSH  m_hBrush;
   HGDIOBJ m_hOldBrush;       // Initial brush for device context
   HPEN    m_hPen;
   HGDIOBJ m_hOldPen;         // Initial pen for device context
   HDC     m_hDC;

   // Management of batch (buffered) drawing in the image overlay
   BOOL    m_BatchMode;       // TRUE if batch drawing is active
   SapView *m_pBatchView;     // View object to which batch drawing applies
   HDC     m_hBatchDC;        // Memory device context for drawing
   HBITMAP m_hBatchBitmap;    // Bitmap to draw into
   HGDIOBJ m_hOldBatchBitmap; // Initial bitmap for batch device context

   // Buffer used for non-primary VGA overlay drawing
   CORBUFFER m_hBuffer;
}; 

#endif   // _SAPGRAPHIC_H_
