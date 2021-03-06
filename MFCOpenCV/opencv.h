#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <string>
#include "pch.h"
#include "MFCOpenCV.h"
#include "MFCOpenCVDlg.h"


void sharpen(const cv::Mat& image, cv::Mat& result);

void canny(const cv::Mat& myImage, cv::Mat& result);

class Histogram1D {
private:
	int histSize[1];
	float hranges[2];
	const float* ranges[1];
	int channels[1];
public:
	Histogram1D();
	cv::MatND getHistogram(const cv::Mat& image);
	cv::Mat getHistogramImage(const cv::Mat& image);
};

