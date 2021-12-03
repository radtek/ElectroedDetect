#pragma once

#include "pch.h"
//#include "ZcStruct.h"

#include ".\..\ControlDLL\ImageControl.h"

#include "ElectrodeDetect2Dlg.h"

#include "PictureButton.h"

// CDlgDetSet 检测设置对话框
class CElectrodeDetect2Dlg;
class CDlgDetSet_Cycle;
class CDlgDetSet_HalfCycle;
class CDlgDetSet_UpBack;

class CDlgDetSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetSet)

public:
	CDlgDetSet(CWnd* pParent = nullptr, CElectrodeDetect2Dlg* Parent = nullptr);   // 标准构造函数
	virtual ~CDlgDetSet();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETECTSETTING_DIALOG };
#endif

public:
	ULONG_PTR m_gdiplusToken;
	CElectrodeDetect2Dlg* m_pParent;						// 父窗口
	CRect m_ClientRect;

	CFont m_BigFont;
	CFont m_MiddleFont;
	CFont m_BoldFont;

	HBRUSH m_BGCBrush;
	Image* m_pBGImage;
	Image* Img_Close_Normal;
	Image* Img_Close_Over;
	Image* Img_Load_Normal;
	Image* Img_Load_Over;
	Image* Img_PrevImg_Normal;
	Image* Img_PrevImg_Over;
	Image* Img_NextImg_Normal;
	Image* Img_NextImg_Over;
	Image* Img_SubMit_Normal;
	Image* Img_SubMit_Over;

	cv::Mat m_LocalImage;
	std::vector<CString> m_LocalImageName;		// 图片名称
	CString m_LocalImageFolder;					// 图片文件路径

	int m_SelectButton;			// 左边被选中的按钮
	int m_LocalImageIndex;

	// 子窗口
	CDlgDetSet_Cycle* m_DlgDetSetCycle;
	CDlgDetSet_UpBack* m_DlgDetSetUpBack;

	CImageControl m_ShowImgControl;
	CPictureButton m_Btn_Close;
	CPictureButton m_Btn_Load;
	CPictureButton m_Btn_PrevImg;
	CPictureButton m_Btn_NextImg;
	CPictureButton m_Btn_SubMit;

public:
	void ChangeSize_Set(UINT nID, int x, int y);
	void InitMfcButtonStyle(int nID, COLORREF crFace, COLORREF crText);
	void SetMfcButtonStyle(int nID, COLORREF crFace, COLORREF crText);
	void SwitchParaWindow(int SelectedButton);
	void ShowDetSetHalfCYCLERegion();
	void ShowDetSetCYCLERegion();
	void ShowDetSetUpBackRegion();
	void FindLocalFile(char* lpPath);
	void LoadLocalImage();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbutton1();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMfcbuttonCycle();
	afx_msg void OnBnClickedMfcbuttonUpback();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMfcbuttonLoad();
	afx_msg void OnBnClickedMfcbuttonPrevimg();
	afx_msg void OnBnClickedMfcbuttonNextimg();
	afx_msg void OnBnClickedMfcbuttonSubmit();
};
