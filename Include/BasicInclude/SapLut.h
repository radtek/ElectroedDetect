#ifndef _SAPLUT_H_
#define _SAPLUT_H_

//	SapLut.h : header file
//

#include "SapClassBasicDef.h"

//
// SapLut class declaration
//
class SAPCLASSBASIC_CLASS SapLut : public SapManager
{
public:
   // Arithmetic operations
   enum ArithmeticOp
   {
      Add,
      ASub,
      Max,
      Min,
      Scale,
      Sub
   };

   // Boolean operations
   enum BooleanOp
   {
      And,
      Or,
      Xor
   };

public:
	// Constructor/Destructor
	SapLut(int numEntries = SapDefLutEntries, SapFormat format = SapFormatUint8, SapLocation loc = SapLocation::ServerSystem);
	SapLut(const char *filename, SapLocation loc = SapLocation::ServerSystem);
	SapLut(const SapLut &lut);
	virtual ~SapLut();

   SapLut &operator= (const SapLut &lut);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
	CORHANDLE GetHandle()     const { return m_hLut; }
   SapLocation GetLocation() const { return m_Location; }

   int GetNumEntries()    const { return m_NumEntries; }
   SapFormat GetFormat()  const { return m_Format; }
   int GetElementSize()   const { return m_DataSize; }
   int GetNumPages()      const { return m_NumPages; }
   BOOL IsSigned()        const { return m_IsSigned; }
   int GetTotalSize()     const { return m_TotalSize; }

	BOOL SetLocation(SapLocation location);
	virtual BOOL SetNumEntries(int numEntries);
	virtual BOOL SetFormat(SapFormat format);	

   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

	// LUT manipulation
   virtual BOOL Copy(SapLut *pSrc);
	virtual BOOL Load(const char *filename);
	virtual BOOL Save(const char *filename);
   virtual BOOL Read(int lutIndex, SapData *pValue);
   virtual BOOL Read(int offset, void *pData, int size);
   virtual BOOL Write(int lutIndex, SapData value);
   virtual BOOL Write(int offset, void *pData, int size);

   // Data generation methods
   virtual BOOL Arithmetic(ArithmeticOp operation, SapData value);
   virtual BOOL BinaryPattern(int bitNumber, SapData newValue);
   virtual BOOL Boolean(BooleanOp operation, SapData value);
   virtual BOOL Gamma(float factor);
   virtual BOOL Normal();
   virtual BOOL Reverse();
   virtual BOOL Roll(int numEntries);
   virtual BOOL Shift(int numBits);
   virtual BOOL Slope(int startIndex, int endIndex, SapData minValue, SapData maxValue, BOOL clipOutside = FALSE);
   virtual BOOL Threshold(SapData threshValue);
   virtual BOOL Threshold(SapData lowValue, SapData highValue);

protected:
   // Utility methods
   void Construct(SapLocation loc, int numEntries, SapFormat format, const char *filename);

protected:
	SapLocation m_Location;
	CORLUT m_hLut;

   char m_Filename[MAX_PATH];    // Used when creating LUT from an existing file

   // Parameters
	int m_NumEntries;       // Number of entries
	SapFormat m_Format;     // Data format
   int m_DataSize;         // Number of bytes for one LUT element
   int m_NumPages;         // Number of color pages
   BOOL m_IsSigned;        // TRUE if LUT data is signed
   int m_TotalSize;        // Total number of data bytes
}; 

#endif	// _SAPBUFFER_H_

