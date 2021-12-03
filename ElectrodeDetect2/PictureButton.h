#pragma once
#include "afxbutton.h"
class CPictureButton :
	public CMFCButton
{
private:
	Image*  img_Select;
	Image* img_Normal;
	Image* img_Test;			// 测试
	Image* img_Over;
	Image* img_ForBid;			// 禁止

	CBrush    m_FrameBrush;
	CBrush    m_CommonBrush;

	/* 是否登录 */
	bool m_IsLogin;
	bool m_IsOver;		//  移动到上方
	bool m_IsSelect;	//  选中状态

	int m_BtnType;	// 是否子窗口的按钮，如果是，将按钮底色和父窗口按钮底色区分

	Image* LoadGDIImageFromResource(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance);
	Image* LoadGDIImageFromFile(LPCTSTR pszFileName);
public:
	CPictureButton();
	~CPictureButton();
	virtual void DrawItem(LPDRAWITEMSTRUCT);
	virtual void PreSubclassWindow();
	void TriggerInvalidate();
	void SetButtonOver(bool IsOver);
	void SetButtonSelect(bool IsSelect);
	void SetButtonForBid(bool IsOver);
	void SetButtonType(int BtnType);
	//void LoadNormalImage(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance);
	//void LoadOverImage(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance);
	//void LoadSelectImage(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance);
	//void LoadNormalImage(LPCTSTR pszFileName);
	//void LoadOverImage(LPCTSTR pszFileName);
	//void LoadSelectImage(LPCTSTR pszFileName);
	void LoadNormalImage(Image* srcImage);
	void LoadOverImage(Image* srcImage);
	void LoadSelectImage(Image* srcImage);
	void LoadForBidImage(Image* srcImage);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};

