#pragma once

#include "ZcStruct.h"

class CElectrodeDetect2Dlg;
class CPollingThread;

class CDelImgHander
{
public:
	CDelImgHander(CElectrodeDetect2Dlg* Parent,int TimeInterval);
	~CDelImgHander();

public:
	CElectrodeDetect2Dlg* m_pParent;
	CPollingThread* m_pThread;

};