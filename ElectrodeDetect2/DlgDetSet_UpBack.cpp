// DlgDetSet_UpBack.cpp: 实现文件
//

#include "pch.h"
#include "ElectrodeDetect2.h"
#include "DlgDetSet_UpBack.h"
#include "afxdialogex.h"


// CDlgDetSet_UpBack 对话框
#include "ElectrodeDetect2Dlg.h"

IMPLEMENT_DYNAMIC(CDlgDetSet_UpBack, CDialogEx)

CDlgDetSet_UpBack::CDlgDetSet_UpBack(CWnd* pParent, CElectrodeDetect2Dlg* Parent)
	: CDialogEx(IDD_DETECTSETTING_UPBACK_DIALOG, pParent)
{
	m_pParent = Parent;
}

CDlgDetSet_UpBack::~CDlgDetSet_UpBack()
{
}

void CDlgDetSet_UpBack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDetSet_UpBack, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgDetSet_UpBack 消息处理程序


void CDlgDetSet_UpBack::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ChangeSize_Set_1(IDC_STATIC_ELEUPBACK,cx,cy);
}


BOOL CDlgDetSet_UpBack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetClientRect(&m_ClientRect);

	m_BGCBrush = CreateSolidBrush(COLOR_DETBACKGROUND);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgDetSet_UpBack::ChangeSize_Set_1(UINT nID, int x, int y)
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
		tempRect.top = tempRect.top * y / m_ClientRect.Height() + 7;
		tempRect.bottom = tempRect.bottom * y / m_ClientRect.Height() - 7;
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


void CDlgDetSet_UpBack::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);

	dc.FillSolidRect(rect,COLOR_DETBACKGROUND);
}


HBRUSH CDlgDetSet_UpBack::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
