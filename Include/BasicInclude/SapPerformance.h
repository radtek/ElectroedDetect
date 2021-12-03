#ifndef _SAPPERFORMANCE_H_
#define _SAPPERFORMANCE_H_

//	SapPerformance.h : header file
//

#include "SapClassBasicDef.h"


class SAPCLASSBASIC_CLASS SapPerformance
{
public:
	SapPerformance();
	void Reset();
	float GetTime(BOOL bReset)			{ return ComputeTime(bReset) * 1.0f; }
	float GetTimeMilli(BOOL bReset)	{ return ComputeTime(bReset) * 1000.0f; }
	float GetTimeMicro(BOOL bReset)	{ return ComputeTime(bReset) * 1000000.0f; }

protected:
	float ComputeTime(BOOL bReset);

protected:
	LONGLONG m_CounterFrequency;
	LONGLONG m_ResetTime;
};

#endif	// _SAPPERFORMANCE_H_

