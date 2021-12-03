#ifndef _SAPBUFFER_H_
#define _SAPBUFFER_H_

//	SapBuffer.h : header file
//

#include "SapClassBasicDef.h"

// Forward declarations
#if !defined(POSIX_HOSTPC)
class SAPCLASSBASIC_CLASS SapDisplay;
#endif

//
// SapBuffer class declaration
//
class SAPCLASSBASIC_CLASS SapBuffer : public SapXferNode
{
public:
   // Buffer types
   typedef int Type;    // For compatibility with old Sapera++ application code
   enum _Type
   {
      TypeDefault					 = -1,
      TypeVirtual					 = CORBUFFER_VAL_TYPE_VIRTUAL,
      TypeContiguous				 = CORBUFFER_VAL_TYPE_CONTIGUOUS,
      TypeScatterGather			 = CORBUFFER_VAL_TYPE_SCATTER_GATHER,
      TypeOffscreen				 = CORBUFFER_VAL_TYPE_OFFSCREEN,
      TypeOffscreenVideo		 = CORBUFFER_VAL_TYPE_OFFSCREEN | CORBUFFER_VAL_TYPE_VIDEO,
      TypeOverlay					 = CORBUFFER_VAL_TYPE_OVERLAY | CORBUFFER_VAL_TYPE_VIDEO,
      TypeDummy					 = CORBUFFER_VAL_TYPE_DUMMY,
      TypePhysical				 = CORBUFFER_VAL_TYPE_PHYSICAL,
		TypeScatterGatherPhysical= CORBUFFER_VAL_TYPE_SCATTER_GATHER | CORBUFFER_VAL_TYPE_PHYSICAL,
      TypeUnmapped             = CORBUFFER_VAL_TYPE_UNMAPPED,
		TypeScatterGatherUnmapped= CORBUFFER_VAL_TYPE_SCATTER_GATHER | CORBUFFER_VAL_TYPE_UNMAPPED
   };

   // Buffer states
   typedef int State;
   enum _State
   {
      StateEmpty    = CORBUFFER_VAL_STATE_EMPTY,
      StateOverflow = CORBUFFER_VAL_STATE_OVERFLOW,
      StateFull     = CORBUFFER_VAL_STATE_FULL
   };

   // Color Conversion filter options
   typedef int ColorAlign;
   enum _ColorAlign
   {
      ColorAlignGBRG = CORBUFFER_VAL_COLOR_ALIGN_GB_RG,
      ColorAlignBGGR = CORBUFFER_VAL_COLOR_ALIGN_BG_GR,
      ColorAlignRGGB = CORBUFFER_VAL_COLOR_ALIGN_RG_GB,
      ColorAlignGRBG = CORBUFFER_VAL_COLOR_ALIGN_GR_BG,
      ColorAlignRGBG = CORBUFFER_VAL_COLOR_ALIGN_RG_BG,
      ColorAlignBGRG = CORBUFFER_VAL_COLOR_ALIGN_BG_RG
   };

   typedef int ColorMethod;
   enum _ColorMethod
   {
      ColorMethod1 = CORBUFFER_VAL_COLOR_METHOD_1,
      ColorMethod2 = CORBUFFER_VAL_COLOR_METHOD_2,
      ColorMethod3 = CORBUFFER_VAL_COLOR_METHOD_3,
      ColorMethod4 = CORBUFFER_VAL_COLOR_METHOD_4,
      ColorMethod5 = CORBUFFER_VAL_COLOR_METHOD_5,
      ColorMethod6 = CORBUFFER_VAL_COLOR_METHOD_6,
      ColorMethod7 = CORBUFFER_VAL_COLOR_METHOD_7
   };

   // Bayer filter options (obsolete)
   typedef int BayerAlign;
   enum _BayerAlign
   {
      BayerAlignGBRG = CORBUFFER_VAL_BAYER_ALIGN_GB_RG,
      BayerAlignBGGR = CORBUFFER_VAL_BAYER_ALIGN_BG_GR,
      BayerAlignRGGB = CORBUFFER_VAL_BAYER_ALIGN_RG_GB,
      BayerAlignGRBG = CORBUFFER_VAL_BAYER_ALIGN_GR_BG
   };

   typedef int BayerMethod;
   enum _BayerMethod
   {
      BayerMethod1 = CORBUFFER_VAL_BAYER_METHOD_1,
      BayerMethod2 = CORBUFFER_VAL_BAYER_METHOD_2,
      BayerMethod3 = CORBUFFER_VAL_BAYER_METHOD_3,
      BayerMethod4 = CORBUFFER_VAL_BAYER_METHOD_4,
      BayerMethod5 = CORBUFFER_VAL_BAYER_METHOD_5,
      BayerMethod6 = CORBUFFER_VAL_BAYER_METHOD_6,

      BayerMethodInterpolate = CORBUFFER_VAL_BAYER_METHOD_1,
      BayerMethodGoldenEagle = CORBUFFER_VAL_BAYER_METHOD_2,
      BayerMethodEagle       = CORBUFFER_VAL_BAYER_METHOD_3
   };

   typedef int FileFormat;
   enum _FileFormat
   {
      FileFormatBMP      = CORFILE_VAL_FORMAT_BMP,
      FileFormatTIFF     = CORFILE_VAL_FORMAT_TIFF,
      FileFormatCRC      = CORFILE_VAL_FORMAT_CRC,
      FileFormatRAW      = CORFILE_VAL_FORMAT_RAW,
      FileFormatJPEG     = CORFILE_VAL_FORMAT_JPEG,
      FileFormatJPEG2000 = CORFILE_VAL_FORMAT_JPEG_2000,
      FileFormatColorCorrection = CORFILE_FORMAT_COLOR_CORRECTION,
      FileFormatAVI      = CORFILE_VAL_FORMAT_AVI
   };

	typedef struct
	{
		void* virtualAddress;
		void* virtualBaseAddress;
		UINT64 offset;
		size_t size;
		int refCount;
	} LOCK_INFO, *PLOCK_INFO;

public:
	// Constructor/Destructor
	SapBuffer(int count = SapDefBufferCount, int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBuffer(int count, ULONG_PTR physAddress[], int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = TypeContiguous);
	SapBuffer(int count, void *virtAddress[], int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = TypeScatterGather);
	SapBuffer(int count, SapXferNode *pSrcNode, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
	SapBuffer(const char *fileName, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBuffer(int count, const char *bufName, int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = TypeScatterGather, SapLocation loc= SapLocation::ServerSystem);
   SapBuffer(int count, const char *bufName, SapXferNode *pSrcNode, Type type = SapDefBufferType, SapLocation loc= SapLocation::ServerSystem);
   SapBuffer(const char *bufName, int startIndex, int count, Type type = TypeVirtual, SapLocation loc= SapLocation::ServerSystem);
#if !defined(POSIX_HOSTPC)
	SapBuffer(int count, SapDisplay *pDisplay, int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = SapDefBufferType);
	SapBuffer(int count, SapDisplay *pDisplay, SapXferNode *pSrcNode, Type type = SapDefBufferType);
#endif
	SapBuffer(const SapBuffer &buf);
	virtual ~SapBuffer();

   SapBuffer &operator= (const SapBuffer &buf);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

   // SapXferNode type information
   XferNodeType GetXferNodeType() { return (m_pBufferMulti != NULL) ? NodeTypeBufferMulti : NodeTypeBuffer; }

	// Access to implementation
	int GetCount()         const { return m_Count; }
	int GetWidth()         const { return m_XferParams[0].GetWidth(); }
	int GetHeight()        const { return m_XferParams[0].GetHeight(); }
	SapFormat GetFormat()  const { return m_XferParams[0].GetFormat(); }
	Type GetType()         const { return m_Type; }
	int GetPixelDepth()    const { return m_PixelDepth; }
	int GetPixelDepthCap() const;
   int GetBytesPerPixel() const;
   int GetPitch()         const;
	void GetParameters(int *count, int *width, int *height, SapFormat *format, Type *type) const;
	const  char* GetBufName() const { return m_BufName;}

	virtual BOOL SetCount(int count);	
	virtual BOOL SetWidth(int width);		
	virtual BOOL SetHeight(int height);	
	virtual BOOL SetFormat(SapFormat format);	
	virtual BOOL SetType(Type type);		
	virtual BOOL SetPixelDepth(int pixelDepth);	
	virtual BOOL SetVirtualAddress( void* virtAddress[]);
   virtual BOOL SetPhysicalAddress(ULONG_PTR physAddress[]);
	virtual BOOL SetParameters(int count, int width, int height, SapFormat format, Type type);
	virtual BOOL SetParameters(int count, void* virtAddress[], int width, int height, SapFormat format, Type type);
   virtual BOOL SetParameters(int count, ULONG_PTR physAddress[], int width, int height, SapFormat format, Type type);
	virtual BOOL SetParametersFromFile(const char *fileName, Type type);

	float GetFrameRate() const { return m_FrameRate; }
	virtual void SetFrameRate(float frameRate) { m_FrameRate = frameRate; }

   virtual BOOL GetAddress( void **pData);
   virtual BOOL GetAddress( void* virtualBaseAddress, void **pData);

   virtual BOOL GetAddress(int index, void **pData);
   virtual BOOL GetAddress(int index, void* virtualBaseAddress, void **pData);

   virtual BOOL GetAddress(UINT64 offset, size_t size, void **pData);
   virtual BOOL GetAddress(UINT64 offset, size_t size, void* virtualBaseAddress, void **pData);

   virtual BOOL GetAddress(int index, UINT64 offset, size_t size, void **pData);
   virtual BOOL GetAddress(int index, UINT64 offset, size_t size, void* virtualBaseAddress, void **pData);

   virtual BOOL ReleaseAddress(void *pData);
   virtual BOOL ReleaseAddress(int index, void *pData= NULL);

	virtual BOOL IsMapped( int index);
	virtual BOOL IsMapped();

   virtual BOOL GetCounterStamp(int *pCounterStamp);
   virtual BOOL GetCounterStamp(int index, int *pCounterStamp);

   virtual BOOL GetHostCounterStamp(UINT64 *pCounterStamp);
   virtual BOOL GetHostCounterStamp(int index, UINT64 *pCounterStamp);

   virtual BOOL GetDeviceTimeStamp(UINT64 *pTimeStamp);
   virtual BOOL GetDeviceTimeStamp(int index, UINT64 *pTimeStamp);

   virtual BOOL GetSpaceUsed(int *pSpaceUsed);
   virtual BOOL GetSpaceUsed(int index, int *pSpaceUsed);

   virtual CORHANDLE *GetHandles()          const { return m_bInitOK ? m_pBuffers : NULL; }
	virtual CORHANDLE GetHandle(int index)	  const;
	virtual CORHANDLE GetHandle()	           const { return GetHandle(m_Index); }
	virtual CORHANDLE operator[] (int index) const { return GetHandle(index); }

	virtual int GetIndex() const { return m_Index; }
	virtual BOOL SetIndex(int index);
	virtual void ResetIndex() { m_Index = m_Count - 1; }
	virtual void Next() { m_Index = (m_Index + 1 == m_Count) ? 0 : m_Index + 1; }

   virtual BOOL IsCapabilityValid(int cap);
   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL GetCapability(int index, int cap, void *pValue);

   virtual BOOL IsParameterValid(int param);
   virtual BOOL IsParameterValid(int index, int param);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL GetParameter(int index, int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int index, int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int index, int param, void *pValue);

	// Access to derived class implementation
   virtual CORBUFFER GetTrash()   const { return CORHANDLE_NULL; }
   virtual SapBuffer *GetParent()       { return this; }
   virtual SapBuffer *GetRoot()         { return this; }

	// State manipulation
	virtual BOOL SetState(State state);
	virtual BOOL SetState(int index, State state);
	virtual BOOL SetAllState(State state);
	virtual BOOL GetState(State *pState);
	virtual BOOL GetState(int index, State *pState);

   // Page number management, relevant for planar and multi-format buffers only
   virtual BOOL GetNumPages(int *pNumPages);
   virtual BOOL SetPage(int page);
   virtual BOOL SetPage(int index, int page);
   virtual BOOL SetAllPage(int page);
   virtual BOOL GetPage(int *pPage);
   virtual BOOL GetPage(int index, int *pPage);

   // Management of multi-format buffers
   virtual BOOL IsMultiFormat();
   virtual BOOL GetPageFormat(SapFormat *pageFormat);

	// Buffer manipulation
	virtual BOOL Clear();
	virtual BOOL Clear(int index);
	virtual BOOL Clear(SapData value);
	virtual BOOL Clear(int index, SapData value);

	virtual BOOL Load(const char *fileName, int bufIndex, int numBuffers = 0, int frameIndex = 0, const char *options = "-format auto");
	virtual BOOL Save(const char *fileName, const char *options, int bufIndex = -1, int numBuffers = 0);

   virtual BOOL Read(UINT64 offset, int numElements, void *pData);
   virtual BOOL Read(int index, UINT64 offset, int numElements, void *pData);
   virtual BOOL ReadElement(int x, int y, void *pData);
   virtual BOOL ReadElement(int index, int x, int y, void *pData);
   virtual BOOL ReadElement(int x, int y, SapData *pData);
   virtual BOOL ReadElement(int index, int x, int y, SapData *pData);
   virtual BOOL ReadLine(int x1, int y1, int x2, int y2, void *pData, int *numRead);
   virtual BOOL ReadLine(int index, int x1, int y1, int x2, int y2, void *pData, int *numRead);
   virtual BOOL ReadRect(int x, int y, int width, int height, void *pData);
   virtual BOOL ReadRect(int index, int x, int y, int width, int height, void *pData);

   virtual BOOL Write(UINT64 offset, int numElements, const void *pData);
   virtual BOOL Write(int index, UINT64 offset, int numElements, const void *pData);
   virtual BOOL WriteElement(int x, int y, const void *pData);
   virtual BOOL WriteElement(int index, int x, int y, const void *pData);
   virtual BOOL WriteElement(int x, int y, SapData data);
   virtual BOOL WriteElement(int index, int x, int y, SapData data);
   virtual BOOL WriteLine(int x1, int y1, int x2, int y2, const void *pData, int *numWritten);
   virtual BOOL WriteLine(int index, int x1, int y1, int x2, int y2, const void *pData, int *numWritten);
   virtual BOOL WriteRect(int x, int y, int width, int height, const void *pData);
   virtual BOOL WriteRect(int index, int x, int y, int width, int height, const void *pData);

	virtual BOOL Copy(SapBuffer *pSrc);
	virtual BOOL Copy(SapBuffer *pSrc, int srcIndex, int dstIndex);
	virtual BOOL CopyAll(SapBuffer *pSrc);
   virtual BOOL CopyRect(SapBuffer *pSrc, int srcIndex, int xSrc, int ySrc, int width, int height, int dstIndex, int xDest, int yDest);

   virtual BOOL ColorConvert(SapBuffer *pSrc, ColorAlign align, ColorMethod method, SapDataFRGB wbCoef, SapLut *pLut = NULL);
   virtual BOOL ColorConvert(SapBuffer *pSrc, int srcIndex, int dstIndex, ColorAlign align, ColorMethod method, SapDataFRGB wbCoef, SapLut *pLut = NULL);
   virtual BOOL ColorWhiteBalance(ColorAlign align, SapDataFRGB *pWbCoef);
   virtual BOOL ColorWhiteBalance(int index, ColorAlign align, SapDataFRGB *pWbCoef);

   virtual BOOL SplitComponents(SapBuffer *pSrc);
   virtual BOOL SplitComponents(SapBuffer *pSrc, int srcIndex);
   virtual BOOL SplitComponents(SapBuffer *pFirstDst, SapBuffer *pSecondDst, SapBuffer *pThirdDst);
   virtual BOOL SplitComponents(SapBuffer *pFirstDst, SapBuffer *pSecondDst, SapBuffer *pThirdDst, int srcIndex);

   virtual BOOL MergeComponents(SapBuffer *pSrc);
   virtual BOOL MergeComponents(SapBuffer *pSrc, int dstIndex);
   virtual BOOL MergeComponents(SapBuffer *pFirstSrc, SapBuffer *pSecondSrc, SapBuffer *pThirdSrc);
   virtual BOOL MergeComponents(SapBuffer *pFirstSrc, SapBuffer *pSecondSrc, SapBuffer *pThirdSrc, int dstIndex);

	// Remote access
	virtual BOOL Register(const char *name);
	virtual BOOL Unregister();

   // Available buffer type inquiry
   static BOOL IsBufferTypeSupported(int serverIndex, Type bufType);
   static BOOL IsBufferTypeSupported(const char *serverName, Type bufType);
   static BOOL IsBufferTypeSupported(SapLocation loc, Type bufType);

	// Obsolete state manipulation methods
	virtual BOOL Empty()          { return SetState(m_Index, StateEmpty); }
	virtual BOOL Empty(int index) { return SetState(index, StateEmpty); }
	virtual BOOL EmptyAll()       { return SetAllState(StateEmpty); }

   // Obsolete methods, use class SapBufferRoi instead
	virtual int GetNumRoi() const { return 0; }
	virtual const LPRECT GetRoi(int index) const { return NULL; }
	virtual BOOL AddRoi(RECT roi) { return FALSE; }
	virtual BOOL RemoveAllRoi() { return FALSE; }
	virtual CORBUFFER GetChild(int roiIndex, int bufIndex) const { return CORHANDLE_NULL; }

   // Obsolete prototypes for these methods
	virtual BOOL Load(const char *fileName, const char *options = "-format auto", int index = -1, int numFrames = 0);
	virtual BOOL ReadElement(int x, int y, int *red, int *green, int *blue);

   // Obsolete methods, use color conversion instead
   virtual BOOL BayerConvert(SapBuffer *pSrc, BayerAlign align, BayerMethod method, SapDataFRGB wbCoef, SapLut *pLut = NULL);
   virtual BOOL BayerConvert(SapBuffer *pSrc, int srcIndex, int dstIndex, BayerAlign align, BayerMethod method, SapDataFRGB wbCoef, SapLut *pLut = NULL);
   virtual BOOL BayerWhiteBalance(BayerAlign align, SapDataFRGB *pWbCoef);
   virtual BOOL BayerWhiteBalance(int index, BayerAlign align, SapDataFRGB *pWbCoef);

protected:
   // Utility methods
#if defined(POSIX_HOSTPC)
   virtual void Construct(const char *bufName, void *pDisplay);
#else
   virtual void Construct(const char *bufName, SapDisplay *pDisplay);
#endif
   void UpdatePixelDepth(int index);
	static FileFormat GetFileFormatFromOptions(const char *options);

protected:
	// Buffer-related variables
	int m_Count;             // Number of buffers
	Type m_Type;             // Buffer type
	int m_Index;             // Index of last grabbed buffer
   BOOL m_PixelDepthCap;    // Pixel depth capability
   int m_PixelDepth;        // Number of actual data bits per pixel
   int m_DataSize;          // Number of bytes per pixel
   int m_Pitch;             // Byte offset between start addresses of consecutive lines
   int m_NumPages;          // Number of pages, relevant for planar and multi-format buffers only
   BOOL m_IsMultiFormat;    // Indicates multi-format buffers
   SapFormat *m_PageFormat; // Individual page formats for multi-format buffers 
   ULONG_PTR *m_PhysAddress;  // Physical addresses for creating buffers
   void **m_VirtAddress;    // Virtual addresses for creating buffers
   PLOCK_INFO m_LockInfo;	 // Information for locked buffers ( video, physical)
	
	CRITICAL_SECTION m_criticalSection;

	// Shared buffer related variables
   char			m_BufName[CORHANDLE_MAX_STRLEN];	// Name of the shared buffer objects
	CORBUFFER*	m_pRemoteBuffers;
	CORBUFFER	m_BufferSharedInfo;					// Buffer handle to shared buffer information
   int			m_StartIndex;

	// File-related variables
	float m_FrameRate;      // Number of frames per second

   // Display object when buffer creation is done from a display handle
#if defined(POSIX_HOSTPC)
	void *m_pDisplay; 	// No video/display based buffers.
#else
   SapDisplay *m_pDisplay;
#endif

	// Sapera handles
	CORBUFFER *m_pBuffers;					// Table of buffer handles
	CORBUFFERMULTI m_pBufferMulti;
}; 

#endif	// _SAPBUFFER_H_
