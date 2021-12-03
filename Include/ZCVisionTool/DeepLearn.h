#ifndef DEEPLEARN_H
#define DEEPLEARN_H

DLLAPI void STDCALL DeepLearnModelInit(vector<std::string> PathArray);
DLLAPI bool STDCALL DeepLearnModelPred(int index, Mat srcImage, Mat& dstImage);
DLLAPI void STDCALL DeepLearnModelPred_Classify(int index, Mat srcImage, int ValidIndiceStartEnd, vector<int>* ResultIndice);

#endif