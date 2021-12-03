#include "HFunction.h"

#define MODEL_NUM 20

HTuple hv_ModelId[MODEL_NUM];
bool   m_IsShapeMatchModel[MODEL_NUM];

#define MATCH_LEVEL 5

void MyHalconExceptionHandler(const HException& except)
{
	throw except;
}

Mat HImageToMat(HObject& Hobj)
{
	HTuple htChannels;
	HTuple cType;
	HTuple width, height;
	int W, H;
	Herror  error_num;

	Mat OutImage;
	try
	{
		ConvertImageType(Hobj, &Hobj, "byte");
		CountChannels(Hobj, &htChannels);
		if (htChannels[0].I() == 1)
		{
			HTuple ptr;
			GetImagePointer1(Hobj, &ptr, &cType, &width, &height);
			W = width[0].I();
			H = height[0].I();

			OutImage.create(H, W, CV_8U);

			uchar* pdata = (uchar*)ptr[0].L();
			memcpy(OutImage.data, pdata, W * H);
		}
	}
	catch (HException& except)
	{
		error_num = except.ErrorCode();
	}
	return OutImage;
}

bool MatToHImage(Mat pImage, HObject* Hobj)
{
	Herror  error_num;

	int height = pImage.rows;
	int width = pImage.cols;

	try
	{
		if (3 == pImage.channels())
		{
			Mat channel[3];
			split(pImage, channel);
			GenImage3(Hobj, "byte", pImage.cols, pImage.rows, (Hlong)(channel[2].ptr()), (Hlong)(channel[1].ptr()), (Hlong)(channel[0].ptr()));
		}
		if (1 == pImage.channels())
		{
			GenImage1(Hobj, "byte", width, height, (Hlong)(pImage.ptr()));
		}
	}
	catch (HException& except)
	{
		error_num = except.ErrorCode();
		return false;
	}
	return true;
}

//----模板匹配
DLLAPI void STDCALL InitShapeMatchFunc()
{
	HException::InstallHHandler(&MyHalconExceptionHandler);

	for (int MatchIndex = 0; MatchIndex < MODEL_NUM; MatchIndex++)
	{
		m_IsShapeMatchModel[MatchIndex] = false;
		try
		{
			ClearShapeModel(hv_ModelId[MatchIndex]);
		}
		catch (HException& except)
		{
		}
	}
}

DLLAPI bool STDCALL CreateShapeMatchFunc(Mat MtachModelImage, MatchParaIn* MtachModelParaIn)
{
	int ModelIndex = MtachModelParaIn->MatchParaIndex;

	if (ModelIndex < 0)
		ModelIndex = MODEL_NUM - 1;

	bool ret = true;

	HTuple hv_ModelRow, hv_ModelCol, hv_ModelAngle, hv_ModelScore;

	HObject ho_SrcImage, ho_ReducedImage, ho_ModelImage, ho_ModelRegion, ho_TemplateImage;

	MatToHImage(MtachModelImage, &ho_SrcImage);

	int MinXValue = MtachModelParaIn->GetSearchRectX1();
	int MaxXValue = MtachModelParaIn->GetSearchRectX2();

	int MinYValue = MtachModelParaIn->GetSearchRectY1();
	int MaxYValue = MtachModelParaIn->GetSearchRectY2();

	GenRectangle1(&ho_ModelRegion, MinYValue, MinXValue, MaxYValue, MaxXValue);

	ReduceDomain(ho_SrcImage, ho_ModelRegion, &ho_ReducedImage);

	CropDomain(ho_ReducedImage, &ho_ModelImage);

	MaxXValue = MtachModelParaIn->GetModelRectX2() - MinXValue;
	MaxYValue = MtachModelParaIn->GetModelRectY2() - MinYValue;

	MinXValue = MtachModelParaIn->GetModelRectX1() - MinXValue;
	MinYValue = MtachModelParaIn->GetModelRectY1() - MinYValue;

	GenRectangle1(&ho_ModelRegion, MinYValue, MinXValue, MaxYValue, MaxXValue);

	ReduceDomain(ho_ModelImage, ho_ModelRegion, &ho_TemplateImage);

	HException::InstallHHandler(&MyHalconExceptionHandler);

	try
	{
		if (m_IsShapeMatchModel[ModelIndex] == true)
		{
			ClearShapeModel(hv_ModelId[ModelIndex]);
			m_IsShapeMatchModel[ModelIndex] = false;
		}

		CreateShapeModel(ho_TemplateImage,
			HTuple(MATCH_LEVEL),                                                     // 金字塔层数
			HTuple(0).TupleRad(), HTuple(360).TupleRad(), HTuple(0.4258).TupleRad(),      // 角度
			(HTuple("point_reduction_high").Append("no_pregeneration")),   // 优化方法
			"use_polarity",	                                               // 匹配方法
			((HTuple(MtachModelParaIn->LowContrast).Append(MtachModelParaIn->HighContrast)).Append(MtachModelParaIn->MinXLDLength)),
			3,
			&hv_ModelId[ModelIndex]);

		m_IsShapeMatchModel[ModelIndex] = true;

		FindShapeModel(ho_ModelImage, hv_ModelId[ModelIndex],
			HTuple(0).TupleRad(), HTuple(360).TupleRad(),                             //角度
			0.2,                         //最低匹配得分
			1,                                                              //匹配数目
			0.3,                                                            //最大重叠
			"least_squares",                                                //SubPixel的方法
			(HTuple(MATCH_LEVEL).Append(1)),                                          //层数
			0.75,                               //贪婪程度  0  0.9  1
			&hv_ModelRow, &hv_ModelCol, &hv_ModelAngle, &hv_ModelScore);

		if (hv_ModelCol.TupleLength() > 0)
		{
			MtachModelParaIn->LocatePoint.x = hv_ModelCol[0].D() + MtachModelParaIn->GetSearchRectX1();
			MtachModelParaIn->LocatePoint.y = hv_ModelRow[0].D() + MtachModelParaIn->GetSearchRectY1();
			MtachModelParaIn->LocateR = hv_ModelAngle[0].D() * 180 / VL_PI;
			MtachModelParaIn->LocateScore = hv_ModelScore[0].D();

			if (MtachModelParaIn->LocateR >= 180)
				MtachModelParaIn->LocateR -= 360;
			if (MtachModelParaIn->LocateR <= -180)
				MtachModelParaIn->LocateR += 360;
		}
		else
		{
			ret = false;
		}
	}
	catch (HException& except)
	{
		return false;
	}
	if (ret && MtachModelParaIn->LocateScore < MtachModelParaIn->MinScore)
	{
		ret = false;
	}
	return ret;
}

DLLAPI bool STDCALL FindShapeMatchFunc(Mat srcImage, MatchParaIn* MtachModelParaIn, MatchParaOut* MtachModelParaOut)
{
	int ModelIndex = MtachModelParaIn->MatchParaIndex;

	if (ModelIndex < 0)
		ModelIndex = MODEL_NUM - 1;

	if (m_IsShapeMatchModel[ModelIndex] == false)
	{
		return false;
	}

	HObject ho_SrcImage, ho_ReducedImage, ho_ModelImage, ho_ROI;

	HTuple hv_ModelRow, hv_ModelCol, hv_ModelAngle, hv_ModelScore;

	MatToHImage(srcImage, &ho_SrcImage);

	int MinXValue = VL_MIN(MtachModelParaIn->Search_FirstPoint.x, MtachModelParaIn->Search_ThirdPoint.x);
	int MaxXValue = VL_MAX(MtachModelParaIn->Search_FirstPoint.x, MtachModelParaIn->Search_ThirdPoint.x);

	int MinYValue = VL_MIN(MtachModelParaIn->Search_FirstPoint.y, MtachModelParaIn->Search_ThirdPoint.y);
	int MaxYValue = VL_MAX(MtachModelParaIn->Search_FirstPoint.y, MtachModelParaIn->Search_ThirdPoint.y);

	GenRectangle1(&ho_ROI, MinYValue, MinXValue, MaxYValue, MaxXValue);

	ReduceDomain(ho_SrcImage, ho_ROI, &ho_ReducedImage);

	CropDomain(ho_ReducedImage, &ho_ModelImage);

	try
	{
		FindShapeModel(ho_ModelImage, hv_ModelId[ModelIndex],
			HTuple(0).TupleRad(), HTuple(360).TupleRad(),                             //角度
			0.2,                        //最低匹配得分
			1,                                                              //匹配数目
			0.3,                                                            //最大重叠
			"least_squares",                                                //SubPixel的方法
			(HTuple(MATCH_LEVEL).Append(1)),                                          //层数
			0.75,                               //贪婪程度  0  0.9  1
			&hv_ModelRow, &hv_ModelCol, &hv_ModelAngle, &hv_ModelScore);

		MtachModelParaOut->LocatePoint.x = hv_ModelCol[0].D() + MtachModelParaIn->GetSearchRectX1();
		MtachModelParaOut->LocatePoint.y = hv_ModelRow[0].D() + MtachModelParaIn->GetSearchRectY1();
		MtachModelParaOut->LocateR = hv_ModelAngle[0].D() * 180 / VL_PI;
		MtachModelParaOut->LocateScore = hv_ModelScore[0].D();

		if (MtachModelParaOut->LocateR >= 180)
			MtachModelParaOut->LocateR -= 360;
		if (MtachModelParaOut->LocateR <= -180)
			MtachModelParaOut->LocateR += 360;
	}
	catch (HException& except)
	{
		return false;
	}

	if (MtachModelParaOut->LocateScore < MtachModelParaIn->MinScore)
	{
		return false;
	}

	return true;
}