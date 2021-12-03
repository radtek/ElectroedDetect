#ifndef _SAPMULTIACQTOBUFTHRUCAB_H_
#define _SAPMULTIACQTOBUFTHRUCAB_H_

//	SapAcqToBufThruCab.h : header file
//

#include "SapClassBasicDef.h"

//
// SapAcqToBufThruCab class declaration
//
class SAPCLASSBASIC_CLASS SapMultiAcqToBufThruCab : public SapTransfer
{
public:
	// Constructor/Destructor
	SapMultiAcqToBufThruCab(SapAcquisition *pAcq[], SapBuffer *pBuf[], int nPair, SapXferCallback pCallback = NULL, void *pContext = NULL);
	SapMultiAcqToBufThruCab(SapAcquisition *pAcq[], SapCab *pSrcCab, SapCab *pDstCab, SapBuffer *pBuf[], int nPair, SapXferCallback pCallback = NULL, void *pContext = NULL);
	SapMultiAcqToBufThruCab(const SapMultiAcqToBufThruCab &xfer);
	virtual ~SapMultiAcqToBufThruCab();

	SapMultiAcqToBufThruCab &operator=(const SapMultiAcqToBufThruCab &xfer);

	// Creation/destruction
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
	SapXferCallback	GetCallback()	const { return m_pDstXfer->GetCallback(); }
	void					*GetContext()	const { return m_pDstXfer->GetContext(); }

	BOOL	IsGrabbing()	const { return m_pSrcXfer->IsGrabbing() && m_pDstXfer->IsGrabbing(); }

	BOOL				IsAutoEmpty()					const { return m_pDstXfer->IsAutoEmpty(); }
	virtual void	SetAutoEmpty(BOOL bValue)	{ m_pDstXfer->SetAutoEmpty(bValue); }

	// Transfer Control
	virtual BOOL Snap(int count = 1);
	virtual BOOL Grab();
	virtual BOOL Freeze();
	virtual BOOL Abort();
	virtual BOOL Wait(int timeout);
	virtual BOOL Init(BOOL bResetIndex = TRUE);

protected:
   void Construct(SapAcquisition *pAcq[], SapCab *pSrcCab, SapCab *pDstCab, SapBuffer *pBuf[], int nPair, SapXferCallback pCallback, void *pContext);

protected:
	SapTransfer *m_pSrcXfer;
	SapCab		*m_pSrcCab;
	SapTransfer *m_pDstXfer;
	SapCab		*m_pDstCab;
	BOOL			m_bDeleteCab;
}; 

#endif	// _SAPMULTIACQTOBUFTHRUCAB_H_

