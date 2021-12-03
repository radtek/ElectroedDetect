#ifndef _SAPACQTOBUFTHRUCAB_H_
#define _SAPACQTOBUFTHRUCAB_H_

//	SapAcqToBufThruCab.h : header file
//

#include "SapClassBasicDef.h"

//
// SapAcqToBufThruCab class declaration
//
class SAPCLASSBASIC_CLASS SapAcqToBufThruCab : public SapTransfer
{
public:
	// Constructor/Destructor
	SapAcqToBufThruCab(SapAcquisition *pAcq, SapBuffer *pBuf, SapXferCallback pCallback = NULL, void *pContext = NULL);
	SapAcqToBufThruCab(SapAcquisition *pAcq, SapCab *pSrcCab, SapCab *pDstCab, SapBuffer *pBuf, SapXferCallback pCallback = NULL, void *pContext = NULL);
	SapAcqToBufThruCab(SapAcquisition *pAcq, SapCab *pSrcCab, int srcPort, SapCab *pDstCab, int dstPort, SapBuffer *pBuf, SapXferCallback pCallback = NULL, void *pContext = NULL);
	SapAcqToBufThruCab(const SapAcqToBufThruCab &xfer);
	virtual ~SapAcqToBufThruCab();

	SapAcqToBufThruCab &operator=(const SapAcqToBufThruCab &xfer);

	// Creation/destruction
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
	SapXferCallback	GetCallback() const { return m_pDstXfer->GetCallback(); }
	void					*GetContext() const { return m_pDstXfer->GetContext(); }

	BOOL	IsGrabbing() const { return m_pSrcXfer->IsGrabbing() && m_pDstXfer->IsGrabbing(); }

	BOOL				IsAutoEmpty() const        { return m_pDstXfer->IsAutoEmpty(); }
	virtual void	SetAutoEmpty(BOOL bValue)	{ m_pDstXfer->SetAutoEmpty(bValue); }

	// Transfer Control
	virtual BOOL Snap(int count = 1);
	virtual BOOL Grab();
	virtual BOOL Freeze();
	virtual BOOL Abort();
	virtual BOOL Wait(int timeout);
	virtual BOOL Init(BOOL bResetIndex = TRUE);

protected:
   void Construct(SapAcquisition *pAcq, SapCab *pSrcCab, int srcPort, SapCab *pDstCab, int dstPort, SapBuffer *pBuf, SapXferCallback pCallback, void *pContext);

protected:
	SapTransfer *m_pSrcXfer;
	SapCab		*m_pSrcCab;
	SapTransfer *m_pDstXfer;
	SapCab		*m_pDstCab;
	BOOL			m_bDeleteCab;
}; 

#endif	// _SAPACQTOBUFTHRUCAB_H_

