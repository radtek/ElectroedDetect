#pragma once

#include "ZcStruct.h"

//--  OpenCV
void ConnectedRegion(Mat BinaryImage, int DstValue, CvRect roiRect, vector<vector<Point2i>>* ClosePointSet);
void ConnectedRegionEx(Mat srcImage, int DstValue, CvRect rect, vector<vector<Point2i>>* ClosePointSet);
Mat FilterRegionBySize(cv::Size ImgSize, vector<vector<Point2i>>* PointArrayOfArray, int MinSize, int MaxSize = 0, int OffsetX = 0, int OffsetY = 0);
void DeepLearnSegMent(Mat srcImage, DeepLearnSegmentIn* SegmentParaIn, DeepLearnSegmentOut* SegmentParaOut, int ModelIndex);
bool IsPtInCircleLoop(Point2i pt, Point2i CircleCenter, float r1, float r2);
bool IsPtInCircle(Point2i pt, Point2i CircleCenter, float r1);
Mat fillHole(const Mat srcBw);

bool FitCircle(vector<Point2i>* EdgePoints, CircleObj* Circle);
int FitCircleObj(vector<Point2i> PointSet, CircleObj* OutCircle);
bool RansacCirclePoints(vector<Point2i> EdgePoints, vector<Point2i>* BestPoint);
int DotThreeCircle(Point2i Point1, Point2i Point2, Point2i Point3, CircleObj* OutCircle);
void EstimateCircle(vector<Point2i> PointSet, CircleObj Circle, vector<Point2i>* BestPoint);