#include <ZCVisionTool/ZCVisionTool.h>
#include <ZCVisionTool/DeepLearn.h>
#include "DeepLearnInstance.h"

bool CDeepLearn::LoadModel(std::string path)
{
	if (path == "NAN")
		return false;

	weights_file = path;

	try
	{
		net = cv::dnn::readNetFromTensorflow(weights_file);
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();

		return false;
	}

	//  CPU
	//net.setPreferableBackend(dnn::DNN_BACKEND_OPENCV);
	//net.setPreferableTarget(dnn::DNN_TARGET_CPU);

	//GPU
	net.setPreferableBackend(dnn::DNN_BACKEND_CUDA);
	net.setPreferableTarget(dnn::DNN_TARGET_CUDA);

	m_IsLoadSuccess = true;

	return true;
}

bool CDeepLearn::PredictImage(Mat srcImage, Mat& ProbilityImage)
{
	if (!m_IsLoadSuccess)
		return false;

	Mat mat;

	Mat blob = dnn::blobFromImage(srcImage, 1.0/255);

	net.setInput(blob);

	Mat pred = net.forward();
	std::vector<Mat> outArray;

	dnn::imagesFromBlob(pred, outArray);

	if (outArray.size() > 0)
	{
		mat = outArray[0];
	}
	else
	{
		return false;
	}

	double maxVal = 0, minVal = 0;
	minMaxLoc(mat, &minVal, &maxVal);

	Mat mat_8U;
	mat.convertTo(mat_8U, CV_8U, 255.0);

	ProbilityImage = mat_8U;

	return true;
}

bool CDeepLearn::PredictImage_Classify(Mat srcImage, std::vector<std::vector<float>>* Probility)
{
	if (!m_IsLoadSuccess)
		return false;

	Mat mat;

	Mat blob = dnn::blobFromImage(srcImage, 1.0 / 255);

	net.setInput(blob);

	Mat pred = net.forward();

	if (pred.dims != 3)
		return false;

	int byteSizeTotal = pred.step[0];
	int byteSizePixel = pred.step[1];
	int byteSizeVar = pred.step[2];

	int outPutPixelNum = byteSizeTotal / byteSizePixel;
	int classNum = byteSizePixel / byteSizeVar;

	if (outPutPixelNum <= 0 || classNum <= 0)
		return false;

	std::vector<float> piexlProbility;
	for (int pixelIndex = 0; pixelIndex < outPutPixelNum; pixelIndex++)
	{
		float* ptr = pred.ptr<float>(0, pixelIndex);

		piexlProbility.clear();
		for (int classIndex = 0; classIndex < classNum; classIndex++)
		{
			piexlProbility.push_back(ptr[classIndex]);
		}
		Probility->push_back(piexlProbility);
	}

	return true;
}