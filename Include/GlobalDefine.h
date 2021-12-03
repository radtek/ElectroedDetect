//宏定义文件---定义公用的宏
#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_

#include "afxmt.h"
#include "Public.h"
#include "CameraPara.h"

#define COLOR_BACKGROUND_TITLE RGB(10,10,10)
#define COLOR_TEXT_TITLE RGB(14,230,255)
#define COLOR_TEXT_WHITE RGB(255,255,255)
#define COLOR_TEXT_GREEN RGB(66,200,90)

#define COLOR_TEXT_OK RGB(40,235,75)
#define COLOR_TEXT_NG RGB(250,70,70)
#define COLOR_TEXT_BLACK RGB(10,10,10)

#define COLOR_BACKGROUND_OK RGB(37,57,41)
#define COLOR_BACKGROUND_NG RGB(58,39,39)

#define COLOR_BACKGROUND_SET RGB(240,240,240)
#define COLOR_BACKGROUND_SET_MENU RGB(200,200,200)
#define COLOR_DETBACKGROUND_SET_MENU RGB(50,49,48)
#define COLOR_DETBACKGROUND RGB(0,0,0)

#define COLOR_BACKGROUND_SUB_REGION RGB(30,30,30)
#define COLOR_BORDER_SUB_REGION RGB(60,60,60)

#define COLOR_BACKGROUND_SUB_REGION_2 RGB(37,37,37)
#define COLOR_BACKGROUND_MAIN RGB(42,42,42)

#define COLOR_BUTTON_OVER_QUIT RGB(232,17,35)
#define COLOR_BUTTON_CLICK_QUIT RGB(243,112,120)

#define COLOR_BUTTON_OVER RGB(170,170,170)
#define COLOR_SETBUTTON_OVER RGB(142,169,219)
#define COLOR_BUTTON_CLICK RGB(140,140,140)
#define COLOR_SETBUTTON_CLICK RGB(68,114,196)

// 父窗口和子窗口中按钮的颜色
#define COLOR_BUTTON_PARENT RGB(50,49,48)
#define COLOR_BUTTON_CHILD RGB(0,0,0)

//定义所有的统计信息
typedef struct tagStatisticElement
{
	UINT dwSumCount;         //获得的信号总数
	UINT dwUsedTimeSum;      //获得的耗时总数

	UINT dwMinTime;          //单次最小时间
	UINT dwMaxTime;

	UINT nMinLimitTime;      //统计的最小时间和最大时间界限
	UINT nMaxLimitTime;
	UINT nMinLimitCount;
	UINT nMaxLimitCount;

	UINT dwStart;

	CCriticalSection cs;

	char m_szMsg[MAX_FILE];

	void Init()
	{
		dwSumCount = 0; dwUsedTimeSum = 0;
		dwMinTime = 100000;
		dwMaxTime = 0;  dwStart = 0;

		nMinLimitTime = 30; nMaxLimitCount = 100;
		nMinLimitCount = nMaxLimitCount = 0;

		memset(m_szMsg, '\0', MAX_FILE);
	}

	void Start()
	{
		dwStart = GetTickCount64();
	}

	void Stop()
	{
		UINT dwTime;

		cs.Lock();

		dwTime = GetTickCount64() - dwStart;

		dwSumCount++;
		dwUsedTimeSum += dwTime;

		if(dwTime < nMinLimitTime)
			nMinLimitCount++;

		if(dwTime > nMaxLimitTime)
			nMaxLimitCount++;

		if(dwTime > dwMaxTime)
			dwMaxTime = dwTime;

		if(dwTime < dwMinTime)
			dwMinTime = dwTime;

		cs.Unlock();		
	}
}StatisticElement;

//typedef enum RunTimeEnum {seAnalyse1, seAnalyse2,seAnalyse3,seAnalyse4,seAnalyse5, seDisplay, seIOControl};
//
//#define  RUNTIMESTATUS    9
//所有检测软件的统计信息实时显示
typedef struct tagRunTimeElement
{
	//统计各个相机的采集时间
	StatisticElement GrabElement[2];
	//统计各个相机的分析时间
	StatisticElement AnalyElement[2];
	//统计各个相机的显示时间
	StatisticElement DisplayElement[2];
	StatisticElement SaveElement[2];
	StatisticElement ModbusElement;
	//统计各个相机的IO信号时间
	StatisticElement ControlElement;

	StatisticElement LocalClientElement;

	StatisticElement FileHanderElement;
	//统计所有的处理信息
	int dwRGBLostCount[CAMERANUM];	   //RGB转换丢帧数
	int dwAnalyLostCount[CAMERANUM];   //分析队列丢帧数	
	int dwSaveLostCount[CAMERANUM];    //保存图片丢帧数

	int dwAnalyGood[CAMERANUM];       //分析正常数目
	int dwAnalyseNG[CAMERANUM];       //分析次品数目

	int dwLaterAnalyCount[CAMERANUM]; //分析不及时数目

	int dwExceptionCount[CAMERANUM];  //异常模式发生的异常个数

	void Init()
	{
		AnalyElement[0].Init();    AnalyElement[1].Init();

		GrabElement[0].Init();     GrabElement[2].Init();

		DisplayElement[0].Init();  DisplayElement[2].Init();

		SaveElement[0].Init();     SaveElement[2].Init();

		ModbusElement.Init(); FileHanderElement.Init();

		ControlElement.Init();

		for (int hIndex = 0; hIndex < CAMERANUM; hIndex++)
		{
			dwRGBLostCount[hIndex] = 0;
			dwAnalyLostCount[hIndex] = 0;
			dwSaveLostCount[hIndex] = 0;

			dwAnalyGood[hIndex] = dwAnalyseNG[hIndex] = 0;

			dwLaterAnalyCount[hIndex] = 0;

			dwExceptionCount[hIndex] = 0;
		}
	}
}RunTimeElement;


#endif  //_GLOBAL_DEFINE_H_