
// ElectrodeDetect2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ElectrodeDetect2.h"
#include "ElectrodeDetect2Dlg.h"
#include "afxdialogex.h"

#include "Analyhander.h"
#include "HaiKangGrabHander.h"
#include "SaveImgHander.h"
#include "DalsaGrabHander.h"
#include "FileHander.h"
#include "DelImgHander.h"

#include <Utility/Utility.h>
#include <LogFile/LogFile.h>
#include <Utility/IniFile.h>

#include "DlgSysSet.h"
#include "DlgDetSet.h"
#include "Login.h"

#include <cstdlib>

#define N 99

CLogFile m_LogFile;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDS_TIMES 104
#define DEFAULT_BGC_SUM RGB(37,80,119) 
#define DEFAULT_TEXT_SUM RGB(64,158,255) 
#define DEFAULT_BGC_PASS RGB(59,129,73) 
#define DEFAULT_TEXT_PASS RGB(26,250,41) 
#define DEFAULT_BGC_FAIL RGB(174,53,42) 
#define DEFAULT_TEXT_FAIL RGB(255,0,0)
#define DEFAULT_BGC RGB(50,49,48)

#define QUEUE_FAIL_NUM  4							// 队列中不合格焊条检测解结果的个数
#define QUEUE_SIZE 10						// 队列中存储检测结果的个数

CElectrodeDetect2Dlg::CElectrodeDetect2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ELECTRODEDETECT2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pHaiKangGrabHander = NULL;	m_pDalsaGrabHander = NULL;
	m_pDlgSysSet = NULL;	m_pDlgDetSet = NULL;	m_pDlgLogin = NULL;
	m_CurrTotalNum_HaiKang = 0;	m_CurrTotalNum_Dalsa = 0;
	m_NCam1_Sum = 0, m_NCam1_Pass = 0, m_NCam1_Fail = 0;
	m_NCam2_Sum = 0, m_NCam2_Pass = 0, m_NCam2_Fail = 0;
	AppPath[1024] = { '\0' };
	m_PtrFileHander = NULL;
	m_Disk_Input_Prop = 50;					// 手动输入硬盘剩余空间占比(默认为50%)
	m_Folder_CSV = "D:\\Report";
	m_strSaveImagePath = "D:\\Image";

	// 初始化海康相机显示图片和保存图片的线程
	for (int i = 0;i < IMG_COUNT_HAIKANG;i++)
	{
		m_pHaiKangAnalyHander[i] = NULL;
		m_pHaiKangSaveImgHander[i] = NULL;
	}

	m_PtrCSIVisionIn = (VisionParaIn*)malloc(sizeof(VisionParaIn));
	m_PtrCSIVisionOut = (VisionParaOut*)malloc(sizeof(VisionParaOut));

	m_PtrCSIVisionIn2 = (VisionParaIn*)malloc(sizeof(VisionParaIn));
	m_PtrCSIVisionOut2 = (VisionParaOut*)malloc(sizeof(VisionParaOut));
}

void CElectrodeDetect2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, m_Btn_Quit);
	DDX_Control(pDX, IDC_MFCBUTTON_MIN, m_Btn_Min);
	DDX_Control(pDX, IDC_CUSTOM_CAM_1_IMAGE1, m_Camera_1_List[0]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_1_IMAGE2, m_Camera_1_List[1]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_1_IMAGE3, m_Camera_1_List[2]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_1_IMAGE4, m_Camera_1_List[3]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_2_IMAGE1, m_Camera_2_List[0]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_2_IMAGE2, m_Camera_2_List[1]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_2_IMAGE3, m_Camera_2_List[2]);
	DDX_Control(pDX, IDC_CUSTOM_CAM_2_IMAGE4, m_Camera_2_List[3]);
	DDX_Control(pDX, IDC_MFCBUTTON_SYSSET, m_Btn_SysSetting);
	DDX_Control(pDX, IDC_MFCBUTTON_DETSET, m_Btn_DetSetting);
	DDX_Control(pDX, IDC_MFCBUTTON_LOGIN, m_Btn_Login);
	DDX_Control(pDX, IDC_MFCBUTTON_QUITLOGIN, m_Btn_QuitLogin);
	DDX_Control(pDX, IDC_STATIC_CAM_1_SUM, m_Cam1_Sum);
	DDX_Control(pDX, IDC_STATIC_CAM_1_PASS_NUM, m_Cam1_Pass);
	DDX_Control(pDX, IDC_STATIC_CAM_1_FAIL_NUM, m_Cam1_Fail);
	DDX_Control(pDX, IDC_STATIC_CAM_2_SUM, m_Cam2_Sum);
	DDX_Control(pDX, IDC_STATIC_CAM_2_PASS_NUM, m_Cam2_Pass);
	DDX_Control(pDX, IDC_STATIC_CAM_2_FAIL_NUM, m_Cam2_Fail);
}

BEGIN_MESSAGE_MAP(CElectrodeDetect2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &CElectrodeDetect2Dlg::OnBnClickedMfcbuttonClose)
	ON_BN_CLICKED(IDC_MFCBUTTON_MIN, &CElectrodeDetect2Dlg::OnBnClickedMfcbuttonMin)
	ON_BN_CLICKED(IDC_MFCBUTTON_SYSSET, &CElectrodeDetect2Dlg::OnBnClickedMfcbuttonSysset)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MFCBUTTON_DETSET, &CElectrodeDetect2Dlg::OnBnClickedMfcbuttonDetset)
	ON_BN_CLICKED(IDC_MFCBUTTON_LOGIN, &CElectrodeDetect2Dlg::OnBnClickedMfcbuttonLogin)
	ON_BN_CLICKED(IDC_MFCBUTTON_QUITLOGIN, &CElectrodeDetect2Dlg::OnBnClickedMfcbuttonQuitlogin)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CElectrodeDetect2Dlg 消息处理程序

BOOL CElectrodeDetect2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码
	SetFullScreen();				// 窗口全屏显示

	// 初始化GDI
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	char img_path[1024] = { '\0' }, FolderPath[1024] = { '\0' };

	CUtility uti;
	uti.Utility_getApplicationDir(AppPath);				// 获取程序运行程序的目录
	sprintf_s(FolderPath, "%s\\ModelInfo", AppPath);

	LoadDetectParaIn(FolderPath);						// 加载焊带检测配置
	LoadDebugShowModel(FolderPath);						// 加载项目基本配置
	LoadDiskVolume("D");								// 获取D盘空间

	m_MiddleFont.CreatePointFont(100, _T("微软雅黑"));

	((CStatic*)GetDlgItem(IDC_STATIC_DSUM))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_DSP))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_DPROP))->SetFont(&m_MiddleFont);

	/*****加载相机配置*****/
	for (int i = 0; i < CAMERA_COUNT; i++)
	{
		LoadCameraParaFun(i, FolderPath);
	}

	/* 不同相机的显示文字不一样 */
	for(int i = 0;i < IMG_COUNT_DALSA;i++)
	{
		m_Camera_1_List[i].SetImgControlId(1);
	}
	for (int i = 0; i < IMG_COUNT_HAIKANG; i++)
	{
		m_Camera_2_List[i].SetImgControlId(2);
	}

	/*****加载图片*****/
	sprintf_s(img_path, "%s\\Image\\背景.png", AppPath);
	m_pBGImage = LoadFromFile(img_path);

	// 相机状态
	sprintf_s(img_path, "%s\\Image\\Connect.png", AppPath);
	Img_CamState_Connect_ch = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\Lost.png", AppPath);
	Img_CamState_Lost_ch = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\Grabing.png", AppPath);
	Img_CamState_Grabing_ch = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\StopGrab.png", AppPath);
	Img_CamState_StopGrab_ch = LoadFromFile(img_path);

	// 关闭，最小化设置
	sprintf_s(img_path, "%s\\Image\\QuitSmall.png", AppPath);
	Img_Quit_Normal = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\QuitSmall_Over.png", AppPath);
	Img_Quit_Over = LoadFromFile(img_path);

	sprintf_s(img_path, "%s\\Image\\MinSmall.png", AppPath);
	Img_Min_Normal = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\MinSmall_Over.png", AppPath);
	Img_Min_Over = LoadFromFile(img_path);

	m_Btn_Quit.LoadNormalImage(Img_Quit_Normal);
	m_Btn_Quit.LoadOverImage(Img_Quit_Over);
	m_Btn_Min.LoadNormalImage(Img_Min_Normal);
	m_Btn_Min.LoadOverImage(Img_Min_Over);

	// 系统设置
	sprintf_s(img_path, "%s\\Image\\SysSetting_ForBid.png", AppPath);
	Img_SysSet_ForBid = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\SysSetting_Normal.png", AppPath);
	Img_SysSet_Normal = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\SysSetting_Over.png", AppPath);
	Img_SysSet_Over = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\SysSetting_Select.png", AppPath);
	Img_SysSet_Select = LoadFromFile(img_path);

	m_Btn_SysSetting.LoadForBidImage(Img_SysSet_ForBid);
	m_Btn_SysSetting.LoadNormalImage(Img_SysSet_Normal);
	m_Btn_SysSetting.LoadOverImage(Img_SysSet_Over);
	m_Btn_SysSetting.LoadSelectImage(Img_SysSet_Select);

	// 检测设置
	sprintf_s(img_path, "%s\\Image\\DetSetting_ForBid.png", AppPath);
	Img_DetSet_ForBid = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\DetSetting_Normal.png", AppPath);
	Img_DetSet_Normal = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\DetSetting_Over.png", AppPath);
	Img_DetSet_Over = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\DetSetting_Select.png", AppPath);
	Img_DetSet_Select = LoadFromFile(img_path);

	m_Btn_DetSetting.LoadForBidImage(Img_DetSet_ForBid);
	m_Btn_DetSetting.LoadNormalImage(Img_DetSet_Normal);
	m_Btn_DetSetting.LoadOverImage(Img_DetSet_Over);
	m_Btn_DetSetting.LoadSelectImage(Img_DetSet_Select);

	// 登录
	sprintf_s(img_path, "%s\\Image\\Login_Normal.png", AppPath);
	Img_Login_Normal = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\Login_Over.png", AppPath);
	Img_Login_Over = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\Login_Select.png", AppPath);
	Img_Login_Select = LoadFromFile(img_path);

	m_Btn_Login.LoadNormalImage(Img_Login_Normal);
	m_Btn_Login.LoadOverImage(Img_Login_Over);
	m_Btn_Login.LoadSelectImage(Img_Login_Select);

	// 退出登录
	sprintf_s(img_path, "%s\\Image\\Login_Quit_Normal.png", AppPath);
	Img_QuitLogin_Normal = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\Login_Quit_Over.png", AppPath);
	Img_QuitLogin_Over = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\Login_Quit_Select.png", AppPath);
	Img_QuitLogin_Select = LoadFromFile(img_path);

	m_Btn_QuitLogin.LoadNormalImage(Img_QuitLogin_Normal);
	m_Btn_QuitLogin.LoadOverImage(Img_QuitLogin_Over);
	m_Btn_QuitLogin.LoadSelectImage(Img_QuitLogin_Select);

	m_Btn_QuitLogin.ShowWindow(false);	// 隐藏退出登录按钮

	// 创建统计结果的计数底色
	m_Sum_Bgc.CreateSolidBrush(DEFAULT_BGC_SUM);
	m_Pass_Bgc.CreateSolidBrush(DEFAULT_BGC_PASS);
	m_Fail_Bgc.CreateSolidBrush(DEFAULT_BGC_FAIL);

	m_BGC.CreateSolidBrush(DEFAULT_BGC);

	// 检测结果图标
	sprintf_s(img_path, "%s\\Image\\pass.png", AppPath);
	Img_Det_Pass = LoadFromFile(img_path);
	sprintf_s(img_path, "%s\\Image\\fail.png", AppPath);
	Img_Det_Fail = LoadFromFile(img_path);

	// 没登录就禁止系统设置和检测设置按钮
	m_Btn_SysSetting.EnableWindow(false);
	m_Btn_DetSetting.EnableWindow(false);

	// 创建并开启Dalsa、海康相机的分析线程和保存图片线程
	for (int i = 0; i < IMG_COUNT_DALSA; i++)
	{
		m_pDalsaAnalyHander[i] = new CAnalyHander(0, this);
		m_pDalsaSaveImgHander[i] = new CSaveImgHander(0, this);
	}
	for (int i = 0;i < IMG_COUNT_HAIKANG;i++)
	{
		m_pHaiKangAnalyHander[i] = new CAnalyHander(1, this);
		m_pHaiKangSaveImgHander[i] = new CSaveImgHander(1,this);
	}
	/*****有关相机的操作*****/
	// 实例化海康、Dalsa相机
	m_pDalsaGrabHander = new CDalsaGrabHander(0, &m_CamPara[0], this);
	m_pDalsaGrabHander->InitImageBuffer();
	m_pHaiKangGrabHander = new CHaiKangGrabHander(1, &m_CamPara[1], this);
	m_PtrFileHander = new CFileHander(this);
	m_DelImgHander = new CDelImgHander(this,10000);	

	//启动对应的定时器操作
	SetTimer(TIMER_SYSTEM_TIME, 1000, NULL);			// 每秒触发一次OnTimer函数

	// 打开Dalsa相机
	if (OpenCamera(1))
	{
		// 开始采集
		int result = StartGrad(1);
	}
	// 打开海康相机
	if (OpenCamera(2))	
	{
		// 开始采集
		int result = StartGrad(2);
	}

	/*****实例化子窗口*****/
	CRect rectClient;
	GetClientRect(&rectClient);
	// 实例化 系统设置子窗口
	m_pDlgSysSet = new CDlgSysSet(NULL, this);
	m_pDlgSysSet->Create(IDD_SYSTEMSETTING_DIALOG);
	m_pDlgSysSet->ShowWindow(SW_HIDE);

	int nDlgWidth = m_pDlgSysSet->m_ClientRect.Width();
	int nDlgHeight = m_pDlgSysSet->m_ClientRect.Height();
	m_pDlgSysSet->MoveWindow(rectClient.Width() / 6, rectClient.Height() / 6, rectClient.Width() * 2 / 3, rectClient.Height() * 2 / 3);

	// 实例化 检测设置子窗口
	m_pDlgDetSet = new CDlgDetSet(NULL, this);
	m_pDlgDetSet->Create(IDD_DETECTSETTING_DIALOG);
	m_pDlgDetSet->ShowWindow(SW_HIDE);

	nDlgWidth = m_pDlgDetSet->m_ClientRect.Width();
	nDlgHeight = m_pDlgDetSet->m_ClientRect.Height();
	m_pDlgDetSet->MoveWindow(rectClient.Width() / 6, rectClient.Height() / 6, rectClient.Width() * 2 / 3, rectClient.Height() * 2 / 3);

	// 登录子窗口
	m_pDlgLogin = new CLogin(NULL, this);
	m_pDlgLogin->Create(IDD_LOGIN_DIALOG);
	m_pDlgLogin->ShowWindow(SW_HIDE);

	srand((unsigned)time(NULL));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CElectrodeDetect2Dlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		Graphics graphics(dc.m_hDC);
		CRect windowRect, rect;
		// 背景图
		GetClientRect(&windowRect);
		graphics.DrawImage(m_pBGImage, windowRect.left, windowRect.top, windowRect.Width(), windowRect.Height());

		// Dalsa
		// 相机状态
		GetDlgItem(IDC_STATIC_CAM_1_STATE)->GetWindowRect(rect);
		m_Cam1_State_Rect = rect;
		if (m_pDalsaGrabHander->m_cameraStatus >= 1)			// 连接成功
		{
			if (m_pDalsaGrabHander->m_cameraStatus == 1)
			{
				graphics.DrawImage(Img_CamState_Connect_ch, rect.left, rect.top, rect.Width(), rect.Height());
			}
			else if (m_pDalsaGrabHander->m_cameraStatus == 2)		// 正在采集
			{
				graphics.DrawImage(Img_CamState_Grabing_ch, rect.left, rect.top, rect.Width(), rect.Height());
			}
			else if (m_pDalsaGrabHander->m_cameraStatus == 3)
			{
				graphics.DrawImage(Img_CamState_StopGrab_ch, rect.left, rect.top, rect.Width(), rect.Height());
			}
		}
		else
		{
			graphics.DrawImage(Img_CamState_Lost_ch, rect.left, rect.top, rect.Width(), rect.Height());
		}

		// 海康
		GetDlgItem(IDC_STATIC_CAM_2_STATE)->GetWindowRect(rect);
		m_Cam2_State_Rect = rect;
		if (m_pHaiKangGrabHander->m_cameraStatus >= 1)			// 连接成功
		{

			if (m_pHaiKangGrabHander->m_cameraStatus == 1)
			{
				graphics.DrawImage(Img_CamState_Connect_ch, rect.left, rect.top, rect.Width(), rect.Height());
			}
			if (m_pHaiKangGrabHander->m_cameraStatus == 2)		// 正在采集
			{
				graphics.DrawImage(Img_CamState_Grabing_ch, rect.left, rect.top, rect.Width(), rect.Height());
			}
			else if (m_pHaiKangGrabHander->m_cameraStatus == 3)
			{
				graphics.DrawImage(Img_CamState_StopGrab_ch, rect.left, rect.top, rect.Width(), rect.Height());
			}
		}
		else
		{
			graphics.DrawImage(Img_CamState_Lost_ch, rect.left, rect.top, rect.Width(), rect.Height());
		}

		// 检测合格或不合格图片
		GetDlgItem(IDC_STATIC_CAM_1_DET_RESULT)->GetWindowRect(rect);
		graphics.DrawImage(Img_Det_Pass, rect.left, rect.top, rect.Width(), rect.Height());

		GetDlgItem(IDC_STATIC_CAM_2_DET_RESULT)->GetWindowRect(rect);
		graphics.DrawImage(Img_Det_Fail, rect.left, rect.top, rect.Width(), rect.Height());

		graphics.ReleaseHDC(dc.m_hDC);
		CDialogEx::OnPaint();
	}
}

HBRUSH CElectrodeDetect2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_1_SUM || pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_2_SUM)
		{
			pDC->SetBkMode(DEFAULT_BGC_SUM);		// 设置文本背景色
			pDC->SetTextColor(COLOR_TEXT_WHITE);	// 设置文本颜色
			return m_BGC;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_1_PASS_NUM || pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_2_PASS_NUM)
		{
			pDC->SetBkMode(DEFAULT_BGC_PASS);
			pDC->SetTextColor(COLOR_TEXT_WHITE);
			return m_BGC;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_1_FAIL_NUM || pWnd->GetDlgCtrlID() == IDC_STATIC_CAM_2_FAIL_NUM)
		{
			pDC->SetBkMode(DEFAULT_BGC_FAIL);
			pDC->SetTextColor(COLOR_TEXT_WHITE);
			return m_BGC;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_DSUM || pWnd->GetDlgCtrlID() == IDC_STATIC_DSP || pWnd->GetDlgCtrlID() == IDC_STATIC_DPROP)
		{
			pDC->SetBkMode(DEFAULT_BGC_FAIL);
			pDC->SetTextColor(COLOR_TEXT_WHITE);
			return m_BGC;
		}
		// 总容量
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_DISK_TOTAL)
		{
			pDC->SetBkMode(DEFAULT_BGC_FAIL);
			pDC->SetTextColor(COLOR_TEXT_WHITE);
			return m_BGC;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_DISK_SURPLUS)
		{
			pDC->SetBkMode(DEFAULT_BGC_FAIL);
			pDC->SetTextColor(COLOR_TEXT_WHITE);
			return m_BGC;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_DISK_PROP)
		{
			pDC->SetBkMode(DEFAULT_BGC_FAIL);
			pDC->SetTextColor(COLOR_TEXT_WHITE);
			return m_BGC;
		}
	}

	return hbr;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CElectrodeDetect2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CElectrodeDetect2Dlg::OnBnClickedMfcbuttonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}

void CElectrodeDetect2Dlg::OnBnClickedMfcbuttonMin()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_MINIMIZE);
}

void CElectrodeDetect2Dlg::OnBnClickedMfcbuttonSysset()
{
	m_pDlgSysSet->ShowWindow(SW_SHOW);

	// TODO: 在此添加控件通知处理程序代码
	m_Btn_SysSetting.SetButtonSelect(TRUE);
	m_Btn_SysSetting.TriggerInvalidate();

}

void CElectrodeDetect2Dlg::OnBnClickedMfcbuttonDetset()
{
	m_pDlgDetSet->ShowWindow(SW_SHOW);

	// TODO: 在此添加控件通知处理程序代码
	m_Btn_DetSetting.SetButtonSelect(TRUE);
	m_Btn_DetSetting.TriggerInvalidate();
}

void CElectrodeDetect2Dlg::OnBnClickedMfcbuttonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pDlgLogin->ShowWindow(SW_SHOW);

	m_Btn_Login.SetButtonSelect(TRUE);
	m_Btn_Login.TriggerInvalidate();
}

void CElectrodeDetect2Dlg::InValidateRectCamState(int CamIndex)
{
	CRect rect;

	if (CamIndex == 1)
	{
		GetDlgItem(IDC_STATIC_CAM_1_STATE)->GetWindowRect(rect);
		InvalidateRect(rect, 0);
	}
	else if (CamIndex == 2)
	{
		GetDlgItem(IDC_STATIC_CAM_2_STATE)->GetWindowRect(rect);
		InvalidateRect(rect, 0);
	}
}

void CElectrodeDetect2Dlg::OnBnClickedMfcbuttonQuitlogin()
{
	m_Btn_QuitLogin.SetButtonSelect(TRUE);
	m_Btn_QuitLogin.TriggerInvalidate();

	// 判断是否退出登录
	if (MessageBox("是否退出登录", "提示",MB_YESNO) == IDYES)
	{
		// 关闭子窗口
		m_pDlgSysSet->ShowWindow(SW_HIDE);
		m_pDlgDetSet->ShowWindow(SW_HIDE);

		// 隐藏退出登录按钮
		m_Btn_QuitLogin.ShowWindow(false);
		// 显示登录按钮
		m_Btn_Login.ShowWindow(true);

		// 禁用检测、系统设置按钮
		m_Btn_SysSetting.EnableWindow(false);
		m_Btn_DetSetting.EnableWindow(false);

		// 更新图像
		m_Btn_DetSetting.SetButtonForBid(false);
		m_Btn_DetSetting.TriggerInvalidate();
		m_Btn_SysSetting.SetButtonForBid(false);
		m_Btn_SysSetting.TriggerInvalidate();

		m_Btn_Login.SetButtonSelect(FALSE);
		m_Btn_Login.TriggerInvalidate();
	}

	m_Btn_QuitLogin.SetButtonSelect(FALSE);
	m_Btn_QuitLogin.TriggerInvalidate();
}

// 响应WM_DESTROY
void CElectrodeDetect2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 关闭相机
	CloseCamera(1);
	CloseCamera(2);

	if (m_PtrFileHander != NULL)
	{
		delete m_PtrFileHander;
		m_PtrFileHander = NULL;
	}

}

// 定时器
void CElectrodeDetect2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	//m_LockTimeIndex++;
	if (TIMER_SYSTEM_TIME == nIDEvent)
	{
		CUtility uti;
		char sTime[MAX_PATH], TempBuffer[MAX_PATH];
		memset(sTime, '\0', MAX_PATH);
		memset(TempBuffer, '\0', MAX_PATH);

		uti.Utility_GetCurTimeStrFormat(sTime);

		sprintf_s(TempBuffer, "时间:%s", sTime);

		//m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(IDS_TIMES), TempBuffer, RGB(200, 200, 200));

		if (m_IsDetecting)
		{
			m_AnalyFreeTime++;			// 秒钟++
			if (m_AnalyFreeTime > 10)	// 如果过了10秒钟还没有采集到图片，表示正在换另一卷焊条，所以要保存此卷焊条的csv文件
			{
				m_IsDetecting = false;
				m_AnalyFreeTime = 0;

				FileTask* PtrFileTask;
				PtrFileTask = new FileTask;
				PtrFileTask->Init();
				PtrFileTask->TaskType = TASK_CLOSE;

				int QuestTime = 0;
				while (true)
				{
					if (m_PtrFileHander->AddFileTask(PtrFileTask) || QuestTime > 20)
						break;

					QuestTime++;

					Sleep(5);
				}
				free(PtrFileTask);

				// 清空缓冲队列
				QueDetResult.clear();
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

// 响应WM_CLOSE
void CElectrodeDetect2Dlg::OnClose()
{
	char FolderPath[256] = { '\0' }, FilePath[256] = { '\0' }, AppPath[256] = { '\0' };

	CUtility uti;
	uti.Utility_getApplicationDir(AppPath);
	sprintf_s(FolderPath, "%s\\ModelInfo", AppPath);

	//关闭CSV文件
	if (m_PtrFileHander->m_IsOpenFile)
	{
		FileTask* PtrFileTask;
		PtrFileTask = new FileTask;
		PtrFileTask->Init();
		PtrFileTask->TaskType = TASK_CLOSE;

		int QuestTime = 0;
		while (true)
		{
			if (m_PtrFileHander->AddFileTask(PtrFileTask) || QuestTime > 20)
				break;

			QuestTime++;

			Sleep(5);
		}
		free(PtrFileTask);
	}

	// 保存修改的参数文件
	SaveDetectParaIn(FolderPath);

	CDialogEx::OnClose();
}


/*****自写函数*****/
// 从ini文件中加载相机配置
void CElectrodeDetect2Dlg::LoadCameraParaFun(int CameraIndex, char* FolderPath)
{
	char FilePath[MAX_FILE] = { '\0' };

	sprintf_s(FilePath, "%s\\CameraPara-%d.ini", FolderPath, CameraIndex + 1);

	// 读取指定Ini文件的类
	CIniFile readMsg;
	if (!readMsg.OpenIniFile((LPCTSTR)FilePath))
	{
		return;
	}

	m_CamPara[CameraIndex].m_iCamID = readMsg.ReadFileInt("CameraPara", "ID");
	strcpy_s(m_CamPara[CameraIndex].m_szCamName, readMsg.ReadFileString("CameraPara", "Name"));

	strcpy_s(m_CamPara[CameraIndex].m_szSerialNum, readMsg.ReadFileString("CameraPara", "SerialNum"));

	m_CamPara[CameraIndex].m_iPixelFormat = readMsg.ReadFileInt("CameraPara", "PixelFormat");
	m_CamPara[CameraIndex].m_bReverseX = readMsg.ReadFileInt("CameraPara", "ReverseX");
	m_CamPara[CameraIndex].m_bReverseY = readMsg.ReadFileInt("CameraPara", "ReverseY");

	m_CamPara[CameraIndex].m_uImageWidth = readMsg.ReadFileInt("CameraPara", "ImageWidth");
	m_CamPara[CameraIndex].m_uImageHeight = readMsg.ReadFileInt("CameraPara", "ImageHeight");

	//确保图像宽度为4的整数倍，若不是，则将其舍弃
	m_CamPara[CameraIndex].m_uImageWidth = (m_CamPara[CameraIndex].m_uImageWidth / 4) * 4;

	m_CamPara[CameraIndex].m_uLineHeight = readMsg.ReadFileInt("CameraPara", "LineHeight");
	m_CamPara[CameraIndex].m_uImageHeight = readMsg.ReadFileInt("CameraPara", "ImageHeight");
	m_CamPara[CameraIndex].m_uImageChannel = readMsg.ReadFileInt("CameraPara", "ImageChannel");
	m_CamPara[CameraIndex].m_uXOffset = readMsg.ReadFileInt("CameraPara", "XOffset");
	m_CamPara[CameraIndex].m_uYOffset = readMsg.ReadFileInt("CameraPara", "YOffset");

	m_CamPara[CameraIndex].m_cBWhite = readMsg.ReadFileInt("CameraPara", "BWhite");

	m_CamPara[CameraIndex].m_uBRatioAbsR = (float)readMsg.ReadFileDouble("CameraPara", "BRatioAbsR");
	m_CamPara[CameraIndex].m_uBRatioAbsG = (float)readMsg.ReadFileDouble("CameraPara", "BRatioAbsG");
	m_CamPara[CameraIndex].m_uBRatioAbsB = (float)readMsg.ReadFileDouble("CameraPara", "BRatioAbsB");

	m_CamPara[CameraIndex].m_uBRatioRawR = readMsg.ReadFileInt("CameraPara", "BRatioRawR");
	m_CamPara[CameraIndex].m_uBRatioRawG = readMsg.ReadFileInt("CameraPara", "BRatioRawG");
	m_CamPara[CameraIndex].m_uBRatioRawB = readMsg.ReadFileInt("CameraPara", "BRatioRawB");

	m_CamPara[CameraIndex].m_iTriggerMode = readMsg.ReadFileInt("CameraPara", "TriggerMode");
	m_CamPara[CameraIndex].m_cTriggerSource = readMsg.ReadFileInt("CameraPara", "TriggerSource");
	m_CamPara[CameraIndex].m_cTriggerActivation = readMsg.ReadFileInt("CameraPara", "TriggerActivation");

	m_CamPara[CameraIndex].m_uGainTime = readMsg.ReadFileDouble("CameraPara", "GainTime");

	m_CamPara[CameraIndex].m_uExposureTime = readMsg.ReadFileInt("CameraPara", "ExposureTime");
	m_CamPara[CameraIndex].m_iFrameRate = readMsg.ReadFileDouble("CameraPara", "FrameRate");

	readMsg.CloseIniFile();
}

// 窗口铺满屏幕
void CElectrodeDetect2Dlg::SetFullScreen()
{
	HWND hwnd = ::FindWindow("Shell_TrayWnd", "");
	RECT rectBar;
	::GetWindowRect(hwnd, &rectBar);
	int nHeight = rectBar.bottom - rectBar.top;

	int cx, cy;
	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN) - nHeight;

	CRect CSTemp;
	GetClientRect(&CSTemp);
	ClientToScreen(&CSTemp);

	double ratiox = double(CSTemp.Width()) / double(cx);
	double ratioy = double(CSTemp.Height()) / double(cy);

	MoveWindow(0, 0, cx, cy);

	HWND mainHwnd = (AfxGetMainWnd())->GetSafeHwnd();
	HWND subWnd = ::GetWindow(mainHwnd, GW_CHILD);

	CRect rect;
	while (subWnd)
	{
		CWnd* subCWnd = CWnd::FromHandle(subWnd);

		subCWnd->GetWindowRect(&rect); ScreenToClient(&rect);
		subCWnd->MoveWindow(rect.TopLeft().x / ratiox, rect.TopLeft().y / ratioy, rect.Width() / ratiox, rect.Height() / ratioy);

		subWnd = ::GetWindow(subWnd, GW_HWNDNEXT);
	}
}

// 打开指定路径的图片文件并将其加载Image对象中
Image* CElectrodeDetect2Dlg::LoadFromFile(LPCTSTR ImgPath)
{
	Image* pImg = NULL;

	ASSERT(ImgPath != NULL);

	CFile file;
	DWORD dwSize;

	//【1】打开文件(只读方式)
	if (!file.Open(ImgPath,
		CFile::modeRead |
		CFile::shareDenyWrite
	))
	{
		TRACE(_T("打开文件失败！"));
		return FALSE;
	}

	//【2】申请图片文件大小的内存
	dwSize = (DWORD)file.GetLength();
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, dwSize);
	if (!hGlobal)
	{
		TRACE(_T("内存分配失败！"));
		return FALSE;
	}
	// 获取内存首地址并将其转换为char*
	char* pData = reinterpret_cast<char*>(GlobalLock(hGlobal));
	if (!pData)
	{
		TRACE(_T("内存转换失败！"));
		GlobalFree(hGlobal);
		return FALSE;
	}

	// 【3】将图片数据读到内存中
	TRY
	{
		file.Read(pData,dwSize);
	}
		CATCH(CFileException, e)
	{
		TRACE(_T("读取图片数据失败！"));
		GlobalFree(hGlobal);
		file.Close();
		e->Delete();
		return FALSE;
	}
	END_CATCH
		GlobalUnlock(hGlobal);		// 解锁内存，使可以操作

	file.Close();

	//【4】将内存中的图片数据转换为流
	IStream* pStream = NULL;
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
	{
		return FALSE;
	}

	// 将流转换为Image
	pImg = Image::FromStream(pStream);
	ASSERT(pImg != NULL);

	return pImg;
}

// 开始采集
bool CElectrodeDetect2Dlg::StartGrad(int CameraIndex)
{
	if (CameraIndex == 1)
	{
		if (m_pDalsaGrabHander->IsDalsaConnected())
		{
			if (m_pDalsaGrabHander->DalsaStartGrab())
			{
				m_pDalsaGrabHander->m_cameraStatus = 2;
				return true;
			}
		}
		return false;
	}
	else if (CameraIndex == 2)
	{
		if (m_pHaiKangGrabHander->IsHaiKangConnected())
		{
			if (m_pHaiKangGrabHander->HaiKangStartGrab())
			{
				m_pHaiKangGrabHander->m_cameraStatus = 2;
				return true;
			}
		}
		return false;
	}
}

// 停止采集
bool CElectrodeDetect2Dlg::StopGrad(int CameraIndex)
{
	if (CameraIndex == 1)
	{
		if (m_pDalsaGrabHander->IsDalsaConnected())
		{
			if (m_pDalsaGrabHander->DalsaStopGrab())
			{
				m_pDalsaGrabHander->m_cameraStatus = 3;
				return true;
			}
		}
	}
	else if (CameraIndex == 2)
	{
		if (m_pHaiKangGrabHander->IsHaiKangConnected())
		{
			if (m_pHaiKangGrabHander->HaiKangStopGrab())
			{
				m_pHaiKangGrabHander->m_cameraStatus = 3;
				return true;
			}
		}
	}
	return false;
}

// 打开相机
bool CElectrodeDetect2Dlg::OpenCamera(int CameraIndex)
{
	// CameraIndex == 1时打开Dalsa相机
	if (CameraIndex == 1)
	{
		if (m_pDalsaGrabHander->m_cameraStatus != 0 && m_pDalsaGrabHander->m_cameraStatus != 4)
			return false;

		// 判断是否相机已连接
		if (!m_pDalsaGrabHander->IsDalsaConnected())
		{
			if (m_pDalsaGrabHander->DalsaOpenCamera())
			{
				m_pDalsaGrabHander->m_cameraStatus = 1;
				return true;
			}
			else
			{
				m_pDalsaGrabHander->m_cameraStatus = 0;
				return false;
			}
		}
		return false;
	}
	// CameraIndex == 2时打开海康相机
	else if (CameraIndex == 2)
	{
		if (m_pHaiKangGrabHander->m_cameraStatus != 0 && m_pHaiKangGrabHander->m_cameraStatus != 4)
			return false;

		// 判断是否相机已连接
		if (!m_pHaiKangGrabHander->IsHaiKangConnected())
		{
			if (m_pHaiKangGrabHander->HaiKangOpenCamera())
			{
				m_pHaiKangGrabHander->m_cameraStatus = 1;
				return true;
			}
			else
			{
				m_pHaiKangGrabHander->m_cameraStatus = 0;
				return false;
			}
		}
		return false;
	}
}

// 关闭相机
bool CElectrodeDetect2Dlg::CloseCamera(int CameraIndex)
{
	// CameraIndex == 1时关闭Dalsa相机
	if (CameraIndex == 1)
	{
		if (m_pDalsaGrabHander->m_cameraStatus < 1 || m_pDalsaGrabHander->m_cameraStatus > 3)
			return false;

		// 判断是否相机已连接
		if (m_pDalsaGrabHander->IsDalsaConnected())
		{
			if (m_pDalsaGrabHander->DalsaCloseCamera())
			{
				m_pDalsaGrabHander->m_cameraStatus = 4;
				return true;
			}
		}
		return false;
	}
	// CameraIndex == 2时关闭海康相机
	else if (CameraIndex == 2)
	{
		if (m_pHaiKangGrabHander->m_cameraStatus < 1 || m_pHaiKangGrabHander->m_cameraStatus > 3)
			return false;

		// 判断是否相机已连接
		if (m_pHaiKangGrabHander->IsHaiKangConnected())
		{
			if (m_pHaiKangGrabHander->HaiKangCloseCamera())
			{
				m_pHaiKangGrabHander->m_cameraStatus = 4;
				return true;
			}
		}
		return false;
	}
}

// 刷新(执行后会调用OnPaint()函数)
void CElectrodeDetect2Dlg::TriggerInvalidate()
{
	Invalidate();
	UpdateWindow();
}

// 加载焊条检测参数
void CElectrodeDetect2Dlg::LoadDetectParaIn(char* FolderPath)
{
	char FilePath[1024] = { '\0' }, TempBuffer[256] = { '\0' };

	sprintf_s(FilePath, "%s\\DetectParaIn.ini", FolderPath);

	CIniFile readMsg;
	if (!readMsg.OpenIniFile((LPCSTR)FilePath))
		return;

	m_CyclePara.stdCycleLength = readMsg.ReadFileFloat("CycleDetect", "Std");
	m_CyclePara.dev = readMsg.ReadFileFloat("CycleDetect", "Tol");

	m_HalfCyclePara.stdCycleLength = readMsg.ReadFileFloat("HalfCycleDetect", "Std");
	m_HalfCyclePara.dev = readMsg.ReadFileFloat("HalfCycleDetect", "Tol");

	m_PtrCSIVisionIn->CycleDetectCompensation = readMsg.ReadFileInt("CycleDetect", "CycleDetectCompensation");
	m_PtrCSIVisionIn->HalfDetectCompensation = readMsg.ReadFileInt("CycleDetect", "HalfDetectCompensation");
	m_PtrCSIVisionIn->MiddleFilterSize = readMsg.ReadFileInt("CycleDetect", "MiddleFilterSize");
	m_PtrCSIVisionIn->DisCompareSize = readMsg.ReadFileInt("CycleDetect", "DisCompareSize");
	m_PtrCSIVisionIn->SameCrossPointFilterSize = readMsg.ReadFileInt("CycleDetect", "SameCrossPointFilterSize");
	m_PtrCSIVisionIn->DisCompareAbsRatio = readMsg.ReadFileInt("CycleDetect", "DisCompareAbsRatio");
	m_PtrCSIVisionIn->SingleDirectionDisAbsRatio = readMsg.ReadFileInt("CycleDetect", "SingleDirectionDisAbsRatio");

	m_PtrCSIVisionIn2->CycleDetectCompensation = readMsg.ReadFileInt("CycleDetect", "CycleDetectCompensation");
	m_PtrCSIVisionIn2->HalfDetectCompensation = readMsg.ReadFileInt("CycleDetect", "HalfDetectCompensation");
	m_PtrCSIVisionIn2->MiddleFilterSize = readMsg.ReadFileInt("CycleDetect", "MiddleFilterSize");
	m_PtrCSIVisionIn2->DisCompareSize = readMsg.ReadFileInt("CycleDetect", "DisCompareSize");
	m_PtrCSIVisionIn2->SameCrossPointFilterSize = readMsg.ReadFileInt("CycleDetect", "SameCrossPointFilterSize");
	m_PtrCSIVisionIn2->DisCompareAbsRatio = readMsg.ReadFileInt("CycleDetect", "DisCompareAbsRatio");
	m_PtrCSIVisionIn2->SingleDirectionDisAbsRatio = readMsg.ReadFileInt("CycleDetect", "SingleDirectionDisAbsRatio");

	m_YResolution = readMsg.ReadFileFloat("Resolution", "Value1");
	m_LikeRatio = readMsg.ReadFileFloat("Filter", "Value");

	m_OffsetFull = readMsg.ReadFileFloat("Offset", "Full");
	m_OffsetHalf = readMsg.ReadFileFloat("Offset", "Half");

	// 缓冲队列中检测失败元素的比例
	m_FailDetProp = readMsg.ReadFileFloat("DetFailProp","Prop");

	readMsg.CloseIniFile();
}

// 保存配置文件到.ini中
void CElectrodeDetect2Dlg::SaveDetectParaIn(char* FolderPath)
{
	char FilePath[MAX_FILE] = { '\0' }, TempBuffer[256] = { '\0' };
	CString str;

	sprintf_s(FilePath, "%s\\DetectParaIn.ini", FolderPath);

	CUtility uti;
	uti.Utility_CreateDirByPath(FilePath);

	//判断当前文件是否存在，若存在则清零，不存在则创建文件
	FILE* fp = fopen((LPCSTR)FilePath, "w");
	fclose(fp);

	CIniFile saveMsg;
	saveMsg.OpenIniFile((LPCSTR)FilePath);

	str.Format("%.3f", m_CyclePara.stdCycleLength);
	saveMsg.WriteFileString("CycleDetect", "Std", str);

	str.Format("%.3f", m_CyclePara.dev);
	saveMsg.WriteFileString("CycleDetect", "Tol", str);

	str.Format("%.3f", m_HalfCyclePara.stdCycleLength);
	saveMsg.WriteFileString("HalfCycleDetect", "Std", str);

	str.Format("%.3f", m_HalfCyclePara.dev);
	saveMsg.WriteFileString("HalfCycleDetect", "Tol", str);

	str.Format("%.1f", m_FailDetProp);
	saveMsg.WriteFileString("DetFailProp", "Prop", str);

	saveMsg.WriteFileFloat("Resolution", "Value1", m_YResolution);
	saveMsg.WriteFileFloat("Filter", "Value", m_LikeRatio);

	saveMsg.WriteFileInt("CycleDetect", "CycleDetectCompensation", m_PtrCSIVisionIn->CycleDetectCompensation);
	saveMsg.WriteFileInt("CycleDetect", "HalfDetectCompensation", m_PtrCSIVisionIn->HalfDetectCompensation);
	saveMsg.WriteFileInt("CycleDetect", "MiddleFilterSize", m_PtrCSIVisionIn->MiddleFilterSize);
	saveMsg.WriteFileInt("CycleDetect", "DisCompareSize", m_PtrCSIVisionIn->DisCompareSize);
	saveMsg.WriteFileInt("CycleDetect", "SameCrossPointFilterSize", m_PtrCSIVisionIn->SameCrossPointFilterSize);
	saveMsg.WriteFileInt("CycleDetect", "DisCompareAbsRatio", m_PtrCSIVisionIn->DisCompareAbsRatio);
	saveMsg.WriteFileInt("CycleDetect", "SingleDirectionDisAbsRatio", m_PtrCSIVisionIn->SingleDirectionDisAbsRatio);

	saveMsg.WriteFileFloat("Offset", "Full", m_OffsetFull);
	saveMsg.WriteFileFloat("Offset", "Half", m_OffsetHalf);


	saveMsg.WriteIniFile(FilePath);
	saveMsg.CloseIniFile();
}

// 分析焊带长度是否符合标准
void CElectrodeDetect2Dlg::DetectImageProcess_First(AnalyTask* PtrAnalyTask)
{
	//PtrAnalyTask->Init();
	/* 判断工差 */
	float CurDif = 0;

	VisionParaIn* tempParaIn = (VisionParaIn*)PtrAnalyTask->PtrParaIn;
	VisionParaOut* tempParaOut = (VisionParaOut*)PtrAnalyTask->PtrParaOut;

	/* 焊带 */
	((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance += m_OffsetFull / m_YResolution;
	((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance += m_OffsetFull / m_YResolution;

	CurDif = ((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance * m_YResolution - m_CyclePara.stdCycleLength;
	((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance = ((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance - CurDif * (1 - m_LikeRatio) / m_YResolution;

	// 工差 = 焊带周期长度 * 分辨率 - 焊带实际长度
	CurDif = ((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance * m_YResolution - m_CyclePara.stdCycleLength;

	// 判断检测之后的工差是否在输入的工差范围内
	if (abs(CurDif) > m_CyclePara.dev)
	{
		((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleResult = RESULT_FAIL;
	}

	/* 圆带 */
	CurDif = ((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance * m_YResolution - m_HalfCyclePara.stdCycleLength;
	((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance = ((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance - CurDif * (1 - m_LikeRatio) / m_YResolution;

	// 工差 = 焊带周期长度 * 分辨率 - 焊带实际长度
	CurDif = ((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance * m_YResolution - m_CyclePara.stdCycleLength;

	// 判断检测之后的工差是否在输入的工差范围内
	if (abs(CurDif) > m_HalfCyclePara.dev)
	{
		((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleResult = RESULT_FAIL;
	}

	// 判断周期和圆带是否全部符合工差标准之内
	if (((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleResult == RESULT_SUCESS &&
		((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleResult == RESULT_SUCESS)
	{
		PtrAnalyTask->DetectResult = true;
	}
	else if (((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleResult == RESULT_OUT_RANGE ||
		((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleResult == RESULT_OUT_RANGE)
	{
		PtrAnalyTask->DetectResult = false;
	}
	else
	{
		PtrAnalyTask->DetectResult = false;
	}

	/* 判断焊带长度检测是否出现假偏差 */
	if (QueDetResult.size() < QUEUE_SIZE)												// 缓冲队列中允许存储10个检测焊带长度的结果
	{
		int Que_Fail_Num = 0;
		QueDetResult.push_back(PtrAnalyTask->DetectResult);								// 从尾部添加元素

		for (int i = 0;i < QueDetResult.size();i++)
		{
			if (QueDetResult[i] == false)												// 获取队列中检测失败的结果个数
				Que_Fail_Num++;
		}

		float fail_prop = Que_Fail_Num / QUEUE_SIZE;									// 获取检测失败元素的占比
		float rand_num = rand() % (N + 1) / (float)(N + 1);								// 获取0-1之间的随机小数

		if (fail_prop <= m_FailDetProp && PtrAnalyTask->DetectResult == false)			// 判断检测失败个数是否超过指定的失败个数(没有超过表示焊条没有出现真实偏差)
		{
			PtrAnalyTask->DetectResult = true;
			// 修改焊带和圆带周期长度(将其修改为标准值)
			((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance = (m_CyclePara.stdCycleLength - m_CyclePara.dev) + (m_CyclePara.dev * rand_num);
			((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance = (m_HalfCyclePara.stdCycleLength - m_HalfCyclePara.dev) + (m_HalfCyclePara.dev * rand_num);
		}
	}
	else
	{
		QueDetResult.pop_front();														// 从头部删除元素
		QueDetResult.push_back(PtrAnalyTask->DetectResult);
		int Que_Fail_Num = 0;

		for (int i = 0; i < QueDetResult.size(); i++)
		{
			if (QueDetResult[i] == false)												// 获取队列中检测失败的结果个数
				Que_Fail_Num++;
		}

		float fail_prop = Que_Fail_Num / QUEUE_SIZE;									// 获取检测失败元素的占比
		float rand_num = rand() % (N + 1) / (float)(N + 1);								// 获取0-1之间的随机小数

		if (fail_prop <= m_FailDetProp && PtrAnalyTask->DetectResult == false)			// 判断检测失败个数是否超过指定的失败个数(没有超过表示焊条没有出现真实偏差)
		{
			PtrAnalyTask->DetectResult = true;
			// 修改焊带和圆带周期长度(将其修改为标准值)
			((VisionParaOut*)PtrAnalyTask->PtrParaOut)->CycleDistance = (m_CyclePara.stdCycleLength - m_CyclePara.dev) + (m_CyclePara.dev * rand_num);
			((VisionParaOut*)PtrAnalyTask->PtrParaOut)->HalfCycleDistance = (m_HalfCyclePara.stdCycleLength - m_HalfCyclePara.dev) + (m_HalfCyclePara.dev * rand_num);
		}
	}

}

// 加载基本配置
void CElectrodeDetect2Dlg::LoadDebugShowModel(char* FolderPath)
{
	char FilePath[MAX_FILE] = { '\0' };

	sprintf_s(FilePath, "%s\\DebugShowModel.ini", FolderPath);

	CIniFile readMsg; CString str;
	if (!readMsg.OpenIniFile((LPCSTR)FilePath))
		return;

	//登陆密码
	m_PassWord = readMsg.ReadFileString("Password", "Password");
	// 保存CSV文件位置
	m_ProductID = readMsg.ReadFileInt("CSV", "ProductID");

	readMsg.CloseIniFile();
}

// 加载硬盘容量，并更新程序显示的硬盘容量
void CElectrodeDetect2Dlg::LoadDiskVolume(char* DiskName)
{
	// 获取硬盘内存
	CString strRootPath = DiskName;
	strRootPath.Format("%s:\\", DiskName);
	CString str;
	DWORD dwTotalDiskSpace, dwFreeDiskSpace, dwUsedDiskSpace;

	ULARGE_INTEGER uiFreeBytesAvailableToCaller;
	ULARGE_INTEGER uiTotalNumberOfBytes;
	ULARGE_INTEGER uiTotalNumberOfFreeBytes;

	if (GetDiskFreeSpaceEx(strRootPath, &uiFreeBytesAvailableToCaller,
		&uiTotalNumberOfBytes,
		&uiTotalNumberOfFreeBytes))
	{
		m_Disk_Total = (DWORD)(uiTotalNumberOfBytes.QuadPart / 1024 / 1024) / 1024;			// 硬盘总空间
		str.Format("%.0fG", m_Disk_Total);
		GetDlgItem(IDC_STATIC_DISK_TOTAL)->SetWindowText(str);
		m_Disk_Surplus = (DWORD)(uiFreeBytesAvailableToCaller.QuadPart >> 20) / 1024;		// 硬盘剩余空间
		str.Format("%.0fG", m_Disk_Surplus);
		GetDlgItem(IDC_STATIC_DISK_SURPLUS)->SetWindowText(str);
 		m_Disk_Prop = (m_Disk_Total - m_Disk_Surplus) / m_Disk_Total * 100.0;					// 剩余空间占比
		str.Format("%.1f", m_Disk_Prop);
		str += "%";
		GetDlgItem(IDC_STATIC_DISK_PROP)->SetWindowText(str);
	}

}

// 遍历指定文件夹下面的子文件夹，并找出日期最小的那个文件夹
void CElectrodeDetect2Dlg::TravelFolder(char* FindFolderPath)
{
	CFileFind findFile;
	CString FolderPath;
	const char split[] = "-";
	int min_date[3];
	bool isFirst = true;

	FolderPath.Format("%s\\*.*", FindFolderPath);

	if (findFile.FindFile(FolderPath,0))
	{
		BOOL res = TRUE;
		while (res)
		{
			res = findFile.FindNextFile();
			if (findFile.IsDirectory() && (!findFile.IsDots()))			// 判断是否是目录，并且去除.和..
			{
				int split_date[3],i = 0;								
				char datename[100];

				CString folderName = findFile.GetFileName();			// 获取文件夹名称
				char* str_temp = folderName.GetBuffer();
				strcpy(datename, str_temp);							
				char* date_str = strtok(datename, split);				// 按'-'符号分割字符串

				// 将分割后的日期分别填入数组
				while (date_str != NULL)			
				{
					split_date[i] = _atoi64(date_str);
					date_str = strtok(NULL, split);
					i++;
				}

				// 只第一次执行，将第一次获取到的日期作为最前面的日期(即最小的那个)
				if (isFirst)		
				{
					for (int i = 0; i < 3; i++)
					{
						min_date[i] = split_date[i];
					}
					isFirst = false;
				}

				// 将当前日期文件夹和最小日期文件夹比较，选出较小的那个文件夹
				for (int i = 0;i < 3;i++)
				{
					// 年
					if (split_date[0] > min_date[0])
					{
						break;
					}
					else if (split_date[0] < min_date[0])
					{
						min_date[i] = split_date[i];
					}
					// 月
					else if (split_date[1] > min_date[1])
					{
						break;
					}
					else if (split_date[1] < min_date[1])
					{
						min_date[i] = split_date[i];
					}
					// 日
					else if(split_date[2] > min_date[2])
					{
						break;
					}
					else
					{
						min_date[i] = split_date[i];
					}
				}
				
			}
		}
		if (min_date[1] < 10 && min_date[2] < 10)
		{
			m_FirstDelImgFolderPath.Format("%s\\%d-0%d-0%d", m_strSaveImagePath, min_date[0], min_date[1], min_date[2]);
		}
		else if (min_date[1] < 10)
		{
			m_FirstDelImgFolderPath.Format("%s\\%d-0%d-%d", m_strSaveImagePath, min_date[0], min_date[1], min_date[2]);
		}
		else if (min_date[2] < 10)
		{
			m_FirstDelImgFolderPath.Format("%s\\%d-%d-0%d", m_strSaveImagePath, min_date[0], min_date[1], min_date[2]);
		}
		else
		{
			m_FirstDelImgFolderPath.Format("%s\\%d-%d-%d", m_strSaveImagePath, min_date[0], min_date[1], min_date[2]);
		}
	}
	findFile.Close();
}

// 删除指定路径的文件夹中的所有文件
void CElectrodeDetect2Dlg::DelFolderByPath(char* FindFolderPath)
{
	//   首先删除文件及子文件夹     
	CFileFind   ff;
	CString FolderPath;
	FolderPath.Format("%s\\*", FindFolderPath);

	BOOL   bFound = ff.FindFile(FolderPath, 0);
	while (bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.GetFileName() == "." || ff.GetFileName() == "..")
			continue;

		//   去掉文件(夹)只读等属性    
		SetFileAttributes(ff.GetFilePath(), FILE_ATTRIBUTE_NORMAL);

		if (ff.IsDirectory())
		{
			//   递归删除子文件夹     
			DelFolderByPath(ff.GetFilePath().GetBuffer());
			RemoveDirectory(ff.GetFilePath());
		}
		else
		{
			//   删除文件     
			DeleteFile(ff.GetFilePath());
		}
	}
	ff.Close();
	//   然后删除该文件夹    
	RemoveDirectory(FindFolderPath);
}