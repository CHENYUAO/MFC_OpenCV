#include "pch.h"
#include "opencv.h"

void sharpen(const cv::Mat& image, cv::Mat& result) {
	result.create(image.size(), image.type());
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	cv::filter2D(image, result, image.depth(), kernel);
}

Histogram1D::Histogram1D() {
	histSize[0] = 256;
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	ranges[0] = hranges;
	channels[0] = 0;
}

cv::MatND Histogram1D::getHistogram(const cv::Mat& image) {
	cv::MatND hist;
	cv::calcHist(&image,
		1,
		channels,
		cv::Mat(),
		hist,
		1,
		histSize,
		ranges);
	return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat& image) {
	cv::MatND hist = getHistogram(image);
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));
	int hpt = static_cast<int>(0.9 * histSize[0]);
	for (int h = 0; h < histSize[0]; h++) {
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal * hpt / maxVal);
		cv::line(histImg, cv::Point(h, histSize[0]),
			cv::Point(h, histSize[0] - intensity),
			cv::Scalar::all(0));
	}
	return histImg;
}

void canny(const cv::Mat& myImage, cv::Mat& result) {
	cv::Mat src1 = myImage.clone();

	//ת��Ϊ�Ҷ�ͼ�����룬Ȼ����canny�õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ���õ���ɫ�ı�Եͼ
	cv::Mat  edge, gray;

	//������srcͬ���ͺʹ�С�ľ���
	result.create(src1.size(), src1.type());

	//��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(src1, gray, cv::COLOR_BGR2GRAY);

	//ʹ��3��3�ں˽���
	blur(gray, edge, cv::Size(3, 3));

	//ʹ��canny����
	Canny(edge, edge, 3, 9, 3);

	//��dstImage������Ԫ��Ϊ0
	result = cv::Scalar::all(0);

	//ʹ��Canny��������ı�Եͼ��g_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage������Ŀ��ͼg_dstImage��
	src1.copyTo(result, edge);
}