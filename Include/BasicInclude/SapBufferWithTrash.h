#ifndef _SAPBUFFER_WITH_TRASH_H_
#define _SAPBUFFER_WITH_TRASH_H_

//	SapBufferWithTrash.h : header file
//

#include "SapClassBasicDef.h"

//
// SapBufferWithTrash class declaration
//
class SAPCLASSBASIC_CLASS SapBufferWithTrash : public SapBuffer
{
public:
   // Constructor/Destructor
   SapBufferWithTrash(int count = 2, int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrash(int count, ULONG_PTR physAddress[], int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = TypeContiguous);
   SapBufferWithTrash(int count, void *virtAddress[], int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = TypeScatterGather);
   SapBufferWithTrash(int count, SapXferNode *pSrcNode, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrash(const char *filename, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrash(int count, const char *bufName, int width = SapDefWidth, int height = SapDefHeight, SapFormat format = SapDefFormat, Type type = TypeScatterGather, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrash(int count, const char *bufName, SapXferNode *pSrcNode, Type type = SapDefBufferType, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrash(const char *bufName, int startIndex, int count, Type type= TypeVirtual, SapLocation loc = SapLocation::ServerSystem);
   SapBufferWithTrash(const SapBuffer &buf);
   virtual ~SapBufferWithTrash();

   SapBufferWithTrash &operator= (const SapBuffer &buf);

   // Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

	// Access to implementation
	virtual CORBUFFER GetTrash() const { return m_hTrash; }

   virtual Type GetTrashType() { return m_TrashType;}
   virtual BOOL SetTrashType(Type type);

protected:
   // Utility methods
   virtual void Construct();

protected:
   CORBUFFER m_hTrash;     // Trash buffer handle
   Type      m_TrashType;  // Trash buffer type
}; 

#endif	// _SAPBUFFER_WITH_TRASH_H_

