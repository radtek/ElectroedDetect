#include <ZCVisionTool/ZCVisionTool.h>
#include <ZCVisionTool/Calibration.h>
#include "CalibInstance.h"

int ModelNum = 0;
CCalibrationModel* CalibInstance;

DLLAPI bool STDCALL CalibInit(int Num)
{
	if (Num <= 0)
		return false;

	ModelNum = Num;

	if (CalibInstance != NULL)
	{
		delete[] CalibInstance;
		CalibInstance = NULL;
	}

	CalibInstance = new CCalibrationModel[Num];

	return true;
}

DLLAPI bool STDCALL HandEyeCalibLoad(char* PointFilePath, int ModelIndex)
{
	if (ModelIndex >= ModelNum || ModelIndex < 0)
		return false;

	return CalibInstance[ModelIndex].LoadCalibData(PointFilePath, CALIB_TYPE_HAND_EYE);
}

DLLAPI bool STDCALL CalibTranslate(cv::Point2f ImagePoint, cv::Point2f* RealPoint, int ModelIndex)
{
	if (ModelIndex >= ModelNum || ModelIndex < 0)
		return false;

	return CalibInstance[ModelIndex].TranslateImagePointToWindowPoint(ImagePoint, RealPoint);

	return true;
}

DLLAPI bool STDCALL CalibTranslateEx(vector<cv::Point2f> ImagePointArray, vector<cv::Point2f>* RealPointArray, int ModelIndex)
{
	if (ModelIndex >= ModelNum || ModelIndex < 0 || ImagePointArray.size() <= 0)
		return false;

	Point2f ImagePoint;
	Point2f RealPoint;
	for (int i = 0; i < ImagePointArray.size(); i++)
	{
		ImagePoint = ImagePointArray[i];
		CalibInstance[ModelIndex].TranslateImagePointToWindowPoint(ImagePoint, &RealPoint);
		RealPointArray->push_back(RealPoint);
	}

	return true;
}