#include <ZCVisionTool/ZCVisionTool.h>
#include <ZCVisionTool/DeepLearn.h>
#include "DeepLearnInstance.h"

CDeepLearn* DeepLearnInstance;
int AIModelNum = 0;
DLLAPI void STDCALL DeepLearnModelInit(vector<std::string> PathArray)
{
	int num = PathArray.size();

	AIModelNum = num;

	if (num <= 0)
		return;

	if (DeepLearnInstance != NULL)
	{
		delete[] DeepLearnInstance;
		DeepLearnInstance = NULL;
	}

	DeepLearnInstance = new CDeepLearn[num];

	for (int i = 0; i < num; i++)
	{
		DeepLearnInstance[i].LoadModel(PathArray[i]);
	}
}

DLLAPI bool STDCALL DeepLearnModelPred(int index, Mat srcImage, Mat& dstImage)
{
	if (index >= AIModelNum)
		return false;

	Mat m = Mat::zeros(srcImage.size(), srcImage.type());

	if (DeepLearnInstance == NULL)
		return false;

	bool ret = DeepLearnInstance[index].PredictImage(srcImage, m);

	dstImage = m;

	return ret;
}

void GetMaxScoreIndice(vector<vector<float>> ScoreArrayofArray, vector<int>* MaxScoreIndice)
{
	if (ScoreArrayofArray.size() <= 0)
		return;

	for (int i = 0; i < ScoreArrayofArray.size(); i++)
	{
		vector<float> compareVec = ScoreArrayofArray[i];

		if (compareVec.size() <= 0)
		{
			MaxScoreIndice->push_back(-1);
			continue;
		}

		int maxScore = compareVec[0];
		int indice = 0;

		for (int j = 0; j < compareVec.size(); j++)
		{
			if (compareVec[j] > maxScore)
			{
				maxScore = compareVec[j];
				indice = j;
			}
		}
		MaxScoreIndice->push_back(indice);
	}
}

void CombineRepeteiveResult(vector<int> srcIndice, vector<int>* dstIndice)
{
	if (srcIndice.size() <= 0)
		return;

	dstIndice->push_back(srcIndice[0]);

	if (srcIndice.size() == 1)
		return;

	for (int i = 1; i < srcIndice.size(); i++)
	{
		if (srcIndice[i] != dstIndice->at(dstIndice->size() - 1))
			dstIndice->push_back(srcIndice[i]);
	}
}

void DeleteInvalidResult(int ValidIndiceStartEnd, vector<int> srcIndice, vector<int>* dstIndice)
{
	if (srcIndice.size() <= 0)
		return;

	for (int i = 0; i < srcIndice.size(); i++)
	{
		if (srcIndice[i] >= ValidIndiceStartEnd)
			continue;

		dstIndice->push_back(srcIndice[i]);
	}
}

DLLAPI void STDCALL DeepLearnModelPred_Classify(int index, Mat srcImage, int ValidIndiceStartEnd, vector<int>* ResultIndice)
{
	//   输入图片等比例缩放到高度为64，缩放后宽度方向拉伸1.5倍
	cv::Size size;
	size.height = 64;
	size.width = float(srcImage.cols * size.height) / float(srcImage.rows) * 1.5;
	
	Mat resizedImg;
	resize(srcImage, resizedImg, size);

	Mat src = resizedImg.t();

	vector<vector<float>> classifyResult;
	bool ret = DeepLearnInstance[index].PredictImage_Classify(src, &classifyResult);

	vector<int> maxScoreIndice;
	GetMaxScoreIndice(classifyResult, &maxScoreIndice);

	vector<int> combinedIndeice;
	CombineRepeteiveResult(maxScoreIndice, &combinedIndeice);

	DeleteInvalidResult(ValidIndiceStartEnd, combinedIndeice, ResultIndice);
}