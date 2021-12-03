#ifndef _SAPVIEW_H_
#define _SAPVIEW_H_

//	SapView.h : header file
//

#include "SapClassBasicDef.h"

// Forward declarations
class SAPCLASSBASIC_CLASS SapView;


//
// SapViewScaleParams class declaration
//
class SAPCLASSBASIC_CLASS SapViewScaleParams
{
public:
   SapViewScaleParams()
      { Construct(0, 0, SapDefWidth, SapDefHeight, 1.0, 1.0); }
   SapViewScaleParams(int left, int top, int width, int height)
      { Construct(left, top, width, height, 1.0, 1.0); }
   ~SapViewScaleParams() {}

	int   Left() const     { return m_Left;}
	int   Top() const      { return m_Top;}
	int   Width() const    { return m_Width;}
	int   Height() const   { return m_Height;}
	float ZoomHorz() const { return m_ZoomHorz;}
	float ZoomVert() const { return m_ZoomVert;}

   void SetLeft(int left)           { m_Left = left ;}
   void SetTop(int top)             { m_Top = top; }
   void SetWidth(int width)         { m_Width = width; }
   void SetHeight(int height)       { m_Height = height; }
   void SetZoomHorz(float zoomHorz) { m_ZoomHorz = zoomHorz; }
   void SetZoomVert(float zoomVert) { m_ZoomVert = zoomVert; }

protected:
   // Utility methods
   void Construct(int left, int top, int width, int height, float zoomHorz, float zoomVert)
   {
      m_Left = left;
      m_Top = top;
      m_Width = width;
      m_Height = height;
      m_ZoomHorz = zoomHorz;
      m_ZoomVert = zoomVert;
   }

protected:
   // ROI parameters
   int m_Left;
   int m_Top;
   int m_Width;
   int m_Height;

   // Zooming parameters
   float m_ZoomHorz;
   float m_ZoomVert;
};

//
// SapViewCallbackInfo class declaration
//
class SAPCLASSBASIC_CLASS SapViewCallbackInfo
{
public:
   SapViewCallbackInfo(SapView *pView, void *context)
      { m_pView = pView; m_Context = context; }
	~SapViewCallbackInfo() {}

   // Obsolete constructor
   SapViewCallbackInfo(void *context)
      { m_pView = NULL; m_Context = context; }

   SapView *GetView() const { return m_pView; }
	void *GetContext() const { return m_Context; }

protected:
   SapView *m_pView;
	void *m_Context;
};

typedef void (*SapViewCallback)(SapViewCallbackInfo *);


//
// SapView class declaration
//

// Common view window handles
const HWND SapHwndDesktop = (HWND) NULL;
const HWND SapHwndAutomatic = (HWND) -1;

class SAPCLASSBASIC_CLASS SapView : public SapManager
{
public:
   // Overlay modes
   typedef int OverlayMode;
   enum _OverlayMode
   {
      OverlayNone         = 0,
      OverlayAlwaysOnTop  = CORVIEW_VAL_OVERLAY_MODE_ALWAYS_ON_TOP,
      OverlayAutoKeying   = CORVIEW_VAL_OVERLAY_MODE_AUTO_COLOR_KEYING,
      OverlayManualKeying = CORVIEW_VAL_OVERLAY_MODE_MANUAL_COLOR_KEYING
   };

   // Scaling modes
   enum ScalingMode
   {
      ScalingNone,
      ScalingFitToWindow,
      ScalingZoom,
      ScalingUserDefined
   };

public:
	// Constructor/Destructor
   SapView(SapBuffer *pBuffer = NULL, HWND hWnd = SapHwndDesktop, SapViewCallback pCallback = NULL, void *pContext = NULL);
   SapView(SapDisplay *pDisplay, SapBuffer *pBuffer, HWND hWnd = SapHwndDesktop, SapViewCallback pCallback = NULL, void *pContext = NULL);
	SapView(const SapView &view);
	virtual ~SapView();

	SapView &operator=(const SapView &view);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
   virtual CORHANDLE GetHandle() const { return m_hView; }

   SapBuffer *GetBuffer()        const { return m_pBuffers; }
	SapDisplay *GetDisplay()      const { return m_pDisplay; }
	HWND GetWindow()					const { return m_hWindow; }
	SapViewCallback GetCallback()	const { return m_pCallback; }
	void *GetContext()				const { return m_pContext; }
	POINT GetScrollPos()				const { return m_ScrollPos; }
	SIZE GetScrollRange()			const { return m_ScrollRange; }
   OverlayMode GetOverlayMode()  const { return m_OverlayMode; }
   SapDataRGB GetKeyColor()      const { return m_KeyColor; }
   ScalingMode GetScalingMode()  const { return m_ScalingMode; }
   BOOL GetImmediateMode()       const { return m_bImmediateMode; }
   virtual BOOL IsAutoEmpty()    const { return m_bAutoEmpty; }
   int GetThreadPriority()       const { return m_ThreadPriority; }

	virtual BOOL SetDisplay( SapDisplay *pDisplay);
   virtual BOOL SetBuffer(SapBuffer *pBuffer);
	virtual BOOL SetWindow( HWND hWindow);
	virtual BOOL SetCallbackInfo( SapViewCallback pCallback, void *pContext= NULL);

	virtual int GetWidth();
	virtual int GetHeight();
	virtual BOOL GetViewArea( int *width, int *height);
   int GetIndex() const { return m_Index; }

	const SapViewScaleParams& GetScaleParamsDst() { return m_ScaleParamsDst;}
	const SapViewScaleParams& GetScaleParamsSrc() { return m_ScaleParamsSrc;}

   virtual BOOL IsCapabilityValid(int cap);
   virtual BOOL GetCapability(int cap, void *pValue);

   virtual BOOL IsParameterValid(int param);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   virtual BOOL SetWindowTitle(const char *title);
   virtual BOOL GetWindowTitle(char *title);
   virtual BOOL SetOverlayMode(OverlayMode overlayMode);
   virtual BOOL SetKeyColor(SapDataRGB keyColor);

   // Access to display context
   virtual BOOL GetDC(HDC *pDC);
   virtual BOOL ReleaseDC();

	// Display control
	virtual void Init();
	virtual void Show();
	virtual void Show(int index);
	virtual void ShowNext();
	virtual void Hide();
	virtual BOOL HasRange();
	virtual int GetRange();
	virtual void GetRangeMinMax(int *pRangeMin, int *pRangeMax);
	virtual BOOL SetRange(int range);
   virtual BOOL SetScalingMode(ScalingMode scalingMode, BOOL bKeepAspectRatio= FALSE, BOOL refreshNow = TRUE);
   virtual BOOL SetScalingMode(float zoomHorz, float zoomVert, BOOL refreshNow = TRUE);
   virtual BOOL SetScalingMode(const SapViewScaleParams& srcParams, const SapViewScaleParams& dstParams, BOOL refreshNow = TRUE);

	virtual void SetAutoEmpty(BOOL isAutoEmpty)	{ m_bAutoEmpty = isAutoEmpty; }
   virtual void SetImmediateMode(BOOL immediateMode) { m_bImmediateMode = immediateMode; }
	virtual void SetThreadPriority( int priority) { m_ThreadPriority= priority; if( m_hThread != NULL) ::SetThreadPriority( m_hThread, priority);}

   // Look-up table management
   SapLut *GetLut() { return m_ViewLut; }
	virtual BOOL ApplyLut();

	// Message handlers
	virtual void OnPaint();
	virtual void OnMove();
	virtual void OnSize(BOOL refreshNow = TRUE);
	virtual void OnHScroll(int hPosition);
	virtual void OnVScroll(int vPosition);

   // Obsolete methods, kept for backward compatibility
   virtual CORHANDLE *GetHandles()          const { return (CORHANDLE * const) &m_hView; }
   virtual CORHANDLE GetHandle(int index)   const { return m_hView; }
   virtual CORHANDLE operator[] (int index) const { return m_hView; }
   SapBuffer *GetBuffers()	                 const { return GetBuffer(); }
   virtual BOOL SetBuffers(SapBuffer *pBuffers) { return SetBuffer(pBuffers) ;}

protected:
   // Utility methods
   void Construct(SapDisplay *pDisplay, SapBuffer *pBuffer, HWND hWindow, SapViewCallback pCallback, void *pContext, BOOL bAutoEmpty, int threadPriority);
   virtual BOOL SetKeyColor();
	virtual void DoShow();
	virtual void Next();
	virtual void SetScrollPosAndRange();
	virtual BOOL LoadLut();
   static UINT WINAPI ViewThreadProc(LPVOID lpParam);

protected:
	// Parameters
   SapBuffer       *m_pBuffers;     // Reference to a buffer object
   SapDisplay      *m_pDisplay;     // Reference to a display object
   HWND             m_hWindow;      // Handle to a Window
   SapViewCallback  m_pCallback;    // Application callback function
   void            *m_pContext;     // Application context
   HDC              m_hDC;          // Windows GDI display context for system display
   OverlayMode      m_OverlayMode;  // Current overlay mode
   SapDataRGB       m_KeyColor;     // Current keying color

   BOOL m_bAutomaticWnd;            //TRUE if using SapHwndAutomatic

   // Look-up table management
   int m_LutEntries;
   SapFormat m_LutFormat;
   SapLut *m_ViewLut;

	// Other variables
   ScalingMode m_ScalingMode;					 // Controls how images fit in the view window
	BOOL		   m_bKeepAspectRatio;
   SapViewScaleParams m_ScaleParamsSrc;    // Source parameters for user-defined scaling mode
   SapViewScaleParams m_ScaleParamsDst;    // Destination parameters for user-defined scaling mode
	POINT	m_ScrollPos;	   // Current scrolling position
	SIZE	m_ScrollRange;	   // Current scrolling range
	int	m_Width;			   // Displayable width
	int	m_Height;		   // Displayable height
	int   m_ViewAreaWidth;	// Viewing area width
	int   m_ViewAreaHeight;	// Viewing area height
	BOOL	m_bAutoEmpty;	   // TRUE to automatically empty buffers
	BOOL  m_bDisplayFree;   // TRUE if display object is owned by the view object
   BOOL  m_bImmediateMode; // TRUE if image display does not go through a separate thread
   BOOL  m_IsDispBanditII; // TRUE if displaying on a Bandit II

	// View thread management
   int    m_Index;            // Index of the last displayed buffer
   int    m_NextIndex;        // Index of the next buffer to display
   HANDLE m_hThread;          // Thread handle
   int    m_ThreadPriority;   // Thread priority
   HANDLE m_hStartEvent;      // Signaled by the thread after it is started
   HANDLE m_hExitEvent;       // When signaled, causes the thread to exit
   HANDLE m_hViewEvent;       // Signaled when a buffer is ready to be displayed
   HANDLE m_hIdleEvent;       // Signaled by the thread when it has no work to do
   LONG   m_BuffersLeft;      // Number of buffers left to display by the thread

   // Sapera view handle
   CORVIEW m_hView;
}; 

#endif   // _SAPVIEW_H_
