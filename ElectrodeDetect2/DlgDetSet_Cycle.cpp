// DlgDetSet_Cycle.cpp: 实现文件
//

#include "pch.h"
#include "ElectrodeDetect2.h"
#include "DlgDetSet_Cycle.h"
#include "afxdialogex.h"

#include "ElectrodeDetect2Dlg.h"

// CDlgDetSet_Cycle 对话框

IMPLEMENT_DYNAMIC(CDlgDetSet_Cycle, CDialogEx)

CDlgDetSet_Cycle::CDlgDetSet_Cycle(CWnd* pParent,CElectrodeDetect2Dlg* Parent)
	: CDialogEx(IDD_DETECTSETTING_ELECYCLE_DIALOG, pParent)
{
	m_pParent = Parent;
}

CDlgDetSet_Cycle::~CDlgDetSet_Cycle()
{
}

void CDlgDetSet_Cycle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_SUBMIT, m_Btn_SubMit);
}


BEGIN_MESSAGE_MAP(CDlgDetSet_Cycle, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MFCBUTTON_SUBMIT, &CDlgDetSet_Cycle::OnBnClickedMfcbuttonSubmit)
END_MESSAGE_MAP()


// CDlgDetSet_Cycle 消息处理程序

BOOL CDlgDetSet_Cycle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetClientRect(&m_ClientRect);

	m_BGCBrush = CreateSolidBrush(COLOR_DETBACKGROUND);
	m_MiddleFont.CreatePointFont(97, _T("微软雅黑"));

	((CStatic*)GetDlgItem(IDC_STATIC_Top))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_CYCLE_LENGTH))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_CYCLE_DEV))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_COMPENSATION))->SetFont(&m_MiddleFont);

	((CStatic*)GetDlgItem(IDC_STATIC_BOTTOM))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_HALFCYCLE_LENGTH2))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_HALFCYCLE_DEV2))->SetFont(&m_MiddleFont);
	((CStatic*)GetDlgItem(IDC_STATIC_HALFCYCLE_COMPENSATION2))->SetFont(&m_MiddleFont);

	DisplayPara();

	/* 加载图片至按钮 */
	char imgPath[1024] = { '\0' };
	// 应用按钮
	sprintf_s(imgPath, "%s\\Image\\应用_Normal.png", m_pParent->AppPath);
	Img_SubMit_Normal = m_pParent->LoadFromFile(imgPath);
	sprintf_s(imgPath, "%s\\Image\\应用_Over.png", m_pParent->AppPath);
	Img_SubMit_Over = m_pParent->LoadFromFile(imgPath);

	m_Btn_SubMit.LoadNormalImage(Img_SubMit_Normal);
	m_Btn_SubMit.LoadOverImage(Img_SubMit_Over);
	m_Btn_SubMit.SetButtonType(2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgDetSet_Cycle::ChangeSize_Set_1(UINT nID, int x, int y)
{
	CRect tempRect;

	CWnd* pWnd = GetDlgItem(nID);

	/* 判断是否是文本框 */
	bool isEdit = FALSE;
	char className[20];
	GetClassName(pWnd->GetSafeHwnd(), className, 20);
	isEdit = strcmp(className, "Edit") == 0;

	if (pWnd == NULL)
		return;

	pWnd->GetWindowRect(&tempRect);
	ScreenToClient(&tempRect);

	if (isEdit)
	{
		tempRect.left = tempRect.left * x / m_ClientRect.Width();
		tempRect.top = tempRect.top * y / m_ClientRect.Height() + 2;
		tempRect.bottom = tempRect.bottom * y / m_ClientRect.Height() - 2;
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


void CDlgDetSet_Cycle::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//// TODO: 在此处添加消息处理程序代码
	ChangeSize_Set_1(IDC_STATIC_Top, cx, cy);
	ChangeSize_Set_1(IDC_STATIC_CYCLE_LENGTH, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_CYCLE_LENGTH, cx, cy);
	ChangeSize_Set_1(IDC_STATIC_CYCLE_DEV, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_CYCLE_DEV, cx, cy);
	ChangeSize_Set_1(IDC_STATIC_COMPENSATION, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_COMPENSATION, cx, cy);

	ChangeSize_Set_1(IDC_STATIC_BOTTOM, cx, cy);
	ChangeSize_Set_1(IDC_STATIC_HALFCYCLE_LENGTH2, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_HALFCYCLE_LENGTH, cx, cy);
	ChangeSize_Set_1(IDC_STATIC_HALFCYCLE_DEV2, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_HALFCYCLE_DEV, cx, cy);
	ChangeSize_Set_1(IDC_STATIC_HALFCYCLE_COMPENSATION2, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_COMPENSATION2, cx, cy);

	ChangeSize_Set_1(IDC_STATIC_CYCLE_YRES, cx, cy);
	ChangeSize_Set_1(IDC_EDIT_CYCLE_YRES, cx, cy);
	ChangeSize_Set_1(IDC_CHECK_NORMAL_DISPLAYTOOL, cx, cy);

	ChangeSize_Set_1(IDC_MFCBUTTON_SUBMIT, cx, cy);
}


void CDlgDetSet_Cycle::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, COLOR_DETBACKGROUND);
}


HBRUSH CDlgDetSet_Cycle::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CDlgDetSet_Cycle::DisplayPara()
{
	CString str;

	str.Format("%.4f", m_pParent->m_YResolution);
	((CEdit*)GetDlgItem(IDC_EDIT_CYCLE_YRES))->SetWindowText(str);

	str.Format("%.3f", m_pParent->m_CyclePara.stdCycleLength);
	((CEdit*)GetDlgItem(IDC_EDIT_CYCLE_LENGTH))->SetWindowText(str);

	str.Format("%.3f", m_pParent->m_CyclePara.dev);
	((CEdit*)GetDlgItem(IDC_EDIT_CYCLE_DEV))->SetWindowText(str);

	str.Format("%.3f", m_pParent->m_HalfCyclePara.stdCycleLength);
	((CEdit*)GetDlgItem(IDC_EDIT_HALFCYCLE_LENGTH))->SetWindowText(str);

	str.Format("%.3f", m_pParent->m_HalfCyclePara.dev);
	((CEdit*)GetDlgItem(IDC_EDIT_HALFCYCLE_DEV))->SetWindowText(str);

	str.Format("%.0f", m_pParent->m_PtrCSIVisionIn->CycleDetectCompensation);
	((CEdit*)GetDlgItem(IDC_EDIT_COMPENSATION))->SetWindowText(str);

	str.Format("%.0f", m_pParent->m_PtrCSIVisionIn->HalfDetectCompensation);
	((CEdit*)GetDlgItem(IDC_EDIT_COMPENSATION2))->SetWindowText(str);
}


void CDlgDetSet_Cycle::OnBnClickedMfcbuttonSubmit()
{
	CString str;

	((CEdit*)GetDlgItem(IDC_EDIT_CYCLE_YRES))->GetWindowText(str);
	m_pParent->m_YResolution = _ttof(str);

	((CEdit*)GetDlgItem(IDC_EDIT_CYCLE_LENGTH))->GetWindowText(str);
	m_pParent->m_CyclePara.stdCycleLength = _ttof(str);

	((CEdit*)GetDlgItem(IDC_EDIT_CYCLE_DEV))->GetWindowText(str);
	m_pParent->m_CyclePara.dev = _ttof(str);

	((CEdit*)GetDlgItem(IDC_EDIT_HALFCYCLE_LENGTH))->GetWindowText(str);
	m_pParent->m_HalfCyclePara.stdCycleLength = _ttof(str);

	((CEdit*)GetDlgItem(IDC_EDIT_HALFCYCLE_DEV))->GetWindowText(str);
	m_pParent->m_HalfCyclePara.dev = _ttof(str);

	((CEdit*)GetDlgItem(IDC_EDIT_COMPENSATION))->GetWindowText(str);
	m_pParent->m_PtrCSIVisionIn->CycleDetectCompensation = _ttof(str);

	((CEdit*)GetDlgItem(IDC_EDIT_COMPENSATION2))->GetWindowText(str);
	m_pParent->m_PtrCSIVisionIn->HalfDetectCompensation = _ttof(str);
}
