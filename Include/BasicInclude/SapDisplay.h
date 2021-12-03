#ifndef _SAPDISPLAY_H_
#define _SAPDISPLAY_H_

//	SapDisplay.h : header file
//

#include "SapClassBasicDef.h"

//
// SapDisplay class declaration
//

class SAPCLASSBASIC_CLASS SapDisplay : public SapManager
{
public:
   // Display types
   typedef int Type;    // For compatibility with old Sapera++ application code
   enum _Type
   {
      TypeUnknown     = 0,
      TypeSystem      = CORDISPLAY_VAL_TYPE_SYSTEM,
      TypeDuplicate   = CORDISPLAY_VAL_TYPE_DUPLICATE,
      TypeExtended    = CORDISPLAY_VAL_TYPE_EXTENDED,
      TypeIndependent = CORDISPLAY_VAL_TYPE_INDEPENDENT
   };

   // Various constants
   enum MiscValues
   {
      MaxFormats = 32
   };

public:
	// Constructor/Destructor
	SapDisplay(SapLocation loc = SapLocation::ServerSystem);
	SapDisplay(const SapDisplay &disp);
	virtual ~SapDisplay();

	SapDisplay &operator=(const SapDisplay &disp);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
	CORHANDLE GetHandle()     const { return m_hDisplay;}
	SapLocation GetLocation() const { return m_Location;}

	int GetWidth()			const { return m_Width; }
	int GetHeight()		const { return m_Height; }
   int GetPixelDepth()	const { return m_PixelDepth; }
   int GetRefreshRate()	const { return m_Refresh; }
   BOOL IsInterlaced()	const { return m_Interlaced ? TRUE : FALSE; }
   Type GetType()       const { return m_Type; }
   BOOL GetFormatDetection() const { return m_FormatDetection; }

	BOOL SetLocation(SapLocation location);
   virtual BOOL SetFormatDetection(BOOL formatDetection);

   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   virtual BOOL IsCapabilityValid(int cap);
   virtual BOOL IsParameterValid(int param);

   virtual BOOL IsPrimaryVGABoard();
   virtual BOOL IsOffscreenAvailable(SapFormat format);
   virtual BOOL IsOverlayAvailable(SapFormat format);

   // Access to display context
   virtual BOOL GetDC(HDC *pDC);
   virtual BOOL ReleaseDC();

   // Utility methods
	int IncRef() { m_nRef++; return m_nRef;}
	int DecRef() { if (m_nRef > 0) m_nRef--; return m_nRef;}

   // Obsolete methods
   BOOL IsSystem()      const { return m_Type == TypeSystem; }
   BOOL IsIndependent() const { return m_Type == TypeIndependent; }

#if !COR_WIN64
   // Programmable display support
   virtual BOOL SetMode(int width, int height, SapFormat format, int refresh);
#endif

protected:
   // Utility methods
   void Construct(SapLocation loc);

protected:
   SapLocation m_Location;
   CORDISPLAY m_hDisplay;
   int m_nRef;          // Number of views attached to the object

	// Parameters
   int m_Width;         // Displayable width
   int m_Height;        // Displayable height
   int m_PixelDepth;    // Number of bits per pixel
   int m_Refresh;       // Refresh rate in Hz
   int m_Interlaced;    // Non-zero if current display mode is interlaced
   Type m_Type;         // Display type
   BOOL m_FormatDetection; // Enable or disable detection of available offscreen and overlay formats

   // Available offscreen and overlay display formats
   int m_OffscreenFormats[MaxFormats];
   int m_OverlayFormats[MaxFormats];
}; 

#endif	// _SAPDISPLAY_H_
