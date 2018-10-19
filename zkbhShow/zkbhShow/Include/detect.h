#ifndef DETECT_H_
#define DETECT_H_

#include <opencv2/core.hpp>

#define EXPORT extern "C" __declspec(dllexport)

#define FALL_HANDLE void*

typedef struct Line {
    int num;
    int* points;
} Line;

typedef struct DetectOut {
    int num;
    Line* lines;
} DetectOut;



EXPORT int CreateHandle(FALL_HANDLE* handle);
EXPORT int DestroyHandle(FALL_HANDLE* handle);

//EXPORT int find_target(cv::Mat frame_first, cv::Mat frame, DetectOut* out, float a_ = 0, float b_ = 0);
//EXPORT int find_target(unsigned char* frame_first_, unsigned char* frame_,
//                       unsigned int height, unsigned int width, unsigned int channels,
//                       DetectOut* out, float a_ = 0, float b_ = 0);

EXPORT int find_target(FALL_HANDLE handle,
                       unsigned char* frame_first_, unsigned char* frame_,
                       unsigned int height, unsigned int width, unsigned int channels,
                       DetectOut* out, float a_ = 0, float b_ = 0);

EXPORT int OutputDestroy(DetectOut* output);

#endif //DETECT_H_
