/************************************************************************
   T h e   O p e n   W i n d o w s   P r o j e c t
 ------------------------------------------------------------------------
   Filename   : IniFile.h
   Author(s)  : Carsten Breuer
 ------------------------------------------------------------------------
 Copyright (c) 2000 by Carsten Breuer (CBreuer@openwin.de)
/************************************************************************/

#ifndef INIFILE_H
#define INIFILE_H

#ifndef OWP_DONT_DEF_CCHR
#ifndef CCHR
#define CCHR const char
#endif
#endif

#ifndef OWP_DONT_DEF_UCHR
#ifndef UCHR
#define UCHR unsigned char
#endif
#endif

#ifndef OWP_DONT_DEF_UCCHR
#ifndef UCCHR
#define UCCHR const unsigned char
#endif
#endif

#ifdef LINUX /* Remove CR, on unix systems. */
#define INI_REMOVE_CR
#define DONT_HAVE_STRUPR
#endif

#define tpNULL       0
#define tpSECTION    1
#define tpKEYVALUE   2
#define tpCOMMENT    3

struct ENTRY
{
   char   Type;
   char  *pText;
   struct ENTRY *pPrev;
   struct ENTRY *pNext;
};

typedef struct
{
   struct ENTRY *pSec;
   struct ENTRY *pKey;
   char          KeyText [128];
   char          ValText [4098];
   char          Comment [512];
} EFIND;

#include "Public.h"
/* Macros */
#define ArePtrValid(Sec,Key,Val) ((Sec!=NULL)&&(Key!=NULL)&&(Val!=NULL))

class __declspec(dllexport) CIniFile
{
public:
            CIniFile    (void);
            ~CIniFile   (void);
    UINT    GetVersion  (void);
    BOOL    OpenIniFile (CCHR *pFileName);

    BOOL    ReadFileBool    (CCHR *pSection, CCHR *pKey, BOOL   Default = FALSE);
    int     ReadFileInt     (CCHR *pSection, CCHR *pKey, int    Default = 0);
	float   ReadFileFloat   (CCHR *pSection, CCHR *pKey, float  Default = 0.0);
    double  ReadFileDouble  (CCHR *pSection, CCHR *pKey, double Default = 0.0);
    CCHR    *ReadFileString (CCHR *pSection, CCHR *pKey, CCHR  *pDefault = "");
	void ReadFileFloatArray(CCHR *pSection, CCHR *pKey, float* valueArray, int arrayNum);

    void    WriteFileBool   (CCHR *pSection, CCHR *pKey, BOOL   Value);
    void    WriteFileInt    (CCHR *pSection, CCHR *pKey, int    Value);
	void    WriteFileFloat (CCHR *pSection, CCHR *pKey, float Value);
    void    WriteFileDouble (CCHR *pSection, CCHR *pKey, double Value);
    void    WriteFileString (CCHR *pSection, CCHR *pKey, CCHR  *pValue);

	void WriteFileFloatArray (CCHR *pSection, CCHR *pKey, float* ValueArray, int arrayNum);

    void    CloseIniFile ();
    bool    WriteIniFile (CCHR *pFileName);
	bool	DeleteKey (CCHR *pSection, CCHR *pKey);

protected:
	struct  ENTRY *m_pEntry;
	struct  ENTRY *m_pCurEntry;
	char    m_result [4096];
	FILE    *m_pIniFile;
	void    AddKey     (struct ENTRY *pEntry, CCHR *pKey, CCHR *pValue);
	BOOL    AddItem    (char Type, CCHR *pText);
	bool    AddItemAt (struct ENTRY *pEntryAt, char Mode, CCHR *pText);
	void    FreeMem    (void *pPtr);
	void    FreeAllMem (void);
	bool    FindKey    (CCHR *pSection, CCHR *pKey, EFIND *pList);
	bool    AddSectionAndKey (CCHR *pSection, CCHR *pKey, CCHR *pValue);
	struct  ENTRY *MakeNewEntry (void);
	struct  ENTRY *FindSection (CCHR *pSection);
};

#endif


