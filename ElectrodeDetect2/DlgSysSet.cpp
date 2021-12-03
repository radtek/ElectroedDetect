// DlgSysSet.cpp: 实现文件
//
#include "pch.h"
#include "ElectrodeDetect2.h"
#include "DlgSysSet.h"
#include "afxdialogex.h"

#include "ElectrodeDetect2Dlg.h"
#include "HaiKangGrabHander.h"
#include "DalsaGrabHander.h"
#include "Analyhander.h"

// CDlgSysSet 对话框

IMPLEMENT_DYNAMIC(CDlgSysSet, CDialogEx)

CDlgSysSet::CDlgSysSet(CWnd* pParent, CElectrodeDetect2Dlg* Parent)
	: CDialogEx(IDD_SYSTEMSETTING_DIALOG, pParent)
{
	m_pParent = Parent;
	m_SelectButton = IDC_MFCBUTTON_LOGIN_SET;
}

CDlgSysSet::~CDlgSysSet()
{
}

void CDlgSysSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_MFCBUTTON_CAM1_STATE, m_Btn_Cam1_State);
	DDX_Control(pDX, IDC_MFCBUTTON_CAM2_STATE, m_Btn_Cam2_State);
}


BEGIN_MESSAGE_MAP(CDlgSysSet, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &CDlgSysSet::OnBnClickedMfcbuttonClose)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MFCBUTTON_CAM2_STATE, &CDlgSysSet::OnBnClickedMfcbuttonCam2State)
	ON_BN_CLICKED(IDC_MFCBUTTON_CAM1_STATE, &CDlgSysSet::OnBnClickedMfcbuttonCam1State)
	ON_BN_CLICKED(IDC_CHECK_SAVE_OK, &CDlgSysSet::OnBnClickedCheckSaveOk)
	ON_BN_CLICKED(IDC_CHECK_SAVE_NG, &CDlgSysSet::OnBnClickedCheckSaveNg)
	ON_EN_CHANGE(IDC_EDIT_DISK_PROP, &CDlgSysSet::OnEnChangeEditDiskProp)
END_MESSAGE_MAP()


// CDlgSysSet 消息处理程序


void CDlgSysSet::OnBnClickedMfcbuttonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);

	m_pParent->m_Btn_SysSetting.SetButtonSelect(false);
	m_pParent->m_Btn_SysSetting.TriggerInvalidate();
}


BOOL CDlgSysSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetClientRect(&m_ClientRect);

	m_WriteBrush = CreateSolidBrush(COLOR_BACKGROUND_SET_MENU);
	m_hBrush = CreateSolidBrush(COLOR_BACKGROUND_SET);

	m_BigFont.CreatePointFont(150, _T("微软雅黑"));
	m_MiddleFont.CreatePointFont(100, _T("微软雅黑"));
	m_BGCBrush = CreateSolidBrush(COLOR_DETBACKGROUND);

	((CMFCButton*)GetDlgItem(IDC_MFCBUTTON_CLOSE))->SetFont(&m_BigFont);
	((CStatic*)GetDlgItem(IDC_STATIC_CAMERA1))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_CAMERA2))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_PROP))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_FUHAO))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_EXPLAIN))->SetFont(&m_MiddleFont);
	((CEdit*)GetDlgItem(IDC_EDIT_DISK_PROP))->SetFont(&m_MiddleFont);

	CString str_prop;
	str_prop.Format("%d", m_pParent->m_Disk_Input_Prop);
	((CEdit*)GetDlgItem(IDC_EDIT_DISK_PROP))->SetWindowText(str_prop);

	// 加载按钮
	char bgiPath[1024] = { '\0' }, imgPath[1024] = { '\0' };
	sprintf_s(bgiPath, "%s\\Image\\系统设置bgi.png", m_pParent->AppPath);
	m_pBGImage = m_pParent->LoadFromFile(bgiPath);

	sprintf_s(imgPath, "%s\\Image\\Quit.png", m_pParent->AppPath);
	Img_Close_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\Quit_Over.png", m_pParent->AppPath);
	Img_Close_Over = m_pParent->LoadFromFile(imgPath);

	sprintf_s(imgPath, "%s\\Image\\开始采集_Normal.png", m_pParent->AppPath);
	Img_StartGrab_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\开始采集_Over.png", m_pParent->AppPath);
	Img_StartGrab_Over = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\开始采集_ForBid.png", m_pParent->AppPath);
	Img_StartGrab_ForBid = m_pParent->LoadFromFile(imgPath);

	sprintf_s(imgPath, "%s\\Image\\停止采集_Normal.png", m_pParent->AppPath);
	Img_StopGrab_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\停止采集_Over.png", m_pParent->AppPath);
	Img_StopGrab_Over = m_pParent->LoadFromFile(imgPath);

	m_Btn_Close.LoadNormalImage(Img_Close_Normal);
	m_Btn_Close.LoadOverImage(Img_Close_Over);
	m_Btn_Close.SetButtonType(2);

	m_Btn_Cam1_State.SetButtonType(2);
	m_Btn_Cam2_State.SetButtonType(2);

	// 相机1
	if (m_pParent->m_pDalsaGrabHander->m_cameraStatus < 1)	// 相机1连接断开
	{
		m_Btn_Cam1_State.LoadForBidImage(Img_StartGrab_ForBid);
		m_Btn_Cam1_State.EnableWindow(FALSE);
	}
	else
	{
		if (m_pParent->m_pDalsaGrabHander->m_cameraStatus == 1)	// 连接成功
		{
			m_Btn_Cam1_State.LoadNormalImage(Img_StartGrab_Normal);
			m_Btn_Cam1_State.LoadOverImage(Img_StartGrab_Over);
		}
		if (m_pParent->m_pDalsaGrabHander->m_cameraStatus == 2)	// 正在采集
		{
			m_Btn_Cam1_State.LoadNormalImage(Img_StopGrab_Normal);
			m_Btn_Cam1_State.LoadOverImage(Img_StopGrab_Over);
		}
		if (m_pParent->m_pDalsaGrabHander->m_cameraStatus == 3)	// 停止采集
		{
			m_Btn_Cam1_State.LoadNormalImage(Img_StartGrab_Normal);
			m_Btn_Cam1_State.LoadOverImage(Img_StartGrab_Over);
		}
	}

	// 相机2
	if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus < 1)	// 相机1连接断开
	{
		m_Btn_Cam2_State.LoadForBidImage(Img_StartGrab_ForBid);
		m_Btn_Cam2_State.EnableWindow(FALSE);
	}
	else
	{
		if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus == 1)	// 连接成功
		{
			m_Btn_Cam2_State.LoadNormalImage(Img_StartGrab_Normal);
			m_Btn_Cam2_State.LoadOverImage(Img_StartGrab_Over);
		}
		if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus == 2)	// 正在采集
		{
			m_Btn_Cam2_State.LoadNormalImage(Img_StopGrab_Normal);
			m_Btn_Cam2_State.LoadOverImage(Img_StopGrab_Over);
		}
		if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus == 3)	// 停止采集
		{
			m_Btn_Cam2_State.LoadNormalImage(Img_StartGrab_Normal);
			m_Btn_Cam2_State.LoadOverImage(Img_StartGrab_Over);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgSysSet::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ChangeSize_Set(IDC_STATIC_SET_MENU, cx, cy);
	ChangeSize_Set(IDC_MFCBUTTON_CLOSE, cx, cy);
	ChangeSize_Set(IDC_STATIC_SAVEIMG, cx, cy);
	ChangeSize_Set(IDC_CHECK_SAVE_OK, cx, cy);
	ChangeSize_Set(IDC_CHECK_SAVE_NG, cx, cy);
	ChangeSize_Set(IDC_MFCBUTTON_GRAB_STARTGRAB, cx, cy);
	ChangeSize_Set(IDC_MFCBUTTON_GRAB_STOPGRAB, cx, cy);
	ChangeSize_Set(IDC_MFCBUTTON_CAM1_STATE, cx, cy);
	ChangeSize_Set(IDC_MFCBUTTON_CAM2_STATE, cx, cy);
	ChangeSize_Set(IDC_STATIC_CAMERA1, cx, cy);
	ChangeSize_Set(IDC_STATIC_CAMERA2, cx, cy);
	ChangeSize_Set(IDC_STATIC_CAM_STATE, cx, cy);
	ChangeSize_Set(IDC_STATIC_DISKSET, cx, cy);
	ChangeSize_Set(IDC_STATIC_PROP, cx, cy);
	ChangeSize_Set(IDC_EDIT_DISK_PROP, cx, cy);
	ChangeSize_Set(IDC_STATIC_FUHAO, cx, cy);
	ChangeSize_Set(IDC_STATIC_EXPLAIN, cx, cy);
}


void CDlgSysSet::ChangeSize_Set(UINT nID, int x, int y)
{
	CRect tempRect;

	CWnd* pWnd = GetDlgItem(nID);

	/* 判断是否是文本框 */
	bool isEdit = FALSE;
	char className[20];
	GetClassName(pWnd->GetSafeHwnd(), className, 20);
	isEdit = strcmp(className, "Edit") == 0;

	if (pWnd != NULL)
	{
		pWnd->GetWindowRect(&tempRect);
		ScreenToClient(&tempRect);

		if (isEdit)
		{
			tempRect.left = tempRect.left * x / m_ClientRect.Width();
			tempRect.top = tempRect.top * y / m_ClientRect.Height() + 6;
			tempRect.bottom = tempRect.bottom * y / m_ClientRect.Height() - 6;
			tempRect.right = tempRect.right * x / m_ClientRect.Width();
		}
		else
		{
			tempRect.left = tempRect.left * x / m_ClientRect.Width();
			tempRect.top = tempRect.top * y / m_ClientRect.Height();
			tempRect.bottom = tempRect.bottom * y / m_ClientRect.Height();
			tempRect.right = tempRect.right * x / m_ClientRect.Width();
		}

		pWnd->MoveWindow(tempRect);
	}
}


void CDlgSysSet::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
	// 可以让窗口移动
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

// 初始化MFCButton的样式
void CDlgSysSet::InitMfcButtonStyle(int nID, COLORREF crFace, COLORREF crText)
{
	((CMFCButton*)GetDlgItem(nID))->m_bTransparent = FALSE;
	((CMFCButton*)GetDlgItem(nID))->m_bDontUseWinXPTheme = TRUE;
	((CMFCButton*)GetDlgItem(nID))->m_bDrawFocus = FALSE;
	((CMFCButton*)GetDlgItem(nID))->SetTextColor(crText);
	((CMFCButton*)GetDlgItem(nID))->SetFaceColor(crFace);
}

// 设置MFCButton的样式
void CDlgSysSet::SetMfcButtonStyle(int nID, COLORREF crFace, COLORREF crText)
{
	((CMFCButton*)GetDlgItem(nID))->SetTextColor(crText);
	((CMFCButton*)GetDlgItem(nID))->SetFaceColor(crFace);
}

BOOL CDlgSysSet::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_MFCBUTTON_CLOSE)->m_hWnd)
			SetMfcButtonStyle(IDC_MFCBUTTON_CLOSE, COLOR_BACKGROUND_SET, COLOR_TEXT_BLACK);
	}

	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_DOWN
		|| pMsg->wParam == VK_RETURN || pMsg->wParam == VK_SHIFT
		|| pMsg->wParam == VK_SPACE || pMsg->wParam == VK_END
		|| pMsg->wParam == VK_HOME || pMsg->wParam == VK_LEFT
		|| pMsg->wParam == VK_UP || pMsg->wParam == VK_RIGHT
		|| pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDlgSysSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	Graphics graphics(dc.m_hDC);
	CRect rect;
	GetClientRect(&rect);

	// 背景
	graphics.DrawImage(m_pBGImage, rect.left, rect.top, rect.Width(), rect.Height());
}


HBRUSH CDlgSysSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(COLOR_TEXT_WHITE);
		pDC->SetBkMode(TRANSPARENT);

		return m_BGCBrush;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

// 相机2采集状态
void CDlgSysSet::OnBnClickedMfcbuttonCam2State()
{
	// 判断是否保存OK、NG的图片
	m_pParent->m_IsSaveOKData = ((CButton*)GetDlgItem(IDC_CHECK_SAVE_OK))->GetCheck();
	m_pParent->m_IsSaveNGData = ((CButton*)GetDlgItem(IDC_CHECK_SAVE_NG))->GetCheck();

	if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus == 1)		// 连接成功，但是没有打开
	{
		// 开始采集
		m_pParent->StartGrad(2);
		// 图像转变成停止采集
		m_Btn_Cam2_State.LoadNormalImage(Img_StopGrab_Normal);
		m_Btn_Cam2_State.LoadOverImage(Img_StopGrab_Over);
		// 更新主界面相机2状态
		m_pParent->InValidateRectCamState(2);
	}
	else if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus == 2)	// 状态为正在采集
	{
		// 停止采集
		m_pParent->StopGrad(2);
		m_Btn_Cam2_State.LoadNormalImage(Img_StartGrab_Normal);
		m_Btn_Cam2_State.LoadOverImage(Img_StartGrab_Over);
		m_pParent->InValidateRectCamState(2);
	}
	else if (m_pParent->m_pHaiKangGrabHander->m_cameraStatus == 3)	// 状态为停止采集
	{
		// 开始采集
		m_pParent->StartGrad(2);
		// 图像转变成停止采集
		m_Btn_Cam2_State.LoadNormalImage(Img_StopGrab_Normal);
		m_Btn_Cam2_State.LoadOverImage(Img_StopGrab_Over);
		// 更新主界面相机2状态
		m_pParent->InValidateRectCamState(2);
	}
}


void CDlgSysSet::OnBnClickedMfcbuttonCam1State()
{
	if (m_pParent->m_pDalsaGrabHander->m_cameraStatus == 1)		// 连接成功，但是没有打开
	{
		// 开始采集
		m_pParent->StartGrad(1);
		// 图像转变成停止采集
		m_Btn_Cam1_State.LoadNormalImage(Img_StopGrab_Normal);
		m_Btn_Cam1_State.LoadOverImage(Img_StopGrab_Over);
		// 更新主界面相机2状态
		m_pParent->InValidateRectCamState(1);
	}
	else if (m_pParent->m_pDalsaGrabHander->m_cameraStatus == 2)	// 状态为正在采集
	{
		// 停止采集
		m_pParent->StopGrad(1);
		m_Btn_Cam1_State.LoadNormalImage(Img_StartGrab_Normal);
		m_Btn_Cam1_State.LoadOverImage(Img_StartGrab_Over);
		m_pParent->InValidateRectCamState(1);
	}
	else if (m_pParent->m_pDalsaGrabHander->m_cameraStatus == 3)	// 状态为停止采集
	{
		// 开始采集
		m_pParent->StartGrad(1);
		// 图像转变成停止采集
		m_Btn_Cam1_State.LoadNormalImage(Img_StopGrab_Normal);
		m_Btn_Cam1_State.LoadOverImage(Img_StopGrab_Over);
		// 更新主界面相机2状态
		m_pParent->InValidateRectCamState(1);
	}
}


void CDlgSysSet::OnBnClickedCheckSaveOk()
{
	m_pParent->m_IsSaveOKData = ((CButton*)GetDlgItem(IDC_CHECK_SAVE_OK))->GetCheck();
}


void CDlgSysSet::OnBnClickedCheckSaveNg()
{
	m_pParent->m_IsSaveNGData = ((CButton*)GetDlgItem(IDC_CHECK_SAVE_NG))->GetCheck();
}


void CDlgSysSet::OnEnChangeEditDiskProp()
{
	// 更新硬盘占比
	CString str_Prop;

	((CEdit*)GetDlgItem(IDC_EDIT_DISK_PROP))->GetWindowText(str_Prop);
	m_pParent->m_Disk_Input_Prop = _ttoi(str_Prop);

}
