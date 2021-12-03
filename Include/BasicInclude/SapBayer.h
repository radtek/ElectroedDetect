////////////////////////////////////////////////////////////////////////////////////
//                                                                            //////
// WARNING!                                                                   //////
//                                                                            //////
// THIS CLASS IS NOW OBSOLETE.                                                //////
// IT IS KEPT FOR COMPATIBILITY PURPOSES.                                     //////
//                                                                            //////
// PLEASE USE THE COLOR CONVERSION FACILITY INSTEAD.                          //////
// THAT IS, SapColorConversion Class.                                         //////
//                                                                            //////
//                                                                            //////
////////////////////////////////////////////////////////////////////////////////////


#ifndef _SAPBAYER_H_
#define _SAPBAYER_H_

// SapBayer.h: interface for the SapBayer class.
//

#include "SapClassBasicDef.h"

//
// SapBayer class declaration
//
class SAPCLASSBASIC_CLASS SapBayer : public SapManager  
{
public:
   typedef int Align;
   enum _Align
   {
      AlignGBRG = CORBAYER_ALIGN_GB_RG,
      AlignBGGR = CORBAYER_ALIGN_BG_GR,
      AlignRGGB = CORBAYER_ALIGN_RG_GB,
      AlignGRBG = CORBAYER_ALIGN_GR_BG,
      AlignAll  = CORBAYER_ALIGN_MASK
   };

   typedef int Method;
   enum _Method
   {
      Method1	= CORBAYER_METHOD_1,
      Method2	= CORBAYER_METHOD_2,
      Method3	= CORBAYER_METHOD_3,
      Method4	= CORBAYER_METHOD_4,
      Method5	= CORBAYER_METHOD_5,
      Method6	= CORBAYER_METHOD_6,

      MethodInterpolate	= CORBAYER_METHOD_1,
      MethodGoldenEagle	= CORBAYER_METHOD_2,
      MethodEagle			= CORBAYER_METHOD_3,

      MethodAll= CORBAYER_METHOD_MASK
   };

public:
   SapBayer();
   SapBayer(SapAcquisition *pAcq, SapBuffer* pBuffer);
   SapBayer(SapBuffer *pBuffer);
   SapBayer(const SapBayer &bayer);
   virtual ~SapBayer();

   SapBayer &operator= (const SapBayer &bayer);

   // Creation/destruction
   virtual BOOL Create();
   virtual BOOL Destroy();

public:
   // Access to implementation
   SapAcquisition*GetAcquisition()   const { return m_pAcq; }
   SapBuffer*     GetBuffer()        const { return m_pBuffer; }
   SapBuffer*     GetBayerBuffer()	 const;

   BOOL			IsEnabled()           const { return m_IsEnabled; }
	BOOL			IsSoftware()			 const { return !m_IsHardware || !m_IsHardwareEnabled;}
   Align			GetAlign()				 const { return m_Align; }
   Method		GetMethod()				 const { return m_Method; }
   SapDataFRGB GetWBGain()				 const { return m_WBGain; }
   SapDataFRGB GetWBOffset()			 const { return m_WBOffset; }
   float			GetGamma()				 const { return m_Gamma; }
	SapFormat	GetOutputFormat()		 const ;
   Align       GetAvailAlign()       const { return m_AlignCap; }
   Method      GetAvailMethod()      const { return m_MethodCap; }
	int			GetBayerBufferCount() const { return m_BayerBufferCount;}

   virtual BOOL SetAcquisition(SapAcquisition *pAcq);
   virtual BOOL SetBuffer(SapBuffer *pBuffer);
   virtual BOOL SetAlign(Align align);
   virtual BOOL SetMethod(Method method);
   virtual BOOL SetWBGain(SapDataFRGB wbGain);
   virtual BOOL SetWBOffset(SapDataFRGB wbOffset);
   virtual BOOL SetGamma(float gamma);
	virtual BOOL SetOutputFormat( SapFormat format);
	virtual BOOL SetBayerBufferCount( int bayerBufferCount);

   // Execution control
	virtual BOOL Enable( BOOL enable = TRUE, BOOL useHardware= TRUE);
	virtual BOOL WhiteBalance(int x, int y, int width, int height);
	virtual BOOL WhiteBalance(SapBuffer *pBuffer, int x, int y, int width, int height);
	virtual BOOL Convert();
	virtual BOOL Convert(int srcIndex);
	virtual BOOL Convert(int srcIndex, int dstIndex);

   // Look-up table management
   SapLut*		 GetLut()		 const { return m_pLut; }
   BOOL			 IsLutEnabled() const { return m_IsLutEnabled; }
   BOOL			 IsAcqLut()     const { return m_IsAcqLut; }
   virtual BOOL EnableLut(BOOL enable = TRUE);

protected:
   // Utility methods
   virtual void Construct(SapAcquisition *pAcq, SapBuffer *pBuffer);
   virtual BOOL SetAlignImmediate(Align align);
   virtual BOOL SetMethodImmediate(Method method);
   virtual BOOL SetWBGainImmediate(SapDataFRGB& wbGain);
   virtual BOOL GetWBGainLimits(SapDataFRGB *gainMin, SapDataFRGB *gainMax);
   virtual BOOL SetWBOffsetImmediate(SapDataFRGB& wbOffset);
   virtual BOOL SetGammaImmediate(float gamma);
	virtual BOOL SetAcqOutputFormat( BOOL enable, BOOL useHardware);

protected:
   SapAcquisition *m_pAcq;
   SapBuffer *m_pBuffer;
   SapBufferRoi *m_pBufferRoi;
   SapBuffer *m_pBayerBuffer;

	int		m_BayerBufferCount;

   Align m_AlignCap;
   Method m_MethodCap;
   SapDataFRGB m_GainMin;
   SapDataFRGB m_GainMax;
   float m_OffsetMin;
   float m_OffsetMax;

   BOOL m_IsEnabled;
   BOOL m_IsHardware;
	BOOL m_IsHardwareEnabled;

	SapFormat  m_colorOutputFormat;
	int        m_pixelDepth;

   Align m_Align;
   Method m_Method;
   SapDataFRGB m_WBGain;
   SapDataFRGB m_WBOffset;
   float m_Gamma;

   BOOL m_IsDefaultGain;
   BOOL m_IsDefaultOffset;

   // Look-up table management
   SapLut *m_pLut;
   BOOL m_IsLutEnabled;
   BOOL m_IsAcqLut;
};

#endif
