#ifndef _CSIDETECT_TOOL_
#define _CSIDETECT_TOOL_

#include "CSIItemStruct.h"
#include "CameraPara.h"


DLLAPI void STDCALL CheckImageFunction_First(IplImage* srcImage, IplImage* dstImage, CSIVisionParaIn* DetectParaIn, CSIVisionParaOut* DetectParaOut);
DLLAPI void STDCALL CheckImageFunction_Second(IplImage* srcImage,  IplImage* dstImage, CSIVisionParaIn2* DetectParaIn, CSIVisionParaOut2* DetectParaOut);

#ifdef UPPROCESS
#ifndef CSIDETECTTOOL_IMPLEMENT
#pragma comment(lib,"CSIDetectTool.lib")
#endif
#endif

#endif  //_CSIDETECT_TOOL_