#ifndef _SAPCOUNTER_H_
#define _SAPCOUNTER_H_

// SapCounter.h : header file
//

#include "SapClassBasicDef.h"

// Forward declarations
class SAPCLASSBASIC_CLASS SapCounterCallbackInfo;
typedef void (*SapCounterCallback)(SapCounterCallbackInfo *);

//
// SapCounter class declaration
//

class SAPCLASSBASIC_CLASS SapCounter : public SapManager
{
public:
   // Base units
   typedef int BaseUnits;
   enum _BaseUnits
   {
      UnitsTime     = CORCOUNTER_VAL_BASE_UNITS_TIME,
      UnitsHSync    = CORCOUNTER_VAL_BASE_UNITS_HS,
      UnitsVSync    = CORCOUNTER_VAL_BASE_UNITS_VS,
      UnitsExternal = CORCOUNTER_VAL_BASE_UNITS_EXTERNAL
   };

   // Counter detection types
   typedef int DetectType;
   enum _DetectType
   {
      DetectRisingEdge  = CORCOUNTER_VAL_RISING_EDGE,
      DetectFallingEdge = CORCOUNTER_VAL_FALLING_EDGE
   };

   // Counter direction types
   typedef int Direction;
   enum _Direction
   {
      DirectionUp   = CORCOUNTER_VAL_DIRECTION_UP,
      DirectionDown = CORCOUNTER_VAL_DIRECTION_DOWN
   };

   // Event types
   typedef int EventType;
   enum _EventType
   {
      EventNone        = 0,
      EventElapsedTime = CORCOUNTER_VAL_EVENT_TYPE_ELAPSED_TIME
   };

public:
   // Constructor/Destructor
   SapCounter(SapLocation loc = SapLocation::ServerSystem, SapCounterCallback pCallback = NULL, void *pContext = NULL);
   SapCounter(const SapCounter &counter);
   virtual ~SapCounter();

   SapCounter &operator=(const SapCounter &counter);

   // Module create/destroy
   virtual BOOL Create();
   virtual BOOL Destroy();

   // Access to implementation
   CORHANDLE GetHandle()            const { return m_hCounter; }
   SapLocation GetLocation()        const { return m_Location; }
   SapCounterCallback GetCallback() const { return m_pCallback; }
   void *GetContext()               const { return m_pContext; }
   BaseUnits GetBaseUnits()         const { return m_BaseUnits; }
   DetectType GetDetectType()       const { return m_DetectType; }
   Direction GetDirection()         const { return m_Direction; }

   virtual BOOL GetCount(int *pCount);
   virtual BOOL SetBaseUnits(BaseUnits baseUnits);
   virtual BOOL SetDetectType(DetectType detectType);
   virtual BOOL SetDirection(Direction direction);
   virtual BOOL SetCallbackInfo(SapCounterCallback pCallback, void *pContext = NULL);

   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   virtual BOOL Start();
   virtual BOOL Stop();

   // Callback management
   virtual BOOL EnableCallback(EventType eventType, int elapsedTime);
   virtual BOOL DisableCallback();

protected:
   // Utility methods
   void Construct(SapLocation loc, SapCounterCallback pCallback, void *pContext);

   // Callback management
   static SAPSTATUS CounterCallback(void *context, UINT32 eventType, UINT32 eventCount);

protected:
   SapLocation m_Location;
   CORCOUNTER  m_hCounter;

   // Parameters
   BaseUnits  m_BaseUnits;
   DetectType m_DetectType;
   Direction  m_Direction;

   // Callback management
   SapCounterCallback m_pCallback;        // Application callback function
   void               *m_pContext;        // Application context
   BOOL               m_IsCallbackActive; // Callback status
}; 

//
// SapCounterCallbackInfo class declaration
//
class SAPCLASSBASIC_CLASS SapCounterCallbackInfo
{
public:
   SapCounterCallbackInfo(SapCounter *pCounter, void *context, SapCounter::EventType eventType, int eventCount)
      { m_pCounter = pCounter; m_Context = context; m_EventType = eventType; m_EventCount = eventCount; }
   ~SapCounterCallbackInfo() {}

   SapCounter *GetCounter()             const { return m_pCounter; }
   void *GetContext()                   const { return m_Context; }
   SapCounter::EventType GetEventType() const { return m_EventType; }
   int GetEventCount()                  const { return m_EventCount; }

protected:
   SapCounter *m_pCounter;
   void *m_Context;
   SapCounter::EventType m_EventType;
   int m_EventCount;
};

#endif   // _SAPCOUNTER_H_
