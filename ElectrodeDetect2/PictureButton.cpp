#include "pch.h"
#include "PictureButton.h"

#include "GlobalDefine.h"

#define BTN_PARENT_NUM	1
#define BTN_CHILD_NUM	2

// CMFCButton是宿主
BEGIN_MESSAGE_MAP(CPictureButton, CMFCButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

CPictureButton::CPictureButton()
{
	m_IsOver = false;    m_IsSelect = false;
	m_IsLogin = false;	 m_BtnType = 1;

	img_Select = NULL;		// 选择
	img_Normal = NULL;		// 普通
	img_Over = NULL;		// 覆盖
	img_ForBid = NULL;		// 禁止
}

CPictureButton::~CPictureButton()
{
	m_FrameBrush.DeleteObject();
	m_CommonBrush.DeleteObject();
}

// 在宿主中的OnDrawItem()中被调用，对应的是WM_DRAWITEM的相应函数
// 宿主类可以根据nIDCtl来判定是哪个子控件。
void CPictureButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC = pDC->SaveDC();

	CRect rct = lpDrawItemStruct->rcItem;

	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC, rct.Width(), rct.Height());
	CBitmap* pOldBitmap = MemDC.SelectObject(&MemBitmap);

	if(m_BtnType == 1)
		MemDC.FillSolidRect(0, 0, rct.Width(), rct.Height(), RGB(50, 49, 48));		// 给父窗口按钮创建指定颜色画笔画画布
	else if(m_BtnType == 2)
		MemDC.FillSolidRect(0, 0, rct.Width(), rct.Height(), RGB(0, 0, 0));			// 给子窗口按钮创建指定颜色画笔画画布
		
	Graphics graphics(MemDC.m_hDC);

	if (!m_IsLogin && img_ForBid != NULL)
	{
		graphics.DrawImage(img_ForBid, rct.left, rct.top, rct.Width(), rct.Height());
	}
	else
	{
		if (m_IsSelect)
		{
			graphics.DrawImage(img_Select, rct.left, rct.top, rct.Width(), rct.Height());
		}
		else
		{
			if (m_IsOver)
				graphics.DrawImage(img_Over, rct.left, rct.top, rct.Width() + 1, rct.Height());
			else
				graphics.DrawImage(img_Normal, rct.left, rct.top, rct.Width() + 1, rct.Height());
		}
	}

	MemDC.SetBkMode(TRANSPARENT);
	pDC->BitBlt(0, 0, rct.Width(), rct.Height(), &MemDC, 0, 0, SRCCOPY);
	pDC->RestoreDC(nSaveDC);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CPictureButton::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	CMFCButton::PreSubclassWindow();
}

void CPictureButton::SetButtonOver(bool IsOver)
{
	m_IsOver = IsOver;
}

void CPictureButton::SetButtonForBid(bool IsOver)
{
	m_IsLogin = IsOver;
}

void CPictureButton::SetButtonSelect(bool IsSelect)
{
	m_IsSelect = IsSelect;
}

void CPictureButton::SetButtonType(int BtnType)
{
	m_BtnType = BtnType;
}

void CPictureButton::TriggerInvalidate()
{
	Invalidate();
	UpdateWindow();
}

void CPictureButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (img_Over == NULL)
	{
		CMFCButton::OnMouseMove(nFlags, point);
		return;
	}

	TRACKMOUSEEVENT csTME;						// 追踪鼠标事件
	csTME.cbSize = sizeof(csTME);
	csTME.dwFlags = TME_LEAVE | TME_HOVER;
	csTME.hwndTrack = m_hWnd;
	csTME.dwHoverTime = 5;
	::_TrackMouseEvent(&csTME);

	SetButtonOver(true);

	CMFCButton::OnMouseMove(nFlags, point);
}

void CPictureButton::OnMouseLeave()
{
	if (img_Over == NULL)
	{
		CMFCButton::OnMouseLeave();
		return;
	}

	SetButtonOver(false);
	TriggerInvalidate();
	CMFCButton::OnMouseLeave();
}

// 正常的图片
void CPictureButton::LoadNormalImage(Image* srcImage)
{
	img_Normal = srcImage;
}

// 鼠标覆盖上去的图片
void CPictureButton::LoadOverImage(Image* srcImage)
{
	img_Over = srcImage;
}

// 鼠标点击后的图片
void CPictureButton::LoadSelectImage(Image* srcImage)
{
	img_Select = srcImage;
}

// 禁止的图片
void CPictureButton::LoadForBidImage(Image* srcImage)
{
	img_ForBid = srcImage;
}
//void CPictureButton::LoadNormalImage(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance)
//{
//	if (img_Normal != NULL)
//	{
//		delete img_Normal;
//		img_Normal = NULL;
//	}
//	img_Normal = LoadGDIImageFromResource(nResID, lpszResType, hInstance);
//}
//
//void CPictureButton::LoadSelectImage(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance)
//{
//	if (img_Select != NULL)
//	{
//		delete img_Select;
//		img_Select = NULL;
//	}
//	img_Select = LoadGDIImageFromResource(nResID, lpszResType, hInstance);
//}
//
//void CPictureButton::LoadOverImage(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance)
//{
//	if (img_Over != NULL)
//	{
//		delete img_Over;
//		img_Over = NULL;
//	}
//	img_Over = LoadGDIImageFromResource(nResID, lpszResType, hInstance);
//}
//
//void CPictureButton::LoadNormalImage(LPCTSTR pszFileName)
//{
//	if (img_Normal != NULL)
//	{
//		delete img_Normal;
//		img_Normal = NULL;
//	}
//	img_Normal = LoadGDIImageFromFile(pszFileName);
//}
//
//void CPictureButton::LoadSelectImage(LPCTSTR pszFileName)
//{
//	if (img_Select != NULL)
//	{
//		delete img_Select;
//		img_Select = NULL;
//	}
//	img_Select = LoadGDIImageFromFile(pszFileName);
//}
//
//void CPictureButton::LoadOverImage(LPCTSTR pszFileName)
//{
//	if (img_Over != NULL)
//	{
//		delete img_Over;
//		img_Over = NULL;
//	}
//	img_Over = LoadGDIImageFromFile(pszFileName);
//}

Image* CPictureButton::LoadGDIImageFromResource(UINT nResID, LPCTSTR lpszResType, HINSTANCE hInstance)
{
	Image* pImage = NULL;

	HRSRC hPic = FindResource(hInstance/*AfxGetResourceHandle()*/, MAKEINTRESOURCE(nResID), lpszResType);
	HANDLE hResData = NULL;
	if (!hPic || !(hResData = LoadResource(AfxGetResourceHandle(), hPic)))
	{
		::OutputDebugString(_T("Load (resource): Error loading resource: %d\n"));
		return NULL;
	}

	// 获取资源数据的大小，供GlobalAlloc使用
	DWORD dwSize = SizeofResource(AfxGetResourceHandle(), hPic);

	// 根据资源数据大小，分配HGLOBAL内存
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, dwSize);
	if (!hGlobal)
	{
		::OutputDebugString(_T("Load (resource): Error allocating memory\n"));
		FreeResource(hResData);
		return NULL;
	}

	char *pDest = reinterpret_cast<char *> (GlobalLock(hGlobal));
	char *pSrc = reinterpret_cast<char *> (LockResource(hResData)); // 锁住资源
	if (!pSrc || !pDest)
	{
		::OutputDebugString(_T("Load (resource): Error locking memory\n"));
		GlobalFree(hGlobal);
		FreeResource(hResData);
		return NULL;
	};

	// 将资源数据拷贝到HGLOBAL内存中，用于创建流
	memcpy(pDest, pSrc, dwSize);
	FreeResource(hResData);
	GlobalUnlock(hGlobal);

	IStream *pStream = NULL;
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
	{
		return NULL;
	}
	pImage = Image::FromStream(pStream);

	pStream->Release();
	return pImage;
}

Image* CPictureButton::LoadGDIImageFromFile(LPCTSTR pszFileName)
{
	Image* pImage = NULL;
	ASSERT(pszFileName != NULL);

	CFile file;
	DWORD dwSize;

	// 打开文件
	if (!file.Open(pszFileName,
		CFile::modeRead |
		CFile::shareDenyWrite))
	{
		TRACE(_T("Load (file): Error opening file %s\n"), pszFileName);
		return FALSE;
	};

	// 根据文件内容大小分配HGLOBAL内存  
	dwSize = (DWORD)file.GetLength();
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, dwSize);
	if (!hGlobal)
	{
		TRACE(_T("Load (file): Error allocating memory\n"));
		return FALSE;
	};

	char* pData = reinterpret_cast<char*>(GlobalLock(hGlobal));
	if (!pData)
	{
		TRACE(_T("Load (file): Error locking memory\n"));
		GlobalFree(hGlobal);
		return FALSE;
	};

	// 将文件内容读到HGLOBAL内存中  
	TRY
	{
		file.Read(pData, dwSize);
	}
	CATCH(CFileException, e);
	{
		TRACE(_T("Load (file): An exception occured while reading the file %s\n"),
			pszFileName);
		GlobalFree(hGlobal);
		e->Delete();
		file.Close();
		return FALSE;
	}
	END_CATCH

		GlobalUnlock(hGlobal);
	file.Close();

	// 利用hGlobal内存中的数据创建stream  
	IStream* pStream = NULL;
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
	{
		return FALSE;
	}

	// 将图片文件数据加载到Image对象中
	pImage = Image::FromStream(pStream);
	ASSERT(pImage != NULL);
	pStream->Release();

	return pImage;
}