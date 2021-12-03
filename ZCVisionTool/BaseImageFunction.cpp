#include "BaseImageFunction.h"

#include <ZCVisionTool/DeepLearn.h>

#define DIS_EUCLIDEN(x1,y1,x2,y2) sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))

#define CIRCLEDIS 2
#define MAXCIRCLEVALUE 100000

void ConnectedRegion(Mat srcImage, int DstValue, CvRect rect, vector<vector<Point2i>>* ClosePointSet)
{
	Mat MarkImage = Mat::zeros(srcImage.size(), CV_8U);

	int hIndex = 0, wIndex = 0, Position = 0;

	int iStartNum = 0, iEndNum = 0;

	int XValue = 0, YValue = 0, dIndex = 0;

	int MinXValue = 0, MaxXValue = 0, MinYValue = 0, MaxYValue = 0;

	vector<Point2i> tempPointSet;

	for (hIndex = rect.y; hIndex < rect.y + rect.height; hIndex++)
	{
		for (wIndex = rect.x; wIndex < rect.x + rect.width; wIndex++)
		{
			Position = hIndex * srcImage.cols + wIndex;

			if (srcImage.data[Position] == 255 - DstValue || MarkImage.data[Position] == 128)
				continue;

			iStartNum = -1; iEndNum = 0;

			MaxXValue = 0; MaxYValue = 0; MinXValue = 1 << 30; MinYValue = 1 << 30;

			tempPointSet.push_back(cvPoint(wIndex, hIndex));

			MarkImage.data[Position] = 128;

			while (iStartNum < iEndNum)
			{
				iStartNum = iStartNum + 1;

				XValue = tempPointSet[iStartNum].x;
				YValue = tempPointSet[iStartNum].y;

				if (XValue < rect.x || XValue > rect.x + rect.width - 1
					|| YValue < rect.y || YValue > rect.y + rect.height - 1)
					continue;

				MinXValue = MinXValue > XValue ? XValue : MinXValue;
				MaxXValue = MaxXValue < XValue ? XValue : MaxXValue;

				MinYValue = MinYValue > YValue ? YValue : MinYValue;
				MaxYValue = MaxYValue < YValue ? YValue : MaxYValue;

				Position = YValue * srcImage.cols + XValue;

				if (XValue - 1 >= rect.x && YValue - 1 >= rect.y
					&& MarkImage.data[Position - srcImage.cols - 1] == 0
					&& srcImage.data[Position - srcImage.cols - 1] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue - 1, YValue - 1));
					MarkImage.data[Position - srcImage.cols - 1] = 128;
				}

				if (YValue - 1 >= rect.y && XValue >= rect.x
					&& MarkImage.data[Position - srcImage.cols] == 0
					&& srcImage.data[Position - srcImage.cols] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue, YValue - 1));
					MarkImage.data[Position - srcImage.cols] = 128;
				}

				if (XValue + 1 < rect.x + rect.width && YValue - 1 >= rect.y
					&& MarkImage.data[Position - srcImage.cols + 1] == 0
					&& srcImage.data[Position - srcImage.cols + 1] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue + 1, YValue - 1));
					MarkImage.data[Position - srcImage.cols + 1] = 128;
				}

				if (XValue + 1 < rect.x + rect.width && YValue >= rect.y
					&& MarkImage.data[Position + 1] == 0
					&& srcImage.data[Position + 1] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue + 1, YValue));
					MarkImage.data[Position + 1] = 128;
				}

				if (XValue + 1 < rect.x + rect.width && YValue + 1 < rect.y + rect.height
					&& MarkImage.data[Position + srcImage.cols + 1] == 0
					&& srcImage.data[Position + srcImage.cols + 1] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue + 1, YValue + 1));
					MarkImage.data[Position + srcImage.cols + 1] = 128;
				}

				if (YValue + 1 < rect.y + rect.height && XValue >= rect.x
					&& MarkImage.data[Position + srcImage.cols] == 0
					&& srcImage.data[Position + srcImage.cols] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue, YValue + 1));
					MarkImage.data[Position + srcImage.cols] = 128;
				}

				if (XValue - 1 >= rect.x && YValue + 1 < rect.y + rect.height
					&& MarkImage.data[Position + srcImage.cols - 1] == 0
					&& srcImage.data[Position + srcImage.cols - 1] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue - 1, YValue + 1));
					MarkImage.data[Position + srcImage.cols - 1] = 128;
				}

				if (XValue - 1 >= rect.x && YValue > rect.x
					&& MarkImage.data[Position - 1] == 0
					&& srcImage.data[Position - 1] == DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue - 1, YValue));
					MarkImage.data[Position - 1] = 128;
				}
				iEndNum = tempPointSet.size() - 1;
			}
			ClosePointSet->push_back(tempPointSet);

			tempPointSet.clear();
		}
	}
}

void ConnectedRegionEx(Mat srcImage, int DstValue, CvRect rect, vector<vector<Point2i>>* ClosePointSet)
{
	Mat MarkImage = Mat::zeros(srcImage.size(), CV_8U);

	int hIndex = 0, wIndex = 0, Position = 0;

	int iStartNum = 0, iEndNum = 0;

	int XValue = 0, YValue = 0, dIndex = 0;

	int MinXValue = 0, MaxXValue = 0, MinYValue = 0, MaxYValue = 0;

	vector<Point2i> tempPointSet;

	int InValidNum = 0;

	for (hIndex = rect.y; hIndex < rect.y + rect.height; hIndex++)
	{
		for (wIndex = rect.x; wIndex < rect.x + rect.width; wIndex++)
		{
			Position = hIndex * srcImage.cols + wIndex;

			if (srcImage.data[Position] == 255 - DstValue || MarkImage.data[Position] == 128)
				continue;

			InValidNum = 0;

			iStartNum = -1; iEndNum = 0;

			MaxXValue = 0; MaxYValue = 0; MinXValue = 1 << 30; MinYValue = 1 << 30;

			tempPointSet.push_back(cvPoint(wIndex, hIndex));

			if (srcImage.data[Position] == 128)
				InValidNum++;

			MarkImage.data[Position] = 128;

			while (iStartNum < iEndNum)
			{
				iStartNum = iStartNum + 1;

				XValue = tempPointSet[iStartNum].x;
				YValue = tempPointSet[iStartNum].y;

				if (XValue < rect.x || XValue > rect.x + rect.width - 1
					|| YValue < rect.y || YValue > rect.y + rect.height - 1)
					continue;

				MinXValue = MinXValue > XValue ? XValue : MinXValue;
				MaxXValue = MaxXValue < XValue ? XValue : MaxXValue;

				MinYValue = MinYValue > YValue ? YValue : MinYValue;
				MaxYValue = MaxYValue < YValue ? YValue : MaxYValue;

				Position = YValue * srcImage.cols + XValue;

				if (XValue - 1 >= rect.x && YValue - 1 >= rect.y
					&& MarkImage.data[Position - srcImage.cols - 1] == 0
					&& srcImage.data[Position - srcImage.cols - 1] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue - 1, YValue - 1));
					MarkImage.data[Position - srcImage.cols - 1] = 128;

					if (srcImage.data[Position - srcImage.cols - 1] != DstValue)
						InValidNum++;
				}

				if (YValue - 1 >= rect.y && XValue >= rect.x
					&& MarkImage.data[Position - srcImage.cols] == 0
					&& srcImage.data[Position - srcImage.cols] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue, YValue - 1));
					MarkImage.data[Position - srcImage.cols] = 128;

					if (srcImage.data[Position - srcImage.cols] != DstValue)
						InValidNum++;
				}

				if (XValue + 1 < rect.x + rect.width && YValue - 1 >= rect.y
					&& MarkImage.data[Position - srcImage.cols + 1] == 0
					&& srcImage.data[Position - srcImage.cols + 1] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue + 1, YValue - 1));
					MarkImage.data[Position - srcImage.cols + 1] = 128;

					if (srcImage.data[Position - srcImage.cols + 1] != DstValue)
						InValidNum++;
				}

				if (XValue + 1 < rect.x + rect.width && YValue >= rect.y
					&& MarkImage.data[Position + 1] == 0
					&& srcImage.data[Position + 1] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue + 1, YValue));
					MarkImage.data[Position + 1] = 128;

					if (srcImage.data[Position + 1] != DstValue)
						InValidNum++;
				}

				if (XValue + 1 < rect.x + rect.width && YValue + 1 < rect.y + rect.height
					&& MarkImage.data[Position + srcImage.cols + 1] == 0
					&& srcImage.data[Position + srcImage.cols + 1] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue + 1, YValue + 1));
					MarkImage.data[Position + srcImage.cols + 1] = 128;

					if (srcImage.data[Position + srcImage.cols + 1] != DstValue)
						InValidNum++;
				}

				if (YValue + 1 < rect.y + rect.height && XValue >= rect.x
					&& MarkImage.data[Position + srcImage.cols] == 0
					&& srcImage.data[Position + srcImage.cols] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue, YValue + 1));
					MarkImage.data[Position + srcImage.cols] = 128;

					if (srcImage.data[Position + srcImage.cols] != DstValue)
						InValidNum++;
				}

				if (XValue - 1 >= rect.x && YValue + 1 < rect.y + rect.height
					&& MarkImage.data[Position + srcImage.cols - 1] == 0
					&& srcImage.data[Position + srcImage.cols - 1] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue - 1, YValue + 1));
					MarkImage.data[Position + srcImage.cols - 1] = 128;

					if (srcImage.data[Position + srcImage.cols - 1] != DstValue)
						InValidNum++;
				}

				if (XValue - 1 >= rect.x && YValue > rect.x
					&& MarkImage.data[Position - 1] == 0
					&& srcImage.data[Position - 1] != 255 - DstValue)
				{
					tempPointSet.push_back(cvPoint(XValue - 1, YValue));
					MarkImage.data[Position - 1] = 128;

					if (srcImage.data[Position - 1] != DstValue)
						InValidNum++;
				}
				iEndNum = tempPointSet.size() - 1;
			}

			if (tempPointSet.size() <= 5 || float(InValidNum) / tempPointSet.size() > 0.5)
			{
				tempPointSet.clear();
				continue;
			}

			ClosePointSet->push_back(tempPointSet);

			tempPointSet.clear();
		}
	}
}

Mat FilterRegionBySize(cv::Size ImgSize, vector<vector<Point2i>>* PointArrayOfArray, int MinSize, int MaxSize, int OffsetX, int OffsetY)
{
	Mat m;
	m = Mat::zeros(ImgSize, CV_8U);

	if (PointArrayOfArray->size() <= 0 || MinSize <= 0)
		return m;

	vector<Point2i> tempPointArray;
	vector<vector<Point2i>> tempPointArrayofArray;
	tempPointArrayofArray.swap(*PointArrayOfArray);

	Point2i p;

	for (int i = 0; i < tempPointArrayofArray.size(); i++)
	{
		tempPointArray.clear();

		if (tempPointArrayofArray[i].size() < MinSize)
			continue;

		if (MaxSize > MinSize && tempPointArrayofArray[i].size() > MaxSize)
			continue;

		for (int j = 0; j < tempPointArrayofArray[i].size(); j++)
		{
			p = tempPointArrayofArray[i][j];
			m.at<uchar>(p.y, p.x) = 255;

			tempPointArray.push_back(Point2i(p.x + OffsetX, p.y + OffsetY));
		}
		PointArrayOfArray->push_back(tempPointArray);
	}
	return m;
}

void DeepLearnSegMent(Mat srcImage, DeepLearnSegmentIn* SegmentParaIn, DeepLearnSegmentOut* SegmentParaOut, int ModelIndex)
{
	Mat inputImg;
	cv::resize(srcImage, inputImg, cv::Size(512,512));

	Mat preditImg;
	bool ret = DeepLearnModelPred(ModelIndex, inputImg, preditImg);

	if (!ret)
		return;

	Mat ResizedImg;
	cv::resize(preditImg, ResizedImg, srcImage.size());

	int iThreshold = SegmentParaIn->ProbabilityThreshold * 255;

	Mat binaryImg;
	cv::threshold(ResizedImg, binaryImg, iThreshold, 255, THRESH_BINARY);

	if (SegmentParaIn->MorphSize >= 3)
	{
		Mat structureElement = getStructuringElement(MORPH_RECT, Size(SegmentParaIn->MorphSize, SegmentParaIn->MorphSize));
		Mat erodeImg;
		erode(binaryImg, erodeImg, structureElement);
		erodeImg.copyTo(binaryImg);
	}
	vector<vector<Point>> ConnectPointArrayOfArray;
	ConnectedRegion(binaryImg, 255, cvRect(0, 0, binaryImg.cols, binaryImg.rows), &ConnectPointArrayOfArray);

	Mat filterSizeImage = FilterRegionBySize(binaryImg.size(), &ConnectPointArrayOfArray, SegmentParaIn->AreaThreshold);

	SegmentParaOut->DefectPointArrayOfArray.swap(ConnectPointArrayOfArray);
}

bool IsPtInCircleLoop(Point2i pt, Point2i CircleCenter, float r1, float r2)
{
	bool ret = true;

	float rOuter = r1 > r2 ? r1 : r2;
	float rInner = r1 > r2 ? r2 : r1;

	float dis = DIS_EUCLIDEN(pt.x, pt.y, CircleCenter.x, CircleCenter.y);

	if (dis > rOuter || dis < rInner)
		ret = false;

	return ret;
}

bool IsPtInCircle(Point2i pt, Point2i CircleCenter, float r1)
{
	bool ret = true;

	float dis = DIS_EUCLIDEN(pt.x, pt.y, CircleCenter.x, CircleCenter.y);

	if (dis > r1)
		ret = false;

	return ret;
}

bool FitCircle(vector<Point2i>* EdgePoints, CircleObj* Circle)
{
	vector<Point2i> CirclePoints;

	RansacCirclePoints(*EdgePoints, &CirclePoints);

	if (CirclePoints.size() < EdgePoints->size() * 0.3 || CirclePoints.size() < 30)
		return false;

	FitCircleObj(CirclePoints, Circle);

	return true;
}

bool RansacCirclePoints(vector<Point2i> EdgePoints, vector<Point2i>* BestPoint)
{
	int hIndex = 0, wIndex = 0, dIndex = 0, IsCircleObj = 0;

	CircleObj TempCircle;

	vector<Point2i> dBestPoint;

	int TempValue = EdgePoints.size() * 0.3;

	if (TempValue <= 0)
		return false;

	for (hIndex = 0; hIndex < TempValue; hIndex++)
	{
		wIndex = 0.60 * EdgePoints.size() + hIndex - 2;

		dIndex = (hIndex + wIndex) / 2;

		if (!DotThreeCircle(EdgePoints[hIndex], EdgePoints[dIndex], EdgePoints[wIndex], &TempCircle))
			continue;

		if (TempCircle.Radius > MAXCIRCLEVALUE)
			continue;

		EstimateCircle(EdgePoints, TempCircle, &dBestPoint);

		if (dBestPoint.size() > BestPoint->size())
		{
			BestPoint->clear();

			for (int i = 0; i < dBestPoint.size(); i++)
				BestPoint->push_back(dBestPoint[i]);
		}
		dBestPoint.clear();
	}//0---1/3之后部分的图像构建

	for (hIndex = 0; hIndex < TempValue; hIndex++)
	{
		wIndex = EdgePoints.size() * 0.4 + hIndex - 2;

		dIndex = (hIndex + wIndex) / 2;

		if (!DotThreeCircle(EdgePoints[hIndex], EdgePoints[dIndex], EdgePoints[wIndex], &TempCircle))
			continue;

		if (TempCircle.Radius > MAXCIRCLEVALUE)
			continue;

		EstimateCircle(EdgePoints, TempCircle, &dBestPoint);

		if (dBestPoint.size() > BestPoint->size())
		{
			BestPoint->clear();

			for (int i = 0; i < dBestPoint.size(); i++)
				BestPoint->push_back(dBestPoint[i]);
		}
		dBestPoint.clear();
	}//0---1/3之后部分的图像构建

	for (hIndex = TempValue; hIndex < EdgePoints.size() * 0.56; hIndex++)
	{
		wIndex = EdgePoints.size() * 0.70 + (hIndex - TempValue);

		dIndex = (hIndex + wIndex) / 2;

		//以当期序号的点集组成圆周，评估圆周的比例
		if (!DotThreeCircle(EdgePoints[hIndex], EdgePoints[dIndex], EdgePoints[wIndex], &TempCircle))
			continue;

		if (TempCircle.Radius > MAXCIRCLEVALUE)
			continue;

		EstimateCircle(EdgePoints, TempCircle, &dBestPoint);

		if (dBestPoint.size() > BestPoint->size())
		{
			BestPoint->clear();

			for (int i = 0; i < dBestPoint.size(); i++)
				BestPoint->push_back(dBestPoint[i]);
		}
		dBestPoint.clear();
	}//0---1/3之后部分的图像构建
	return true;
}

int DotThreeCircle(Point2i Point1, Point2i Point2, Point2i Point3, CircleObj* OutCircle)
{
	double Point1X = Point1.x, Point1Y = Point1.y;
	double Point2X = Point2.x, Point2Y = Point2.y;
	double Point3X = Point3.x, Point3Y = Point3.y;

	double SumX1Value = Point1X + Point2X + Point3X;
	double SumY1Value = Point1Y + Point2Y + Point3Y;

	double SumX2Value = Point1X * Point1X + Point2X * Point2X + Point3X * Point3X;
	double SumY2Value = Point1Y * Point1Y + Point2Y * Point2Y + Point3Y * Point3Y;

	double SumX3Value = Point1X * Point1X * Point1X + Point2X * Point2X * Point2X + Point3X * Point3X * Point3X;
	double SumY3Value = Point1Y * Point1Y * Point1Y + Point2Y * Point2Y * Point2Y + Point3Y * Point3Y * Point3Y;

	double SumX1Y1Value = Point1X * Point1Y + Point2X * Point2Y + Point3X * Point3Y;
	double SumX1Y2Value = Point1X * Point1Y * Point1Y + Point2X * Point2Y * Point2Y + Point3X * Point3Y * Point3Y;
	double SumX2Y1Value = Point1X * Point1X * Point1Y + Point2X * Point2X * Point2Y + Point3X * Point3X * Point3Y;

	int N = 3, result = 1;

	double C = N * SumX2Value - SumX1Value * SumX1Value;
	double D = N * SumX1Y1Value - SumX1Value * SumY1Value;
	double E = N * SumX3Value + N * SumX1Y2Value - (SumX2Value + SumY2Value) * SumX1Value;
	double G = N * SumY2Value - SumY1Value * SumY1Value;
	double H = N * SumX2Y1Value + N * SumY3Value - (SumX2Value + SumY2Value) * SumY1Value;

	double A1 = 0, B1 = 0, C1 = 0;

	A1 = (H * D - E * G) / (C * G - D * D);
	B1 = (H * C - E * D) / (D * D - G * C);
	C1 = -(A1 * SumX1Value + B1 * SumY1Value + SumX2Value + SumY2Value) / N;

	OutCircle->CirclePoint.x = -A1 / 2;
	OutCircle->CirclePoint.y = -B1 / 2;
	OutCircle->Radius = sqrtf((float)(A1 * A1 + B1 * B1 - 4 * C1)) / 2;

	return result;
}

void EstimateCircle(vector<Point2i> PointSet, CircleObj Circle, vector<Point2i>* BestPoint)
{
	float dis = 0;

	Point2f dTempPoint;

	float MinDis = (Circle.Radius - CIRCLEDIS) * (Circle.Radius - CIRCLEDIS);
	float MaxDis = (Circle.Radius + CIRCLEDIS) * (Circle.Radius + CIRCLEDIS);

	for (int hIndex = 0; hIndex < PointSet.size(); hIndex++)
	{
		dTempPoint = PointSet[hIndex];

		dis = (dTempPoint.x - Circle.CirclePoint.x) * (dTempPoint.x - Circle.CirclePoint.x)
			+ (dTempPoint.y - Circle.CirclePoint.y) * (dTempPoint.y - Circle.CirclePoint.y);

		if (dis >= MinDis && dis <= MaxDis)
			BestPoint->push_back(dTempPoint);
	}
}

int FitCircleObj(vector<Point2i> PointSet, CircleObj* OutCircle)
{
	double SumX1Value = 0, SumY1Value = 0, SumX2Value = 0, SumY2Value = 0;
	double SumX3Value = 0, SumY3Value = 0, SumX1Y1Value = 0, SumX1Y2Value = 0, SumX2Y1Value = 0;

	double TempPointX = 0, TempPointY = 0;  Point2f TempPoint;

	for (int hIndex = 0; hIndex < PointSet.size(); hIndex++)
	{
		TempPoint = PointSet[hIndex];

		TempPointX = TempPoint.x; TempPointY = TempPoint.y;

		SumX1Value += TempPointX;
		SumY1Value += TempPointY;

		SumX2Value += TempPointX * TempPointX;
		SumY2Value += TempPointY * TempPointY;

		SumX3Value += TempPointX * TempPointX * TempPointX;
		SumY3Value += TempPointY * TempPointY * TempPointY;

		SumX1Y1Value += TempPointX * TempPointY;
		SumX1Y2Value += TempPointX * TempPointY * TempPointY;
		SumX2Y1Value += TempPointX * TempPointX * TempPointY;
	}

	int N = PointSet.size(), result = 1;

	double C = N * SumX2Value - SumX1Value * SumX1Value;
	double D = N * SumX1Y1Value - SumX1Value * SumY1Value;
	double E = N * SumX3Value + N * SumX1Y2Value - (SumX2Value + SumY2Value) * SumX1Value;
	double G = N * SumY2Value - SumY1Value * SumY1Value;
	double H = N * SumX2Y1Value + N * SumY3Value - (SumX2Value + SumY2Value) * SumY1Value;

	double A1 = 0, B1 = 0, C1 = 0;

	if (C * G - D * D < 1 && C * G - D * D > -1)
	{
		A1 = 0; B1 = 0; C1 = 0;

		result = 0;
	}
	else
	{
		A1 = (H * D - E * G) / (C * G - D * D);
		B1 = (H * C - E * D) / (D * D - G * C);
		C1 = -(A1 * SumX1Value + B1 * SumY1Value + SumX2Value + SumY2Value) / N;
	}

	OutCircle->CirclePoint.x = -A1 / 2;
	OutCircle->CirclePoint.y = -B1 / 2;
	OutCircle->Radius = sqrtf(A1 * A1 + B1 * B1 - 4 * C1) / 2;

	return result;
}

Mat fillHole(const Mat srcBw)
{
	Mat m;

	Size m_Size = srcBw.size();
	Mat Temp = Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcBw.type());//延展图像
	srcBw.copyTo(Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));

	cv::floodFill(Temp, Point(0, 0), Scalar(255));

	Mat cutImg;//裁剪延展的图像
	Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);

	m = srcBw | (~cutImg);

	return m;
}