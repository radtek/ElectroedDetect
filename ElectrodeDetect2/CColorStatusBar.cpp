#include "pch.h"
#include "CColorStatusBar.h"

CColorStatusBar::CColorStatusBar(void)
{
	Color = new COLORREF[8];
	Text = new CString[8];
}

CColorStatusBar::~CColorStatusBar(void)
{
	if (Color != NULL)
	{
		delete[]Color;
	}

	if (Text != NULL)
	{
		delete[]Text;
	}
}

BEGIN_MESSAGE_MAP(CColorStatusBar, CStatusBar)

END_MESSAGE_MAP()

void CColorStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//DRAWITEMSTRUCT 为需要自绘的控件或者菜单项提供了必要的信息
	
	//获取ID
	UINT unID = lpDrawItemStruct->itemID;
	CDC dc;
	//hDC附加到CDC对象
	dc.Attach(lpDrawItemStruct->hDC);
	//设置设备上下文对象的背景模式为
	dc.SetBkMode(TRANSPARENT);
	//lpDrawItemStruct->rcItem指定了将被绘制的矩形区域
	//创建一个矩形区域
	CRect rect(&lpDrawItemStruct->rcItem);
	//设置颜色 Color[unID]--根据ID传值设置颜色
	dc.SetTextColor(Color[unID]);
	//输出 Text[unID]根据ID传值设置文本
	dc.TextOut(rect.left + 1, rect.top, Text[unID]);
	//分离DC
	dc.Detach();
}


void CColorStatusBar::SetPaneText(int nIndex, LPCTSTR lpszNewText, COLORREF crItemColor)
{
	//给数组赋值
	Text[nIndex] = lpszNewText;
	Color[nIndex] = crItemColor;
	//在一个状态条控件的给定部分中设置文本 SBT_OWNERDRAW| SBT_NOBORDERS -组合使用没有3D外观
	GetStatusBarCtrl().SetText("", nIndex, SBT_OWNERDRAW | SBT_NOBORDERS);
}