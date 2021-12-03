#pragma once

#include "ZCStruct.h"

#include <iostream>
#include <fstream>
#include <queue>

class CElectrodeDetect2Dlg;
class CSaveCsvFileThread;

class CFileHander
{
public:
	CFileHander(CElectrodeDetect2Dlg* Parent);
	~CFileHander();

	HANDLE m_hMutex;

	bool AddFileTask(FileTask* Info);
	bool GetFileTask(FileTask** Info);

	bool OpenFile();
	bool CloseFile();

	bool WriteData(FileTask* Info);

	bool           m_IsOpenFile;

	ofstream       m_FileStream;

public:
	CElectrodeDetect2Dlg* m_pParent;

	FileTask* m_FileDataUnit;
	CSaveCsvFileThread* m_pSavCsvThread;

	ArrayInt* m_PushUnitList;
	ArrayInt* m_PopUnitList;

	float  m_MaxValue;
	float  m_MinValue;

	float  m_MaxValue_Half;
	float  m_MinValue_Half;

	std::queue<int> data;
	int sumResult;
};
