#pragma once

#include "ZcStruct.h"

#define  TOPPOINT    1
#define  BOTTOMPOINT 2

/*
*/
void ConnectedRegion(Mat BinaryImage, int DstValue, CvRect roiRect, PointsArray* ClosePointSet);

void FilterRegionBySize(cv::Size ImgSize, vector<vector<Point2i>>* PointArrayOfArray, int MinSize, int MaxSize, Mat& FilterImg);

int FilterMiddleValue(std::map<int, int>* mapSrc, int CurIndex, int FilterSize);

double GetAverageValue(std::map<int, int>* mapSrc, int CurIndex, int FilterSize, int FindType);

int GetFirstPos(Mat srcImg, int wIndex);

int GetLastPos(Mat srcImg, int wIndex);