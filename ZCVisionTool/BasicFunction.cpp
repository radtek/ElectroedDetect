#include "BasicFunction.h"


void ConnectedRegion(Mat srcImage, int DstValue, CvRect rect, PointsArray* ClosePointSet)
{
	Mat MarkImage = Mat::zeros(srcImage.size(), CV_8U);

	int hIndex = 0, wIndex = 0, Position = 0;

	int iStartNum = 0, iEndNum = 0;

	int XValue = 0, YValue = 0, dIndex = 0;

	vector<Point2i> tempPointSet;

	for (hIndex = rect.y; hIndex < rect.y + rect.height; hIndex++)
	{
		for (wIndex = rect.x; wIndex < rect.x + rect.width; wIndex++)
		{
			Position = hIndex * srcImage.cols + wIndex;

			if (srcImage.data[Position] == 255 - DstValue || MarkImage.data[Position] == 128)
				continue;

			iStartNum = -1; iEndNum = 0;

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

void FilterRegionBySize(cv::Size ImgSize, vector<vector<Point2i>>* PointArrayOfArray, int MinSize, int MaxSize, Mat& FilterImg)
{
	Mat m;
	m = Mat::zeros(ImgSize, CV_8U);

	if (PointArrayOfArray->size() <= 0 || MinSize <= 0)
	{
		FilterImg = m;
		return;
	}

	vector<vector<Point2i>> tempPointArrayofArray;
	tempPointArrayofArray.swap(*PointArrayOfArray);

	Point2i p;

	for (int i = 0; i < tempPointArrayofArray.size(); i++)
	{
		if (tempPointArrayofArray[i].size() < MinSize)
			continue;

		if (MaxSize > MinSize && tempPointArrayofArray[i].size() > MaxSize)
			continue;

		PointArrayOfArray->push_back(tempPointArrayofArray[i]);

		for (int j = 0; j < tempPointArrayofArray[i].size(); j++)
		{
			p = tempPointArrayofArray[i][j];
			m.at<uchar>(p.y, p.x) = 255;
		}
	}
	FilterImg = m;
}

int FilterMiddleValue(std::map<int, int>* mapSrc, int CurIndex, int FilterSize)
{
	vector<int> tempVec;

	std::map<int, int>::iterator iter;

	for (int hIndex = CurIndex - FilterSize; hIndex <= CurIndex + FilterSize; hIndex++)
	{
		iter = mapSrc->find(hIndex);
		tempVec.push_back(iter->second);
	}
	sort(tempVec.begin(), tempVec.end());

	return tempVec.at(FilterSize);
}

double GetAverageValue(std::map<int, int>* mapSrc, int CurIndex, int FilterSize, int FindType)
{
	double rtn = 0; int LineNum = 0;

	std::map<int, int>::iterator iter;

	if (FindType == TOPPOINT)
	{
		for (int hIndex = CurIndex - FilterSize; hIndex < CurIndex; hIndex++)
		{
			iter = mapSrc->find(hIndex);
			rtn += iter->second;
			LineNum++;
		}
	}
	else
	{
		for (int hIndex = CurIndex + 1; hIndex <= CurIndex + FilterSize; hIndex++)
		{
			iter = mapSrc->find(hIndex);
			rtn += iter->second;
			LineNum++;
		}
	}
	rtn = rtn / LineNum;

	return rtn;
}

int GetFirstPos(Mat srcImg, int wIndex)
{
	int rtn = -1;

	for (int hIndex = 0; hIndex < srcImg.rows; hIndex++)
	{
		if (srcImg.data[hIndex * srcImg.cols + wIndex] == 0)
		{
			rtn = hIndex;
			break;
		}
	}
	return rtn;
}

int GetLastPos(Mat srcImg, int wIndex)
{
	int rtn = -1;

	for (int hIndex = srcImg.rows - 1; hIndex >= 0; hIndex--)
	{
		if (srcImg.data[hIndex * srcImg.cols + wIndex] == 0)
		{
			rtn = hIndex;
			break;
		}
	}
	return rtn;
}