#ifndef _SAPCOLORCONVERT_H_
#define _SAPCOLORCONVERT_H_

// SapColorConversion.h: interface for the SapColorConversion class.
//

// This class can perform the following operations:
// - Apply Color Conversion on a raw Bayer Mono8/16 input buffer and get a resulting RGB888/8888 output buffer (Methods 1-5)
// - Apply Color Conversion on a raw Bi-Color88/1616 input buffer and get a resulting RGB888/8888 output buffer (Methods 6-7)
// - Apply White-Balance Gain on a RGB/Bayer/Bi-Color input buffer

#include "SapClassBasicDef.h"

// Default gain and offset values
const float SapDefWBGainMin   =      0.0f;
const float SapDefWBGainMax   =    256.0f;
const float SapDefWBOffsetMin = -65536.0f;
const float SapDefWBOffsetMax =  65536.0f;

// Gain and offset conversion factor for corresponding capability and parameter values
const float WBConversionFactor = 100000.0f;

//
// SapColorConversion class declaration
//
class SAPCLASSBASIC_CLASS SapColorConversion : public SapManager  
{
public:
   typedef int Align;
   enum _Align
   {
      AlignNone = 0,
      AlignGBRG = CORCOLORCONV_ALIGN_GB_RG,
      AlignBGGR = CORCOLORCONV_ALIGN_BG_GR,
      AlignRGGB = CORCOLORCONV_ALIGN_RG_GB,
      AlignGRBG = CORCOLORCONV_ALIGN_GR_BG,
      AlignRGBG = CORCOLORCONV_ALIGN_RGBG,
      AlignBGRG = CORCOLORCONV_ALIGN_BGRG,
      AlignAll  = CORCOLORCONV_ALIGN_MASK
   };

   typedef int Method;
   enum _Method
   {
      MethodNone = 0,
      Method1   = CORCOLORCONV_METHOD_1,
      Method2   = CORCOLORCONV_METHOD_2,
      Method3   = CORCOLORCONV_METHOD_3,
      Method4   = CORCOLORCONV_METHOD_4,
      Method5   = CORCOLORCONV_METHOD_5,
      Method6   = CORCOLORCONV_METHOD_6,
      Method7   = CORCOLORCONV_METHOD_7,
      MethodAll = CORCOLORCONV_METHOD_MASK
   };

public:
   SapColorConversion();
   SapColorConversion(SapAcquisition *pAcq, SapBuffer* pBuffer);
   SapColorConversion(SapAcqDevice *pAcqDevice, SapBuffer* pBuffer);
   SapColorConversion(SapBuffer *pBuffer);
   SapColorConversion(const SapColorConversion &colorConversion);
   virtual ~SapColorConversion();

   SapColorConversion &operator= (const SapColorConversion &colorConversion);

   virtual BOOL Create();
   virtual BOOL Destroy();

public:

   BOOL Enable(BOOL enable, BOOL useHardware);
      
   BOOL IsSoftwareSupported(bool bDisplayErrorMsg = false) const;
   BOOL IsSoftwareEnabled() const { return m_IsSoftwareEnabled; }
   BOOL IsHardwareSupported(bool bDisplayErrorMsg = false) const;
   BOOL IsHardwareEnabled() const { return m_IsHardwareEnabled; }
   BOOL IsEnabled() const { return (IsSoftwareEnabled() || IsHardwareEnabled()); };

   Align GetAvailAlign() const;
   Method GetAvailMethod() const;

   virtual BOOL SetAcquisition(SapAcquisition *pAcq);
   SapAcquisition* GetAcquisition() const { return mp_Acq; }

   virtual BOOL SetAcqDevice(SapAcqDevice *pAcqDevice);
   SapAcqDevice* GetAcqDevice() const { return mp_AcqDevice; }

   virtual BOOL SetInputBuffer(SapBuffer *pBuffer);
   SapBuffer* GetInputBuffer() const { return mp_InputBuffer; }

   BOOL IsOutputFormatSupported(SapFormat format);
   virtual BOOL SetOutputFormat(SapFormat format);
   SapFormat GetOutputFormat() const;

   virtual BOOL SetOutputBufferCount(int bufferCount);
   int GetOutputBufferCount() const { return m_OutputBufferCount; }

   SapBuffer* GetOutputBuffer() const;

   virtual BOOL SetAlign(Align align);
   Align GetAlign() const { return m_AlignPrm; }

   virtual BOOL SetMethod(Method method);
   Method GetMethod() const { return m_MethodPrm; }

   virtual BOOL SetWBGain(SapDataFRGB wbGain);
   SapDataFRGB GetWBGain() const { return m_WBGain; }

   virtual BOOL SetWBOffset(SapDataFRGB wbOffset);
   SapDataFRGB GetWBOffset() const { return m_WBOffset; }

   virtual BOOL SetGamma(float gamma);
   float GetGamma() const { return m_Gamma; }
	
   // Execution control
	virtual BOOL Convert();
	virtual BOOL Convert(int srcIndex);
	virtual BOOL Convert(int srcIndex, int dstIndex);
   virtual BOOL WhiteBalance(int x, int y, int width, int height);
	virtual BOOL WhiteBalance(SapBuffer *pBuffer, int x, int y, int width, int height);
   virtual BOOL WhiteBalanceManual(const SapDataFRGB& wbGain);

   // Look-up table management
   SapLut* GetLut() const { return mp_Lut; }
   BOOL IsLutEnabled() const { return m_IsLutEnabled; }
   BOOL IsAcqLut() const { return m_IsAcqLut; }
   virtual BOOL EnableLut(BOOL enable = TRUE);

   // helper functions
   static SapColorConversion::Align GetAlignModeFromAcqDevice(SapAcqDevice* pAcqDevice);

protected:
   // Utility methods
   virtual void Construct(SapAcquisition *pAcq, SapBuffer *pBuffer);
   virtual BOOL _ReCreateOutputBuffer();
   virtual void DestroyLut();

   BOOL SetSoftwareEnable();
   virtual BOOL _SetSoftwareEnable();
   BOOL SetHardwareEnable();
   virtual BOOL _SetHardwareEnable();

   void Disable();

   virtual BOOL SetAlignImmediate(Align align);
   virtual BOOL SetMethodImmediate(Method method);

   virtual BOOL SetWBGainImmediate(SapDataFRGB& wbGain);

   virtual BOOL GetWBGainLimits(SapDataFRGB *gainMin, SapDataFRGB *gainMax);
   virtual BOOL ApplyWBGainLimits(SapDataFRGB& wbGain, bool bMessage = true);

   virtual BOOL SetWBOffsetImmediate(SapDataFRGB& wbOffset);
   virtual BOOL SetGammaImmediate(float gamma);
	virtual BOOL SetAcqOutputFormat();
   virtual SapFormat GetOutputFormat(int pixelDepth) const;

protected:
   /* resources */
   SapAcquisition *mp_Acq;
   SapAcqDevice *mp_AcqDevice;
   SapBuffer *mp_InputBuffer;
   SapBuffer *mp_OutputBuffer;
   SapBufferRoi *mp_BufferRoi;
	int m_OutputBufferCount;

   /* current state */
   BOOL m_IsSoftwareEnabled;        // 'true' if color conversion is done in SW; 'false' otherwise
   BOOL m_IsHardwareEnabled;        // 'true' if color conversion is done in HW; 'false' otherwise
   BOOL m_IsColorConvHWCapable;     // 'true' if the device has color decoding embedded; 'false' otherwise
   BOOL m_IsWhiteBalanceHWCapable;  // 'true' if the device has white-balance processing embedded; 'false' otherwise

   /* internal data */
   Align m_AlignCap;
   Align m_AlignPrm;
   Method m_MethodCap;
   Method m_MethodPrm;
   SapDataFRGB m_GainMin;
   SapDataFRGB m_GainMax;
   float m_OffsetMin;
   float m_OffsetMax;
	SapFormat m_ColorOutputFormat;
	int m_PixelDepth;
   bool m_bIsOriginalGainValid;
   SapDataFRGB m_WBOriginalGain;
   SapDataFRGB m_WBGain;
   bool m_bIsOriginalOffsetValid;
   SapDataFRGB m_WBOriginalOffset;
   SapDataFRGB m_WBOffset;
   float m_Gamma;
   SapLut *mp_Lut;
   BOOL m_IsLutEnabled;
   BOOL m_IsAcqLut;

};

#endif
