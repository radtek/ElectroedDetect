#pragma once

#define CALIB_TYPE_HAND_EYE     1
#define CALIB_TYPE_CHESS_BOARD  2
//--  Calibration
DLLAPI bool STDCALL CalibInit(int Num);

DLLAPI bool STDCALL HandEyeCalibLoad(char* PointFilePath, int ModelIndex);

DLLAPI bool STDCALL CalibTranslate(cv::Point2f ImagePoint, cv::Point2f* RealPoint, int ModelIndex);

DLLAPI bool STDCALL CalibTranslateEx(vector<cv::Point2f> ImagePointArray, vector<cv::Point2f>* RealPointArray, int ModelIndex);