
// ElectrodeDetect2Dlg.h: 头文件
//

#pragma once
#include "ZcStruct.h"
#include "GlobalDefine.h"
#include "PictureButton.h"
#include "CColorStatusBar.h"
#include <deque>
#include "opencv2/opencv.hpp"
#include "opencv2//imgproc/imgproc_c.h"

#include ".\..\ControlDLL\ImageControl.h"

#define IMG_COUNT_DALSA 4
#define IMG_COUNT_HAIKANG 4
#define CAMERA_COUNT 2

// CElectrodeDetect2Dlg 对话框
class CDlgSysSet;
class CDlgDetSet;
class CAnalyHander;
class CLogin;
class CHaiKangGrabHander;
class CSaveImgHander;
class CDalsaGrabHander;
class CFileHander;
class CDelImgHander;

class CColorStatusBar;

class CElectrodeDetect2Dlg : public CDialogEx
{
// 构造
public:
	CElectrodeDetect2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELECTRODEDETECT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
// 实现
protected:
	//CStatusBar  m_wndStatusBar;
	CColorStatusBar m_wndStatusBar;

public:
	ULONG_PTR m_gdiplusToken;

	CBrush m_Sum_Bgc;
	CBrush m_Pass_Bgc;
	CBrush m_Fail_Bgc;
	CBrush m_BGC;

	CFont m_MiddleFont;

	CRect m_Cam1_State_Rect;
	CRect m_Cam2_State_Rect;

	Image* m_pBGImage;
	Image* m_Btn_State_Cam_1;										// 第1个相机的连接和断开状态
	Image* m_Btn_State_Cam_2;										// 第2个相机的连接和断开状态
	Image* Img_Quit_Normal;
	Image* Img_Min_Normal;
	Image* Img_Quit_Over;
	Image* Img_Min_Over;
	Image* Img_CamState_Connect_ch;
	Image* Img_CamState_Lost_ch;
	Image* Img_CamState_Grabing_ch;
	Image* Img_CamState_StopGrab_ch;
	Image* Img_SysSet_Normal;
	Image* Img_SysSet_ForBid;
	Image* Img_SysSet_Over;
	Image* Img_SysSet_Select;
	Image* Img_DetSet_Normal;
	Image* Img_DetSet_ForBid;
	Image* Img_DetSet_Over;
	Image* Img_DetSet_Select;
	Image* Img_Login_Normal;
	Image* Img_Login_Over;
	Image* Img_Login_Select;
	Image* Img_QuitLogin_Normal;
	Image* Img_QuitLogin_Over;
	Image* Img_QuitLogin_Select;
	Image* Img_Det_Pass;
	Image* Img_Det_Fail;

	CPictureButton m_Btn_Quit;
	CPictureButton m_Btn_Min;
	CPictureButton m_Btn_SysSetting;								// 系统设置
	CPictureButton m_Btn_DetSetting;								// 检测设置
	CPictureButton m_Btn_Login;										// 登录
	CPictureButton m_Btn_QuitLogin;									// 退出登录

	CStatic m_Cam1_Sum;												// 相机采集数目						
	CStatic m_Cam1_Pass;
	CStatic m_Cam1_Fail;
	CStatic m_Cam2_Sum;
	CStatic m_Cam2_Pass;
	CStatic m_Cam2_Fail;

	int m_NCam1_Sum;
	int m_NCam1_Pass;
	int m_NCam1_Fail;
	int m_NCam2_Sum;
	int m_NCam2_Pass;
	int m_NCam2_Fail;

	CImageControl m_Camera_1_List[IMG_COUNT_DALSA];					// 第1个相机(线扫相机)
	CImageControl m_Camera_2_List[IMG_COUNT_HAIKANG];				// 第2个相机(普通相机)

	CAnalyHander* m_pHaiKangAnalyHander[IMG_COUNT_HAIKANG];			// 海康相机分析队列
	CAnalyHander* m_pDalsaAnalyHander[IMG_COUNT_DALSA];				// Dalsa相机分析队列
	CSaveImgHander* m_pHaiKangSaveImgHander[IMG_COUNT_HAIKANG];		// 海康相机图片保存队列
	CSaveImgHander* m_pDalsaSaveImgHander[IMG_COUNT_DALSA];			// Dalsa相机图片保存队列

	CFileHander* m_PtrFileHander;									// 保存.csv文件
	CDelImgHander* m_DelImgHander;									// 定时删除溢出的图片

	CHaiKangGrabHander* m_pHaiKangGrabHander;						// 海康相机
	CDalsaGrabHander* m_pDalsaGrabHander;							// Dalsa相机

	CameraGrabPara m_CamPara[CAMERA_COUNT];							// 海康相机和Dalsa相机的配置参数

	CDlgSysSet* m_pDlgSysSet;										// 系统设置子窗体
	CDlgDetSet* m_pDlgDetSet;										// 检测设置子窗口
	CLogin* m_pDlgLogin;											// 登录

	CString m_strSaveImagePath;										// 从ini中读入的配置
	CString m_PassWord;												// 密码
	CString m_Folder_CSV;											// CSV文件保存目录
	CString m_SaveDisk;												// 保存图片和csv文件的盘符
	int m_ProductID;												// 产品id
	bool m_IsDetecting;
	int  m_AnalyFreeTime;

	CyclePara m_CyclePara;
	CyclePara m_HalfCyclePara;

	float     m_OffsetFull;
	float     m_OffsetHalf;

	float     m_YResolution;
	float     m_LikeRatio;

	float	  m_FailDetProp;

	char AppPath[1024];												// 项目目录

	int m_IsLogin;
	int m_IsSaveNGData;
	int m_IsSaveOKData;
	int m_CurrTotalNum_Dalsa;										// Dalsa相机图片总数(也充当当前显示到哪个图片控件上的索引)
	int m_CurrTotalNum_HaiKang;										// 海康相机图片总数(也充当当前显示到哪个图片控件上的索引)

	RunTimeElement m_RunTime;

	VisionParaIn* m_PtrCSIVisionIn;
	VisionParaOut* m_PtrCSIVisionOut;

	VisionParaIn* m_PtrCSIVisionIn2;
	VisionParaOut* m_PtrCSIVisionOut2;

	float m_Disk_Total;
	float m_Disk_Surplus;
	float m_Disk_Prop;

	int m_Disk_Input_Prop;											// 设置的硬盘剩余空间占比
	CString m_FirstDelImgFolderPath;								// 要删除的最早的那个图片文件夹

	std::deque<bool> QueDetResult;									// 保存焊带长度检测结果双端缓冲队列
	
public:
	void SetFullScreen();
	Image* LoadFromFile(LPCTSTR imgPath);
	// 加载相机配置
	void LoadCameraParaFun(int CameraIndex, char* FolderPath);
	bool OpenCamera(int CameraIndex);
	bool CloseCamera(int CameraIndex);
	bool StartGrad(int CameraIndex);
	bool StopGrad(int CameraIndex);
	void TriggerInvalidate();
	void InValidateRectCamState(int CamIndex);
	void LoadDetectParaIn(char* FolderPath);
	void SaveDetectParaIn(char* FolderPath);
	void DetectImageProcess_First(AnalyTask* PtrAnalyTask);
	void LoadDebugShowModel(char* FolderPath);
	void LoadDiskVolume(char* DiskName);
	void TravelFolder(char* FolderName);
	void DelFolderByPath(char* FindFolderPath);

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedMfcbuttonClose();
	afx_msg void OnBnClickedMfcbuttonMin();
	afx_msg void OnBnClickedMfcbuttonSysset();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMfcbuttonDetset();
	afx_msg void OnBnClickedMfcbuttonLogin();
	afx_msg void OnBnClickedMfcbuttonQuitlogin();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};

