#include "pch.h"
#include "DelImgHander.h"

#include "ElectrodeDetect2Dlg.h"
#include "TaskThread.h"

LRESULT __cdecl FunCallBackDelImgThread(void* param)
{
	CDelImgHander* handle = (CDelImgHander*)param;

	bool flag = true;
	CElectrodeDetect2Dlg* Parent = handle->m_pParent;

	while (flag)
	{
		Parent->LoadDiskVolume("D");	// 获取D盘空间
		if (Parent->m_Disk_Prop > Parent->m_Disk_Input_Prop)							// 判断硬盘剩余容量占比是否是手动输入占比-10%更大
		{
			Parent->TravelFolder(Parent->m_strSaveImagePath.GetBuffer());				// 遍历并找出日期最早的图片文件夹
			Parent->DelFolderByPath(Parent->m_FirstDelImgFolderPath.GetBuffer());
			int a = 1;
		}
		else
		{
			flag = false;
		}
	}
	Parent->LoadDiskVolume("D");	// 刷新D盘空间

	return true;
}

CDelImgHander::CDelImgHander(CElectrodeDetect2Dlg* Parent,int TimeInterval)
{
	m_pParent = Parent;

	// 实例化线程对象
	m_pThread = new CPollingThread();
	// 设置线程启动后执行的回调函数
	m_pThread->SetCallBackFun(FunCallBackDelImgThread,this, TimeInterval);

	HANDLE handle;
	handle = m_pThread->Start();
}

CDelImgHander::~CDelImgHander()
{
	// 停止线程
	if (m_pThread->IsRuning())
		m_pThread->Stop();

	// 释放线程的内存空间
	delete m_pThread;
	m_pThread = NULL;
}