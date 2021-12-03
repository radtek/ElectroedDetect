// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBROULETTE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBROULETTE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifndef _IMAGECONVERT_H_INCLUDED_
#define _IMAGECONVERT_H_INCLUDED_

#ifdef IMAGECONVERT_EXPORTS
#define IMAGECONVERT_API  __declspec(dllexport)
#else
#define IMAGECONVERT_API __declspec(dllimport)
#endif
#include<vector>
#include<fstream> 
#include <string>
#include <iostream>
#include <string>
struct PointCloudHead
{
	unsigned int _height; //点云行数
	unsigned int _width; //点云列数
	double _xInterval; //点云列间距
	double _yInterval; //点云行间距
};
extern "C" _declspec(dllexport) int savePly(const char* file, int* data, PointCloudHead pcHead);
extern "C" _declspec(dllexport) int savePcd(const char* file, int* data, PointCloudHead pcHead);
















#endif