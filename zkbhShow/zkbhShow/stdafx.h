// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <atlbase.h>

// TODO: reference additional headers your program requires here
#include "CvvImage.h"
#include "..\DuiLib\UIlib.h"
#ifdef _DEBUG
#pragma comment(lib,"../lib/DuiLib_d.lib")
#else
#pragma comment(lib,"../lib/DuiLib.lib")
#endif


#ifndef NO_USING_DUILIB_NAMESPACE
using namespace DuiLib;
using namespace std;
#endif

#include "opencv2/opencv.hpp"
#ifdef _DEBUG
#pragma comment(lib,"lib/Debug/opencv_highgui2413d.lib")
#pragma comment(lib,"lib/Debug/opencv_imgproc2413d.lib")
#pragma comment(lib,"lib/Debug/opencv_core2413d.lib")

#else
#pragma comment(lib,"lib/Release/opencv_highgui2413.lib")
#pragma comment(lib,"lib/Release/opencv_imgproc2413.lib")
#pragma comment(lib,"lib/Release/opencv_core2413.lib")
#endif

#pragma warning (disable:4996)
using namespace cv;

#include "detect.h"
#pragma comment(lib,"lib/fall_detect_x86.lib")