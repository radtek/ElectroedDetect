#ifndef _SAPBUFFERREMOTE_H_
#define _SAPBUFFERREMOTE_H_

//	SapBufferRemote.h : header file
//

#include "SapClassBasicDef.h"

//
// SapBufferRemote class declaration
//
class SAPCLASSBASIC_CLASS SapBufferRemote : public SapBuffer
{
public:
	// Constructor/Destructor
	SapBufferRemote(SapLocation loc, const char *name, int startIndex = 0, int count = 1);
   SapBufferRemote(const SapBufferRemote &buf);
	virtual ~SapBufferRemote();

   SapBufferRemote &operator= (const SapBufferRemote &buf);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

protected:
	// Utility
	virtual BOOL UpdateParameters();

protected:
	char m_Name[CORHANDLE_MAX_STRLEN];
	int m_StartIndex;
}; 

#endif	// _SAPBUFFERREMOTE_H_

