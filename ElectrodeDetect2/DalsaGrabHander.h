#pragma once

#include "CameraPara.h"
#include <DalsaCamLib/DalsaCamLib.h>

class CElectrodeDetect2Dlg;			// 父窗口

class CDalsaGrabHander : public CDalseCameraGrab
{
public:
	//初始化采集线程
	CDalsaGrabHander(int cameraIndex, CameraGrabPara* dGrabPara, void* dlgDetection);
	~CDalsaGrabHander();

public:

	int m_cameraIndex;

	int  m_cameraStatus;

	bool m_ExitFlag;

	void* m_dlgDetection;

	unsigned char* pTempBuffer;
};