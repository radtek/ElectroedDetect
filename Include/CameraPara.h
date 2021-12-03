//宏定义文件---定义公用的宏
#ifndef _CAMERA_PARA_H_
#define _CAMERA_PARA_H_

#include <string.h>

typedef unsigned int        UINT;
typedef unsigned long       DWORD;
typedef wchar_t             WCHAR;
typedef unsigned char       BYTE;

#define FILEDATAMAXNUM 500
#define CAMERANUM   2

//相机硬件的配置信息
//相机硬件的配置信息
typedef struct tagCameraGrabPara
{
	//相机ID，索引号
	int m_iCamID;
	//相机名称
	char m_szCamName[128];

	char m_szSerialNum[128];

	UINT m_iPixelFormat;       //图像格式	
	UINT m_bReverseX;          //图像是否水平翻转
	UINT m_bReverseY;          //图像是否垂直翻转

	UINT m_uImageWidth;        //图像宽度
	UINT m_uLineHeight;        //针对线扫相机
	UINT m_uImageHeight;       //图像高度
	UINT m_uImageChannel;      //图像通道
	UINT m_uXOffset;           //图像x方向偏移
	UINT m_uYOffset;           //图像y方向偏移	

	UINT m_cBWhite;            //0 ---白平衡关闭 
							   //1 ---白平衡启动时设置一次 
							   //2 ---用户自定义白平衡值
	float m_uBRatioAbsR;       //白平衡值 R 实际值是用此值除以100	
	float m_uBRatioAbsG;       //白平衡值 G 实际值是用此值除以100
	float m_uBRatioAbsB;       //白平衡值 B 实际值是用此值除以100

	UINT m_uBRatioRawR;
	UINT m_uBRatioRawG;
	UINT m_uBRatioRawB;

	UINT m_iTriggerMode;       //触发模式 0---关闭        1---打开	
	UINT m_cTriggerSource;     //触发源   0---line1输入端 1---软触发	
	UINT m_cTriggerActivation; //触发动作 0---上升沿触发  1---下降沿触发

	//UINT m_uTriggerDelay;      //延迟触发 时间 绝对值 微秒 Abs(us)	
	//BYTE m_cExposureTimeMode;  //曝光时间模式 0---内部定时器 
	//                           //             1---外触发时间宽度	
	//BYTE m_cExposureAuto;      //自动曝光模式 0关闭，1自动曝光	

	UINT m_uExposureTime;      //曝光时间 Abs(us)绝对值微秒

	float m_iFrameRate;

	double m_uGainTime;

	tagCameraGrabPara()             //设置相机信息的初值
	{
		m_iCamID = 0;

		memset(m_szCamName, '\0', 128);
		memset(m_szSerialNum, '\0', 128);

		m_iPixelFormat = 1;       //图像格式	
		m_bReverseX = 0;          //图像是否水平翻转
		m_bReverseY = 0;

		m_uImageWidth = 0;        //图像宽度	
		m_uImageHeight = 0;       //图像高度
		m_uImageChannel = 1;      //图像通道
		m_uXOffset = 0;           //图像x方向偏移
		m_uYOffset = 0;           //图像y方向偏移	
		//m_uImageSize = 0;         //图像长度

		//m_uGain = 0;              //图像增益

		m_cBWhite = 2;
		m_uBRatioAbsR = 0;           //白平衡值 R 实际值是用此值除以100	
		m_uBRatioAbsG = 0;           //白平衡值 G 实际值是用此值除以100
		m_uBRatioAbsB = 0;           //白平衡值 B 实际值是用此值除以100

		m_uBRatioRawR = 0;
		m_uBRatioRawG = 0;
		m_uBRatioRawB = 0;

		m_iTriggerMode = 0;         //触发模式 0---关闭        1---打开	
		m_cTriggerSource = 0;       //触发源   0---line1输入端 1---软触发	
		m_cTriggerActivation = 0;   //触发动作 0---上升沿触发  1---下降沿触发

		//m_uTriggerDelay = 0;      //延迟触发 时间 绝对值 微秒 Abs(us)	
		//m_cExposureTimeMode = 0;  //曝光时间模式 0---内部定时器 
		//                          //             1---外触发时间宽度	
		//m_cExposureAuto = 0;      //自动曝光模式 0关闭，1自动曝光	
		m_uExposureTime = 100;    //曝光时间 Abs(us)绝对值微秒
		m_uGainTime = 0;

		m_iFrameRate = 0;
	};
}CameraGrabPara;

typedef struct tagImageUnitBase
{
	//宽度
	UINT m_dwWidth;
	//高度
	UINT m_dwHeight;
	//图像长度
	UINT m_dwImageDataLen;
	//图像格式
	UINT   m_dwImageFormat;
	//图像数据指针
	unsigned char* m_dwImageData;

	void Init()
	{
		m_dwHeight = m_dwWidth = 0;
		m_dwImageFormat = 0;
		m_dwImageDataLen = 0;
		m_dwImageData = NULL;
	}
}ImageUnitBase;

enum CameraEvent {ceOpen = 0, ceClose, ceStart, ceStop, ceGrabbing, ceIdle, cePause, ceNoPause};

#endif//_CAMERA_PARA_H_