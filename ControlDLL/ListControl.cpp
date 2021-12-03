#include "pch.h"
#include "ListControl.h"

#define DEFAULT_HEADER_FONT 110
#define DEFAULT_DATA_FONT 100

#define DEFAULT_COLOR_BACK RGB(250,250,250)
#define DEFAULT_COLOR_HEADER RGB(240,240,240)
#define DEFAULT_COLOR_DATA RGB(230,230,230)

#define DEFAULT_COLOR_GRID RGB(180,180,180)

#define TEXT_HEADER_EXTANT 3
#define TEXT_DETAIL_EXTANT 6

#define TEXT_COLOR_WHITE RGB(240,240,240)
#define TEXT_COLOR_BLACK RGB(10,10,10)

CListControlEx::CListControlEx()
{
	RegisterWndClass();

	m_Data_Header.clear();
	m_ColWidth.clear();
	m_Data_Detail.clear();

	m_LClickFunction = NULL; m_pParent = NULL;

	m_HeaderFont.CreatePointFont(DEFAULT_HEADER_FONT, _T("微软雅黑"));
	m_DataFont.CreatePointFont(DEFAULT_DATA_FONT, _T("微软雅黑"));

	m_Fill_Color = DEFAULT_COLOR_BACK;
	m_Header_Color = DEFAULT_COLOR_HEADER;

	m_GridBrush.CreateSolidBrush(DEFAULT_COLOR_GRID);

	CDC dc;
	dc.CreateCompatibleDC(NULL);

	dc.SelectObject(&m_HeaderFont);
	m_HeaderHeight = CSize(dc.GetTextExtent(_T("Test"))).cy;

	dc.SelectObject(&m_DataFont);
	m_DetailHeight = CSize(dc.GetTextExtent(_T("Test"))).cy;

	dc.DeleteDC();

	m_ValidScrollRange_Vertical = 0;
	m_ValidScrollRange_Horizontal = 0;
	m_CurScrollValue_Vertical = 0;

	m_SelectRow = -1;
}

CListControlEx::~CListControlEx()
{

}

BOOL CListControlEx::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, _T("CListControlEx"), &windowclass)))
	{
		windowclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInst;
		windowclass.hIcon = NULL;
		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = _T("CListControlEx");

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CListControlEx, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

BOOL CListControlEx::OnEraseBkgnd(CDC* pDC)
{
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC, m_WndRect.Width(), m_WndRect.Height());

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SelectObject(&MemBitmap);

	MemDC.FillSolidRect(m_WndRect, m_Fill_Color);

	m_HeaderRect = m_WndRect;
	m_DetailRect = m_WndRect;

	int CurX = 0;
	int CurY = 0;

	m_HeaderRect.bottom = m_HeaderRect.top + m_HeaderHeight + TEXT_HEADER_EXTANT * 2;
	m_DetailRect.top = m_HeaderRect.bottom;

	//  绘制数据
	CurX = 0;
	CurY = m_HeaderRect.bottom;
	int ValidDataNum = 0;

	if (m_Data_Detail.size() > 0)
	{
		MemDC.SelectObject(&m_DataFont);

		CRect cellRect;

		COLORREF color;
		COLORREF textColor;

		for (int i = 0; i < m_Data_Detail.size(); i++)
		{
			if (m_Data_Detail[i].size() <= 0)
				continue;

			cellRect.top = m_HeaderRect.bottom - m_CurScrollValue_Vertical + i * (m_DetailHeight + TEXT_DETAIL_EXTANT * 2);
			cellRect.bottom = cellRect.top + m_DetailHeight + TEXT_DETAIL_EXTANT * 2;

			if (cellRect.bottom < m_DetailRect.top || cellRect.top > m_DetailRect.bottom)
				continue;

			if (m_SelectRow == i)
			{
				textColor = TEXT_COLOR_WHITE;
				color = RGB(0, 125, 255);
			}
			else if (m_Data_Color.size() <= 0)
			{
				textColor = TEXT_COLOR_BLACK;
				color = DEFAULT_COLOR_DATA;
			}
			else
			{
				textColor = TEXT_COLOR_BLACK;
				color = m_Data_Color[ValidDataNum % m_Data_Color.size()];
			}

			CurX = 0;

			ValidDataNum++;

			for (int j = 0; j < m_Data_Header.size(); j++)
			{
				cellRect.left = CurX;
				cellRect.right = CurX + m_ColWidth[j];

				if (j == m_Data_Header.size() - 1)
					cellRect.right = m_WndRect.right;

				if (j < m_Data_Detail[i].size())
					DrawCell(&MemDC, cellRect, m_Data_Detail[i][j], color, textColor);
				else
					DrawCell(&MemDC, cellRect, "", color, textColor);

				CurX += m_ColWidth[j];
			}
		}
	}	

	//  绘制表头
	if (m_Data_Header.size() > 0)
	{
		MemDC.SelectObject(&m_HeaderFont);

		CRect cellRect;
		cellRect.top = m_HeaderRect.top;
		cellRect.bottom = m_HeaderRect.bottom;

		CurX = 0;

		for (int i = 0; i < m_Data_Header.size(); i++)
		{
			cellRect.left = CurX;
			cellRect.right = CurX + m_ColWidth[i];

			if (i == m_Data_Header.size() - 1)
				cellRect.right = m_WndRect.right;

			DrawCell(&MemDC, cellRect, m_Data_Header[i], m_Header_Color, TEXT_COLOR_BLACK);
			CurX += m_ColWidth[i];
		}
	}

	// Grid 
	CPen NewPen(PS_SOLID, 1, DEFAULT_COLOR_GRID);		// 创建画笔
	CPen* pOldPen = MemDC.SelectObject(&NewPen);		// 使用SelectObject将画笔载入环境
	MemDC.SelectStockObject(NULL_BRUSH);							

	if (ValidDataNum > 0)
	{
		CurY = m_HeaderRect.bottom - m_CurScrollValue_Vertical;

		for (int i = 0; i < ValidDataNum;)
		{
			CurY += (m_DetailHeight + TEXT_DETAIL_EXTANT * 2);

			if (CurY <= m_DetailRect.top)
				continue;

			if (CurY > m_DetailRect.bottom)
				break;
			i++;

			MemDC.MoveTo(m_WndRect.left, CurY);			// 设置起点 
			MemDC.LineTo(m_WndRect.right, CurY);		// 画线
		}
	}

	if (m_Data_Header.size() > 0)
	{
		CurX = 0;

		for (int i = 0; i < m_Data_Header.size() - 1; i++)
		{
			CurX += m_ColWidth[i];

			MemDC.MoveTo(CurX, m_WndRect.top);
			MemDC.LineTo(CurX, CurY);
		}
		CurY = m_HeaderRect.bottom;
		MemDC.MoveTo(m_WndRect.left, CurY);
		MemDC.LineTo(m_WndRect.right, CurY);
	}

	MemDC.SelectObject(pOldPen);
	NewPen.DeleteObject();


	//  轮廓
	MemDC.FrameRect(m_WndRect, &m_GridBrush);

	pDC->BitBlt(0, 0, m_WndRect.Width(), m_WndRect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	return TRUE;
}

void CListControlEx::DrawCell(CDC* pDC, CRect CellCrect, std::string data, COLORREF backColor, COLORREF textColor)
{
	int TextWidth = CSize(pDC->GetTextExtent(data.c_str())).cx;
	int TextHeight = CSize(pDC->GetTextExtent(data.c_str())).cy;
	
	int x = CellCrect.CenterPoint().x - TextWidth / 2;
	int y = CellCrect.CenterPoint().y - TextHeight / 2;

	if (x <= CellCrect.left)
		x = CellCrect.left + 1;

	pDC->SetTextColor(textColor);
	pDC->FillSolidRect(CellCrect, backColor);
	pDC->TextOut(x, y, data.c_str());
}

void CListControlEx::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect(&m_WndRect);
}

// 右边的自定义ListBox控件的鼠标松开事件
void CListControlEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	ListClickItem ClickInfo;		// 单击listbox时产生的单击事件对象
	bool ret = GetSelectPos(point, ClickInfo);

	if (ret)
	{
		m_SelectRow = ClickInfo.iRow;
		TriggerInvalidate();
	}

	//*****m_LClickFunction是一个函数指针，如果已经它已经有指向，那么他会执行指向的函数
	if (m_LClickFunction != NULL)
		m_LClickFunction(m_pParent, point);

	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CListControlEx::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	GetVerticalScrollValidRange();

	if (m_ValidScrollRange_Vertical <= 0)
		return CWnd::OnMouseWheel(nFlags, zDelta, pt);

	//  响应滚动事件  默认的滚动比例是数据区域的  1/10
	m_CurScrollValue_Vertical += (m_DetailRect.Height() * 0.1 * (zDelta < 0 ? 1 : -1));

	if (m_CurScrollValue_Vertical < 0)
		m_CurScrollValue_Vertical = 0;

	if (m_CurScrollValue_Vertical > m_ValidScrollRange_Vertical)
		m_CurScrollValue_Vertical = m_ValidScrollRange_Vertical;

	TriggerInvalidate();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CListControlEx::TriggerInvalidate()
{
	Invalidate();
	UpdateWindow();
}

void CListControlEx::AddCol(std::vector<std::string> Data_Header, std::vector<int> width, int Pos)
{
	int num = Data_Header.size();

	if (num <= 0 || num <= Pos || Pos < -1)
		return;

	if (Pos == -1)
	{
		for (int i = 0; i < num; i++)
		{
			m_Data_Header.push_back(Data_Header[i]);
			m_ColWidth.push_back(width[i]);
		}
	}
	else
	{
		int InsertIndex = Pos;
		for (int i = 0; i < num; i++)
		{
			m_Data_Header.insert(m_Data_Header.begin() + InsertIndex, Data_Header[i]);
			m_ColWidth.insert(m_ColWidth.begin() + InsertIndex, width[i]);
			InsertIndex++;
		}
	}
}

void CListControlEx::AddCol(std::string Data_Header, int width, int Pos)
{
	if (m_Data_Header.size() <= Pos || Pos < -1)
		return;

	if (Pos == -1)
	{
		m_Data_Header.push_back(Data_Header);
		m_ColWidth.push_back(width);
	}
	else
	{
		m_Data_Header.insert(m_Data_Header.begin() + Pos, Data_Header);
		m_ColWidth.insert(m_ColWidth.begin() + Pos, width);
	}
}

void CListControlEx::SetWidth(int ColIndex, int width)
{
	if (ColIndex >= m_ColWidth.size() || m_ColWidth.size() <= 0 || ColIndex < 0 || width < 0)
		return;

	m_ColWidth[ColIndex] = width;
}

void CListControlEx::SetSelectRow(int iRow)
{
	if (iRow >= m_Data_Detail.size() || iRow < 0)
		return;
	GetClientRect(&m_WndRect);

	m_SelectRow = iRow;

	m_HeaderRect = m_WndRect;
	m_DetailRect = m_WndRect;

	m_HeaderRect.bottom = m_HeaderRect.top + m_HeaderHeight + TEXT_HEADER_EXTANT * 2;
	m_DetailRect.top = m_HeaderRect.bottom;

	int rectTop = m_HeaderRect.bottom - m_CurScrollValue_Vertical + m_SelectRow * (m_DetailHeight + TEXT_DETAIL_EXTANT * 2);
	int rectBottom = rectTop + m_DetailHeight + TEXT_DETAIL_EXTANT * 2;

	int offsetValue = 0;
	if (rectTop < m_DetailRect.top)
		offsetValue = m_DetailRect.top - rectTop;

	if (rectBottom > m_DetailRect.bottom)
		offsetValue = m_DetailRect.bottom - rectBottom;

	m_CurScrollValue_Vertical -= offsetValue;

	if (m_CurScrollValue_Vertical < 0)
		m_CurScrollValue_Vertical = 0;

	GetVerticalScrollValidRange();

	if (m_CurScrollValue_Vertical > m_ValidScrollRange_Vertical)
		m_CurScrollValue_Vertical = m_ValidScrollRange_Vertical;

	TriggerInvalidate();
}

void CListControlEx::AddRow()
{
	std::vector<std::string> newDetail(m_Data_Header.size(), "");
	m_Data_Detail.push_back(newDetail);
}

void CListControlEx::AddRow(std::vector<std::string> Data_Detail)
{
	if (Data_Detail.size() < 0 || m_Data_Header.size() <= 0)
		return;

	std::vector<std::string> tempData;
	for (int i = 0; i < m_Data_Header.size(); i++)
	{
		if (i >= Data_Detail.size())
			tempData.push_back("");
		else
			tempData.push_back(Data_Detail[i]);
	}
	m_Data_Detail.push_back(tempData);
}



void CListControlEx::SetRowData(std::string Data_Detail, int x, int y)
{
	if (y >= m_Data_Detail.size())
		return;

	m_Data_Detail[y][x] = Data_Detail;
}

void CListControlEx::ClearData()
{
	m_SelectRow = -1;
	m_Data_Detail.clear();
	TriggerInvalidate();
}

void CListControlEx::SetHeaderColor(COLORREF color)
{
	m_Header_Color = color;
}

void CListControlEx::AddDataColor(COLORREF color)
{
	m_Data_Color.push_back(color);
}

void CListControlEx::SetDataColor(COLORREF color, int index)
{
	if (m_Data_Color.size() <= index)
		return;

	m_Data_Color[index] = color;
}

void CListControlEx::SetHeaderFontSize(int size)
{
	m_HeaderFont.DeleteObject();
	m_HeaderFont.CreatePointFont(size, _T("微软雅黑"));

	CDC dc;
	dc.CreateCompatibleDC(NULL);

	dc.SelectObject(&m_HeaderFont);
	m_HeaderHeight = CSize(dc.GetTextExtent(_T("Test"))).cy;

	dc.DeleteDC();
}

void CListControlEx::SetDataFontSize(int size)
{
	m_DataFont.DeleteObject();
	m_DataFont.CreatePointFont(size, _T("微软雅黑"));

	CDC dc;
	dc.CreateCompatibleDC(NULL);

	dc.SelectObject(&m_DataFont);
	m_DetailHeight = CSize(dc.GetTextExtent(_T("Test"))).cy;

	dc.DeleteDC();
}

//
void CListControlEx::GetVerticalScrollValidRange()
{
	int DataHeight = (m_DetailHeight + TEXT_DETAIL_EXTANT * 2) * m_Data_Detail.size();

	m_ValidScrollRange_Vertical = DataHeight - m_DetailRect.Height();

	if (m_ValidScrollRange_Vertical < 0)
		m_ValidScrollRange_Vertical = 0;
}

bool CListControlEx::GetSelectPos(CPoint point, ListClickItem& Info)
{
	if (m_Data_Header.size() <= 0)
		return false;

	// PtInRect作用是判断参数中给出的点是否在矩形区域内
	if (m_HeaderRect.PtInRect(point))
	{
		Info.iType = LIST_CLICK_HEADER;

		int xStart = 0, x1 = 0;
		for (int i = 0; i < m_Data_Header.size(); i++)
		{
			x1 = xStart;
			xStart += m_ColWidth[i];

			if (point.x <= x1 || point.x > x1 + m_ColWidth[i])
				continue;

			Info.iCol = i;

			break;
		}
	}
	else if (m_DetailRect.PtInRect(point))
	{
		Info.iType = LIST_CLICK_DETAIL;

		// 行
		if (m_Data_Detail.size() <= 0)
			return false;

		int yStart = m_DetailRect.top - m_CurScrollValue_Vertical, y1 = 0;
		for (int i = 0; i < m_Data_Detail.size(); i++)
		{
			y1 = yStart;
			yStart += (m_DetailHeight + 2 * TEXT_DETAIL_EXTANT);

			if (point.y <= y1 || point.y > y1 + m_DetailHeight + 2 * TEXT_DETAIL_EXTANT)
				continue;

			Info.iRow = i;

			break;
		}

		if (Info.iRow < 0)
			return false;

		// 列
		int xStart = 0, x1 = 0;
		for (int i = 0; i < m_Data_Header.size(); i++)
		{
			x1 = xStart;
			xStart += m_ColWidth[i];

			if (point.x <= x1 || point.x > x1 + m_ColWidth[i])
				continue;

			Info.iCol = i;

			break;
		}
	}

	return true;
}

// 注册一个回调函数，参数1：传入的回调函数地址，参数2：任意类型的指针
// 注意：需要从外部调用
void CListControlEx::RegisterCallbackFunction(ptrCallBackListFun UserFunction, void* parm)
{
	m_LClickFunction = UserFunction;
	m_pParent = parm;
}