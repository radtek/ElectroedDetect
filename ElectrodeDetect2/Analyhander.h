#pragma once

#include "ZcStruct.h"

class CElectrodeDetect2Dlg;
class CPollingThread;

class CAnalyHander
{
public:
	CAnalyHander(int CameraIndex, CElectrodeDetect2Dlg* Parent);
	~CAnalyHander();
public:
	CElectrodeDetect2Dlg* m_pParent;
	CPollingThread* m_pThread;

	int m_CameraIndex;
	bool m_DetectResult;

	// 专属于Dalsa相机采集的图片的周期、圆带长度
	float m_CycleDistance;
	float m_HalfCycleDistance;

	std::queue<AnalyTask> m_Task;			// 队列，头出为进

	bool AddImageTask(AnalyTask* Task);
	bool IsQueueEmpty();
	bool GetImageTask(AnalyTask* Task);
	bool AddWriteTask(AnalyTask* PtrAnalyTask, CElectrodeDetect2Dlg* dlgVision);
};