#pragma once


// CDlgDetSet_UpBack 对话框
class CElectrodeDetect2Dlg;

class CDlgDetSet_UpBack : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetSet_UpBack)

public:
	CDlgDetSet_UpBack(CWnd* pParent = nullptr, CElectrodeDetect2Dlg* Parent = nullptr);   // 标准构造函数
	virtual ~CDlgDetSet_UpBack();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETECTSETTING_UPBACK_DIALOG };
#endif

public:
	CElectrodeDetect2Dlg* m_pParent;				// 父窗口
	CRect m_ClientRect;

	HBRUSH m_BGCBrush;

public:
	void ChangeSize_Set_1(UINT nID, int x, int y);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
