#ifndef _SAPCAB_H_
#define _SAPCAB_H_

//	SapCab.h : header file
//

#include "SapClassBasicDef.h"

//
// SapCab class declaration
//
class SAPCLASSBASIC_CLASS SapCab : public SapXferNode
{
public:
   // Various constants
   enum MiscValues
   {
      MaxPorts = 16
   };

public:
	// Constructor/Destructor
	SapCab(SapLocation loc = SapLocation::ServerSystem, SapXferNode *pSrcNode = NULL);
	SapCab(SapLocation loc, SapXferParams xferParams);
	SapCab(const SapCab &cab);
	virtual ~SapCab();

	SapCab &operator= (const SapCab &cab);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

   // SapXferNode type information
   XferNodeType GetXferNodeType() { return NodeTypeCab; }

   // Direct capability/parameter access
   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

   //cab supports only 1 xferparam
   virtual SapXferParams GetXferParams(int portIndex = 0)	const { return SapXferNode::GetXferParams(0); }
	virtual SapXferParams GetInputXferParams(int portIndex = 0)	const { return SapXferNode::GetInputXferParams(0); }
	virtual SapXferParams GetOutputXferParams(int portIndex = 0)	const { return SapXferNode::GetOutputXferParams(0); }

	virtual BOOL SetXferParams(SapXferParams xferParams, int portIndex = 0)		{  return SapXferNode::SetXferParams(xferParams, 0); }
	virtual BOOL SetInputXferParams(SapXferParams xferParams, int portIndex = 0)		{ return SapXferNode::SetInputXferParams(xferParams, 0); }
	virtual BOOL SetOutputXferParams(SapXferParams xferParams, int portIndex = 0)	{ return SapXferNode::SetOutputXferParams(xferParams, 0); }

protected:
   virtual void Construct(int transferMode, int portCount, const int *channels);
	int GetBlockSize() const;

protected:
	int m_TransferMode;
   int m_PortCount;
   int m_Channels[MaxPorts];
}; 

#endif	// _SAPCAB_H_

