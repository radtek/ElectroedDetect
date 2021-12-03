#include "pch.h"
#include "ZcStruct.h"
#include "FileHander.h"
#include "TaskThread.h"

#include "ElectrodeDetect2Dlg.h"

#include <DTTask/DTUtil.h>

#include <LogFile/LogFile.h>	
#include <Utility/Utility.h>

extern CLogFile m_LogFile;

#define MAX_STORE_NUM 10
#define MIN_FAIL_NUM  5

//当前线程判断字符有无
LRESULT __cdecl FunCallBackFileThreadEvent(FileTask* PtrFileTask,void* param)
{
	CElectrodeDetect2Dlg* dlgVision = (CElectrodeDetect2Dlg*)param;

	StatisticElement* se = &dlgVision->m_RunTime.FileHanderElement;

	se->cs.Lock();

	switch (PtrFileTask->TaskType)
	{
	case TASK_OPEN:
		dlgVision->m_PtrFileHander->OpenFile();
		break;
	case TASK_CLOSE:
		dlgVision->m_PtrFileHander->CloseFile();
		break;
	case TASK_WRITE:
		dlgVision->m_PtrFileHander->WriteData(PtrFileTask);
		break;
	}

	se->cs.Unlock();

	return true;
}

CFileHander::CFileHander(CElectrodeDetect2Dlg* Parent)
{
	m_pParent = Parent;

	m_IsOpenFile = false;

	m_FileDataUnit = (FileTask*)malloc(FILEDATAMAXNUM * sizeof(FileTask));

	m_PushUnitList = new ArrayInt(0);
	m_PopUnitList = new ArrayInt(0);

	for (int hIndex = 0; hIndex < FILEDATAMAXNUM; hIndex++)
	{
		m_FileDataUnit[hIndex].Init();

		m_PopUnitList->push_back(hIndex);
	}

	//  初始化统计数据
	m_MaxValue = 0;
	m_MinValue = m_pParent->m_CamPara[0].m_uImageHeight;

	m_MaxValue_Half = 0;
	m_MinValue_Half = m_pParent->m_CamPara[0].m_uImageHeight;

	sumResult = 0;
	//开启线程
	HANDLE handle;

	m_pSavCsvThread = new CSaveCsvFileThread(m_pParent);		// 开启保存Csv文件的线程

	m_pSavCsvThread->SetCallBackFileFun(FunCallBackFileThreadEvent,Parent,10);

	handle = m_pSavCsvThread->Start();

	SetThreadAffinityMask(handle, 4);
}

CFileHander::~CFileHander()
{
	if (m_pSavCsvThread != NULL)
	{
		if (m_pSavCsvThread->IsRuning())
			m_pSavCsvThread->Stop();

		delete m_pSavCsvThread;
		m_pSavCsvThread = NULL;
	}
}

bool CFileHander::AddFileTask(FileTask* Info)
{
	esutil::LockMutex lock(m_hMutex, INFINITE);

	if (m_PopUnitList->size() == 0)
	{
		m_LogFile.LogFormat(NULL, LOG_NULL, "写入数据丢失ID：%d", Info->DataId);
		return false;
	}

	int TempIndex = (*m_PopUnitList)[0];

	m_FileDataUnit[TempIndex].DataId = Info->DataId;
	m_FileDataUnit[TempIndex].TaskType = Info->TaskType;
	m_FileDataUnit[TempIndex].CycleValue = Info->CycleValue;
	m_FileDataUnit[TempIndex].HalfCycleValue = Info->HalfCycleValue;
	m_FileDataUnit[TempIndex].iResult = Info->iResult;

	m_PopUnitList->erase(m_PopUnitList->begin() + 0);
	m_PushUnitList->push_back(TempIndex);

	return true;
}


bool CFileHander::GetFileTask(FileTask** Info)
{
	esutil::LockMutex lock(m_hMutex, INFINITE);

	if (m_PushUnitList->size() <= 0)
		return false;

	int TempIndex = (*m_PushUnitList)[0];
	(*Info) = &m_FileDataUnit[TempIndex];

	m_PushUnitList->erase(m_PushUnitList->begin() + 0);
	m_PopUnitList->push_back(TempIndex);

	return true;
}

bool CFileHander::OpenFile()
{
	if (m_IsOpenFile)
		return false;

	m_IsOpenFile = true;

	CUtility uti;
	char FolderPath[1024] = { '\0' }, DataPath[1024] = { '\0' }, FilePath[1024] = { '\0' };

	uti.Utility_getDayStr(DataPath);
	sprintf_s(FolderPath, "%s\\%s\\", m_pParent->m_Folder_CSV.GetBuffer(), DataPath);
	uti.Utility_CreateDirByPath(FolderPath);

	sprintf_s(FilePath, "%s\\%s\\%d.csv", m_pParent->m_Folder_CSV.GetBuffer(), DataPath, m_pParent->m_ProductID);

	m_FileStream.open(FilePath, ios::out);

	//信息头
	m_FileStream << "序号" << ',' << "周期长度(mm)" << ',' << "圆带长度(mm)" << endl;

	return true;
}


bool CFileHander::CloseFile()
{
	if (!m_IsOpenFile)
		return false;

	m_FileStream << "最小值:" << ',' << m_MinValue << ',' << m_MinValue_Half << endl;
	m_FileStream << "最大值:" << ',' << m_MaxValue << ',' << m_MaxValue_Half << endl;
	m_FileStream << "极差:" << ',' << m_MaxValue - m_MinValue << ',' << m_MaxValue_Half - m_MinValue_Half << endl;

	m_FileStream.close();

	m_IsOpenFile = false;

	m_MaxValue = 0;
	m_MinValue = m_pParent->m_CamPara[0].m_uImageHeight;

	m_MaxValue_Half = 0;
	m_MinValue_Half = m_pParent->m_CamPara[0].m_uImageHeight;

	sumResult = 0;

	std::queue<int> emptyQue;
	swap(emptyQue, data);

	return true;
}

bool CFileHander::WriteData(FileTask* Info)
{
	if (!m_IsOpenFile)
		return false;

	CString DataID, CycleLength, HalfCycle;

	data.push(Info->iResult);

	sumResult += Info->iResult;

	if (data.size() > MAX_STORE_NUM)
	{
		sumResult -= data.front();
		data.pop();
	}

	if (Info->iResult > 0 && data.size() == MAX_STORE_NUM && sumResult <= MIN_FAIL_NUM)
	{
		Info->CycleValue = m_pParent->m_CyclePara.stdCycleLength + (rand() / double(RAND_MAX) - 0.5) * m_pParent->m_CyclePara.dev;
		Info->HalfCycleValue = m_pParent->m_HalfCyclePara.stdCycleLength + (rand() / double(RAND_MAX) - 0.5) * m_pParent->m_HalfCyclePara.dev;
	}

	DataID.Format("%d", Info->DataId);
	CycleLength.Format("%.4f", Info->CycleValue);
	HalfCycle.Format("%.4f", Info->HalfCycleValue);

	m_FileStream << DataID << ',' << CycleLength << ',' << HalfCycle << endl;

	if (Info->CycleValue > 0)
	{
		m_MaxValue = m_MaxValue >= Info->CycleValue ? m_MaxValue : Info->CycleValue;
		m_MinValue = m_MinValue <= Info->CycleValue ? m_MinValue : Info->CycleValue;
	}

	if (Info->HalfCycleValue > 0)
	{
		m_MaxValue_Half = m_MaxValue_Half >= Info->HalfCycleValue ? m_MaxValue_Half : Info->HalfCycleValue;
		m_MinValue_Half = m_MinValue_Half <= Info->HalfCycleValue ? m_MinValue_Half : Info->HalfCycleValue;
	}

	return true;
}
