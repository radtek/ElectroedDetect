#ifndef CV_CALIB_INSTANCE_H
#define CV_CALIB_INSTANCE_H

/*
* x1 = a * x0 + b * y0 + c;
* y1 = d * x0 + e * y0 + f;
*/
typedef struct tagCalibPara {
	double a, b, c, d, e, f;
	void Init() {
		a = 0; b = 0; c = 0;
		d = 0; e = 0; f = 0;
	}
}CalibPara;

class CCalibrationModel
{
public:
	CCalibrationModel() {
		m_CalibPara.Init();
		m_CalibType = -1;
	};
	~CCalibrationModel() {};
public:
	bool LoadCalibData(char* FolderPath, int CalibModel);
	bool TranslateImagePointToWindowPoint(Point2f ImagePoint, Point2f* RealPoint);
private:
	bool HandEyeLoadCalibData(char* FolderPath);
	bool HandEyeTranslateImagePointToWindowPoint(Point2f ImagePoint, Point2f* RealPoint);

	int m_CalibType;
	CalibPara m_CalibPara;
};
#endif