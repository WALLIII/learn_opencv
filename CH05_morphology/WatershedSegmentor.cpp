#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include"WatershedSegmentor.h"

 
int main(){
    cv::Mat oriimage = cv::imread("/Users/xyx/Documents/workspace/clearning/learn_opencv/image/group.jpg");
    cv::Mat binary = cv::imread("/Users/xyx/Documents/workspace/clearning/learn_opencv/image/binaryGroup.bmp", 
                                                            CV_LOAD_IMAGE_GRAYSCALE);

    WatershedSegmentor segmenter;
    cv::Mat processedBinary = segmenter.getMarker(binary);
    segmenter.setMarker(processedBinary);
    cv::Mat res = segmenter.watershedProcess(oriimage);
    cv::Mat segment_res = segmenter.getSegmentation();
    cv::imshow("final res", segment_res);
    cv::waitKey(0);
    std::cout<<"i am here!!";
    return 0;
}