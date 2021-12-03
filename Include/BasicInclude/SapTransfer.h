#ifndef _SAPTRANSFER_H_
#define _SAPTRANSFER_H_

//	SapTransfer.h : header file
//

#include "SapClassBasicDef.h"
#include "SapPerformance.h"
#include <cfloat>

// Forward declarations
class SAPCLASSBASIC_CLASS SapXferContextInfo;
class SAPCLASSBASIC_CLASS SapTransfer;
class SAPCLASSBASIC_CLASS SapXferCallbackInfo;
#if !SAPERA_DOT_NET
class SAPCLASSBASIC_CLASS SapXferMultiNode;
#endif

typedef void(*SapXferCallback)(SapXferCallbackInfo *);

//
// SapXferPair class declaration
//
class SAPCLASSBASIC_CLASS SapXferPair
{
public:
   // Transfer event types
   typedef int EventType;     // For compatibility with old Sapera++ application code
   enum _EventType
   {
      EventNone = 0,
      EventStartOfField = CORXFER_VAL_EVENT_TYPE_START_OF_FIELD,
      EventStartOfOdd = CORXFER_VAL_EVENT_TYPE_START_OF_ODD,
      EventStartOfEven = CORXFER_VAL_EVENT_TYPE_START_OF_EVEN,
      EventStartOfFrame = CORXFER_VAL_EVENT_TYPE_START_OF_FRAME,
      EventEndOfField = CORXFER_VAL_EVENT_TYPE_END_OF_FIELD,
      EventEndOfOdd = CORXFER_VAL_EVENT_TYPE_END_OF_ODD,
      EventEndOfEven = CORXFER_VAL_EVENT_TYPE_END_OF_EVEN,
      EventEndOfFrame = CORXFER_VAL_EVENT_TYPE_END_OF_FRAME,
      EventEndOfLine = CORXFER_VAL_EVENT_TYPE_END_OF_LINE,
      EventEndOfNLines = CORXFER_VAL_EVENT_TYPE_END_OF_NLINES,
      EventEndOfTransfer = CORXFER_VAL_EVENT_TYPE_END_OF_TRANSFER,
      EventLineUnderrun = CORXFER_VAL_EVENT_TYPE_LINE_UNDERRUN,
      EventFieldUnderrun = CORXFER_VAL_EVENT_TYPE_FIELD_UNDERRUN,
      EventMask = CORXFER_VAL_EVENT_TYPE_MASK
   };

   // Transfer cycle modes
   typedef int CycleMode;
   enum _CycleMode
   {
      CycleUnknown = -1,
      CycleAsynchronous = CORXFER_VAL_CYCLE_MODE_ASYNCHRONOUS,
      CycleSynchronous = CORXFER_VAL_CYCLE_MODE_SYNCHRONOUS,
      CycleWithTrash = CORXFER_VAL_CYCLE_MODE_SYNCHRONOUS_WITH_TRASH,
      CycleOff = CORXFER_VAL_CYCLE_MODE_OFF,
      CycleNextEmpty = CORXFER_VAL_CYCLE_MODE_NEXT_EMPTY,
      CycleNextWithTrash = CORXFER_VAL_CYCLE_MODE_SYNCHRONOUS_NEXT_EMPTY_WITH_TRASH
   };

   //Xfer element
   typedef int XferElement;
   enum _XferElement
   {
      ElementPair = CORXFER_VAL_ELEMENT_PAIR,
      ElementGroup = CORXFER_VAL_ELEMENT_GROUP
   };

   // Flipping modes
   typedef int FlipMode;
   enum _FlipMode
   {
      FlipNone = CORXFER_VAL_FLIP_OFF,
      FlipHorizontal = CORXFER_VAL_FLIP_HORZ,
      FlipVertical = CORXFER_VAL_FLIP_VERT
   };

   // Event count source
   typedef int EventCountSource;
   enum _EventCountSource
   {
      EventCountNone = CORXFER_VAL_EVENT_COUNT_SOURCE_NONE,
      EventCountDst = CORXFER_VAL_EVENT_COUNT_SOURCE_DST,
      EventCountSrc = CORXFER_VAL_EVENT_COUNT_SOURCE_SRC
   };

   // Counter stamp time base
   typedef int CounterStampTimeBase;
   enum _CounterStampTimeBase
   {
      CounterStampMicroSec = CORXFER_VAL_TIME_BASE_US,
      CounterStampMilliSec = CORXFER_VAL_TIME_BASE_MS,
      CounterStampLine = CORXFER_VAL_TIME_BASE_LINE,
      CounterStampLineTrigger = CORXFER_VAL_TIME_BASE_LINE_TRIGGER,
      CounterStampFrame = CORXFER_VAL_TIME_BASE_FRAME,
      CounterStampExtFrameTrigger = CORXFER_VAL_TIME_BASE_EXT_FRAME_TRIGGER,
      CounterStampShaftEncoder = CORXFER_VAL_TIME_BASE_SHAFT_ENCODER
   };

   // Flat-field correction cycle modes
   typedef int FlatFieldCycleMode;
   enum _FlatFieldCycleMode
   {
      FlatFieldCycleOff = CORXFER_VAL_FLATFIELD_CYCLE_MODE_OFF,
      FlatFieldCycleAutomatic = CORXFER_VAL_FLATFIELD_CYCLE_MODE_AUTOMATIC,
   };

   // Dynamic LUT cycle modes
   typedef int DynamicLutCycleMode;
   enum _DynamicLutCycleMode
   {
      DynamicLutCycleOff = CORXFER_VAL_DYNAMIC_LUT_CYCLE_MODE_OFF,
      DynamicLutCycleAutomatic = CORXFER_VAL_DYNAMIC_LUT_CYCLE_MODE_AUTOMATIC,
      DynamicLutCycleManual = CORXFER_VAL_DYNAMIC_LUT_CYCLE_MODE_MANUAL,
   };

   // Various constants
   enum MiscValues
   {
      InvalidFramesOnBoard = -1
   };

public:
   SapXferPair()
      { Construct(NULL, 0, NULL, 0, FALSE); }

   SapXferPair(SapXferNode *pSrc, SapXferNode *pDst, BOOL regCallback = TRUE)
      { Construct(pSrc, 0, pDst, 0, regCallback); }

   SapXferPair(SapXferNode *pSrc, int srcPort, SapXferNode *pDst, int dstPort, BOOL regCallback = TRUE)
      { Construct(pSrc, srcPort, pDst, dstPort, regCallback); }

   ~SapXferPair() {}

   SapXferNode *GetSrc() const { return m_pSrc; }
   int GetSrcPort()      const { return m_SrcPort; }
   int GetSrcIndex()     const { return m_SrcPort; }
   SapXferNode *GetDst() const { return m_pDst; }
   int GetDstPort()      const { return m_DstPort; }

   BOOL IsRegCallback()          const { return m_bRegCallback; }
   SapXferCallback GetCallback() const { return m_pCallback; }
   void *GetContext()            const { return m_pContext; }

   SapXferCallback GetTrashCallback() const { return m_pTrashCallback; }
   void *GetTrashContext()            const { return m_pTrashContext; }

   int GetFramesPerCallback()    const { return m_FramesPerCallback; }
   int GetFramesOnBoard()			const { return m_FramesOnBoard; }
   int GetRelativeBufferIndex()	const { return m_RelativeBufferIndex; }

   int GetNbInputFrames()   const { return m_NbInputFrames; }
   int GetNbOutputFrames()   const { return m_NbOutputFrames; }

   EventType GetEventType() const { return m_EventType; }
   EventCountSource GetEventCountSource() const { return m_EventCountSource; }

   CycleMode GetCycleMode() const
   {
      CycleMode cycleMode = m_CycleMode;
      if (cycleMode == SapXferPair::CycleUnknown && GetDst() != NULL)
      {
         // Determine default mode if none was set by the application
         cycleMode = SapXferPair::CycleAsynchronous;
         if (GetDst()->GetTrash() != CORHANDLE_NULL)
            cycleMode = SapXferPair::CycleWithTrash;
      }

      return cycleMode;
   }

   FlipMode GetFlipMode()   const
		{ 	return m_FlipMode; }

   CounterStampTimeBase GetCounterStampTimeBase() const
		{ 	return m_CounterStampTimeBase; }

   FlatFieldCycleMode GetFlatFieldCycleMode()   const
		{ 	return m_FlatFieldCycleMode; }

   DynamicLutCycleMode GetDynamicLutCycleMode()   const
		{ 	return m_DynamicLutCycleMode; }

   inline BOOL SetCallbackInfo(SapXferCallback pCallback, void *pContext);
   inline BOOL SetEventType(EventType eventType);
   inline BOOL SetEventCountSource(EventCountSource eventCountSource);
   inline BOOL SetCycleMode(CycleMode cycleMode);
   inline BOOL SetFlipMode(FlipMode flipMode);
   inline BOOL SetCounterStampTimeBase(CounterStampTimeBase counterStampTimeBase);
   inline BOOL SetFlatFieldCycleMode(FlatFieldCycleMode flatFieldCycleMode);
   inline BOOL SetDynamicLutCycleMode(DynamicLutCycleMode dynamicLutCycleMode);
   inline BOOL SetFramesPerCallback(int numFrames);
   inline BOOL SetFramesOnBoard(int numFrames);
   inline BOOL SetRelativeBufferIndex(int relativeBufferIndex);
   inline BOOL SetNbInputFrames(int nbInputFrames);
   inline BOOL SetNbOutputFrames(int nbOutputFrames);
   inline BOOL SetTrashCallbackInfo(SapXferCallback pCallback, void *pContext);

   void SetTransfer(SapTransfer *pXfer) { m_Xfer = pXfer; }
   void InternalSetFramesOnBoard(int numFrames) { m_FramesOnBoard = numFrames; }

protected:
   // Utility methods
   inline void Construct(SapXferNode *pSrc, int srcPort, SapXferNode *pDst, int dstPort, BOOL regCallback);

protected:
   // Source/destination node information
   SapXferNode*	m_pSrc;
   int				m_SrcPort;
   SapXferNode*	m_pDst;
   int				m_DstPort;

   // Callback information
   BOOL            m_bRegCallback;
   SapXferCallback m_pCallback;     // Overrides SapTransfer callback if specified
   void*				 m_pContext;		// Relevant only if overriding SapTransfer callback

   SapXferCallback m_pTrashCallback;     // Overrides SapTransfer callback if specified
   void*				 m_pTrashContext;		// Relevant only if overriding SapTransfer callback

   // Transfer parameters
   EventType m_EventType;				// Current transfer event type
   EventCountSource m_EventCountSource;   // Current source of event count
   CycleMode m_CycleMode;				// Current buffer cycle mode
   FlipMode  m_FlipMode;				// Current flipping mode
   CounterStampTimeBase m_CounterStampTimeBase; // Current counter-stamp time base
   FlatFieldCycleMode m_FlatFieldCycleMode;     // Current flat_field cycle mode
   DynamicLutCycleMode m_DynamicLutCycleMode;   // Current dynamic LUT cycle mode

   int		 m_FramesPerCallback;	// Current number of frames per callback
   int		 m_FramesOnBoard;			// Current number of onboard frames
   int       m_RelativeBufferIndex;
   int       m_NbInputFrames;     //number of frames to multiply by.
   int       m_NbOutputFrames;      //number of frames to Divide by.

   SapTransfer* m_Xfer;    // Reference to transfer object (to make parameter changes active)
};

//
// SapXferPairInfo class declaration
//
class SAPCLASSBASIC_CLASS SapXferPairInfo
{
public:
   SapXferPairInfo()
		{ m_Index = 0; m_pXfer = NULL; m_context = NULL; }
   SapXferPairInfo(SapXferPair &pair, int index, SapTransfer *pXfer)
      { m_Pair = pair; m_Pair.SetTransfer(pXfer); m_Index = index; m_pXfer = pXfer; m_context = NULL; }

public:
   SapXferPair	         m_Pair;		// Transfer pair
   int			         m_Index;		// Index in the table
   SapTransfer*         m_pXfer;		// Corresponding transfer object
   SapXferContextInfo*  m_context;
   int                  m_MaxSnapCount;   // Maximum frame count for Snap
   SapXferPair::CycleMode m_CycleModeCap; // Cycle mode capability
   BOOL                 m_DynamicLutCap;  // Availability of dynamic look-up tables
};

//
// SapXferContextInfo class declaration
//
class SAPCLASSBASIC_CLASS SapXferContextInfo
{
public:
   SapXferContextInfo()
		{ m_PairInfo= NULL; m_dstIndex= 0; }
   SapXferContextInfo(SapXferPairInfo *pPairInfo, int dstIndex)
		{ m_PairInfo= pPairInfo; m_dstIndex= dstIndex;}

public:
   SapXferPairInfo* m_PairInfo;
   int		        m_dstIndex;
};

//
// SapXferCounterStampInfo class declaration
//
class SAPCLASSBASIC_CLASS SapXferCounterStampInfo
{
public:
   SapXferCounterStampInfo()
   {
      m_IsSupported = FALSE;
      m_IsAvailable = FALSE;
      m_MaxValue = 0;
      m_EventType = 0;
      m_TimeBase = SapXferPair::CounterStampMicroSec;
   }

   BOOL IsSupported() const { return m_IsSupported; }
   BOOL IsAvailable() const { return m_IsAvailable; }
   int GetMaxValue()  const { return m_MaxValue; }
   SapXferPair::EventType GetEventType()           const { return m_EventType; }
   SapXferPair::CounterStampTimeBase GetTimeBase() const { return m_TimeBase; }

   void SetSupported(BOOL isSupported) { m_IsSupported = isSupported; }
   void SetAvailable(BOOL isAvailable) { m_IsAvailable = isAvailable; }
   void SetMaxValue(int maxValue) { m_MaxValue = maxValue; }
   void SetEventType(SapXferPair::EventType eventType) { m_EventType = eventType; }
   void SetTimeBase(SapXferPair::CounterStampTimeBase timeBase) { m_TimeBase = timeBase; }

protected:
   BOOL m_IsSupported;
   BOOL m_IsAvailable;
   int m_MaxValue;
   SapXferPair::EventType m_EventType;
   SapXferPair::CounterStampTimeBase m_TimeBase;
};

//
// SapXferFrameRateInfo class declaration
//
class SAPCLASSBASIC_CLASS SapXferFrameRateInfo
{
public:

   SapXferFrameRateInfo();

   /// <summary>
   /// Check if frame rate calculated from buffer timestamps is available.
   /// </summary>
   BOOL IsBufferFrameRateAvailable() const { return m_BufferFrameRateEvaluated ? TRUE : FALSE; }

   /// <summary>
   /// Returns the frame rate calculated from buffer timestamps.
   /// </summary>
   /// <returns>the frame rate in frames/second</returns>
   /// <see cref="IsBufferFrameRateAvailable"/>
   float GetBufferFrameRate() const { return m_BufferFrameRate; }

   /// <summary>
   /// Returns the minimum time between 2 frames.
   /// </summary>
   /// <returns>a time in milli-seconds (ms)</returns>
   /// <see cref="IsBufferFrameRateAvailable"/>
   float GetMinTimePerFrame() const;

   /// <summary>
   /// Returns the maximum time between 2 frames.
   /// </summary>
   /// <returns>a time in milli-seconds (ms)</returns>
   /// <see cref="IsBufferFrameRateAvailable"/>
   float GetMaxTimePerFrame() const;

   /// <summary>
   /// Check if live frame rate from timer is available.
   /// </summary>
   BOOL IsLiveFrameRateAvailable() const { return m_LiveFrameRateEvaluated ? TRUE : FALSE; }

   /// <summary>
   /// When time base is not a physical measure of time,
   // like a shaft encoder for example,
   // we use performance timers from SapPerformance to APPROXIMATE
   // the real frame rate.
   /// </summary>
   float GetLiveFrameRate() const { return m_LiveFrameRate; }

   /// <summary>
   /// Check if live frame rate calculation is stalled.
   /// This will happen when no new frame has been received for quite
   /// some time now.
   /// </summary>
   BOOL IsLiveFrameRateStalled();

   /// <summary>
   /// Resets the internal values. 
   /// Automatically called before starting a new transfer stream.
   /// </summary>
   void Reset();

public:

   /* INTERNAL USE ONLY */

   void SetValues(float frameRate = 0.f, float timePerFrame = 0.f);
   void AccumulateFrames(int increment = 1);

protected:

   /* for use with SetValues() */

   float m_BufferFrameRate;
   float m_MinTimePerFrameFromCounterStamp;
   float m_MaxTimePerFrameFromCounterStamp;
   bool m_BufferFrameRateEvaluated;

   /* for use with AccumulateFrames() */

   float m_LiveFrameRate;
   INT32 m_AccFrameCount;
   SapPerformance m_PerfMonitor;
   bool m_LiveFrameRateEvaluated;
   bool m_ForceReset;
};

//
// SapTransfer class declaration
//

class SAPCLASSBASIC_CLASS SapTransfer : public SapManager
{
public:
   // Transfer start modes
   typedef int StartMode;
   enum _StartMode
   {
      StartAsynchronous = CORXFER_VAL_START_MODE_ASYNCHRONOUS,
      StartSynchronous = CORXFER_VAL_START_MODE_SYNCHRONOUS,
      StartHalfAsynchronous = CORXFER_VAL_START_MODE_HALF_ASYNCHRONOUS,
      StartSequential = CORXFER_VAL_START_MODE_SEQUENTIAL
   };

   // Various constants
   enum MiscValues
   {
      MaxPairs = 64,
      MaxMultiNode = 16
   };

public:
   // Constructor/Destructor
   SapTransfer(SapXferCallback pCallback = NULL, void *pContext = NULL, SapLocation location = SapLocation::ServerUnknown);
   SapTransfer(SapXferCallback pCallback, SapXferCallback pTrashCallback, void *pContext, SapLocation location = SapLocation::ServerUnknown);
   SapTransfer(const SapTransfer &xfer);
   virtual ~SapTransfer();

   SapTransfer &operator= (const SapTransfer &xfer);

public:
   // Creation/destruction
   virtual BOOL Create();
   virtual BOOL Destroy();

   virtual BOOL Connect();
   virtual BOOL Disconnect();

   // Access to implementation
   BOOL AddPair(SapXferPair &pair);
   BOOL RemoveAllPairs();
   SapXferPair *GetPair(int pairIndex);
   int GetNumPairs()							  const { return m_NumPairs; }
   const SapXferPairInfo *GetPairInfo()  const { return m_Pairs; }
   const SapXferCounterStampInfo *GetCounterStampInfo(int pairIndex) const;

   virtual CORHANDLE GetHandle()         const { return m_hXfer; }
   SapLocation GetLocation()             const { return m_Location; }

   virtual SapXferCallback GetCallback() const { return m_pCallback; }
   virtual SapXferCallback GetTrashCallback() const { return m_pTrashCallback; }
   virtual void *GetContext()            const { return m_pContext; }
   virtual BOOL IsGrabbing()             const { return m_bGrab; }
   virtual BOOL IsAutoEmpty()            const { return m_bAutoEmpty; }
   virtual BOOL IsAutoConnect()			  const { return m_bAutoConnect; }
   virtual BOOL IsConnected()            const { return m_bConnected; }
   virtual StartMode GetStartMode()      const { return m_StartMode; }
   virtual BOOL IsCycleModeAvailable(int pairIndex, SapXferPair::CycleMode cycleMode);
   virtual int GetConnectTimeout()       const { return m_ConnectTimeout; }

   BOOL SetLocation(SapLocation location);

   virtual BOOL SetCallbackInfo(SapXferCallback pCallback, void *pContext = NULL);
   virtual BOOL SetTrashCallbackInfo(SapXferCallback pTrashCallback);

   virtual void SetAutoEmpty(BOOL bAutoEmpty);
   virtual void SetAutoConnect(BOOL bAutoConnect);

   virtual BOOL IsCapabilityValid(int cap);
   virtual BOOL IsParameterValid(int param);

   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   virtual BOOL Select(int pairIndex, int srcIndex = -1, int dstIndex = -1);
   virtual BOOL Select(SapXferPair* pPair, int srcIndex = -1, int dstIndex = -1);

   virtual BOOL SetStartMode(StartMode startMode);

   virtual BOOL SetConnectTimeout(int timeout);

   // Dynamic LUT management
   BOOL IsDynamicLutAvailable(int pairIndex = 0);

   // Frame rate statistics
   SapXferFrameRateInfo* GetFrameRateStatistics();
   virtual BOOL UpdateFrameRateStatistics();

#if !SAPERA_DOT_NET
   //obosolete functions that are included for compatibility
   //with older applications.
   //Use the XferMultiNode functions instead
   BOOL AddRtProDesign(SapXferMultiNode *pRtProDesign) { return AddXferMultiNode(pRtProDesign); }
   BOOL RemoveRtProDesigns(SapXferMultiNode *pRtProDesign) { return RemoveXferMultiNode(pRtProDesign); }
   BOOL RemoveAllRtProDesigns() { return RemoveAllXferMultiNode(); }

   BOOL AddXferMultiNode(SapXferMultiNode *pXferMultiNode);
   BOOL RemoveXferMultiNode(SapXferMultiNode *pXferMultiNode);
   BOOL RemoveAllXferMultiNode();
#endif

   // Utility methods
   virtual BOOL SetCallbackInfo(SapXferPair* pPair);
   virtual BOOL SetTrashCallbackInfo(SapXferPair* pPair);
   virtual BOOL SetEventType(SapXferPair* pPair);
   virtual BOOL SetEventCountSource(SapXferPair* pPair);
   virtual BOOL SetCycleMode(SapXferPair* pPair);
   virtual BOOL SetFlipMode(SapXferPair* pPair);
   virtual BOOL SetCounterStampTimeBase(SapXferPair* pPair);
   virtual BOOL SetFlatFieldCycleMode(SapXferPair* pPair);
   virtual BOOL SetDynamicLutCycleMode(SapXferPair* pPair);
   virtual BOOL SetFramesPerCallback(SapXferPair* pPair);
   virtual BOOL SetFramesOnBoard(SapXferPair* pPair);
   virtual BOOL SetRelativeBufferIndex(SapXferPair* pPair);
   virtual BOOL SetNbInputFrames(SapXferPair* pPair);
   virtual BOOL SetNbOutputFrames(SapXferPair* pPair);
   virtual BOOL RegisterCallback(SapXferPair::EventType eventType, SapXferCallback callback, void *context, UINT32 xferElement);
   virtual BOOL UnregisterCallback();
   virtual BOOL UpdateParameters(void);

   // Obsolete methods
   BOOL Add(SapXferPair &pair) { return AddPair(pair); }
   void RemoveAll()            { RemoveAllPairs(); }

public:
   // Transfer Control
   virtual BOOL Snap(int count = 1);
   virtual BOOL Grab();
   virtual BOOL Freeze();
   virtual BOOL Abort();
   virtual BOOL Wait(int timeout);
   virtual BOOL Init(BOOL resetIndex = TRUE);

protected:
   // Utility methods
   void Construct(SapXferCallback pCallback, SapXferCallback pTrashCallback, void *pContext, SapLocation location, int numPairs, const SapXferPairInfo *pPairs, BOOL bAutoEmpty, BOOL bAutoConnect = TRUE);
   virtual BOOL SetStartMode();
   virtual BOOL XferIsCycleModeAvailable(SapXferPair* pPair, SapXferPair::CycleMode cycleMode);
   virtual BOOL CreatePair(int pairIndex);
   virtual BOOL DestroyPair(int pairIndex);

   virtual BOOL GetCapabilities(int pairIndex);
   virtual BOOL SetParameters(int pairIndex);

   virtual BOOL SetParameters(void);
   void GetIndexesFromSourceDest(SapXferPair* pPair, int* srcIndex, int* dstIndex);
   void SetSourceDestIndexes(SapXferPair* pPair, int srcIndex, int dstIndex);
   virtual BOOL FindPairIndex(SapXferPair* pPair, int* pIndex);

   // Callback functions
   static SAPSTATUS CCONV OnNormal(void *context, UINT32 eventType, UINT32 eventCount);
   static SAPSTATUS CCONV OnTrash(void *context, UINT32 eventType, UINT32 eventCount);
   static SAPSTATUS CCONV OnNormalEx(void *context, COREVENTINFO eventInfo);
   BOOL ExecuteCallback(void *context, UINT32 eventType, UINT32 eventCount, COREVENTINFO eventInfo);

protected:
   // Parameters
   SapXferCallback	m_pCallback;					   // Application callback function
   SapXferCallback	m_pTrashCallback;				   // Application callback function for trash buffers
   void					*m_pContext;						// Application context
   SapLocation			m_Location;							// Transfer location
   SapXferPairInfo	m_Pairs[MaxPairs];	         // Table of transfer pairs
   int					m_NumPairs;							// Number of transfer pairs
   BOOL	            m_bAutoEmpty;	               // TRUE to automatically empty buffers
   BOOL					m_bAutoConnect;					// TRUE to automatically connect the transfer object to the hardware
   // when calling the create function
   BOOL              m_bMultiBuffersUsed[MaxPairs];// True if pair supports multibuffer mechanism
   int               m_pXferElement;
   // Counter stamp capabilities
   SapXferCounterStampInfo m_CounterStampInfo[MaxPairs];

   BOOL            m_bNewCallbackViaConstructor;
   BOOL            m_bOldCallback;

   SapXferFrameRateInfo m_XferFrameRateInfo;

#if !SAPERA_DOT_NET
   SapXferMultiNode  *m_pXferMultiNode[MaxMultiNode];
#endif

   // Sapera transfer module settings
   CORXFER   m_hXfer;         // Transfer handle
   StartMode m_StartMode;     // Current start mode
   int m_ConnectTimeout;      // Override the communication timeout when calling Connect()

   // Flags
   BOOL m_bGrab;           // TRUE if transfer is active
   BOOL m_NoConnect;       // TRUE for some special transfer pairs that do not need to be connected
   BOOL m_bConnected;		// TRUE if transfer object is connected to hardware, FALSE otherwise
};

//
// SapXferCallbackInfo class declaration
//
class SAPCLASSBASIC_CLASS SapXferCallbackInfo
{
public:
   SapXferCallbackInfo(SapTransfer *pXfer, void *context, SapXferPair::EventType eventType, int eventCount, BOOL isTrash, int pairIndex)
      { m_pXfer = pXfer; m_Context = context; m_EventType = eventType; m_EventCount = eventCount; m_bTrash = isTrash; m_PairIndex = pairIndex; m_NewCallback = FALSE;}
   SapXferCallbackInfo(SapTransfer *pXfer, void *context, COREVENTINFO eventInfo, BOOL isTrash, int pairIndex);
   ~SapXferCallbackInfo() {}


   // Obsolete constructor
   SapXferCallbackInfo(void *context, SapXferPair::EventType eventType, int eventCount, BOOL isTrash, int pairIndex)
      { m_pXfer = NULL; m_Context = context; m_EventType = eventType; m_EventCount = eventCount; m_bTrash = isTrash; m_PairIndex = pairIndex; }

   SapTransfer *GetTransfer()                const { return m_pXfer; }
   void *GetContext()                        const { return m_Context; }
   BOOL IsTrash()                            const { return m_bTrash; }
   int GetPairIndex()                        const { return m_PairIndex; }
   COREVENTINFO GetEventInfo()               const { return m_EventInfo; }

   //Event Count
   int GetEventCount()                       const { return m_EventCount; }
   BOOL GetEventCount(int *eventCount);

   //Event Type
   SapXferPair::EventType GetEventType()     const { return m_EventType; }
   BOOL GetEventType(SapXferPair::EventType *eventType);

   //Timestamp
   BOOL GetHostTimeStamp(UINT64 *hostTimeStamp);
   BOOL GetAuxiliaryTimeStamp(UINT64 *auxTimeStamp);


   // Custom Parameters
   BOOL GetCustomData(void **customData);
   BOOL GetCustomSize(int *customSize);

   // Unnamed Parameters
   BOOL GetGenericParam0(int *paramValue);
   BOOL GetGenericParam1(int *paramValue);
   BOOL GetGenericParam2(int *paramValue);
   BOOL GetGenericParam3(int *paramValue);

protected:
   SapTransfer *m_pXfer;
   void *m_Context;
   SapXferPair::EventType m_EventType;
   int m_EventCount;
   BOOL m_bTrash;
   int m_PairIndex;
   COREVENTINFO m_EventInfo;
   BOOL m_NewCallback;
};

//
// SapXferPair class inline implementation
//
inline BOOL SapXferPair::SetCallbackInfo(SapXferCallback pCallback, void *pContext)
{
   m_pCallback = pCallback;
   m_pContext = pContext;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetCallbackInfo(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetTrashCallbackInfo(SapXferCallback pCallback, void *pContext)
{
   m_pTrashCallback = pCallback;
   m_pTrashContext = pContext;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetTrashCallbackInfo(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetEventType(EventType eventType)
{
   m_EventType = eventType;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetEventType(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetEventCountSource(EventCountSource eventCountSource)
{
   m_EventCountSource = eventCountSource;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetEventCountSource(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetCycleMode(CycleMode cycleMode)
{
   m_CycleMode = cycleMode;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetCycleMode(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetFlipMode(FlipMode flipMode)
{
   m_FlipMode = flipMode;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetFlipMode(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetCounterStampTimeBase(CounterStampTimeBase counterStampTimeBase)
{
   m_CounterStampTimeBase = counterStampTimeBase;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetCounterStampTimeBase(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetFlatFieldCycleMode(FlatFieldCycleMode flatFieldCycleMode)
{
   m_FlatFieldCycleMode = flatFieldCycleMode;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetFlatFieldCycleMode(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetDynamicLutCycleMode(DynamicLutCycleMode dynamicLutCycleMode)
{
   m_DynamicLutCycleMode = dynamicLutCycleMode;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetDynamicLutCycleMode(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetFramesPerCallback(int numFrames)
{
   int nDstCount = GetDst()->GetCount();

   if (numFrames > nDstCount / 2)
      numFrames = nDstCount / 2 + ((nDstCount & 1) ? 1 : 0);

   if (numFrames > 0)
   {
      m_FramesPerCallback = numFrames;

      if (m_Xfer && *m_Xfer)
         m_Xfer->SetFramesPerCallback(this);
      else
         return TRUE;
   }

   return FALSE;
}

inline BOOL SapXferPair::SetFramesOnBoard(int numFrames)
{
   if (numFrames > 0)
   {
      m_FramesOnBoard = numFrames;

      if (m_Xfer && *m_Xfer)
      {
         if (!m_Xfer->SetFramesOnBoard(this))
            return FALSE;
         return m_Xfer->UpdateParameters();
      }
      else
         return TRUE;
   }

   return FALSE;
}

inline BOOL SapXferPair::SetRelativeBufferIndex(int relativeBufferIndex)
{
   m_RelativeBufferIndex = relativeBufferIndex;
   if (m_Xfer && *m_Xfer)
      return m_Xfer->SetRelativeBufferIndex(this);
   else
      return TRUE;
}

inline BOOL SapXferPair::SetNbInputFrames(int nbInputFrames)
{
   if (nbInputFrames > 0)
   {
      m_NbInputFrames = nbInputFrames;

      if (m_Xfer && *m_Xfer)
         return m_Xfer->SetNbInputFrames(this);
      else
         return TRUE;
   }

   return FALSE;
}

inline BOOL SapXferPair::SetNbOutputFrames(int nbOutputFrames)
{
   if (nbOutputFrames > 0)
   {
      m_NbOutputFrames = nbOutputFrames;

      if (m_Xfer && *m_Xfer)
         return m_Xfer->SetNbOutputFrames(this);
      else
         return TRUE;
   }

   return FALSE;
}

inline void SapXferPair::Construct(SapXferNode *pSrc, int srcPort, SapXferNode *pDst, int dstPort, BOOL regCallback)
{
   m_pSrc = pSrc;
   m_SrcPort = srcPort;
   m_pDst = pDst;
   m_DstPort = dstPort;

   m_bRegCallback = regCallback;
   m_pCallback = NULL;
   m_pContext = NULL;

   m_pTrashCallback = NULL;
   m_pTrashContext = NULL;

   m_FramesPerCallback = 1;
   m_FramesOnBoard = InvalidFramesOnBoard;

   m_RelativeBufferIndex = 0;

   m_NbInputFrames = 1;
   m_NbOutputFrames = 1;

   m_EventType = EventEndOfFrame;
   m_EventCountSource = EventCountDst;
   m_CycleMode = CycleUnknown;
   m_FlipMode = FlipNone;
   m_CounterStampTimeBase = CounterStampMicroSec;
   m_FlatFieldCycleMode = FlatFieldCycleOff;
   m_DynamicLutCycleMode = DynamicLutCycleOff;

   m_Xfer = NULL;
}

#endif   // _SAPTRANSFER_H_
