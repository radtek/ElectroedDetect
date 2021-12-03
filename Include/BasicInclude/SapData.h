#ifndef _SAPDATA_H_
#define _SAPDATA_H_

// SapData.h : header file
//

#include "SapClassBasicDef.h"


//
// Basic definitions available to all classes
//

// Sapera data formats
typedef int SapFormat;     // For compatibility with old Sapera++ application code
enum _SapFormat
{
   SapFormatUnknown = 0,

   // Monochrome data formats
   SapFormatMono8  = CORDATA_FORMAT_MONO8,
   SapFormatInt8   = CORDATA_FORMAT_INT8,
   SapFormatUint8  = CORDATA_FORMAT_UINT8,
   SapFormatMono16 = CORDATA_FORMAT_MONO16,
   SapFormatInt16  = CORDATA_FORMAT_INT16,
   SapFormatUint16 = CORDATA_FORMAT_UINT16,
   SapFormatMono24 = CORDATA_FORMAT_MONO24,
   SapFormatInt24  = CORDATA_FORMAT_INT24,
   SapFormatUint24 = CORDATA_FORMAT_UINT24,
   SapFormatMono32 = CORDATA_FORMAT_MONO32,
   SapFormatInt32  = CORDATA_FORMAT_INT32,
   SapFormatUint32 = CORDATA_FORMAT_UINT32,
   SapFormatMono64 = CORDATA_FORMAT_MONO64,
   SapFormatInt64  = CORDATA_FORMAT_INT64,
   SapFormatUint64 = CORDATA_FORMAT_UINT64,

   // Color RGB data formats
   SapFormatRGB5551   = CORDATA_FORMAT_RGB5551,    // 16-bit
   SapFormatRGB565    = CORDATA_FORMAT_RGB565,     // 16-bit
   SapFormatRGB888    = CORDATA_FORMAT_RGB888,     // 24-bit
   SapFormatRGBR888   = CORDATA_FORMAT_RGBR888,    // 24-bit
   SapFormatRGB8888   = CORDATA_FORMAT_RGB8888,    // 32-bit
   SapFormatRGB101010 = CORDATA_FORMAT_RGB101010,  // 32-bit
   SapFormatRGB161616 = CORDATA_FORMAT_RGB161616,  // 48-bit
   SapFormatRGB16161616 = CORDATA_FORMAT_RGB16161616,  // 64-bit

   // Bi-color data formats
   SapFormatBICOLOR88   = CORDATA_FORMAT_BICOLOR88,
   SapFormatBICOLOR1616 = CORDATA_FORMAT_BICOLOR1616,

   // Multispectral RGB-IR formats
   SapFormatRGB888_MONO8     = CORDATA_FORMAT_RGB888_MONO8,
   SapFormatRGB161616_MONO16 = CORDATA_FORMAT_RGB161616_MONO16,

   // Planar monochrome formats
   SapFormatMono8P2  = CORDATA_FORMAT_MONO8P2,
   SapFormatMono8P3  = CORDATA_FORMAT_MONO8P3,
   SapFormatMono16P2 = CORDATA_FORMAT_MONO16P2,
   SapFormatMono16P3 = CORDATA_FORMAT_MONO16P3,

   // Color HSV data formats
   SapFormatHSV   = CORDATA_FORMAT_HSV,

   // Color YUV data formats
   SapFormatUYVY = CORDATA_FORMAT_UYVY,
   SapFormatYUY2 = CORDATA_FORMAT_YUY2,
   SapFormatYVYU = CORDATA_FORMAT_YVYU,
   SapFormatYUYV = CORDATA_FORMAT_YUYV,
   SapFormatY411 = CORDATA_FORMAT_Y411,   // 4:1:1 also known as Y41P
   SapFormatY211 = CORDATA_FORMAT_Y211,   // 2:1:1
   SapFormatYUV  = CORDATA_FORMAT_YUV,
	SapFormatAYU2 = CORDATA_FORMAT_AYUV,
	SapFormatIYU1 = CORDATA_FORMAT_IYU1,
	SapFormatIYU2 = CORDATA_FORMAT_IYU2,

   // Other data formats
   SapFormatFloat   = CORDATA_FORMAT_FLOAT,
   SapFormatComplex = CORDATA_FORMAT_COMPLEX,   // Real and imaginary components
   SapFormatPoint   = CORDATA_FORMAT_POINT,     // X and Y integer components
   SapFormatFPoint  = CORDATA_FORMAT_FPOINT,    // Like Fpoint, but components are float instead of integer

   SapFormatMono1  = CORDATA_FORMAT_MONO1,      // 1-bit monochrome
   SapFormatUint1  = CORDATA_FORMAT_UINT1,
   SapFormatBinary = CORDATA_FORMAT_BINARY,
   SapFormatHSI    = CORDATA_FORMAT_HSI,
   SapFormatLAB    = CORDATA_FORMAT_LAB,
	SapFormatLAB16161616 = CORDATA_FORMAT_LAB16161616,
	SapFormatLAB101010 = CORDATA_FORMAT_LAB101010,

   // Planar formats
   SapFormatRGBP8  = CORDATA_FORMAT_RGBP8,      // 8-bit RGB
   SapFormatRGBP16 = CORDATA_FORMAT_RGBP16,     // 16-bit RGB
   SapFormatYUVP8  = CORDATA_FORMAT_YUVP8,      // 8-bit YUV
   SapFormatYUVP16 = CORDATA_FORMAT_YUVP16,     // 16-bit YUV
   SapFormatHSVP8  = CORDATA_FORMAT_HSVP8,      // 8-bit HSV
   SapFormatHSVP16 = CORDATA_FORMAT_HSVP16,     // 16-bit HSV
   SapFormatHSIP8 = CORDATA_FORMAT_HSIP8,       // 8-bit HSI
   SapFormatHSIP16 = CORDATA_FORMAT_HSIP16,     // 16-bit HSI
   SapFormatLABP8  = CORDATA_FORMAT_LABP8,      // 8-bit LAB
   SapFormatLABP16 = CORDATA_FORMAT_LABP16,     // 16-bit LAB

   // Additional monochrome data formats used by look-up tables
   SapFormatMono9  = CORDATA_FORMAT_MONO9,
   SapFormatMono10 = CORDATA_FORMAT_MONO10,
   SapFormatMono11 = CORDATA_FORMAT_MONO11,
   SapFormatMono12 = CORDATA_FORMAT_MONO12,
   SapFormatMono13 = CORDATA_FORMAT_MONO13,
   SapFormatMono14 = CORDATA_FORMAT_MONO14,
   SapFormatMono15 = CORDATA_FORMAT_MONO15,

   SapFormatUint9  = CORDATA_FORMAT_UINT9,
   SapFormatUint10 = CORDATA_FORMAT_UINT10,
   SapFormatUint11 = CORDATA_FORMAT_UINT11,
   SapFormatUint12 = CORDATA_FORMAT_UINT12,
   SapFormatUint13 = CORDATA_FORMAT_UINT13,
   SapFormatUint14 = CORDATA_FORMAT_UINT14,
   SapFormatUint15 = CORDATA_FORMAT_UINT15,

   SapFormatInt9   = CORDATA_FORMAT_INT9,
   SapFormatInt10  = CORDATA_FORMAT_INT10,
   SapFormatInt11  = CORDATA_FORMAT_INT11,
   SapFormatInt12  = CORDATA_FORMAT_INT12,
   SapFormatInt13  = CORDATA_FORMAT_INT13,
   SapFormatInt14  = CORDATA_FORMAT_INT14,
   SapFormatInt15  = CORDATA_FORMAT_INT15,

   // Interlaced color data formats used by look-up tables, data stored as:
   //    RGBRGBRGB ...
   SapFormatColorI8  = CORDATA_FORMAT_COLORI8,
   SapFormatColorI9  = CORDATA_FORMAT_COLORI9,
   SapFormatColorI10 = CORDATA_FORMAT_COLORI10,
   SapFormatColorI11 = CORDATA_FORMAT_COLORI11,
   SapFormatColorI12 = CORDATA_FORMAT_COLORI12,
   SapFormatColorI13 = CORDATA_FORMAT_COLORI13,
   SapFormatColorI14 = CORDATA_FORMAT_COLORI14,
   SapFormatColorI15 = CORDATA_FORMAT_COLORI15,
   SapFormatColorI16 = CORDATA_FORMAT_COLORI16,

   // Non-interlaced color data formats used by look-up tables, data stored as:
   //    RRRRRR ... GGGGGG ... BBBBBB
   SapFormatColorNI8  = CORDATA_FORMAT_COLORNI8,
   SapFormatColorNI9  = CORDATA_FORMAT_COLORNI9,
   SapFormatColorNI10 = CORDATA_FORMAT_COLORNI10,
   SapFormatColorNI11 = CORDATA_FORMAT_COLORNI11,
   SapFormatColorNI12 = CORDATA_FORMAT_COLORNI12,
   SapFormatColorNI13 = CORDATA_FORMAT_COLORNI13,
   SapFormatColorNI14 = CORDATA_FORMAT_COLORNI14,
   SapFormatColorNI15 = CORDATA_FORMAT_COLORNI15,
   SapFormatColorNI16 = CORDATA_FORMAT_COLORNI16 
};

// Format categories
enum SapFormatType
{
   SapFormatTypeUnknown,
   SapFormatTypeMono,
   SapFormatTypeRGB,
   SapFormatTypeYUV,
   SapFormatTypeHSI,
   SapFormatTypeHSV,
   SapFormatTypeFloat,
   SapFormatTypeComplex,
   SapFormatTypePoint,
   SapFormatTypeFPoint,
   SapFormatTypeFRGB,
   SapFormatTypeColor,
   SapFormatTypeRGBA,
   SapFormatTypeLAB,
   SapFormatTypeLABA,
   SapFormatTypeBiColor,
};

// Default values for parameters used in various classes
const int SapDefWidth         = 640;
const int SapDefHeight        = 480;
const SapFormat SapDefFormat  = SapFormatMono8;
const int SapDefPixelDepth    = 8;
const int SapDefPixelShift    = 0;
const int SapDefBufferCount   = 1;
const int SapDefLutEntries    = (1 << CORDATA_FORMAT_DATADEPTH(SapFormatUint8));

#define SapDefBufferType   SapBuffer::TypeDefault
#define SapDefFrameType    SapXferParams::FrameInterlaced
#define SapDefFieldOrder   SapXferParams::FieldOrderOddEven

//
// SapData class declaration
//

class SAPCLASSBASIC_CLASS SapData
{
public:
   // Constructor
   SapData()
      { m_Type = SapFormatTypeUnknown; Clear(); }
   virtual ~SapData() {}

   virtual void Clear() { memset(&m_Data, 0, sizeof(m_Data)); }

	// Access to implementation
   CORDATA GetData()       const { return m_Data; }
   SapFormatType GetType() const { return m_Type; }

   void SetData(CORDATA data) { m_Data = data; }

protected:
   CORDATA m_Data;
   SapFormatType m_Type;
};


//
// Derived classes declarations
//

class SAPCLASSBASIC_CLASS SapDataMono : public SapData
{
public:
   // Constructors
   SapDataMono()
      { m_Type = SapFormatTypeMono; }
   SapDataMono(int mono)
      { m_Type = SapFormatTypeMono; m_Data.mono = mono; }
   SapDataMono(const SapData &data)
      { m_Type = SapFormatTypeMono; m_Data = data.GetData(); }

   SapDataMono &operator=(const SapData &data) { m_Type = SapFormatTypeMono; m_Data = data.GetData(); return *this; }

   // Data access methods
   int Mono() { return m_Data.mono; }

   void Set(int mono) { m_Data.mono = mono; }
};

class SAPCLASSBASIC_CLASS SapDataRGBA : public SapData
{
public:
   // Constructors
   SapDataRGBA()
      { m_Type = SapFormatTypeRGBA; }
   SapDataRGBA(int red, int green, int blue, int alpha)
      { m_Type = SapFormatTypeRGBA; m_Data.rgba.red = (UINT16)red; m_Data.rgba.green = (UINT16)green; m_Data.rgba.blue = (UINT16)blue; m_Data.rgba.alpha = (UINT16)alpha;}
   SapDataRGBA(const SapData &data)
      { m_Type = SapFormatTypeRGBA; m_Data = data.GetData(); }

   SapDataRGBA &operator=(const SapData &data) { m_Type = SapFormatTypeRGBA; m_Data = data.GetData(); return *this; }

   // Data access methods
   int Red()   { return m_Data.rgba.red; }
   int Green() { return m_Data.rgba.green; }
   int Blue()  { return m_Data.rgba.blue; }
   int Alpha()  { return m_Data.rgba.alpha; }

   void Set(int red, int green, int blue, int alpha) { m_Data.rgba.red = (UINT16)red; m_Data.rgba.green = (UINT16)green; m_Data.rgba.blue = (UINT16)blue; m_Data.rgba.alpha = (UINT16)alpha;}
};

class SAPCLASSBASIC_CLASS SapDataRGB : public SapData
{
public:
   // Constructors
   SapDataRGB()
      { m_Type = SapFormatTypeRGB; }
   SapDataRGB(int red, int green, int blue)
      { m_Type = SapFormatTypeRGB; m_Data.rgb.red = red; m_Data.rgb.green = green; m_Data.rgb.blue = blue; }
   SapDataRGB(const SapData &data)
      { m_Type = SapFormatTypeRGB; m_Data = data.GetData(); }

   SapDataRGB &operator=(const SapData &data) { m_Type = SapFormatTypeRGB; m_Data = data.GetData(); return *this; }

   // Data access methods
   int Red()   { return m_Data.rgb.red; }
   int Green() { return m_Data.rgb.green; }
   int Blue()  { return m_Data.rgb.blue; }

   void Set(int red, int green, int blue) { m_Data.rgb.red = red; m_Data.rgb.green = green; m_Data.rgb.blue = blue; }
};

class SAPCLASSBASIC_CLASS SapDataYUV : public SapData
{
public:
   // Constructors
   SapDataYUV()
      { m_Type = SapFormatTypeYUV; }
   SapDataYUV(int y, int u, int v)
      { m_Type = SapFormatTypeYUV; m_Data.yuv.y = y; m_Data.yuv.u = u; m_Data.yuv.v = v; }
   SapDataYUV(const SapData &data)
      { m_Type = SapFormatTypeYUV; m_Data = data.GetData(); }

   // Data access methods
   int Y() { return m_Data.yuv.y; }
   int U() { return m_Data.yuv.u; }
   int V() { return m_Data.yuv.v; }

   void Clear() { SapData::Clear(); m_Data.yuv.u = 0x80; m_Data.yuv.v = 0x80; }
   void Set(int y, int u, int v) { m_Data.yuv.y = y; m_Data.yuv.u = u; m_Data.yuv.v = v; }
};

class SAPCLASSBASIC_CLASS SapDataHSI : public SapData
{
public:
   // Constructors
   SapDataHSI()
      { m_Type = SapFormatTypeHSI; }
   SapDataHSI(int h, int s, int i)
      { m_Type = SapFormatTypeHSI; m_Data.hsi.h = h; m_Data.hsi.s = s; m_Data.hsi.i = i; }
   SapDataHSI(const SapData &data)
      { m_Type = SapFormatTypeHSI; m_Data = data.GetData(); }

   // Data access methods
   int H() { return m_Data.hsi.h; }
   int S() { return m_Data.hsi.s; }
   int I() { return m_Data.hsi.i; }

   void Set(int h, int s, int i) { m_Data.hsi.h = h; m_Data.hsi.s = s; m_Data.hsi.i = i; }
};

class SAPCLASSBASIC_CLASS SapDataLAB : public SapData
{
public:
   // Constructors
   SapDataLAB()
      { m_Type = SapFormatTypeLAB; }
   SapDataLAB(int l, int a, int b)
      { m_Type = SapFormatTypeLAB; m_Data.lab.l = l; m_Data.lab.a = a; m_Data.lab.b = b; }
   SapDataLAB(const SapData &data)
      { m_Type = SapFormatTypeLAB; m_Data = data.GetData(); }

   // Data access methods
   int L() { return m_Data.lab.l; }
   int A() { return m_Data.lab.a; }
   int B() { return m_Data.lab.b; }

   void Set(int l, int a, int b) { m_Data.lab.l = l; m_Data.lab.a = a; m_Data.lab.b = b; }
};

class SAPCLASSBASIC_CLASS SapDataLABA : public SapData
{
public:
   // Constructors
   SapDataLABA()
      { m_Type = SapFormatTypeLABA; }
   SapDataLABA(int l, int a, int b, int alpha)
      { m_Type = SapFormatTypeLABA; m_Data.laba.l = (UINT16)l; m_Data.laba.a = (UINT16)a; m_Data.laba.b = (UINT16)b; m_Data.laba.alpha = (UINT16)alpha; }
   SapDataLABA(const SapData &data)
      { m_Type = SapFormatTypeLABA; m_Data = data.GetData(); }

   // Data access methods
   int L() { return m_Data.laba.l; }
   int A() { return m_Data.laba.a; }
   int B() { return m_Data.laba.b; }
   int Alpha() { return m_Data.laba.alpha; }

   void Set(int l, int a, int b, int alpha) { m_Data.laba.l = (UINT16)l; m_Data.laba.a = (UINT16)a; m_Data.laba.b = (UINT16)b; m_Data.laba.alpha = (UINT16)alpha; }
};

class SAPCLASSBASIC_CLASS SapDataHSV : public SapData
{
public:
   // Constructors
   SapDataHSV()
      { m_Type = SapFormatTypeHSV; }
   SapDataHSV(int h, int s, int v)
      { m_Type = SapFormatTypeHSV; m_Data.hsv.h = h; m_Data.hsv.s = s; m_Data.hsv.v = v; }
   SapDataHSV(const SapData &data)
      { m_Type = SapFormatTypeHSV; m_Data = data.GetData(); }

   // Data access methods
   int H() { return m_Data.hsv.h; }
   int S() { return m_Data.hsv.s; }
   int V() { return m_Data.hsv.v; }

   void Set(int h, int s, int v) { m_Data.hsv.h = h; m_Data.hsv.s = s; m_Data.hsv.v = v; }
};

class SAPCLASSBASIC_CLASS SapDataFloat : public SapData
{
public:
   // Constructors
   SapDataFloat()
      { m_Type = SapFormatTypeFloat; }
   SapDataFloat(float flt)
      { m_Type = SapFormatTypeFloat; m_Data.flt = flt; }
   SapDataFloat(const SapData &data)
      { m_Type = SapFormatTypeFloat; m_Data = data.GetData(); }

   // Data access methods
   float Float() { return m_Data.flt; }

   void Clear() { SapData::Clear(); m_Data.flt = 0.0; }
   void Set(float flt) { m_Data.flt = flt; }
};

class SAPCLASSBASIC_CLASS SapDataPoint : public SapData
{
public:
   // Constructors
   SapDataPoint()
      { m_Type = SapFormatTypePoint; }
   SapDataPoint(int x, int y)
      { m_Type = SapFormatTypePoint; m_Data.point.x = x; m_Data.point.y = y; }
   SapDataPoint(const SapData &data)
      { m_Type = SapFormatTypePoint; m_Data = data.GetData(); }

   // Data access methods
   int X() { return m_Data.point.x; }
   int Y() { return m_Data.point.y; }

   void Set(int x, int y) { m_Data.point.x = x; m_Data.point.y = y; }
};

class SAPCLASSBASIC_CLASS SapDataFPoint : public SapData
{
public:
   // Constructors
   SapDataFPoint()
      { m_Type = SapFormatTypeFPoint; }
   SapDataFPoint(float x, float y)
      { m_Type = SapFormatTypeFPoint; m_Data.fpoint.x = x; m_Data.fpoint.y = y; }
   SapDataFPoint(const SapData &data)
      { m_Type = SapFormatTypeFPoint; m_Data = data.GetData(); }

   // Data access methods
   float X() { return m_Data.fpoint.x; }
   float Y() { return m_Data.fpoint.y; }

   void Clear() { SapData::Clear(); m_Data.fpoint.x = 0.0; m_Data.fpoint.y = 0.0; }
   void Set(float x, float y) { m_Data.fpoint.x = x; m_Data.fpoint.y = y; }
};

class SAPCLASSBASIC_CLASS SapDataFRGB : public SapData
{
public:
   // Constructors
   SapDataFRGB()
      { m_Type = SapFormatTypeFRGB; }
   SapDataFRGB(float red, float green, float blue)
      { m_Type = SapFormatTypeFRGB; m_Data.frgb.red = red; m_Data.frgb.green = green; m_Data.frgb.blue = blue; }
   SapDataFRGB(const SapData &data)
      { m_Type = SapFormatTypeFRGB; m_Data = data.GetData(); }

   // Data access methods
   float Red()   { return m_Data.frgb.red; }
   float Green() { return m_Data.frgb.green; }
   float Blue()  { return m_Data.frgb.blue; }

   void Clear() { SapData::Clear(); m_Data.frgb.red = 0.0; m_Data.frgb.green = 0.0; m_Data.frgb.blue = 0.0; }
   void Set(float red, float green, float blue) { m_Data.frgb.red = red; m_Data.frgb.green = green; m_Data.frgb.blue = blue; }
};

#endif   // _SAPDATA_H_
