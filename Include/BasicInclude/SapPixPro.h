#ifndef _SAPPIXPRO_H_
#define _SAPPIXPRO_H_

//	SapPixPro.h : header file
//

#include "SapClassBasicDef.h"
#include "design.h"

//
// SapPixProParams class declaration
//
class SAPCLASSBASIC_CLASS SapPixProParams
{
public:
	SapPixProParams() 
      { memset(this, 0, sizeof(SapPixProParams)); m_FunctionIndex = -1; }
	~SapPixProParams() {}

	int GetFunctionIndex()     const { return m_FunctionIndex; }
	int GetConfigIndex()       const { return m_ConfigIndex; }
	int GetBankId()            const { return m_BankId; }
	BOOL GetRefImage()         const { return m_bRefImage; }
	int GetWeightingFactor()   const { return m_WeightingFactor; }
	int GetIntegrateCount()    const { return m_IntegrateCount; }
	int GetIntegrateFactor()   const { return m_IntegrateFactor; }

	void SetFunctionIndex(int index)    { m_FunctionIndex = index; }
	void SetConfigIndex(int index)      { m_ConfigIndex = index; }
	void SetBankId(int bankId)          { m_BankId = bankId; }
	void SetRefImage(BOOL isRefImage)   { m_bRefImage = isRefImage; }
	void SetWeightingFactor(int factor) { m_WeightingFactor = factor; }
	void SetIntegrateCount(int count)   { m_IntegrateCount = count; }
	void SetIntegrateFactor(int factor) { m_IntegrateFactor = factor; }

protected:
	int m_FunctionIndex;
	int m_ConfigIndex;
	int m_BankId;
	BOOL m_bRefImage;
	int m_WeightingFactor;
	int m_IntegrateCount;
	int m_IntegrateFactor;
};

//
// SapPixPro class declaration
//
class SAPCLASSBASIC_CLASS SapPixPro : public SapXferNode
{
   // Maximum length of name strings
   enum MaxValues
   {
      MaxFuncNameSize = 64,
      MaxConfigNameSize = 64
   };

public:
	// Constructor/Destructor
	SapPixPro(SapLocation loc = SapLocation::ServerSystem, const char *fileName = "", SapXferNode *pSrcNode = NULL, SapPixProParams *pParams = NULL);
	SapPixPro(SapLocation loc, const char *fileName, SapXferParams xferParams, SapPixProParams *pParams = NULL);
	SapPixPro(const SapPixPro &pixpro);
	virtual ~SapPixPro();

	SapPixPro &operator=(const SapPixPro &pixpro);

   // SapXferNode type information
   XferNodeType GetXferNodeType() { return NodeTypePixPro; }

   // Access to implementation
	const char *GetFile() const { return m_FileName; }
	virtual BOOL SetFile( const char *fileName);

	const SapPixProParams *GetParams() const { return &m_Params; }
	virtual BOOL SetParams(const SapPixProParams *pParams);

	virtual SapXferParams GetOutputXferParams(int portIndex = 0) const;
	virtual BOOL SetOutputXferParams(SapXferParams params, int portIndex = 0);

   // Direct capability/parameter access
   virtual BOOL GetCapability(int cap, void *pValue);
   virtual BOOL GetParameter(int param, void *pValue);
   virtual BOOL SetParameter(int param, int value);
   virtual BOOL SetParameter(int param, void *pValue);

	BOOL ReadDesign(char *fileName);
	int GetNumFunctions();
	int GetNumConfigs();

   // Note: nameSize argument is now obsolete
	BOOL GetFunctionInfo(int index, PCORPPL_FCT_PROP pFuncProp, char *funcName, int nameSize = MaxFuncNameSize);
	BOOL GetConfigInfo(int index, char *configName, int nameSize = MaxConfigNameSize);

	// Module create/destroy
	virtual BOOL Create();
	virtual BOOL Destroy();

protected:
	virtual BOOL ProgramConfig();
	virtual BOOL ProgramFunction();
   virtual BOOL SetAcqSnapCount(int snapCount);
   virtual BOOL UpdateOutputXferParams();

protected:
	char					m_FileName[MAX_PATH];
	SapPixProParams	m_Params;
	SapXferParams		m_OutputXferParams;
	static char			m_LastFileName[MAX_PATH];
	static char *		m_FunctionNames[CORPPL_FCT_LAST + 1];
}; 

#endif	// _SAPPIXPRO_H_

