#ifndef _VISION_STRUCR_H_
#define _VISION_STRUCR_H_

#include "CameraPara.h"
#include "Public.h"

#define	TIMER_SYSTEM_TIME	1
#define	TIMER_HALF_HOUR		2
#define REGION_NONE            0
#define REGION_IN_RECT         1
#define REGION_IN_MATCHRECT    2
#define REGION_IN_CIRCLE       3
#define REGION_IN_CIRCLE_LOOP  4
#define REGION_IN_ARC_LOOP     5

#define RESULT_FAIL         0
#define RESULT_SUCESS       1
#define RESULT_NONE         2
#define RESULT_OUT_RANGE    3

#define REGION_OUT_RECT         7
#define REGION_OUT_CIRCLE       8
#define REGION_OUT_ARC          9
#define REGION_OUT_CIRCLE_LOOP  10

#define DETECT_ST1_MATCH  1
#define DETECT_ST2_RECT   2
#define DETECT_ST3_MATCH  3
#define DETECT_ST3_CIRCLE 4

#define DETECT_ST1_MATCH_RESULT 10
#define DETECT_ST3_MATCH_RESULT 11

#define IMAGEBUFFER  20
#define MAXTHREADNUM 10

#define CAMERA_NUM 4

#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)
#define DIBWIDTHBYTES(bi) (DWORD)WIDTHBYTES((DWORD)(bi).biWidth * (DWORD)(bi).biBitCount)
#define _DIBSIZE(bi) (DIBWIDTHBYTES(bi) * (DWORD)(bi).biHeight)
#define DIBSIZE(bi) ((bi).biHeight < 0 ? (-1)*(_DIBSIZE(bi)) : _DIBSIZE(bi))

#define TASK_NONE    0
#define TASK_OPEN    1
#define TASK_WRITE   2
#define TASK_CLOSE   3
#define TASK_GET     4

typedef vector<vector<cv::Point2i>> PointsArray;

typedef struct tagAnalyTask
{
	void* PtrParaIn;
	void* PtrParaOut;

	ImageUnitBase DetectImageUnit;
	ImageUnitBase ImageUnit;

	bool          DetectResult;
	int           PictureId;

	void Init()
	{
		PtrParaIn = NULL;  PtrParaOut = NULL;

		ImageUnit.Init();

		DetectResult = true;  PictureId = 0;
	}
}AnalyTask;

typedef struct tagPointCloudBase
{
	UINT m_Width;
	UINT m_Length;
	UINT m_DataNum;
	unsigned char* m_GrayData;
	int* m_HeightData;
	double ResolutionX;
	double ResolutionY;
	void Init()
	{
		ResolutionX = 0; ResolutionY = 0;
		m_Length = m_Width = 0;
		m_GrayData = NULL;
		m_HeightData = NULL;
	}
}PointCloudBase;

typedef struct tagPointCloudTask
{
	PointCloudBase PointCloud;

	bool          DetectResult;
	int           PictureId;

	void Init()
	{
		PointCloud.Init();

		DetectResult = true;  PictureId = 0;
	}
}PointCloudTask;

typedef struct tagRegionForm
{
	int FormID;  //  区域类型ID

	void* RegionPara;

	int DetectID;  //  检测项ID

	void Init()
	{
		FormID = REGION_NONE;  DetectID = -1;

		RegionPara = NULL;

		RegionPara = (void*)malloc(1024);
	}
}RegionForm;

typedef struct tagRectObj      //矩形区域的结构对象
{
	Point2d FirstPoint;
	Point2d ThirdPoint;

	void Init() { FirstPoint.x = -1;  ThirdPoint.x = -1; }
	int Width() { return abs(ThirdPoint.x - FirstPoint.x); }
	int Height() { return abs(ThirdPoint.y - FirstPoint.y); }
}RectObj;

typedef struct tagMatchObj      //矩形区域的结构对象
{
	RectObj SearchRect;
	RectObj ModelRect;

	void Init()
	{
		SearchRect.Init();  ModelRect.Init();
	}
}MatchObj;

typedef struct tagCircleObj
{
	float Radius;            //圆周半径
	Point2d  CirclePoint;    //圆心

	void Init()
	{
		Radius = 0;
	}
}CircleObj;

typedef struct tagCircleLoopObj
{
	Point2d   CirclePoint;                  //圆心坐标
	float     Radius1;                      //半径1
	float     Radius2;                      //半径2

	void Init()
	{
		Radius1 = 0; Radius2 = 0; CirclePoint.x = 0; CirclePoint.y = 0;
	}
}CircleLoopObj;

typedef struct tagArcObj
{
	CircleObj circleObj;                    //圆周参数
	Point2d   startPoint;                   //起始坐标
	Point2d   endPoint;                     //终止坐标
	Point2d   middlePoint;                  //中点坐标
	double    startAngle;                   //起始角度
	double    offsetAngle;                  //相对角度
	int       ArcDirect;

	void Init() {
		startPoint = cvPoint(-1, -1); endPoint = cvPoint(-1, -1); middlePoint = cvPoint(-1, -1);
	}

	void CalculateCircle() {
		double x1 = startPoint.x, x2 = middlePoint.x, x3 = endPoint.x;
		double y1 = startPoint.y, y2 = middlePoint.y, y3 = endPoint.y;
		double a = x1 - x2;
		double b = y1 - y2;
		double c = x1 - x3;
		double d = y1 - y3;
		double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
		double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
		double det = b * c - a * d;
		if (fabs(det) < 1e-5)
		{
			circleObj.Radius = -1;
			circleObj.CirclePoint = cvPoint(0, 0);
			return;
		}
		double x0 = -(d * e - b * f) / det;
		double y0 = -(a * f - c * e) / det;

		circleObj.Radius = hypot(x1 - x0, y1 - y0);
		circleObj.CirclePoint = cvPoint(x0, y0);

		//3个点组成不重复过点的圆弧
		double middleAngle, endAngle;
		if (startPoint.x - x0 == 0)
			startAngle = -(abs(startPoint.y - y0) / (startPoint.y - y0)) * 90;
		else
			startAngle = -atan2((startPoint.y - y0), (startPoint.x - x0)) * 180 / VL_PI;

		if (middlePoint.x - x0 == 0)
			middleAngle = -(abs(middlePoint.y - y0) / (middlePoint.y - y0)) * 90;
		else
			middleAngle = -atan2((middlePoint.y - y0), (middlePoint.x - x0)) * 180 / VL_PI;

		if (endPoint.x - x0 == 0)
			endAngle = -(abs(endPoint.y - y0) / (endPoint.y - y0)) * 90;
		else
			endAngle = -atan2((endPoint.y - y0), (endPoint.x - x0)) * 180 / VL_PI;

		double relativeStart = 0, relativeMiddle = middleAngle - startAngle, relativeEnd = endAngle - startAngle;

		if (relativeMiddle < 0)  relativeMiddle += 360;

		if (relativeEnd < 0)  relativeEnd += 360;

		if (relativeMiddle > 360)  relativeMiddle -= 360;

		if (relativeEnd > 360)  relativeEnd -= 360;

		if (relativeEnd > relativeMiddle)
		{
			offsetAngle = relativeEnd;
			ArcDirect = ARC_DIRECT_ANTI_CLOSCWISE;
		}
		else
		{
			offsetAngle = 360 - relativeEnd;
			ArcDirect = ARC_DIRECT_CLOSCWISE;
		}
	}
}ArcObj;

typedef struct tagArcLoopObj
{
	ArcObj  arcObj;                       //圆弧
	float   deltaRadius;                  //半径改变距离

	void Init() {
		arcObj.Init();
		deltaRadius = 0;
	}

	void CalculateDeltaRadius(Point2f point) {
		deltaRadius = hypot(arcObj.circleObj.CirclePoint.x - point.x, arcObj.circleObj.CirclePoint.y - point.y) - arcObj.circleObj.Radius;
	}
}ArcLoopObj;

#define ATLINE    0
#define UNDERLINE 1
#define ONLINE    2

struct LineOb
{
	float k;
	float b;

	LineOb(int point1_x, int point1_y, int point2_x, int point2_y)
	{
		if (point2_x == point1_x)
		{
			k = 0;
			b = point2_x;
		}
		else
		{
			k = float(point2_y - point1_y) / float(point2_x - point1_x);
			b = point2_y - k * point2_x;
		}
	}

	void Init()
	{
		k = 0; b = 0;
	}

	int Point2LinePos(int x, int y)
	{
		float y_line = k * x + b;

		if (y > y_line)
			return UNDERLINE;
		else if (y < y_line)
			return ONLINE;
		else
			return ATLINE;
	}
};

typedef struct tagMatchParaIn
{
	// ID
	int MatchParaIndex;

	// Create
	Point2d Model_FirstPoint, Model_ThirdPoint;
	Point2d Search_FirstPoint, Search_ThirdPoint;

	int HighContrast, LowContrast, MinXLDLength;

	// Detect
	float MinScore;

	// Result
	Point2f LocatePoint;
	float LocateR, LocateScore;

	void Init()
	{
		MatchParaIndex = 0;  Model_FirstPoint.x = -1;  Search_FirstPoint.x = -1;

		HighContrast = 38;   LowContrast = 22;   MinXLDLength = 100;

		MinScore = 0.2;

		LocatePoint.x = 0;  LocatePoint.y = 0;  LocateR = 0;  LocateScore = 0;
	}

	int GetSearchRectX1() {return VL_MIN(Search_FirstPoint.x, Search_ThirdPoint.x);}
	int GetSearchRectX2() {return VL_MAX(Search_FirstPoint.x, Search_ThirdPoint.x);}
	int GetSearchRectY1() {return VL_MIN(Search_FirstPoint.y, Search_ThirdPoint.y);}
	int GetSearchRectY2() {return VL_MAX(Search_FirstPoint.y, Search_ThirdPoint.y);}

	int GetModelRectX1() { return VL_MIN(Model_FirstPoint.x, Model_ThirdPoint.x); }
	int GetModelRectX2() { return VL_MAX(Model_FirstPoint.x, Model_ThirdPoint.x); }
	int GetModelRectY1() { return VL_MIN(Model_FirstPoint.y, Model_ThirdPoint.y); }
	int GetModelRectY2() { return VL_MAX(Model_FirstPoint.y, Model_ThirdPoint.y); }

}MatchParaIn;

typedef struct tagMatchParaOut
{
	// Result
	Point2f LocatePoint;
	float LocateR, LocateScore;

	bool IsMatchSuccess;

	void Init()
	{
		LocatePoint.x = 0;  LocatePoint.y = 0;  LocateR = 0;  LocateScore = 0;
		IsMatchSuccess = true;
	}
}MatchParaOut;

typedef struct tagDeepLearnSegmentIn
{
	float ProbabilityThreshold;
	int   MorphSize;
	int   AreaThreshold;

	cv::Rect InputRegion;

	void Init()
	{
		ProbabilityThreshold = 0.5;
		AreaThreshold = 100;
		MorphSize = 3;

		InputRegion.x = 0; InputRegion.y = 0;
	}
	void Check()
	{
		if (ProbabilityThreshold < 0.1) ProbabilityThreshold = 0.1;
		if (ProbabilityThreshold > 1) ProbabilityThreshold = 1;

		if (AreaThreshold < 1) AreaThreshold = 1;

		if (MorphSize % 2 == 0) MorphSize = MorphSize / 2 + 1;
	}
}DeepLearnSegmentIn;

typedef struct tagDeepLearnSegmentOut
{
	vector<vector<Point2i>> DefectPointArrayOfArray;

	void Init()
	{
		DefectPointArrayOfArray.clear();
	}
}DeepLearnSegmentOut;

typedef struct tagCam1DetectPara
{
	DeepLearnSegmentIn SegmentParaIn;
	DeepLearnSegmentOut SegmentParaOut;

	void Init()
	{
		SegmentParaIn.Init();   SegmentParaOut.Init();
	}
	void InitResult()
	{
		SegmentParaOut.Init();
	}
}Cam1DetectPara;

typedef struct tagCam2DetectPara
{
	DeepLearnSegmentIn SegmentParaIn;
	DeepLearnSegmentOut SegmentParaOut;

	void Init()
	{
		SegmentParaIn.Init();   SegmentParaOut.Init();
	}
	void InitResult()
	{
		SegmentParaOut.Init();
	}
}Cam2DetectPara;

typedef struct tagFileTask
{
	int TaskType;

	int DataId;

	float CycleValue, HalfCycleValue;

	int iResult;

	void Init()
	{
		TaskType = TASK_NONE; DataId = 0;

		CycleValue = 0; HalfCycleValue = 0;

		iResult = 0;
	}
}FileTask;

//  焊带周期长度检测参数
typedef struct tagCyclePara
{
	float stdCycleLength; //  周期长度  mm
	float dev;            //  公差  mm
	void Init()
	{
		stdCycleLength = 0; dev = 0.5;
	}
}CyclePara;

typedef struct tagVisionParaIn
{
	int MiddleFilterSize;          //  中值滤波尺寸(像素)
	int DisCompareSize;            //  计算变化距离的范围(像素)
	int SameCrossPointFilterSize;  //  过滤重复节点的搜索范围(像素)
	int DisCompareAbsRatio;        //  点的上下距离变化差值比例  abs(Top - Bottom) >= DisCompareSize / DisCompareAbsRatio
	int SingleDirectionDisAbsRatio;//  上或下方距离变化值比例    abs(Top) 或 abs(Bottom) <= DisCompareSize / SingleDirectionDisAbsRatio

	float CycleDetectCompensation;		//  周期检测异常补偿
	float HalfDetectCompensation;		//  半周期检测异常补偿

	void Init()
	{
		MiddleFilterSize = 5;
		DisCompareSize = 5;
		SameCrossPointFilterSize = 20;
		DisCompareAbsRatio = 2;
		SingleDirectionDisAbsRatio = 4;
		CycleDetectCompensation = 2;
		HalfDetectCompensation = 2;
	}
}VisionParaIn;

typedef struct tagVisionParaOut
{
	int    DetectResult;

	int    CycleResult;
	int    HalfCycleResult;

	float  CycleDistance;
	int    CycleStart;
	int    CycleEnd;

	float  HalfCycleDistance;
	int    HalfCycleStart;
	int    HalfCycleEnd;

	void Init()
	{
		DetectResult = TOOL_PASS; CycleResult = TOOL_PASS; HalfCycleResult = TOOL_PASS;

		CycleDistance = 0; CycleStart = 0; CycleEnd = 0;
		HalfCycleDistance = 0; HalfCycleStart = 0; HalfCycleEnd = 0;
	}
}VisionParaOut;
#endif