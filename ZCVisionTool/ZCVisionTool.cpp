#include <ZCVisionTool/ZCVisionTool.h>
#include "BasicFunction.h"

DLLAPI void STDCALL Cam1_Function(Mat srcImg, VisionParaIn* DetectParaIn, VisionParaOut* DetectParaOut, Mat& labeledImg)
{
	int w = srcImg.cols;
	int h = srcImg.rows;

	Mat dstImg = cv::Mat::zeros(srcImg.size(), CV_8U);

	Mat binImg;
	cv::threshold(srcImg, binImg, 250, 255, THRESH_BINARY);

	PointsArray dstRegion;
	ConnectedRegion(binImg, 0, cvRect(0, 0, w, h), &dstRegion);

	labeledImg = srcImg;

	if (dstRegion.size() <= 0)
	{
		DetectParaOut->CycleDistance = 0;
		DetectParaOut->HalfCycleDistance = 0;
		return;
	}

	Mat FilterImg;
	FilterRegionBySize(binImg.size(), &dstRegion, 1, binImg.total(), FilterImg);

	int stratX = w, endX = 0;
	int regionWidth = 0, OffsetX = 0;

	int ImagePosition = 0, RegionPosition = 0;

	std::map<int, int> map_WidthPerLine;

	for (int hIndex = 0; hIndex < h; hIndex++)
	{
		stratX = w; endX = 0;
		regionWidth = 0;

		uchar* pSrc = FilterImg.ptr<uchar>(hIndex);
		//  找目标区域
		for (int wIndex = 0; wIndex < w; wIndex++)
		{
			if (pSrc[wIndex] == 0)
			{
				stratX = stratX < wIndex ? stratX : wIndex;
				endX = endX > wIndex ? endX : wIndex;
			}
		}

		regionWidth = endX - stratX + 1;

		if (regionWidth <= 0)
		{
			map_WidthPerLine[hIndex] = 0;
			continue;
		}
		map_WidthPerLine[hIndex] = regionWidth;

		//  基于图片中心纠正图片
		OffsetX = (w - regionWidth) / 2;

		for (int wIndex = 0; wIndex < regionWidth; wIndex++)
		{
			RegionPosition = hIndex * w + wIndex + stratX;
			ImagePosition = hIndex * w + wIndex + OffsetX;

			dstImg.data[ImagePosition] = srcImg.data[RegionPosition];
		}
	}

	//  中值滤波
	std::map<int, int> map_WidthPerLine_Filter;

	int HeightWide = DetectParaIn->MiddleFilterSize;  //  中值滤波窗口尺寸

	for (int hIndex = 0; hIndex < HeightWide; hIndex++)
	{
		map_WidthPerLine_Filter[hIndex] = map_WidthPerLine[hIndex];
	}

	for (int hIndex = h - HeightWide; hIndex < h; hIndex++)
	{
		map_WidthPerLine_Filter[hIndex] = map_WidthPerLine[hIndex];
	}

	for (int hIndex = HeightWide; hIndex < h - HeightWide; hIndex++)
	{
		map_WidthPerLine_Filter[hIndex] = FilterMiddleValue(&map_WidthPerLine, hIndex, HeightWide);
	}
	//  分离起伏位置

	std::map<int, double> map_LineDis_Wide2Thin, map_LineDis_Thin2Wide;
	vector<int> vec_Indice_Wide2Thin, vec_Indice_Thin2Wide;

	int CompareWide = DetectParaIn->DisCompareSize;
	int DisCompareAbsRatio = DetectParaIn->DisCompareAbsRatio;
	int SingleDirectionDisAbsRatio = DetectParaIn->SingleDirectionDisAbsRatio;

	double TopDis = 0, BottomDis = 0;

	//  将所有可能为节点的行加入
	for (int hIndex = CompareWide; hIndex < h - CompareWide; hIndex++)
	{
		TopDis = GetAverageValue(&map_WidthPerLine, hIndex, CompareWide, TOPPOINT) - map_WidthPerLine[hIndex];
		BottomDis = map_WidthPerLine[hIndex] - GetAverageValue(&map_WidthPerLine, hIndex, CompareWide, BOTTOMPOINT);

		if ((abs(TopDis - BottomDis) >= double(CompareWide) / DisCompareAbsRatio) &&                                                                     //  行的上、下 斜率变化的差异要大
			(abs(TopDis) <= double(CompareWide) / SingleDirectionDisAbsRatio || abs(BottomDis) <= double(CompareWide) / SingleDirectionDisAbsRatio) &&   //  上或下的斜率必须有一个差异小
			TopDis > BottomDis &&
			abs(abs(TopDis) - abs(BottomDis)) > abs(TopDis - BottomDis) / 2)                                                                                                                      //  上斜率大于下斜率
		{
			if (abs(TopDis) < abs(BottomDis))
			{
				map_LineDis_Thin2Wide[hIndex] = TopDis - BottomDis;
				vec_Indice_Thin2Wide.push_back(hIndex);
			}
			else
			{
				map_LineDis_Wide2Thin[hIndex] = TopDis - BottomDis;
				vec_Indice_Wide2Thin.push_back(hIndex);
			}
		}
	}

	//  过滤重复的行，
	int GroupThreshold = DetectParaIn->SameCrossPointFilterSize;   //  重复行的搜索范围
	int Order;
	int BaseLine, CurLine;
	int    MaxValue_Line;
	double MaxValue;
	vector<float> vec_Wide2Thin, vec_Thin2Wide;
	vector<int> vec_tmp;

	float AverageLine = 0;

	vec_tmp.clear();
	if (vec_Indice_Thin2Wide.size() > 1)
	{
		BaseLine = vec_Indice_Thin2Wide.at(0);
		vec_tmp.push_back(BaseLine);

		MaxValue_Line = BaseLine;
		MaxValue = map_LineDis_Thin2Wide[MaxValue_Line];

		for (int hIndex = 1; hIndex < vec_Indice_Thin2Wide.size(); hIndex++)
		{
			CurLine = vec_Indice_Thin2Wide.at(hIndex);
			if (CurLine - BaseLine <= GroupThreshold)
			{
				vec_tmp.push_back(CurLine);
			}
			else
			{
				for (int tIndex = 0; tIndex < vec_tmp.size(); tIndex++)
				{
					Order = vec_tmp.at(tIndex);
					AverageLine += Order;
					//if (map_LineDis_Thin2Wide[Order] >= MaxValue)
					//{
					//	MaxValue = map_LineDis_Thin2Wide[Order];
					//	MaxValue_Line = Order;
					//}
				}
				AverageLine = AverageLine / vec_tmp.size();
				vec_Thin2Wide.push_back(AverageLine);

				vec_tmp.clear();

				BaseLine = vec_Indice_Thin2Wide.at(hIndex);
				vec_tmp.push_back(BaseLine);

				AverageLine = 0;

				MaxValue_Line = BaseLine;
				MaxValue = map_LineDis_Thin2Wide[MaxValue_Line];
			}
			if (hIndex == vec_Indice_Thin2Wide.size() - 1)
			{
				for (int tIndex = 0; tIndex < vec_tmp.size(); tIndex++)
				{
					Order = vec_tmp.at(tIndex);
					//if (map_LineDis_Thin2Wide[Order] >= MaxValue)
					//{
					//	MaxValue = map_LineDis_Thin2Wide[Order];
					//	MaxValue_Line = Order;
					//}
					AverageLine += Order;
				}
				AverageLine = AverageLine / vec_tmp.size();
				vec_Thin2Wide.push_back(AverageLine);
			}
		}
	}

	if (vec_Indice_Wide2Thin.size() > 1)
	{
		vec_tmp.clear();

		BaseLine = vec_Indice_Wide2Thin.at(0);
		vec_tmp.push_back(BaseLine);

		MaxValue_Line = BaseLine;
		MaxValue = map_LineDis_Wide2Thin[MaxValue_Line];

		AverageLine = 0;

		for (int hIndex = 1; hIndex < vec_Indice_Wide2Thin.size(); hIndex++)
		{
			CurLine = vec_Indice_Wide2Thin.at(hIndex);
			if (CurLine - BaseLine <= GroupThreshold)
			{
				vec_tmp.push_back(CurLine);
			}
			else
			{
				for (int tIndex = 0; tIndex < vec_tmp.size(); tIndex++)
				{
					Order = vec_tmp.at(tIndex);
					//if (map_LineDis_Wide2Thin[Order] >= MaxValue)
					//{
					//	MaxValue = map_LineDis_Wide2Thin[Order];
					//	MaxValue_Line = Order;
					//}
					AverageLine += Order;
				}
				AverageLine = AverageLine / vec_tmp.size();
				vec_Wide2Thin.push_back(AverageLine);

				vec_tmp.clear();

				BaseLine = vec_Indice_Wide2Thin.at(hIndex);
				vec_tmp.push_back(BaseLine);

				MaxValue_Line = BaseLine;
				MaxValue = map_LineDis_Wide2Thin[MaxValue_Line];

				AverageLine = 0;
			}
			if (hIndex == vec_Indice_Wide2Thin.size() - 1)
			{
				for (int tIndex = 0; tIndex < vec_tmp.size(); tIndex++)
				{
					Order = vec_tmp.at(tIndex);
					//if (map_LineDis_Wide2Thin[Order] >= MaxValue)
					//{
					//	MaxValue = map_LineDis_Wide2Thin[Order];
					//	MaxValue_Line = Order;
					//}
					AverageLine += Order;
				}
				AverageLine = AverageLine / vec_tmp.size();
				vec_Wide2Thin.push_back(AverageLine);
			}
		}
	}

	Mat rgb;
	cv::cvtColor(srcImg, rgb, COLOR_GRAY2RGB);

	//  计算周期长度
	float Pixel_Dis = 0;

	if (vec_Wide2Thin.size() >= 2)
	{
		Pixel_Dis = vec_Wide2Thin.at(1) - vec_Wide2Thin.at(0);

		DetectParaOut->CycleStart = int(vec_Wide2Thin.at(0) + 0.5);
		DetectParaOut->CycleEnd = int(vec_Wide2Thin.at(1) + 0.5);
	}
	else if (vec_Thin2Wide.size() >= 2)
	{
		Pixel_Dis = vec_Thin2Wide.at(1) - vec_Thin2Wide.at(0);

		DetectParaOut->CycleStart = int(vec_Thin2Wide.at(0) + 0.5);
		DetectParaOut->CycleEnd = int(vec_Thin2Wide.at(1) + 0.5);
	}
	cv::line(rgb, Point2i(0, DetectParaOut->CycleStart), Point2i(rgb.cols - 1, DetectParaOut->CycleStart), CV_RGB(0, 250, 0));
	cv::line(rgb, Point2i(0, DetectParaOut->CycleEnd), Point2i(rgb.cols - 1, DetectParaOut->CycleEnd), CV_RGB(0, 250, 0));
	DetectParaOut->CycleDistance = Pixel_Dis;

	float StartPos = 0;
	float EndPos = 0;
	if (vec_Wide2Thin.size() > 0 && vec_Thin2Wide.size() > 0)
	{
		DetectParaOut->HalfCycleStart = int(vec_Wide2Thin.at(0) + 0.5);
		StartPos = vec_Wide2Thin.at(0);

		if (vec_Thin2Wide.at(0) - vec_Wide2Thin.at(0) >= DetectParaOut->CycleDistance * 0.3)
		{
			EndPos = vec_Thin2Wide.at(0);
			DetectParaOut->HalfCycleEnd = int(vec_Thin2Wide.at(0) + 0.5);
		}
		else
		{
			if (vec_Thin2Wide.size() > 1)
			{
				for (int hIndex = 1; hIndex < vec_Thin2Wide.size(); hIndex++)
				{
					if (vec_Thin2Wide.at(hIndex) - vec_Wide2Thin.at(0) >= DetectParaOut->CycleDistance * 0.3)
					{
						EndPos = vec_Thin2Wide.at(hIndex);
						DetectParaOut->HalfCycleEnd = int(vec_Thin2Wide.at(hIndex) + 0.5);
						break;
					}
				}
			}
		}

		if (DetectParaOut->HalfCycleEnd > 0)
		{
			DetectParaOut->HalfCycleDistance = EndPos - StartPos;
		}

		cv::line(rgb, Point2i(0, DetectParaOut->HalfCycleStart), Point2i(rgb.cols - 1, DetectParaOut->HalfCycleStart), CV_RGB(0, 0, 250));
		cv::line(rgb, Point2i(0, DetectParaOut->HalfCycleEnd), Point2i(rgb.cols - 1, DetectParaOut->HalfCycleEnd), CV_RGB(0, 0, 250));
	}
	labeledImg = rgb;
}

DLLAPI void STDCALL Cam2_Function(Mat srcImg, VisionParaIn* DetectParaIn, VisionParaOut* DetectParaOut, Mat& labeledImg)
{
	Mat dstImg;
	srcImg.copyTo(dstImg);

	labeledImg = dstImg;

	int w = srcImg.cols;
	int h = srcImg.rows;

	DetectParaOut->DetectResult = TOOL_INVALID;

	Mat binImg;
	cv::threshold(srcImg, binImg, 50, 255, CV_THRESH_BINARY);

	//  按照每列获取焊带上下位置坐标
	int TopPos = 0;
	int BottomPos = 0;

	std::map<int, int> map_TopDis, map_BottomDis, map_Dif, map_Height;

	for (int wIndex = 0; wIndex < w; wIndex++)
	{
		TopPos = GetFirstPos(binImg, wIndex);
		BottomPos = GetLastPos(binImg, wIndex);

		if (TopPos < 0 || BottomPos < 0)
		{
			map_TopDis[wIndex] = 0;
			map_BottomDis[wIndex] = 0;
			map_Dif[wIndex] = 0;
		}
		else
		{
			map_TopDis[wIndex] = TopPos;
			//下方需由位置转换为距离
			map_BottomDis[wIndex] = (h - BottomPos - 1);

			map_Dif[wIndex] = (h - BottomPos - 1) - TopPos;

			map_Height[wIndex] = BottomPos - TopPos;
		}
	}

	float LeftHeight = 0;
	float RightHeight = 0;

	int CalcuWidth = w / 10;

	int LeftNum = 0, RightNum = 0;
	for (int wIndex = 0; wIndex < CalcuWidth; wIndex++)
	{
		LeftHeight = LeftHeight + map_Height[wIndex];
		LeftNum++;
	}
	for (int wIndex = w - w / 20; wIndex < w; wIndex++)
	{
		RightHeight = RightHeight + map_Height[wIndex];
		RightNum++;
	}
	LeftHeight = LeftHeight / LeftNum;
	RightHeight = RightHeight / RightNum;

	if (RightHeight - LeftHeight < 20)
	{
		return;
	}

	int x1 = 0, x2 = 0;

	for (int wIndex = 0; wIndex < w; wIndex++)
	{
		if (abs(LeftHeight - map_Height[wIndex]) >= 5)
		{
			x1 = wIndex;
			break;
		}
	}

	//for (int wIndex = srcImage->width - 1; wIndex >= 0; wIndex--)
	//{
	//	if (abs(RightHeight - map_Height[wIndex]) >= 5)
	//	{
	//		x2 = wIndex;
	//		break;
	//	}
	//}
	for (int wIndex = x1 + 1; wIndex < w; wIndex++)
	{
		if (abs(RightHeight - map_Height[wIndex]) <= 5)
		{
			x2 = wIndex;
			break;
		}
	}

	if (x1 <= 0 || x2 <= 0 || x2 <= x1)
	{
		return;
	}

	x2 = x2 + 5;

	if (x2 >= w)
		x2 = w - 1;

	for (int hIndex = 0; hIndex < h; hIndex++)
	{
		dstImg.data[hIndex * w + x1] = 0;
		dstImg.data[hIndex * w + x2] = 0;
	}

	int CalcuLinePoint1 = x2 + 5;
	int CalcuLinePoint2 = x2 + 100;

	if (CalcuLinePoint2 >= w)
		CalcuLinePoint2 = w - 1;

	LineOb TopLine(x2, map_TopDis[x2], CalcuLinePoint2, map_TopDis[CalcuLinePoint2]);
	LineOb BottomLine(x2, map_Height[x2] + map_TopDis[x2], CalcuLinePoint2, map_Height[CalcuLinePoint2] + map_TopDis[CalcuLinePoint2]);

	int TopArea = 0, BottomArea = 0;
	for (int hIndex = 0; hIndex < h; hIndex++)
	{
		for (int wIndex = x1; wIndex <= x2; wIndex++)
		{
			if (TopLine.Point2LinePos(wIndex, hIndex) == ONLINE || BottomLine.Point2LinePos(wIndex, hIndex) == UNDERLINE)
				continue;

			if (hIndex < map_TopDis[wIndex])
			{
				TopArea++;
				dstImg.data[hIndex * w + wIndex] = 84;
			}
			if (hIndex > map_Height[wIndex] + map_TopDis[wIndex])
			{
				BottomArea++;
				dstImg.data[hIndex * w + wIndex] = 168;
			}
		}
	}

	if (TopArea - BottomArea > 0)
		DetectParaOut->DetectResult = TOOL_PASS;
	else
		DetectParaOut->DetectResult = TOOL_ERROR;

	labeledImg = dstImg;
}