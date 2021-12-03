#pragma once
#include "afxext.h"


class CColorStatusBar : public CStatusBar
{
public:
	CColorStatusBar(void);
	~CColorStatusBar(void);

public:
	COLORREF* Color;
	CString* Text;

public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetPaneText(int nIndex, LPCTSTR lpszNewText, COLORREF crItemColor);

	DECLARE_MESSAGE_MAP()
};