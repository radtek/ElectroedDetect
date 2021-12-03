#ifndef _SAPDYNAMICLUT_H_
#define _SAPDYNAMICLUT_H_

// SapDynamicLut.h : header file
//

#include "SapClassBasicDef.h"

//
// SapDynamicLut class declaration
//
class SAPCLASSBASIC_CLASS SapDynamicLut : public SapManager
{
public:
   // Various constants
   enum MiscValues
   {
      InvalidDynamicLutNumber = -1,
      TrashBufferIndex = -1
   };

public:
   // Constructor/Destructor
   SapDynamicLut(SapAcquisition *acq, SapTransfer *xfer, int numDynamicLut = 1);
   SapDynamicLut(const SapDynamicLut &dynamicLut);
   virtual ~SapDynamicLut();

   SapDynamicLut &operator= (const SapDynamicLut &dynamicLut);

   // Creation/destruction
   virtual BOOL Create();
   virtual BOOL Destroy();

public:
   // Access to implementation
   SapAcquisition *GetAcquisition() const { return m_Acq; }
   SapTransfer *GetTransfer()       const { return m_Xfer; }
   SapLut *GetLut(int lutIndex);

   BOOL IsEnabled()       const { return m_IsEnabled; }
   int GetNumDynamicLut() const { return m_NumDynamicLut; }

   virtual BOOL SetAcquisition(SapAcquisition *acq);
   virtual BOOL SetTransfer(SapTransfer *xfer);
   virtual BOOL SetNumDynamicLut(int numDynamicLut);

   // Load/save LUTs from/to disk files
   virtual BOOL Load(int lutIndex, const char *fileName);
   virtual BOOL Save(int lutIndex, const char *fileName);

   // Associate a dynamic LUT with a destination index (usually a buffer)
   virtual BOOL SetDestDynamicLutIndex(int bufIndex, int lutIndex);

   // Execution control
   virtual BOOL Enable(BOOL enable = TRUE);

protected:
   // Utility methods
   virtual void Construct(SapAcquisition *acq, SapTransfer *xfer, int numDynamicLut);
   virtual BOOL SetAcqDynamicLut(int lutIndex);
   virtual BOOL SetAllAcqDynamicLut();
   virtual BOOL ResetAllAcqDynamicLut();

protected:
   SapAcquisition *m_Acq;
   SapTransfer    *m_Xfer;
   SapLut         **m_Lut;

   BOOL m_IsEnabled;
   int  *m_DynamicLutNumbers;    // Dynamic LUT numbers returned from acquisition device
   int  m_NumDynamicLut;
};

#endif
