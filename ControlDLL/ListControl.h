/* ListControl
* 自定义控件, Class使用 CListControlEx
*/

#pragma once
#include <afxwin.h>
#include <string>
#include <vector>

#include "ControlDLL.h"

#define LIST_CLICK_NULL 0
#define LIST_CLICK_HEADER 1
#define LIST_CLICK_DETAIL 2

typedef void(*ptrCallBackListFun)(void* parm, CPoint point);		// 函数指针指向匿名函数的指针

typedef std::vector<std::vector<std::string>> MatString;

typedef struct tagListClickItem 
{
	int iRow;
	int iCol;
	int iType;

	tagListClickItem()
	{
		iRow = -1; iCol = -1; iType = LIST_CLICK_NULL;
	};
}ListClickItem;

class DLL_API CListControlEx : public CWnd
{
	DECLARE_MESSAGE_MAP()
public:
	CListControlEx();
	~CListControlEx();

public:
	void TriggerInvalidate();

	// Size
	void SetHeaderFontSize(int size);
	void SetDataFontSize(int size);

	// Color
	void SetHeaderColor(COLORREF color);
	void AddDataColor(COLORREF color);
	void SetDataColor(COLORREF color, int index);

	// Header Info
	void AddCol(std::vector<std::string> Data_Header, std::vector<int> width, int Pos = -1);
	void AddCol(std::string Data_Header, int width, int Pos = -1);
	void SetWidth(int ColIndex, int width);

	// Detail Info
	void AddRow();
	void AddRow(std::vector<std::string> Data_Detail);
	void SetRowData(std::string Data_Detail, int x, int y);	
	void ClearData();

	// CallBack
	void RegisterCallbackFunction(ptrCallBackListFun UserFunction, void* parm);

	void SetSelectRow(int iRow);
	bool GetSelectPos(CPoint point, ListClickItem& Info);

protected:
	void* m_pParent;

	CRect m_WndRect;
	CRect m_HeaderRect;
	CRect m_DetailRect;

	CFont m_HeaderFont;
	CFont m_DataFont;

	CBrush m_GridBrush;

	COLORREF m_Fill_Color;
	COLORREF m_Header_Color;
	std::vector<COLORREF> m_Data_Color;	 

	std::vector<std::string> m_Data_Header;

	std::vector<int> m_ColWidth;

	MatString m_Data_Detail;

	int m_HeaderHeight;
	int m_DetailHeight;

	int m_ValidScrollRange_Vertical;
	int m_ValidScrollRange_Horizontal;

	int m_CurScrollValue_Vertical;

	int m_SelectRow;
protected:
	BOOL RegisterWndClass();
	void DrawCell(CDC* pDC, CRect CellCrect, std::string data, COLORREF backColor, COLORREF textColor);

	void GetVerticalScrollValidRange();

	ptrCallBackListFun m_LClickFunction;
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};