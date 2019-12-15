#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "LineFInder.h"

int main()
{
    cv::Mat image = cv::imread("/Users/xyx/Documents/workspace/deeplearning/yolov3_darknet/dataset23/image/DE_BBBR667_2015-04-24_12-50-00-958489_k0.png");
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::Mat contour;
    cv::Canny(image, contour, 100, 350);
    LineFinder finder;
    finder.setLineLengthAndGap(100, 20);
    finder.setMinVote(30);
    std::vector<cv::Vec4i> lines = finder.findLines(contour);
    finder.drawDetectedLines(image);
    cv::imshow("canny result", image);
    cv::imwrite("/Users/xyx/Documents/workspace/clearning/learn_opencv/CH07_lineExtract/canny_result.jpg", image);
    cv::waitKey(0);

    return 0;
}