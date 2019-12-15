#ifndef LAPLACIAN_OPERATOR_H
#define LAPLACIAN_OPERATOR_H
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

class LaplacianOperator
{
public:
    LaplacianOperator() : aperatur(3) {}
    void serAperatur(int a) { aperatur = a; }
    cv::Mat conputerLaplacisan(const cv::Mat &image)
    {
        cv::Laplacian(image, laplace, CV_32F, aperatur);
        return laplace;
    }
    cv::Mat getLaplacianImage(double scalar = -1);
    cv::Mat getLaplacianCrossing();

private:
    //  define a laplacian operator
    cv::Mat laplace;
    //  define the aperture of kernel
    int aperatur;
};
cv::Mat LaplacianOperator::getLaplacianImage(double scalar)
{
    if (scalar < 0)
    {
        double lapmin, lapmax;
        cv::minMaxLoc(laplace, &lapmin, &lapmax);
        scalar = 127 / std::max(-lapmin, lapmax);
    }
    cv::Mat laplaceImage;
    laplace.convertTo(laplaceImage, CV_8U, scalar, 128);
    return laplaceImage;
}
cv::Mat LaplacianOperator::getLaplacianCrossing(){
    cv::Mat signImage;
    cv::threshold(laplace, signImage, 0, 255, cv::THRESH_BINARY);
    cv::Mat binary;
    signImage.convertTo(binary, CV_8U);
    cv::Mat dilated;
    cv::dilate(binary, dilated, cv::Mat());
    return dilated-binary;
}
#endif