#ifndef _SAPGIO_H_
#define _SAPGIO_H_

// SapGio.h : header file
//

#include "SapClassBasicDef.h"

// Forward declarations
class SAPCLASSBASIC_CLASS SapGioCallbackInfo;
typedef void (*SapGioCallback)(SapGioCallbackInfo *);

//
// SapGio class declaration
//

class SAPCLASSBASIC_CLASS SapGio : public SapManager
{
public:
   // Pin configurations
   typedef int PinConfig;
   enum _PinConfig
   {
      PinInput    = 1,
      PinOutput   = 2,
      PinTristate = 4
   };

   // Pin states
   enum PinState
   {
      PinLow  = 0,
      PinHigh = 1
   };

   // I/O event types
   typedef int EventType;
   enum _EventType
   {
      EventRisingEdge  = CORGIO_VAL_EVENT_TYPE_RISING_EDGE,
      EventFallingEdge = CORGIO_VAL_EVENT_TYPE_FALLING_EDGE
   };

   // Various constants
   enum MiscValues
   {
      AllPins = -1,
      MaxCallbacks = 8
   };

public:
   // Constructor/Destructor
   SapGio(SapLocation loc = SapLocation::ServerSystem, SapGioCallback pCallback = NULL, void *pContext = NULL);
   SapGio(const SapGio &gio);
   virtual ~SapGio();

   SapGio &operator=(const SapGio &gio);

   // Module create/destroy
   virtual BOOL Create();
   virtual BOOL Destroy();

   // Access to implementation
   CORHANDLE GetHandle()        const { return m_hGio; }
   SapLocation GetLocation()    const { return m_Location; }
   SapGioCallback GetCallback() const { return m_pCallback; }
   void *GetContext()           const { return m_pContext; }
   int GetNumPins()             const { return m_NumPins; }

	BOOL SetLocation(SapLocation location);

   virtual BOOL GetAvailPinConfig(int pinNumber, PinConfig *pAvailPinConfig);
   virtual BOOL GetAvailPinConfig(PinConfig *pAvailPinConfig);
   virtual BOOL GetPinConfig(int pinNumber, PinConfig *pPinConfig);
   virtual BOOL GetPinConfig(PinConfig *pPinConfig);
   virtual BOOL SetPinConfig(int pinNumber, PinConfig pinConfig);
   virtual BOOL SetPinConfig(PinConfig *pPinConfig);

   virtual BOOL GetPinState(int pinNumber, PinState *pPinState);
   virtual BOOL GetPinState(PinState *pPinState);
   virtual BOOL SetPinState(int pinNumber, PinState pinState);
   virtual BOOL SetPinState(int pinMask, PinState *pPinState);

   virtual BOOL SetCallbackInfo(SapGioCallback pCallback, void *pContext = NULL);

//
// Direct capability/parameter access
//
   virtual BOOL IsCapabilityValid(int cap);
   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL IsParameterValid(int param);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   // Callback management
   virtual BOOL EnableCallback(int pinNumber, EventType eventType);
   virtual BOOL EnableCallback(int pinMask, EventType *pEventType);
   virtual BOOL EnableCallback(EventType eventType);
   virtual BOOL DisableCallback(int pinNumber);
   virtual BOOL DisableCallback();

   // Obsolete methods
#if COR_WIN32 && !COR_WIN64 && !SAPERA_DOT_NET
   virtual BOOL AutoTrigger(SapCounter *pCounter, int startCount, int stopCount, int pinMask, int pinState);
#endif // COR_WIN32

protected:
   // Utility methods
   void Construct(SapLocation loc, SapGioCallback pCallback, void *pContext);

   virtual BOOL SetPinConfig(int pinNumber, PinConfig *pPinConfig);

   // Callback management
   // Note that we have separate a function for each pin so that we can guarantee
   // that each callback will be called for no more than one pin at a time.
   static SAPSTATUS CCONV GioCallback0(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 0); }
   static SAPSTATUS CCONV GioCallback1(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 1); }
   static SAPSTATUS CCONV GioCallback2(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 2); }
   static SAPSTATUS CCONV GioCallback3(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 3); }
   static SAPSTATUS CCONV GioCallback4(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 4); }
   static SAPSTATUS CCONV GioCallback5(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 5); }
   static SAPSTATUS CCONV GioCallback6(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 6); }
   static SAPSTATUS CCONV GioCallback7(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, 7); }

   static SAPSTATUS CCONV GioCallbackAll(void *context, UINT32 eventType, UINT32 eventCount)
      { return GioCallback(context, (EventType) eventType, eventCount, AllPins); }

   static SAPSTATUS GioCallback(void *context, EventType eventType, UINT32 eventCount, int pinNumber);


   //functions for the new callbacks
   static SAPSTATUS CCONV GioCallback0Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 0); }
   static SAPSTATUS CCONV GioCallback1Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 1); }
   static SAPSTATUS CCONV GioCallback2Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 2); }
   static SAPSTATUS CCONV GioCallback3Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 3); }
   static SAPSTATUS CCONV GioCallback4Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 4); }
   static SAPSTATUS CCONV GioCallback5Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 5); }
   static SAPSTATUS CCONV GioCallback6Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 6); }
   static SAPSTATUS CCONV GioCallback7Ex(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, 7); }

   static SAPSTATUS CCONV GioCallbackAllEx(void *context, COREVENTINFO eventInfo)
      { return GioCallbackEx(context, eventInfo, AllPins); }

   static SAPSTATUS GioCallbackEx(void *context, COREVENTINFO eventInfo, int pinNumber);


protected:
   SapLocation m_Location;
   CORGIO      m_hGio;

   // Parameters and capabilities
   int       m_NumPins;             // Number of I/O pins
   PinConfig *m_AvailPinConfig;     // Possible configurations for each pin
   PinConfig *m_PinConfig;          // Current configuration for each pin
   int       m_DirOutputPrm;        // Current CORGIO_PRM_DIR_OUTPUT value
   int       m_DirTristatePrm;      // Current CORGIO_PRM_DIR_TRISTATE value
   int       m_ReadOnlyCap;          // Current CORGIO_CAP_READ_ONLY value

   // Callback management
   SapGioCallback m_pCallback;         // Application callback function
   void           *m_pContext;         // Application context
   BOOL           m_IsNewCallback;     // TRUE if we're using the new callback function
   BOOL           m_IsCallbackAll;     // TRUE if using GioCallbackAll() for all pins
   BOOL           *m_IsCallbackActive; // Callback status for all pins
	static PCORCALLBACK m_CallbackList[MaxCallbacks];              // Callback function table
	static PCOREVENTINFOCALLBACK m_CallbackListEx[MaxCallbacks];  // New Callback function table
}; 

//
// SapGioCallbackInfo class declaration
//
class SAPCLASSBASIC_CLASS SapGioCallbackInfo
{
public:
   SapGioCallbackInfo(SapGio *pGio, void *context, SapGio::EventType eventType, int eventCount, int pinNumber)
      { m_pGio = pGio; m_Context = context; m_EventType = eventType; m_EventCount = eventCount; m_PinNumber = pinNumber; m_NewCallback = FALSE; }
	SapGioCallbackInfo(SapGio *pGio, void *context, COREVENTINFO eventInfo, int pinNumber);

   ~SapGioCallbackInfo() {}

   SapGio *GetGio()                          const { return m_pGio; }
   void *GetContext()                        const { return m_Context; }
   int GetPinNumber()                        const { return m_PinNumber; }
   COREVENTINFO GetEventInfo()               const { return m_EventInfo; }

   //Event Count
   int GetEventCount()                       const { return m_EventCount; }
   BOOL GetEventCount(int *eventCount);

   //Event Type
   SapGio::EventType GetEventType()          const { return m_EventType; }
   BOOL GetEventType(SapGio::EventType *eventType);

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
   SapGio *m_pGio;
   void *m_Context;
   SapGio::EventType m_EventType;
   int m_EventCount;
   int m_PinNumber;
   COREVENTINFO m_EventInfo;
   BOOL m_NewCallback;
};

#endif   // _SAPGIO_H_
