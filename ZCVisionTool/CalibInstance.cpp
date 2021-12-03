#include <ZCVisionTool/ZCVisionTool.h>
#include <ZCVisionTool/Calibration.h>
#include "CalibInstance.h"

#include <Utility/Utility.h>
#include <Utility/IniFile.h>

bool CCalibrationModel::LoadCalibData(char* FolderPath, int CalibModel)
{
	m_CalibType = CalibModel;

	if (m_CalibType == CALIB_TYPE_HAND_EYE)
	{
		return HandEyeLoadCalibData(FolderPath);
	}
	else
	{
		return false;
	}
}

bool CCalibrationModel::HandEyeLoadCalibData(char* FolderPath)
{
	char FilePath[1024] = { '\0' }; char tagStr[1024] = { '\0' };

	sprintf_s(FilePath, "%s\\CalibPoints.ini", FolderPath);

	CIniFile readMsg;
	if (!readMsg.OpenIniFile((LPCSTR)FilePath))
		return false;

	cv::Point2f ReadPoint;
	vector<cv::Point2f>points_camera, points_robot;

	for (int hIndex = 0; hIndex < 9; hIndex++)
	{
		sprintf_s(tagStr, "Point-%d", hIndex + 1);

		ReadPoint.x = readMsg.ReadFileFloat(tagStr, "CamPointX");
		ReadPoint.y = readMsg.ReadFileFloat(tagStr, "CamPointY");
		points_camera.push_back(ReadPoint);

		ReadPoint.x = readMsg.ReadFileFloat(tagStr, "RobotPointX");
		ReadPoint.y = readMsg.ReadFileFloat(tagStr, "RobotPointY");
		points_robot.push_back(ReadPoint);
	}

	readMsg.CloseIniFile();

	Mat warpMat = estimateRigidTransform(points_camera, points_robot, true);

	m_CalibPara.a = warpMat.ptr<double>(0)[0];
	m_CalibPara.b = warpMat.ptr<double>(0)[1];
	m_CalibPara.c = warpMat.ptr<double>(0)[2];
	m_CalibPara.d = warpMat.ptr<double>(1)[0];
	m_CalibPara.e = warpMat.ptr<double>(1)[1];
	m_CalibPara.f = warpMat.ptr<double>(1)[2];

	return true;
}

bool CCalibrationModel::TranslateImagePointToWindowPoint(Point2f ImagePoint,Point2f* RealPoint)
{
	if (m_CalibType == CALIB_TYPE_HAND_EYE)
	{
		return HandEyeTranslateImagePointToWindowPoint(ImagePoint, RealPoint);
	}
	else
	{
		return false;
	}
}

bool CCalibrationModel::HandEyeTranslateImagePointToWindowPoint(Point2f ImagePoint, Point2f* RealPoint)
{
	RealPoint->x = m_CalibPara.a * ImagePoint.x + m_CalibPara.b * ImagePoint.y + m_CalibPara.c;
	RealPoint->y = m_CalibPara.d * ImagePoint.x + m_CalibPara.e * ImagePoint.y + m_CalibPara.f;

	return true;
}