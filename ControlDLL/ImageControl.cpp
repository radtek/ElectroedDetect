#include "pch.h"
#include "ImageControl.h"

#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)
#define DIBWIDTHBYTES(bi) (DWORD)WIDTHBYTES((DWORD)(bi).biWidth * (DWORD)(bi).biBitCount)
#define _DIBSIZE(bi) (DIBWIDTHBYTES(bi) * (DWORD)(bi).biHeight)
#define DIBSIZE(bi) ((bi).biHeight < 0 ? (-1)*(_DIBSIZE(bi)) : _DIBSIZE(bi))

#define PICKRADIUS 5

#define COLOR_TOOL RGB(210, 150, 70)
#define COLOR_NG RGB(230,40,40)
#define COLOR_OK RGB(540,230,40)
#define COLOR_TEXT RGB(70,80,220)

CImageControl::CImageControl()
{
	RegisterWndClass();

	m_pParent = NULL;
	m_Image_Data = NULL;
	m_Disp_Data = NULL;
	m_Mark_Data = NULL;

	m_pBitmapInfo = NULL;
	m_Image_Width = 0;
	m_Image_Height = 0;
	m_Image_Channel = 0;

	m_Disp_Width = 0;
	m_Disp_Height = 0;

	m_ImgIndex = -1;

	m_Max_Region_Width = 0;
	m_Max_Region_Height = 0;
	m_LeftButtonDown = false;  m_RightButtonDown = false;  m_DrawMode = ACTION_NULL;

	m_IsHideMark = false;

	m_Fill_Color = RGB(156, 151, 146);

	m_DrawSize = 1;

	m_DisplayFont.CreateFont(18,                    //   字体的高度   
		0,                                          //   字体的宽度  
		0,                                          //   nEscapement 
		0,                                          //   nOrientation   
		FW_BOLD,                                    //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                          //   cStrikeOut   
		ANSI_CHARSET,                               //   nCharSet   
		OUT_DEFAULT_PRECIS,                         //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,                        //   nClipPrecision   
		DEFAULT_QUALITY,                            //   nQuality   
		DEFAULT_PITCH | FF_SWISS,                   //   nPitchAndFamily     
		_T("宋体"));
}

CImageControl::~CImageControl()
{

}

BOOL CImageControl::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, _T("CImageControl"), &windowclass)))
	{
		windowclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInst;
		windowclass.hIcon = NULL;
		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = _T("CImageControl");

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CImageControl, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CImageControl::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC, m_WndRect.Width(), m_WndRect.Height());

	MemDC.SelectObject(&MemBitmap);
	MemDC.SelectObject(&m_DisplayFont);
	MemDC.SetBkMode(TRANSPARENT);

	if (m_Disp_Height > 0 && m_Disp_Width > 0)
	{
		m_Scale_H = (double)m_ImageRect.Height() / (m_Disp_Y2 - m_Disp_Y1 + 1);
		m_Scale_W = (double)m_ImageRect.Width() / (m_Disp_X2 - m_Disp_X1 + 1);

		// 更新图片
		DisplayImage(&MemDC);

		if (m_FillRect1.left >= 0)
			MemDC.FillSolidRect(m_FillRect1, m_Fill_Color);

		if (m_FillRect2.left >= 0)
			MemDC.FillSolidRect(m_FillRect2, m_Fill_Color);
	}

	DisplayResult(&MemDC);

	pDC->BitBlt(0, 0, m_WndRect.Width(), m_WndRect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	return TRUE;
}

void CImageControl::SetFillColor(COLORREF color)
{
	m_Fill_Color = color;
	TriggerInvalidate();
}

void CImageControl::DisplayResult(CDC* pDC)
{
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetTextColor(RGB(0, 220, 0));

	CFont font_num, font_dis;
	font_dis.CreatePointFont(100, "微软雅黑");
	font_num.CreatePointFont(130, "微软雅黑");
	pDC->SelectObject(font_num);

	CString str_Picid,str_Distance,str_HalfDistance;

	if (m_ImgIndex >= 0)
	{
		str_Picid.Format("%d", m_ImgIndex);
		str_Distance.Format("%.4f", m_Dalsa_CycleDistance);
		str_HalfDistance.Format("%.4f", m_Dalsa_HalfCycleDistance);
	}
	else
	{
		str_Picid.Format("无图片");
	}

	switch (m_ImageControl_Id)
	{
	case 1:
	{
		pDC->SetTextColor(COLOR_OK);
		// TextOut是写入文字到屏幕上
		pDC->TextOut(4, 4, str_Picid, strlen(str_Picid.GetBuffer()));

		if (m_Dalsa_IsDetPass)
			pDC->SetTextColor(COLOR_OK);
		else
			pDC->SetTextColor(COLOR_NG);

		// 周期和半周期长度
		pDC->SelectObject(font_dis);
		pDC->TextOut(100, 4, str_Distance, strlen(str_Distance.GetBuffer()));
		pDC->TextOut(100, 20, str_HalfDistance, strlen(str_HalfDistance.GetBuffer()));
		break;
	}
	case 2:
	{
		pDC->SelectObject(font_num);
		pDC->SetTextColor(COLOR_OK);
		// TextOut是写入文字到屏幕上
		pDC->TextOut(22, 5, str_Picid, strlen(str_Picid.GetBuffer()));
		break;
	}
	case 3:
		break;
	default:
		break;
	}

}

void CImageControl::SetImgControlId(int ImgControlId)
{
	m_ImageControl_Id = ImgControlId;
}

void CImageControl::DisplayImage(CDC* pDC)
{
	UpdataDisplayImageData();

	pDC->SetStretchBltMode(HALFTONE);

	StretchDIBits(pDC->GetSafeHdc(),
		m_ImageRect.left, m_ImageRect.top, m_ImageRect.Width(), m_ImageRect.Height(),
		0, m_Disp_Height,
		m_Disp_Width, -m_Disp_Height,
		m_Disp_Data, m_pBitmapInfo,
		DIB_RGB_COLORS, SRCCOPY);
}

void CImageControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_LeftButtonDown = true;

	if (m_DrawMode != ACTION_NULL)
	{
		ZC::PointF fPoint;
		TranslateWindowPointToImagePoint(point, fPoint);

		int x = fPoint.x - 0.2;
		int y = fPoint.y - 1;

		for (int i = y - m_DrawSize; i <= y + m_DrawSize; i++)
		{
			for (int j = x - m_DrawSize; j <= x + m_DrawSize; j++)
			{
				if (j >= 0 && i >= 0 && j < m_Image_Width && i < m_Image_Height)
				{
					if (m_DrawMode == ACTION_DRAW)
						m_Mark_Data[i * m_Image_Width + j] = 255;
					else if (m_DrawMode == ACTION_ERASE)
						m_Mark_Data[i * m_Image_Width + j] = 0;
				}
			}
		}
		TriggerInvalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CImageControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_LeftButtonDown = false;

	CWnd::OnLButtonUp(nFlags, point);
}

void CImageControl::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_RightButtonDown = true;
	m_MousePt = point;

	CWnd::OnRButtonDown(nFlags, point);
}

void CImageControl::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_RightButtonDown = false;

	CWnd::OnRButtonUp(nFlags, point);
}

BOOL CImageControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0)
		m_Zoom_Value += 0.5;
	else
		m_Zoom_Value -= 0.5;

	m_MousePt = pt;

	UpdataDisplayScaleInfo();

	TriggerInvalidate();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageControl::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT csTME;
	csTME.cbSize = sizeof(csTME);
	csTME.dwFlags = TME_LEAVE | TME_HOVER;
	csTME.hwndTrack = m_hWnd;
	csTME.dwHoverTime = 10;
	::_TrackMouseEvent(&csTME);

	if (m_RightButtonDown)
	{
		if (m_Zoom_Value > 1)
		{
			int xOffset = int((point.x - m_MousePt.x) / m_Scale_W + 0.5);
			int yOffset = int((point.y - m_MousePt.y) / m_Scale_H + 0.5);

			m_Disp_X1 -= xOffset;	m_Disp_X2 -= xOffset;
			m_Disp_Y1 -= yOffset;	m_Disp_Y2 -= yOffset;

			m_MousePt = point;
			TriggerInvalidate();
		}
	}

	if (m_LeftButtonDown && m_DrawMode != ACTION_NULL)
	{
		ZC::PointF fPoint;
		TranslateWindowPointToImagePoint(point, fPoint);

		int x = fPoint.x - 0.2;
		int y = fPoint.y - 1;

		for (int i = y - m_DrawSize; i <= y + m_DrawSize; i++)
		{
			for (int j = x - m_DrawSize; j <= x + m_DrawSize; j++)
			{
				if (j >= 0 && i >= 0 && j < m_Image_Width && i < m_Image_Height)
				{
					if (m_DrawMode == ACTION_DRAW)
						m_Mark_Data[i * m_Image_Width + j] = 255;
					else if (m_DrawMode == ACTION_ERASE)
						m_Mark_Data[i * m_Image_Width + j] = 0;
				}
			}
		}
		TriggerInvalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CImageControl::OnMouseLeave()
{
	m_LeftButtonDown = false;
	m_RightButtonDown = false;
	CWnd::OnMouseLeave();
}

void CImageControl::UpdataDisplayImageData()
{
	int hIndex = 0, wIndex = 0, ImagePosition = 0, TempPosition = 0;

	m_Disp_Width = m_Disp_X2 - m_Disp_X1 + 1;
	m_Disp_Height = m_Disp_Y2 - m_Disp_Y1 + 1;

	for (hIndex = m_Disp_Y1; hIndex <= m_Disp_Y2; hIndex++)
	{
		for (wIndex = m_Disp_X1; wIndex <= m_Disp_X2; wIndex++)
		{
			TempPosition = (hIndex - m_Disp_Y1) * m_Disp_Width * m_Image_Channel + (wIndex - m_Disp_X1) * m_Image_Channel;

			if (hIndex < 0 || wIndex < 0 || hIndex >= m_Image_Height || wIndex >= m_Image_Width)
			{
				memset(m_Disp_Data + TempPosition, 128, m_Image_Channel);
				continue;
			}

			ImagePosition = (hIndex * m_Image_Width + wIndex) * m_Image_Channel;

			memcpy(m_Disp_Data + TempPosition, m_Image_Data + ImagePosition, m_Image_Channel);

			if (m_DrawMode != ACTION_NULL && !m_IsHideMark)
			{
				if (m_Mark_Data[hIndex * m_Image_Width + wIndex] != 0)
				{
					m_Disp_Data[TempPosition + 2] = 255;

					m_Disp_Data[TempPosition + 1] = 0;
					m_Disp_Data[TempPosition] = 0;
				}
					
			}
		}
	}
	m_pBitmapInfo->bmiHeader.biHeight = m_Disp_Height;
	m_pBitmapInfo->bmiHeader.biWidth = m_Disp_Width;
}

void CImageControl::UpdataDisplayScaleInfo()
{
	if (m_Zoom_Value <= 1)
	{
		m_Zoom_Value = 1;
		m_Disp_X1 = 0;
		m_Disp_X2 = m_Image_Width - 1;

		m_Disp_Y1 = 0;
		m_Disp_Y2 = m_Image_Height - 1;

		return;
	}

	int CutImageHeight = round(float(m_Image_Height) / m_Zoom_Value);
	int CutImageWidth = round(float(m_Image_Width) / m_Zoom_Value);

	if (CutImageWidth % 4 > 0)
		CutImageWidth = (CutImageWidth / 4) * 4;

	CPoint ClientPoint;
	ClientPoint = m_MousePt;

	int xOffset = 0;
	int yOffset = 0;
	double xPosRatio = 0;
	double yPosRatio = 0;

	CPoint RelativePos;

	CRect rect;
	rect = m_ImageRect;
	ClientToScreen(rect);

	//鼠标图像控件的坐标
	RelativePos.x = ClientPoint.x - rect.left + 1;
	RelativePos.y = ClientPoint.y - rect.top + 1;

	//鼠标在图像控件中的比例
	xPosRatio = double(RelativePos.x) / m_ImageRect.Width();
	yPosRatio = double(RelativePos.y) / m_ImageRect.Height();

	//由当前显示的图片范围以及比例，计算鼠标位置的像素坐标
	xOffset = (m_Disp_X2 - m_Disp_X1 + 1) * xPosRatio + 1 + m_Disp_X1;
	yOffset = (m_Disp_Y2 - m_Disp_Y1 + 1) * yPosRatio + 1 + m_Disp_Y1;

	//更新显示图片的范围
	m_Disp_X1 = int(xOffset - CutImageWidth * xPosRatio);
	m_Disp_X2 = m_Disp_X1 + CutImageWidth - 1;

	m_Disp_Y1 = int(yOffset - CutImageHeight * yPosRatio);
	m_Disp_Y2 = m_Disp_Y1 + CutImageHeight - 1;
}

void CImageControl::TriggerInvalidate()
{
	Invalidate();
	UpdateWindow();
}

void CImageControl::InitImageBuffer()
{
	if (m_Image_Data != NULL)
	{
		free(m_Image_Data);
		m_Image_Data = NULL;
	}

	if (m_Disp_Data != NULL)
	{
		free(m_Disp_Data);
		m_Disp_Data = NULL;
	}

	if (m_Mark_Data != NULL)
	{
		free(m_Mark_Data);
		m_Mark_Data = NULL;
	}

	if (m_pBitmapInfo != NULL)
	{
		free(m_pBitmapInfo);
		m_pBitmapInfo = NULL;
	}

	int DataSize = m_Image_Width * m_Image_Height * m_Image_Channel;

	if (DataSize <= 0)
		return;

	m_Image_Data = (unsigned char*)malloc(DataSize);
	memset(m_Image_Data, 0, DataSize);

	m_Disp_Data = (unsigned char*)malloc(DataSize);
	memset(m_Disp_Data, 0, DataSize);

	m_Mark_Data = (unsigned char*)malloc(m_Image_Width * m_Image_Height);
	memset(m_Disp_Data, 0, m_Image_Width * m_Image_Height);

	if (m_Image_Channel == 1)
	{
		m_pBitmapInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
		m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pBitmapInfo->bmiHeader.biPlanes = 1;
		m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
		m_pBitmapInfo->bmiHeader.biClrUsed = 0;
		m_pBitmapInfo->bmiHeader.biClrImportant = 0;
		m_pBitmapInfo->bmiHeader.biBitCount = 8;
		m_pBitmapInfo->bmiHeader.biHeight = m_Image_Height;
		m_pBitmapInfo->bmiHeader.biWidth = m_Image_Width;
		m_pBitmapInfo->bmiHeader.biSizeImage = DIBSIZE(m_pBitmapInfo->bmiHeader);

		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbRed = BYTE(i);
			m_pBitmapInfo->bmiColors[i].rgbBlue = BYTE(i);
			m_pBitmapInfo->bmiColors[i].rgbGreen = BYTE(i);
			m_pBitmapInfo->bmiColors[i].rgbReserved = BYTE(0);
		}
	}
	else
	{
		m_pBitmapInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO));
		m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pBitmapInfo->bmiHeader.biPlanes = 1;
		m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
		m_pBitmapInfo->bmiHeader.biClrUsed = 0;
		m_pBitmapInfo->bmiHeader.biClrImportant = 0;
		m_pBitmapInfo->bmiHeader.biBitCount = 24;
		m_pBitmapInfo->bmiHeader.biHeight = m_Image_Height;
		m_pBitmapInfo->bmiHeader.biWidth = m_Image_Width;
		m_pBitmapInfo->bmiHeader.biSizeImage = DIBSIZE(m_pBitmapInfo->bmiHeader);
	}
}

void CImageControl::UpdateImageData(unsigned char* ImageData, int Width, int Height, int DataSize, int Channel)
{
	if (ImageData == NULL || Width <= 0 || Height <= 0 || DataSize <= 0)
		return;

	int fixedWidth = Width;
	if (fixedWidth % 4 != 0)
		fixedWidth = (Width / 4 + 1) * 4;

	CheckImageSize(fixedWidth, Height, Channel);

	for (int i = 0; i < Height; i++)
	{
		memcpy(m_Image_Data + i * Channel * fixedWidth, ImageData + i * Channel * Width, Channel * Width);
	}

	if (m_DrawMode != ACTION_NULL)
		memset(m_Mark_Data, 0, m_Image_Width * m_Image_Height);
}

void CImageControl::UpdateMarkData(unsigned char* ImageData, int Width, int Height, int DataSize, int Channel)
{
	if (ImageData == NULL || Width <= 0 || Height <= 0 || DataSize <= 0 || Channel != 1)
		return;

	if (Width != m_Image_Width || Height != m_Image_Height || Channel != 1)
		return;

	for (int i = 0; i < Height; i++)
	{
		memcpy(m_Mark_Data + i * Width, ImageData + i * Width, Width);
	}
}

void CImageControl::CheckImageSize(int ImageWidth, int ImageHeight, int ImageChannel)
{
	if (ImageWidth != m_Image_Width || ImageHeight != m_Image_Height || ImageChannel != m_Image_Channel)
	{
		m_Image_Width = m_Disp_Width = ImageWidth;
		m_Image_Height = m_Disp_Height = ImageHeight;
		m_Image_Channel = ImageChannel;

		m_Disp_X1 = 0;
		m_Disp_X2 = ImageWidth - 1;
		m_Disp_Y1 = 0;
		m_Disp_Y2 = ImageHeight - 1;

		m_Scale_H = m_Scale_W = m_Zoom_Value = 1;

		InitImageBuffer();
		InitDispRect();
	}
}

void CImageControl::SetParentPointer(void* Pointer)
{
	m_pParent = Pointer;
}

void CImageControl::InitDispRect()
{
	GetClientRect(&m_WndRect);

	m_ImageRect = m_WndRect;

	float WindowRatio = float(m_ImageRect.Width()) / float(m_ImageRect.Height());
	float ImageRatio = float(m_Image_Width) / float(m_Image_Height);

	m_FillRect1.left = -1; m_FillRect2.left = -1;

	if (abs(WindowRatio - ImageRatio) >= 0.05)
	{
		if (WindowRatio > ImageRatio)
		{
			int FillWidth = (m_ImageRect.Width() - ImageRatio * m_ImageRect.Height()) / 2;

			m_ImageRect.left = m_ImageRect.left + FillWidth;
			m_ImageRect.right = m_ImageRect.right - FillWidth;

			m_FillRect1.left = 0; m_FillRect1.right = m_ImageRect.left;
			m_FillRect1.top = 0; m_FillRect1.bottom = m_ImageRect.bottom;

			m_FillRect2.left = m_ImageRect.right;
			m_FillRect2.right = m_FillRect2.left + FillWidth;
			m_FillRect2.top = 0; m_FillRect2.bottom = m_ImageRect.bottom;
		}
		else
		{
			int FillHeight = (m_ImageRect.Height() - m_ImageRect.Width() / ImageRatio) / 2;

			m_ImageRect.top = m_ImageRect.top + FillHeight;
			m_ImageRect.bottom = m_ImageRect.bottom - FillHeight;

			m_FillRect1.left = 0; m_FillRect1.right = m_ImageRect.right;
			m_FillRect1.top = 0; m_FillRect1.bottom = m_ImageRect.top;

			m_FillRect2.left = 0; m_FillRect2.right = m_ImageRect.right;
			m_FillRect2.top = m_ImageRect.bottom; m_FillRect2.bottom = m_FillRect2.top + FillHeight;
		}
	}
}

void CImageControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	InitDispRect();
}

// 设置显示图片索引
void CImageControl::SetImgIndex(int imgIndex)
{
	m_ImgIndex = imgIndex;
}

void CImageControl::SetDetPass(bool isPass)
{
	m_Dalsa_IsDetPass = isPass;
}

// 设置显示在图片上的圆带和周期长度
void CImageControl::SetDistance(float CycleDistance, float HalfCycleDistance)
{
	m_Dalsa_CycleDistance = CycleDistance;
	m_Dalsa_HalfCycleDistance = HalfCycleDistance;
}

bool CImageControl::TranslateWindowPointToImagePoint(CPoint WindowPoint, ZC::PointF& ImagePoint)
{
	if (m_ImageRect.Width() > 0)
		ImagePoint.x = m_Disp_X1 + round(double(WindowPoint.x - m_ImageRect.left) / m_Scale_W);
	else
		return false;

	if (m_ImageRect.Height() > 0)
		ImagePoint.y = m_Disp_Y1 + round(double(WindowPoint.y - m_ImageRect.top) / m_Scale_H);
	else
		return false;

	if (ImagePoint.x < 0)
		ImagePoint.x = 0;

	if (ImagePoint.x >= m_Image_Width)
		ImagePoint.x = m_Image_Width - 1;

	if (ImagePoint.y < 0)
		ImagePoint.y = 0;

	if (ImagePoint.y >= m_Image_Height)
		ImagePoint.y = m_Image_Height - 1;

	return true;
}

bool CImageControl::TranslateImagePointToWindowPoint(ZC::PointF ImagePoint, CPoint& WindowPoint)
{
	WindowPoint.x = float(ImagePoint.x - m_Disp_X1) * m_Scale_W + m_ImageRect.left;
	WindowPoint.y = float(ImagePoint.y - m_Disp_Y1) * m_Scale_H + m_ImageRect.top;

	return true;
}

void CImageControl::SetTextSize(int size)
{
	m_DisplayFont.DeleteObject();

	m_DisplayFont.CreateFont(size,                    //   字体的高度   
		0,                                          //   字体的宽度  
		0,                                          //   nEscapement 
		0,                                          //   nOrientation   
		FW_BOLD,                                    //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                          //   cStrikeOut   
		ANSI_CHARSET,                               //   nCharSet   
		OUT_DEFAULT_PRECIS,                         //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,                        //   nClipPrecision   
		DEFAULT_QUALITY,                            //   nQuality   
		DEFAULT_PITCH | FF_SWISS,                   //   nPitchAndFamily     
		_T("宋体"));
}

void CImageControl::EnableDrawModel(float TransParentValue)
{
	m_DrawMode = ACTION_DRAW;
	m_TransParentValue = TransParentValue;
}

void CImageControl::SetEraseMarkData()
{
	m_DrawMode = ACTION_ERASE;
}

void CImageControl::DisableDrawModel()
{
	m_DrawMode = ACTION_NULL;
}

void CImageControl::SetDrawSize(int DrawSize)
{
	m_DrawSize = DrawSize;
}

void CImageControl::SetTransParentValue(float TransParentValue)
{
	m_TransParentValue = TransParentValue;
}

void CImageControl::GetMarkData(unsigned char* MarkData)
{
	memcpy(MarkData, m_Mark_Data, m_Image_Width * m_Image_Height);
}

void CImageControl::ShowMark()
{
	m_IsHideMark = false;
	TriggerInvalidate();
}

void CImageControl::HideMark()
{
	m_IsHideMark = true;
	TriggerInvalidate();
}