#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "LaplacianOperator.h"

int main()
{
    cv::Mat image = cv::imread("/Users/xyx/Documents/workspace/deeplearning/yolov3_darknet/dataset23/image/DE_BBBR667_2015-04-24_12-50-00-958489_k0.png");
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    LaplacianOperator laplaceop;
    laplaceop.conputerLaplacisan(image);
    cv::Mat laplaceimg = laplaceop.getLaplacianImage(-2);
    cv::imshow("laplace result", laplaceimg);
    cv::imwrite("/Users/xyx/Documents/workspace/clearning/learn_opencv/CH06_filter/laplaceimg.jpg", laplaceimg);
    cv::waitKey(0);

    return 0;
}