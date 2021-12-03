#pragma once

#include "PictureButton.h"

// CDlgDetSet_Cycle 对话框
class CElectrodeDetect2Dlg;

class CDlgDetSet_Cycle : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetSet_Cycle)

public:
	CDlgDetSet_Cycle(CWnd* pParent = nullptr, CElectrodeDetect2Dlg* Parent = nullptr);   // 标准构造函数
	virtual ~CDlgDetSet_Cycle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETECTSETTING_ELECYCLE_DIALOG };
#endif

public:
	CElectrodeDetect2Dlg* m_pParent;
	CRect m_ClientRect;

	HBRUSH m_BGCBrush;

	CFont m_MiddleFont;

	Image* Img_SubMit_Normal;
	Image* Img_SubMit_Over;

	CPictureButton m_Btn_SubMit;

public:
	void ChangeSize_Set_1(UINT nID, int x, int y);
	void DisplayPara();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMfcbuttonSubmit();
};
