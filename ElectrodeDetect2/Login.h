#pragma once

#include "PictureButton.h"

// CLogin 对话框
class CElectrodeDetect2Dlg;

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = nullptr, CElectrodeDetect2Dlg* Parent = nullptr);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

public:
	ULONG_PTR m_gdiplusToken;
	CElectrodeDetect2Dlg* m_pParent;				// 父窗口

	CRect m_VisionCameraRectSize;

	Image* m_pBGImage;				// 背景图

	Image* Img_Close_Normal;
	Image* Img_Close_Over;
	Image* Img_Login_Normal;
	Image* Img_Login_Over;
	Image* Img_Cancel_Normal;
	Image* Img_Cancel_Over;

	CPictureButton m_Btn_Close;
	CPictureButton m_Btn_Login;
	CPictureButton m_Btn_Cancel;
public:
	void ChangeSize_VisionPassword(UINT nID, int x, int y);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedMfcbuttonCancel();
	afx_msg void OnBnClickedMfcbuttonPaslogin();
	afx_msg void OnBnClickedMfcbuttonClose();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
