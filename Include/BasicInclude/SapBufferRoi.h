#ifndef _SAPBUFFER_ROI_H_
#define _SAPBUFFER_ROI_H_

//	SapBufferRoi.h : header file
//

#include "SapClassBasicDef.h"

//
// SapBufferRoi class declaration
//
class SAPCLASSBASIC_CLASS SapBufferRoi : public SapBuffer
{
public:
	// Constructor/Destructor
	SapBufferRoi(SapBuffer *pParent, int xmin=0, int ymin=0, int width=-1, int height=-1);
	virtual ~SapBufferRoi();

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
   SapBuffer *GetParent() { return m_pParent; }
   SapBuffer *GetRoot();

   virtual CORBUFFER GetTrash() const { return m_hTrashChild; }

   int GetXMin() const { return m_XMin; }
   int GetYMin() const { return m_YMin; }

   virtual BOOL SetParent(SapBuffer *pParent);
	virtual BOOL SetXMin(int xmin);
	virtual BOOL SetYMin(int ymin);
	virtual BOOL SetParametersFromFile(const char *filename, Type type) { return FALSE; }

	virtual BOOL SetRoi(int xmin, int ymin, int width, int height);
   virtual BOOL SetRoi(RECT *pRect);
	virtual BOOL ResetRoi();

protected:
   SapBuffer *m_pParent;
   CORBUFFER m_hTrashChild;   // Child buffer for trash

	int m_XMin;	   // Minimum X position
	int m_YMin;		// Minimum Y position
}; 

#endif	// _SAPBUFFER_ROI_H_
