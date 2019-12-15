#ifndef WATERSHED_SEGMENTOR_H
#define WATERSHED_SEGMENTOR_H
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
class WatershedSegmentor{
public:
WatershedSegmentor():markers(0,0, CV_32S){};
// preprocess for binary image
cv::Mat getMarker(const cv::Mat& binary);
//  maerker image must be CV_32S
void setMarker(const cv::Mat& markerImage){
    markerImage.convertTo(markers, CV_32S);
}
cv::Mat watershedProcess(const cv::Mat& oriImage){
    cv::watershed(oriImage, markers);
    return markers;
}
cv::Mat getSegmentation(){
    cv::Mat temp;
    markers.convertTo(temp, CV_8U);
    return temp;
}

private:
cv::Mat markers;

};
cv::Mat WatershedSegmentor::getMarker(const cv::Mat& binary){
    cv::Mat fg;
    cv::erode(binary, fg, cv::Mat(), cv::Point(-1,-1), 4);
    // cv::imshow("erode res, fg", fg);
    cv::Mat bg;
    cv::dilate(binary, bg, cv::Mat(), cv::Point(-1,-1), 4);
    cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);
    // cv::imshow("dilate res, bg", bg);
    
    cv::Mat markerImage(binary.size(), CV_8U, cv::Scalar(0));
    markerImage = bg + fg;
    // cv::imshow("preprocess res", markerImage);
    return markerImage;
}
#endif