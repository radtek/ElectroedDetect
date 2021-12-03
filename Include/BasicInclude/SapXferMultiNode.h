#ifndef _SAPXFER_MULTINODE_H_
#define _SAPXFER_MULTINODE_H_

//	SapXferMultiNode.h : header file
//

#include "SapClassBasicDef.h"
#include "SapTransfer.h"


//
// Class SapXferMultiNodeParam
// Stores parameters that define an input or an output
// of the SapXferMultiNode class.
//
class SAPCLASSBASIC_CLASS SapXferMultiNodeParam
{

   public:

   // Various constants
   enum OnBrdBufferCreateMode
   {
      Default = 0x0001,
      AlwaysCreate = 0x0002,
      NeverCreate  = 0x0004,
   };

   public:
	// Constructor/destructor
	SapXferMultiNodeParam( SapXferNode *pSrcNode = NULL,
                             int srcPort = 0,
                             SapXferNode *pDstNode = NULL,
                             int dstPort = 0,
                             UINT32 nbOnBrdBuffers = 1,
                             int relativeBufferIdx = 0, 
                             SapBuffer *pOnBrdbuffers = NULL,
                             BOOL bOwnOnBrdBuffers = FALSE )
   {
      m_pSrcNode = pSrcNode;
      m_SrcPort = srcPort;
      m_pDstNode = pDstNode;
      m_dstPort = dstPort;
      m_nbOnBrdBuffers = nbOnBrdBuffers;
      m_relativeBufferIdx = relativeBufferIdx;
      m_pOnBrdBuffers = pOnBrdbuffers;
      m_bOwnOnBrdBuffers = bOwnOnBrdBuffers;
      m_pXferCallBack = NULL;
      m_pXferContext = NULL;
      m_nbInputFrames = 1;
      m_nbOutputFrames = 1;
      m_OnBrdBufferCreateMode = Default;
      m_CycleMode = SapXferPair::CycleUnknown;
      m_pTrashCallBack = NULL;
      m_pTrashContext = NULL;
   }

	SapXferMultiNodeParam(const SapXferMultiNodeParam &param)
   {
      //use the = operator.
      *this = param;
   }

   virtual ~SapXferMultiNodeParam(){  return;}

	SapXferMultiNodeParam &operator=(const SapXferMultiNodeParam &param)
   {
      m_pSrcNode = param.m_pSrcNode;
      m_SrcPort = param.m_SrcPort;
      m_pDstNode = param.m_pDstNode;
      m_dstPort = param.m_dstPort;
      m_nbOnBrdBuffers = param.m_nbOnBrdBuffers;
      m_relativeBufferIdx = param.m_relativeBufferIdx;
      m_pOnBrdBuffers = param.m_pOnBrdBuffers;
      m_bOwnOnBrdBuffers = param.m_bOwnOnBrdBuffers;
      m_pXferCallBack = param.m_pXferCallBack;
      m_pXferContext = param.m_pXferContext;
      m_nbInputFrames = param.m_nbInputFrames;
      m_nbOutputFrames = param.m_nbOutputFrames;
      m_CycleMode = param.m_CycleMode;
      m_pTrashCallBack = param.m_pTrashCallBack;
      m_pTrashContext = param.m_pTrashContext;

      return *this;
   }

   BOOL SetSrcNode(SapXferNode* pSrcNode)  { m_pSrcNode = pSrcNode; return TRUE;}
   BOOL SetSrcPort(int srcPort)           { m_SrcPort = srcPort; return TRUE;}
   BOOL SetDstNode(SapXferNode *pDstNode)   { m_pDstNode = pDstNode; return TRUE;}
   BOOL SetDstPort(int dstPort)           { m_dstPort = dstPort; return TRUE;}

   BOOL SetNbInputFrames( int nbInputFrames)               { m_nbInputFrames = nbInputFrames; return TRUE;}
   BOOL SetNbOutputFrames( int nbOutputFrames)               { m_nbOutputFrames = nbOutputFrames; return TRUE;}


   BOOL SetNbOnBrdBuffers(int nbOnBrdBuffers)     { m_nbOnBrdBuffers = nbOnBrdBuffers; return TRUE;}
   BOOL SetRelativeBufferIdx(int relativeBufferIdx)       { m_relativeBufferIdx = relativeBufferIdx; return TRUE;}
   BOOL SetOnBrdBuffers(SapBuffer *pOnBrdBuffers)     { m_pOnBrdBuffers = pOnBrdBuffers; return TRUE;}
   BOOL SetOnBrdBufferOwner(BOOL bOwnOnBrdBuffers)   { m_bOwnOnBrdBuffers = bOwnOnBrdBuffers; return TRUE;}
   BOOL SetOnBrdBufferCreateMode( OnBrdBufferCreateMode createMode)   { m_OnBrdBufferCreateMode = createMode; return TRUE;}

	BOOL SetXferCallbackInfo( SapXferCallback pCallback, void *pContext= NULL){ m_pXferCallBack = pCallback; m_pXferContext = pContext; return TRUE;}
	BOOL SetTrashCallbackInfo( SapXferCallback pCallback, void *pContext= NULL){ m_pTrashCallBack = pCallback; m_pTrashContext = pContext; return TRUE;}

   BOOL SetCycleMode( SapXferPair::CycleMode cycleMode) { m_CycleMode = cycleMode; return TRUE;}

   SapXferNode *GetSrcNode()  { return m_pSrcNode;}
   int GetSrcPort()           { return m_SrcPort;}
   SapXferNode *GetDstNode()   { return m_pDstNode;}
   int GetDstPort()           { return m_dstPort;}

   int GetNbOnBrdBuffers()     { return m_nbOnBrdBuffers;}
   int GetRelativeBufferIdx()       { return m_relativeBufferIdx;}
   SapBuffer *GetOnBrdBuffers()     { return m_pOnBrdBuffers;}
   BOOL GetOnBrdBufferOwner()   { return m_bOwnOnBrdBuffers;}
   OnBrdBufferCreateMode GetOnBrdBufferCreateMode()   { return m_OnBrdBufferCreateMode;}

   
   SapXferCallback GetXferCallback( ){ return m_pXferCallBack;}
   void *GetXferContext( ) { return m_pXferContext;}
   int GetNbInputFrames( )               { return m_nbInputFrames;}
   int GetNbOutputFrames( )               { return m_nbOutputFrames;}

   SapXferCallback GetTrashCallback( ){ return m_pTrashCallBack;}
   void *GetTrashContext( ) { return m_pTrashContext;}

   SapXferPair::CycleMode GetCycleMode(void)	{ return m_CycleMode;}

   protected:

      //for xfernode connections.
      SapXferNode   *m_pSrcNode;   // src node for this input or output.
      int           m_SrcPort;     // src port for this input or output.
      SapXferNode   *m_pDstNode;   // dstNode for this input or output
      int           m_dstPort;     // dst port for this output
   
      
      int           m_nbOnBrdBuffers;    // number of onboard buffers to create.
      int           m_relativeBufferIdx; // relative buffer index to use
      SapBuffer     *m_pOnBrdBuffers;    // optional sapera onboard buffers.

      BOOL          m_bOwnOnBrdBuffers;  // True if onboard buffers were created internally by SapXferMultiNode object.

      SapXferCallback m_pXferCallBack;
      void        *m_pXferContext;
      int         m_nbInputFrames;
      int         m_nbOutputFrames;
      OnBrdBufferCreateMode m_OnBrdBufferCreateMode;
      SapXferPair::CycleMode  m_CycleMode;

      SapXferCallback m_pTrashCallBack;
      void        *m_pTrashContext;

};



//
// SapXferMultiNode class declaration
//
class SAPCLASSBASIC_CLASS SapXferMultiNode : public SapManager
{

public:
   
   // Various constants
   enum MiscValues
   {
      MaxInputs = 32,
      MaxOutputs = 32
   };


public:
	// Constructor/Destructor
	SapXferMultiNode( SapLocation location = SapLocation::ServerSystem);

	virtual ~SapXferMultiNode();


   //copy functions
   SapXferMultiNode(const SapXferMultiNode &xferMultiNode);
   SapXferMultiNode &operator=(const SapXferMultiNode &xferMultiNode);

	SapLocation GetLocation()		const { return m_Location; }


   //setting input using a src SapXferNode.
   virtual BOOL SetInputSrc(   int inputIdx, 
                            SapXferNode *pSrcNode,
                            int srcPort = 0,
                            int relativeBufferIdx = 0,
                            int nbOnBrdBuffer = 2,
                            SapBuffer *pOnBrdBuffers = NULL );



   //set input using the output of a SapXferMultiNode object .
   virtual BOOL SetInputSrc( int inputIdx, 
                             SapXferMultiNode *pXferMultiNode, 
                             int outputIdx,
                             int relativeBufferIdx = 0 );

   //set output using a destination SapXferNode
   virtual BOOL SetOutputDst( int outputIdx,
                           SapXferNode *pDstNode,
                           int dstPort = 0,
                           int nbOnBrdBuffer = 2,
                           SapBuffer *pOnBrdBuffers = NULL );


   virtual BOOL SetOutputNbInOutFrames( int outputIdx, int nbInputFrames, int nbOutputFrames);
	virtual BOOL SetOutputXferCallbackInfo( UINT32 outputIdx,  SapXferCallback pCallback, void *pContext= NULL); 
   virtual BOOL SetOutputOnBrdBufferCreateMode( int outputIdx, SapXferMultiNodeParam::OnBrdBufferCreateMode createMode);
   virtual BOOL SetInputOnBrdBufferCreateMode( int inputIdx, SapXferMultiNodeParam::OnBrdBufferCreateMode createMode);
   virtual BOOL SetOutputCycleMode( int outputIdx, SapXferPair::CycleMode cycleMode);
	virtual BOOL SetOutputTrashCallbackInfo( UINT32 outputIdx,  SapXferCallback pCallback, void *pContext= NULL); 

   //obsolete, use the SetOutputXferCallbackInfo instead.
	virtual BOOL SetXferCallbackInfo( SapXferCallback pCallback, void *pContext= NULL);

   BOOL           SetOutputXferParam( int outputIdx, SapXferParams xferParam);

   SapXferParams  GetInputXferParam( int inputIdx);
   SapBuffer      *GetInputOnBrdBuffers( int inputIdx);
   SapXferNode    *GetInputSrcNode( int inputIdx);

   SapXferNode    *GetOutputDstNode( int outputIdx);
   SapBuffer      *GetOutputOnBrdBuffers( int outputIdx);

   virtual BOOL GetOutputNbInOutFrames( int outputIdx, int *pNbInputFrames, int *pNbOutputFrames);

   virtual SapXferMultiNodeParam *GetOutputXferParam( UINT32 outputIdx)
   {
      if( outputIdx < MaxOutputs)
      {
         return m_pOutputInfo[ outputIdx];
      }
      else
      {
         return NULL;
      }

   };

   virtual SapXferPair::CycleMode GetOutputCycleMode( int outputIdx);

   //called by SapTransfer to add the transfer paths to make the multi node connections.
   virtual BOOL AddXferPaths( SapTransfer *pTransfer);

   virtual BOOL Create( void);
   virtual BOOL Destroy( void);


protected:
	SapLocation		m_Location;
   SapXferCallback m_pXferCallBack;
   void        *m_pXferContext;

   SapXferMultiNodeParam *m_pInputInfo[ MaxInputs];
   SapXferMultiNodeParam *m_pOutputInfo[ MaxOutputs];

   //internal functions to manage connections.
   virtual BOOL DefineInput( int inputIdx, SapXferNode *pDstNode, int dstPort);
   virtual BOOL UndefineInput(  int inputIdx );

   virtual BOOL DefineOutput(  int outputIdx, SapXferNode *pSrcNode, int srcPort);
   virtual BOOL UndefineOutput( int outputIdx );

   virtual BOOL AddAllInputXferPaths( SapTransfer *pTransfer);
   virtual BOOL AddInputXferPath( SapTransfer *pTransfer, int inputIdx);

   virtual BOOL AddAllOutputXferPaths( SapTransfer *pTransfer);
   virtual BOOL AddOutputXferPath( SapTransfer *pTransfer, int outputIdx);



}; 

#endif	// _SAPXFER_MULTINODE_H_

