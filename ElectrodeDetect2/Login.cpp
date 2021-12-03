// CLogin.cpp: 实现文件
//

#include "pch.h"
#include "ElectrodeDetect2.h"
#include "Login.h"
#include "afxdialogex.h"

#include "ElectrodeDetect2Dlg.h"

// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent, CElectrodeDetect2Dlg* Parent)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
	m_pParent = Parent;
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_MFCBUTTON_PASLOGIN, m_Btn_Login);
	DDX_Control(pDX, IDC_MFCBUTTON_CANCEL, m_Btn_Cancel);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MFCBUTTON_CANCEL, &CLogin::OnBnClickedMfcbuttonCancel)
	ON_BN_CLICKED(IDC_MFCBUTTON_PASLOGIN, &CLogin::OnBnClickedMfcbuttonPaslogin)
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &CLogin::OnBnClickedMfcbuttonClose)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CLogin 消息处理程序

void CLogin::ChangeSize_VisionPassword(UINT nID, int x, int y)
{
	CRect tempRect;

	CWnd* pWnd = GetDlgItem(nID);

	if (pWnd != NULL)     //判断是否为空
	{
		pWnd->GetWindowRect(&tempRect);  //获取控件变化前的大小
		ScreenToClient(&tempRect);   //将控件大小装换位在对话框中的区域坐标

		tempRect.left = tempRect.left * x / m_VisionCameraRectSize.Width();  //按照比例调整空间的新位置
		tempRect.top = tempRect.top * y / m_VisionCameraRectSize.Height();
		tempRect.bottom = tempRect.bottom * y / m_VisionCameraRectSize.Height();
		tempRect.right = tempRect.right * x / m_VisionCameraRectSize.Width();

		pWnd->MoveWindow(tempRect);   //伸缩控件
	}
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetClientRect(&m_VisionCameraRectSize);

	char imgPath[1024] = { '\0' };
	sprintf_s(imgPath, "%s\\Image\\登录.png", m_pParent->AppPath);
	m_pBGImage = m_pParent->LoadFromFile(imgPath);

	// 关闭按钮
	sprintf_s(imgPath, "%s\\Image\\Quit.png", m_pParent->AppPath);
	Img_Close_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\Quit_Over.png", m_pParent->AppPath);
	Img_Close_Over = m_pParent->LoadFromFile(imgPath);

	sprintf_s(imgPath, "%s\\Image\\LoginDlg_Normal.png", m_pParent->AppPath);
	Img_Login_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\LoginDlg_Over.png", m_pParent->AppPath);
	Img_Login_Over = m_pParent->LoadFromFile(imgPath);

	sprintf_s(imgPath, "%s\\Image\\CancelDlg_Normal.png", m_pParent->AppPath);
	Img_Cancel_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\CancelDlg_Over.png", m_pParent->AppPath);
	Img_Cancel_Over = m_pParent->LoadFromFile(imgPath);

	m_Btn_Close.LoadNormalImage(Img_Close_Normal);
	m_Btn_Close.LoadOverImage(Img_Close_Over);
	m_Btn_Close.SetButtonType(2);
	m_Btn_Login.LoadNormalImage(Img_Login_Normal);
	m_Btn_Login.LoadOverImage(Img_Login_Over);
	m_Btn_Login.SetButtonType(2);
	m_Btn_Cancel.LoadNormalImage(Img_Cancel_Normal);
	m_Btn_Cancel.LoadOverImage(Img_Cancel_Over);
	m_Btn_Cancel.SetButtonType(2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLogin::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//ChangeSize_VisionPassword(IDC_STATIC_PASSWORD, cx, cy);
	ChangeSize_VisionPassword(IDC_EDIT_PASSWORD, cx, cy);
	ChangeSize_VisionPassword(IDC_MFCBUTTON_PASLOGIN, cx, cy);
	ChangeSize_VisionPassword(IDC_MFCBUTTON_CANCEL, cx, cy);
}


void CLogin::OnBnClickedMfcbuttonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pParent->m_Btn_Login.SetButtonSelect(FALSE);
	m_pParent->m_Btn_Login.TriggerInvalidate();
	GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText(_T(""));
	ShowWindow(SW_HIDE);
}


void CLogin::OnBnClickedMfcbuttonPaslogin()
{
	CString str;
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->GetWindowText(str);

	if (str == m_pParent->m_PassWord)
	{
		m_pParent->m_IsLogin = 1;
		// 更新检测、系统设置按钮图像
		m_pParent->m_Btn_DetSetting.SetButtonForBid(true);
		m_pParent->m_Btn_DetSetting.TriggerInvalidate();
		m_pParent->m_Btn_SysSetting.SetButtonForBid(true);
		m_pParent->m_Btn_SysSetting.TriggerInvalidate();

		m_pParent->m_Btn_Login.SetButtonSelect(FALSE);
		m_pParent->m_Btn_Login.TriggerInvalidate();

		m_pParent->m_Btn_QuitLogin.SetButtonSelect(FALSE);
		m_pParent->m_Btn_QuitLogin.TriggerInvalidate();

		// 启用检测、系统设置按钮
		m_pParent->m_Btn_SysSetting.EnableWindow(true);
		m_pParent->m_Btn_DetSetting.EnableWindow(true);

		// 显示退出登录按钮，隐藏登录按钮
		m_pParent->m_Btn_QuitLogin.ShowWindow(true);
		m_pParent->m_Btn_Login.ShowWindow(false);

		ShowWindow(SW_HIDE);
	}
	else
		MessageBox("密码错误", "", MB_OK);

	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetWindowText(_T(""));
}


void CLogin::OnBnClickedMfcbuttonClose()
{
	ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
	m_pParent->m_Btn_Login.SetButtonSelect(FALSE);
	m_pParent->m_Btn_Login.TriggerInvalidate();
}


void CLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	Graphics graphics(dc.m_hDC);
	CRect windowrect,rect;
	GetClientRect(&windowrect);

	graphics.DrawImage(m_pBGImage, windowrect.left, windowrect.top, windowrect.Width(), windowrect.Height());

}


void CLogin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}
