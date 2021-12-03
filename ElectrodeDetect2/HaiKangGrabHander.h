#ifndef _GRABHAIKANG_HANDER_H_
#define _GRABHAIKANG_HANDER_H_

#include "CameraPara.h"						// 相机参数
#include <HaiKangCamLib/HaiKangCamLib.h>

class CHaiKangGrabHander : public CHaiKangCameraGrab
{
public:
	CHaiKangGrabHander(int cameraIndex,CameraGrabPara* dGrabPara,void* dlgDetection);
	~CHaiKangGrabHander();

public:
	int m_cameraIndex;

	int  m_cameraStatus;		// 0为相机打开失败，1为打开成功，2为开始采集，3为停止采集，4为相机关闭成功

	bool m_ExitFlag;

	void* m_dlgDetection;		// 父窗口

	void SetTriModeOn();
};

#endif//_GRABHAIKANG_HANDER_H_

