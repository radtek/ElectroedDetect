//宏定义文件---定义公用的宏
#ifndef _PUBLIC_FILE_H_
#define _PUBLIC_FILE_H_

#include <string>
#include <malloc.h>
#include <string.h>
#include <vector>
#include <atltime.h>
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <iostream>
using namespace std;

#ifndef IGNORE_OPENCV
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc_c.h"
using namespace cv;
#endif

#define ARC_DIRECT_CLOSCWISE        1    
#define ARC_DIRECT_ANTI_CLOSCWISE   2

#define VL_MIN(x,y) (((x)<(y))?(x):(y))
#define VL_MAX(x,y) (((x)>(y))?(x):(y))
#define VL_PI        3.1415926
#define RADIAN       0.017453292519943 // pi/180
#define DEGREE       57.29577951308232 // 180/pi
#define MAX_FILE     512

/***************************************************************
       针对工具的检测问题得到的相关宏定义
****************************************************************/
#define TOOL_INVALID                  0x0000         //有效
#define TOOL_PASS                     0x0001         //通过
#define TOOL_ERROR                    0x0010
#define TOOL_ERROR_OUT_RANGE          0x0020
#define TOOL_NG_LESS_DIS              0x6110         //距离不满足
#define TOOL_NG_NUM_RANGE             0x6120         //数目不满足
#define TOOL_NG_DISVAR_RANGE          0x6121         //方差不满足
#define TOOL_NG_LENGTH_RANGE          0x6122         //长度不满足
#define TOOL_NG_ANGLE_RANGE           0x6123         //角度不满足
#define TOOL_NG_EXIST_DEFECT          0x6124         //存在缺陷
#define TOOL_NG_RADIUS_RANGE          0x6125         //半径不满足
#define TOOL_NG_ECCENT_RANGE          0x6126         //长短轴比值不满足
#define TOOL_NG_LESS_ACCURAY          0x6127         //阈值不满足
#define TOOL_NG_STRNOTMATCH           0x6128         //字符串不匹配
#define TOOL_NG_NO_INFO               0x6129         //没有符合匹配信息
#define TOOL_NG_LESS_SCORE            0x6130         //得分不满足

#define ANGLEERROR      1.6

#define ArrayInt std::vector<int>

#ifndef GenMsgLIB
#   if defined DLL_EXPORT
#       define GM_EXPORT __declspec(dllexport)
#   else
#       define GM_EXPORT __declspec(dllimport)
#   endif
#else
#    define  GM_EXPORT
#endif

#ifdef UPPROCESS
#define DLLAPI    extern "C"
#define STDCALL   _stdcall
#endif
#endif   //_PUBLIC_FILE_H_