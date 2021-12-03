/* ImageControl
* 自定义控件, Class使用 CImageControl
*/

#pragma once
#include <afxwin.h>
#include <string>
#include <vector>

#include "ControlDLL.h"

#define ACTION_NULL 0
#define ACTION_DRAW 1
#define ACTION_ERASE 2

typedef void(*ptrCallBackFun)(void* parm, std::vector<float> OutPut);

class DLL_API CImageControl : public CWnd
{
	DECLARE_MESSAGE_MAP()
public:
	CImageControl();
	~CImageControl();

//  Pointer
protected:
	void* m_pParent;

	CRect m_WndRect;
	CRect m_ImageRect;

	CRect m_FillRect1;
	CRect m_FillRect2;

	COLORREF m_Fill_Color;

	CFont m_DisplayFont;
//  Image Info
protected:
	unsigned char* m_Image_Data;
	unsigned char* m_Disp_Data;

	unsigned char* m_Mark_Data;


	BITMAPINFO* m_pBitmapInfo;

	int m_Image_Width;
	int m_Image_Height;
	int m_Image_Channel;

	int m_Disp_Width;
	int m_Disp_Height;

	int m_Max_Region_Width;
	int m_Max_Region_Height;

	int m_Disp_X1;
	int m_Disp_X2;
	int m_Disp_Y1;
	int m_Disp_Y2;

	double m_Scale_H;
	double m_Scale_W;
	float m_Zoom_Value;
	
	// 相机图片编号和相机类型
	int m_ImgIndex;

	// 图片控件编号
	int m_ImageControl_Id;
	
	// 专属于Dalsa相机采集的图片的周期、圆带长度
	float m_Dalsa_CycleDistance;
	float m_Dalsa_HalfCycleDistance;

	bool m_Dalsa_IsDetPass;

//  Interaction
protected:
	bool m_LeftButtonDown;
	bool m_RightButtonDown;

	CPoint m_MousePt;

	int m_DrawSize;
	int m_DrawMode;
	bool m_IsHideMark;
	float m_TransParentValue;
//  
public:
	void SetParentPointer(void* Pointer);
	void TriggerInvalidate();
	void UpdateImageData(unsigned char* ImageData, int Width, int Height, int DataSize, int Channel);
	void UpdateMarkData(unsigned char* ImageData, int Width, int Height, int DataSize, int Channel);
	void GetMarkData(unsigned char* MarkData);
	void SetTextSize(int size = 18);
	void SetFillColor(COLORREF color);
	void DisplayResult(CDC* pDC);
	void SetImgIndex(int imgIndex);
	void SetDistance(float CycleDistance,float HalfCycleDistance);
	void SetDetPass(bool isPass);

	void SetEraseMarkData();
	void EnableDrawModel(float TransParentValue = 0.2);
	void DisableDrawModel();
	void SetDrawSize(int DrawSize);
	void SetTransParentValue(float TransParentValue);
	void ShowMark();
	void HideMark();

	void SetImgControlId(int ImgControlId);
//
protected:
	BOOL RegisterWndClass();
	void InitImageBuffer();
	void InitDispRect();
	void CheckImageSize(int ImageWidth, int ImageHeight, int ImageChannel);
	void DisplayImage(CDC* pDC);
	void UpdataDisplayImageData();
	void UpdataDisplayScaleInfo();

	//  Tool Motion
	bool TranslateWindowPointToImagePoint(CPoint WindowPoint, ZC::PointF& ImagePoint);
	bool TranslateImagePointToWindowPoint(ZC::PointF ImagePoint, CPoint& WindowPoint);

//  Wnd Message
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};