#ifndef _SAPXFERNODE_H_
#define _SAPXFERNODE_H_

//	SapXferNode.h : header file
//

#include "SapClassBasicDef.h"

//
// SapXferParams class declaration
//
class SAPCLASSBASIC_CLASS SapXferParams
{
public:
   // Transfer frame types
   typedef int FrameType;
   enum _FrameType
   {
      FrameInterlaced  = CORXFER_VAL_FRAME_INTERLACED,
      FrameProgressive = CORXFER_VAL_FRAME_NON_INTERLACED
   };

   // Transfer field order
   typedef int FieldOrder;
   enum _FieldOrder
   {
      FieldOrderOddEven = CORXFER_VAL_FIELD_ORDER_ODD_EVEN,
      FieldOrderEvenOdd = CORXFER_VAL_FIELD_ORDER_EVEN_ODD,
      FieldOrderNext    = CORXFER_VAL_FIELD_ORDER_NEXT_FIELD
   };

public:
	// Constructor/destructor
	SapXferParams();
	~SapXferParams();

	// Access to implementation
   FrameType GetFrameType()       const { return m_Frame; }
   FieldOrder GetFieldOrder() const { return m_FieldOrder; }
	int GetWidth()        const { return m_Width; }
	int GetHeight()       const { return m_Height; }
	SapFormat GetFormat() const { return m_Format; }
	int GetPixelDepth()   const { return m_PixelDepth; }
	int GetPixelShift()   const { return m_PixelShift; }
	void GetParameters(FrameType *frame, FieldOrder *fieldOrder, int *width, int *height, SapFormat *format, int *pixelDepth, int *pixelShift) const;

	void SetFrameType(FrameType frameType) { m_Frame = frameType; }
	void SetFieldOrder(FieldOrder fieldOrder) { m_FieldOrder = fieldOrder; }
	void SetWidth(int width) { m_Width = width; }
	void SetHeight(int height) { m_Height = height; }
	void SetFormat(SapFormat format) { m_Format = format; SetPixelDepth(CorManGetPixelDepthMax(m_Format)); }
	void SetPixelDepth(int pixelDepth) { m_PixelDepth = pixelDepth; SetPixelShift(CorManGetPixelDepthMax(m_Format) - pixelDepth); }
	void SetPixelShift(int pixelShift) { m_PixelShift = pixelShift; }
	void SetParameters(FrameType frame, FieldOrder fieldOrder, int width, int height, SapFormat format, int pixelDepth, int pixelShift);

	// Utility
	operator CORXFER_DESC();

   // Obsolete methods
   FrameType GetFrame() const { return GetFrameType(); }
	void Get(FrameType *frame, FieldOrder *fieldOrder, int *width, int *height, SapFormat *format, int *pixelDepth, int *pixelShift) const;
	void SetFrame(FrameType frame) { SetFrameType(frame); }
	void Set(FrameType frame, FieldOrder fieldOrder, int width, int height, SapFormat format, int pixelDepth, int pixelShift);

protected:
	FrameType m_Frame;
	FieldOrder m_FieldOrder;
	int m_Width;
	int m_Height;
	SapFormat m_Format;
	int m_PixelDepth;
	int m_PixelShift;
};

//
// SapXferNode class declaration
//

class SAPCLASSBASIC_CLASS SapXferNode : public SapManager
{
public:
   // Possible types for derived classes
   enum XferNodeType
   {
      NodeTypeUnknown,
      NodeTypeAcqDevice,
      NodeTypeAcquisition,
      NodeTypeBuffer,
      NodeTypeCab,
      NodeTypeObsolete1,
      NodeTypePixPro,
      NodeTypeRTPro,
      NodeTypeBufferMulti
   };

   // Various constants
   enum MiscValues
   {
      MaxXferParams = 32
   };

public:
	// Constructor/Destructor
	SapXferNode(SapLocation location) 
		{ m_Location = location; m_pSrcNode = NULL; m_SrcPort = 0; m_hServer = m_handle = CORHANDLE_NULL; }

	SapXferNode(SapLocation location, SapXferNode *pSrcNode) 
		{ m_Location = location; m_pSrcNode = pSrcNode; m_SrcPort = 0; m_hServer = m_handle = CORHANDLE_NULL; }

	SapXferNode(SapLocation location, SapXferParams xferParams) 
		{ m_Location = location; m_pSrcNode = NULL; m_SrcPort = 0; m_XferParams[0] = xferParams; m_hServer = m_handle = CORHANDLE_NULL; }

   //should copy all xferParams
	SapXferNode(const SapXferNode& node) 
		{ m_Location = node.m_Location; m_pSrcNode = node.m_pSrcNode; m_SrcPort = node.m_SrcPort;m_XferParams[0] = node.m_XferParams[0]; m_hServer = m_handle = CORHANDLE_NULL; }

	virtual ~SapXferNode() {}

	SapXferNode& operator= (const SapXferNode& node) 
	{ 
		m_Location = node.m_Location; m_pSrcNode = node.m_pSrcNode; m_SrcPort = node.m_SrcPort; m_XferParams[0] = node.m_XferParams[0]; m_bInitOK = FALSE; m_hServer = m_handle = CORHANDLE_NULL; 
		return *this;
	}

	// Creation/destruction
	virtual BOOL Create() = 0;
	virtual BOOL Destroy() = 0;

public:
	// Access to implementation
	SapLocation GetLocation()		const { return m_Location; }
	SapXferNode *GetSrcNode()		const { return m_pSrcNode; }
   int GetSrcPort()              const { return m_SrcPort; }
   CORSERVER GetServer()         const { return m_hServer; }
	virtual SapXferParams GetXferParams(int portIndex = 0)	const { return m_XferParams[CORXFER_PORT_INDEX_MASK(portIndex)]; }
	virtual SapXferParams GetInputXferParams(int portIndex = 0)	const { return GetXferParams(CORXFER_PORT_INDEX_MASK(portIndex)); }
	virtual SapXferParams GetOutputXferParams(int portIndex = 0)	const { return GetXferParams(CORXFER_PORT_INDEX_MASK(portIndex)); }

	BOOL SetLocation(SapLocation loc)					{ if( m_bInitOK) return FALSE; m_Location = loc; return TRUE;}
	virtual BOOL SetSrcNode(SapXferNode *pSrcNode, int srcPort = 0)				{ if( m_bInitOK) return FALSE; m_pSrcNode = pSrcNode; m_SrcPort = srcPort; return TRUE;}
	virtual BOOL SetXferParams(SapXferParams xferParams, int portIndex = 0)		{ if( m_bInitOK) return FALSE; m_XferParams[portIndex] = xferParams; return TRUE;}
	virtual BOOL SetInputXferParams(SapXferParams params, int portIndex = 0)		{ return SetXferParams(params, CORXFER_PORT_INDEX_MASK(portIndex)); }
	virtual BOOL SetOutputXferParams(SapXferParams params, int portIndex = 0)	{ return SetXferParams(params, CORXFER_PORT_INDEX_MASK(portIndex)); }

	virtual CORHANDLE GetHandle()	const { return m_handle; }
	virtual void GetXferParamsFromSrcNode() 
		{ if (m_pSrcNode) SetInputXferParams(m_pSrcNode->GetOutputXferParams( m_SrcPort)); }

   // All classes derived from SapXferNode need to implement this
   virtual XferNodeType GetXferNodeType() = 0;

   // Obsolete method
   virtual BOOL IsBuffer() { return GetXferNodeType() == NodeTypeBuffer; }

public:
	// Cycling specific methods
	virtual CORHANDLE GetHandle(int index)	   const { return index == 0 ? m_handle : CORHANDLE_NULL; }
	virtual CORHANDLE operator[] (int index)	const { return GetHandle(index); }
	virtual int GetCount() const { return 1; }
	virtual int GetIndex() const { return 0; }
	virtual BOOL SetIndex(int index) { return TRUE; }
	virtual void ResetIndex() {}
	virtual void Next() {}

	virtual CORHANDLE GetTrash() const { return CORHANDLE_NULL; }

   // Obsolete methods
   virtual BOOL Empty()          { return TRUE; }
   virtual BOOL Empty(int index) { return TRUE; }
   virtual BOOL EmptyAll()       { return TRUE; }

protected:
	// Parameters
	SapLocation		m_Location;
	SapXferNode		*m_pSrcNode;
   int            m_SrcPort;
	SapXferParams	m_XferParams[MaxXferParams];
	CORSERVER		m_hServer;
	CORHANDLE		m_handle;
}; 

#endif	// _SAPXFERNODE_H_

