#pragma once

#include "pch.h"
#include "ZcStruct.h"
#include "PictureButton.h"

// CDlgSysSet 系统设置对话框
class CElectrodeDetect2Dlg;


class CDlgSysSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSysSet)

public:
	CDlgSysSet(CWnd* pParent = nullptr, CElectrodeDetect2Dlg* Parent = nullptr);   // 标准构造函数
	virtual ~CDlgSysSet();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMSETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	ULONG_PTR m_gdiplusToken;
	CElectrodeDetect2Dlg* m_pParent;				// 父窗口
	CRect m_ClientRect;

	CFont m_BigFont;
	CFont m_MiddleFont;
	CFont m_BoldFont;

	int m_SelectButton;			// 左边被选中的按钮

	Image* m_pBGImage;
	Image* Img_Close_Normal;
	Image* Img_Close_Over;
	Image* Img_StartGrab_Normal;
	Image* Img_StartGrab_Over;
	Image* Img_StartGrab_ForBid;
	Image* Img_StopGrab_Normal;
	Image* Img_StopGrab_Over;

	CPictureButton m_Btn_Close;
	CPictureButton m_Btn_Cam1_State;
	CPictureButton m_Btn_Cam2_State;

	HBRUSH m_WriteBrush;
	HBRUSH m_hBrush;
	HBRUSH m_BGCBrush;

public:
	void ChangeSize_Set(UINT nID, int x, int y);
	void InitMfcButtonStyle(int nID, COLORREF crFace, COLORREF crText);
	void SetMfcButtonStyle(int nID, COLORREF crFace, COLORREF crText);

public:
	afx_msg void OnBnClickedMfcbuttonClose();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMfcbuttonCam2State();
	afx_msg void OnBnClickedMfcbuttonCam1State();
	afx_msg void OnBnClickedCheckSaveOk();
	afx_msg void OnBnClickedCheckSaveNg();
	afx_msg void OnEnChangeEditDiskProp();
};
