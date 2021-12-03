#ifndef _SAPRTPRO_DESIGN_H_
#define _SAPRTPRO_DESIGN_H_

//	SapRTProDesign.h : header file
//

#include "SapClassBasicDef.h"


//for compatibility with older applications.
#define  SapRTProDesignInOutParam    SapXferMultiNodeParam 

//
// SapRTProDesign class declaration
//
class SAPCLASSBASIC_CLASS SapRTProDesign : public SapXferMultiNode
{
public:

public:
	// Constructor/Destructor
	SapRTProDesign( SapLocation location = SapLocation::ServerSystem,
                   char* pLabel = NULL,
                   SapRTProXferNode *pRTPro = NULL,
                   BOOL bCreateInputOnBrdBuffers = TRUE,
                   BOOL bCreateOutputOnBrdBuffers = TRUE );

	SapRTProDesign(const SapRTProDesign &rtProDesign);
	virtual ~SapRTProDesign();

	SapRTProDesign &operator=(const SapRTProDesign &rtpro);

   //obsolete function to support old RTPro demos.
   BOOL CopyClass( const SapRTProDesign *pSrcClass, SapRTProDesign *pDstClass);

   SapRTProXferNode *GetRTPro( void)  { return m_pRTPro; }

   BOOL GetDefaultFirmwareFilename( char *pName, UINT32 size);
   BOOL SetDefaultFirmwareFilename( char *pName);

   BOOL GetDesignName( char *pName, UINT32 size);
   BOOL SetDesignName( char *pName);

   BOOL LoadDefaultFirmware( void);

   virtual BOOL SetMsgCallbackInfo( SapRTProMsgCallback pCallback, void *context);

   //this function must be implemented by the derived class.
   virtual BOOL SetCustomDesignParameters( void) { return TRUE;}


   SapBuffer* GetInputOnBrdBuffers( int inputIdx);


   //must be implemented by derived class
   virtual BOOL Create( void);
   virtual BOOL Destroy( void);

protected:
   BOOL m_bCreateInputOnBrdBuffers;
   BOOL m_bCreateOutputOnBrdBuffers;

   SapRTProXferNode  *m_pRTPro;       //realtime pro object.
   BOOL        m_bOwnRTPro;         //true if realtime pro was created internally by this object.

   //messaging callback info
   SapRTProMsgCallback m_pRTProMsgCallback;
   void *m_pMsgContext;

   char        m_DefaultFirmwareFilename[ SAPRTPRO_MAX_NAME_SIZE];
   char        m_DesignName[ SAPRTPRO_MAX_NAME_SIZE];


   //protected functions.
   virtual SAPSTATUS InternalMsgCommand( SapRTProMsgCallbackInfo *pCallbackInfo);

   // Internal callback management
   static SAPSTATUS CCONV OnRTProMsgCallback( SapRTProMsgCallbackInfo *pCallbackInfo);

   virtual BOOL CreateInputResources( void);
   virtual BOOL CreateInputResources( int inputIdx);

   virtual BOOL CreateOutputResources( void);
   virtual BOOL CreateOutputResources( int outputIdx);

   virtual BOOL DestroyInputResources( void);
   virtual BOOL DestroyInputResources( int inputIdx);

   virtual BOOL DestroyOutputResources( void);
   virtual BOOL DestroyOutputResources( int outputIdx);

}; 

#endif	// _SAPRTPRO_DESIGN_H_

