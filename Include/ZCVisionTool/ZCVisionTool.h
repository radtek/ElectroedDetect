#ifndef _CSIDETECT_TOOL_
#define _CSIDETECT_TOOL_

#include "ZcStruct.h"

DLLAPI void STDCALL Cam1_Function(Mat srcImg, VisionParaIn* DetectParaIn, VisionParaOut* DetectParaOut, Mat& labeledImg);
DLLAPI void STDCALL Cam2_Function(Mat srcImg, VisionParaIn* DetectParaIn, VisionParaOut* DetectParaOut, Mat& labeledImg);

#ifdef UPPROCESS
#ifndef ZCVISIONTOOL_IMPLEMENT
#pragma comment(lib,"ZCVisionTool.lib")
#endif
#endif
#endif  //_CSIDETECT_TOOL_