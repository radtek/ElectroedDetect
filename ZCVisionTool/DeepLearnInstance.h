#ifndef CV_DEEPLEARNING_INSTANCE_H
#define CV_DEEPLEARNING_INSTANCE_H

class CDeepLearn
{
public:
	CDeepLearn() { m_IsLoadSuccess = false; };
	~CDeepLearn() {};

	bool LoadModel(std::string path);
	bool PredictImage(Mat srcImage, Mat& ProbilityImage);
	bool PredictImage_Classify(Mat srcImage, std::vector<std::vector<float>>* Probility);
private:
	bool m_IsLoadSuccess;
	dnn::Net net;
	std::string weights_file;
};

#endif