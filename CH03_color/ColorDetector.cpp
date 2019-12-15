// #include"ColorDetector.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>

// cv::Mat ColorDetector::process(const cv::Mat &image){
//     result.create(image.rows, image.cols, CV_8U);
//     cv::Mat_<cv::Vec3b>::const_iterator it=
//                             image.begin<cv::Vec3b>();
//     cv::Mat_<cv::Vec3b>::const_iterator itend=
//                             image.end<cv::Vec3b>();
//     cv::Mat_<cv::Vec3b>::const_iterator itout=
//                             result.begin<cv::Vec3b>();
//     for(; it!=itend; ++it, ++itout){
//         if (getDistance(*it) <= minDist){
//             *itout=255;
//         }
//         else{
//             *itout = 0;
//         }
//     }
//     return result;
// }

void detectHScolor(const cv::Mat& image, 
                    double minHue, double maxHue,
                    double minSat, double maxSat, cv::Mat& mask){
    cv::Mat hsv;
    cv::cvtColor(image, hsv, CV_BGR2HSV);
    std::vector<cv::Mat> channels;
    cv::split(hsv, channels);

    //mask for hue
    cv::Mat mask1;
    cv::threshold(channels[0], mask1, maxHue, 255, cv::THRESH_BINARY_INV);
    cv::Mat mask2;
    cv::threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY);
    cv::Mat hueMask;
    if(minHue < maxHue){
        hueMask = mask1&mask2;
    }
    else{
        hueMask = mask1|mask2;
    }
    //mask for saturation
    cv::threshold(channels[1], mask1, maxSat, 255, cv::THRESH_BINARY_INV);
    cv::threshold(channels[1], mask2, minSat, 255, cv::THRESH_BINARY);
    cv::Mat satMask;
    if(minSat < maxSat){
        satMask = mask1&mask2;
    }
    else{
        satMask = mask1|mask2;
    }

    mask = hueMask&satMask;
}
int main(){
    
    cv::Mat mask;
    cv::Mat img = cv::imread("/Users/xyx/Documents/workspace/clearning/learn_opencv/image/girl.jpg");
    detectHScolor(img, 160, 10, 25, 166, mask);
    cv::Mat res(img.size(), CV_8UC3, cv::Scalar(0,0,0));
    img.copyTo(res, mask);
    cv::namedWindow("res");
    cv::imshow("res", res);
    cv::waitKey();
    return 0;
}
