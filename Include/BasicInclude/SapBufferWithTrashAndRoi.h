#ifndef _SAPBUFFER_WITH_TRASH_AND_ROI_H_
#define _SAPBUFFER_WITH_TRASH_AND_ROI_H_

//	SapBufferWithTrashAndRoi.h : header file
//

#include "SapClassBasicDef.h"

#define SAPBUFFER_MAX_ROI	256

//
// SapRoi class declaration
//
class SAPCLASSBASIC_CLASS SapRoi
{
public:
   SapRoi() { memset(this, 0, sizeof(SapRoi)); }

public:
	RECT m_Rect;
	CORBUFFER *m_pChildren;
};

//
// SapBufferWithTrash class declaration
//
class SAPCLASSBASIC_CLASS SapBufferWithTrashAndRoi : public SapBufferWithTrash
{
public:
	// Constructor/Destructor
	SapBufferWithTrashAndRoi(int count = SapDefBufferCount, int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
	SapBufferWithTrashAndRoi(int count, SapXferNode *pSrcNode, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
	SapBufferWithTrashAndRoi(const char *filename, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrashAndRoi(const SapBuffer &buf);
	virtual ~SapBufferWithTrashAndRoi();

   SapBufferWithTrashAndRoi &operator= (const SapBuffer &buf);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
	virtual int GetNumRoi() const { return m_NumRoi; }
	virtual const LPRECT GetRoi(int index) const;
	virtual CORBUFFER GetChild(int roiIndex, int bufIndex) const;

	// Operations
	virtual BOOL AddRoi(RECT roi);
	virtual BOOL RemoveAllRoi();

protected:
   // Utility methods
   virtual void Construct();
	virtual BOOL CreateChildren();
	virtual BOOL DestroyChildren();

protected:
	int m_NumRoi;
	SapRoi m_Roi[SAPBUFFER_MAX_ROI];					// Table of ROIs
}; 

#endif	// _SAPBUFFER_WITH_TRASH_AND_ROI_H_

