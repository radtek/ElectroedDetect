#pragma once

#include "ZcStruct.h"
#include <opencv2/opencv.hpp>
#include <HalconCpp\HalconCpp.h>

using namespace HalconCpp;

void MyHalconExceptionHandler(const HException& except);
Mat HImageToMat(HObject& Hobj);
bool MatToHImage(Mat pImage, HObject* Hobj);