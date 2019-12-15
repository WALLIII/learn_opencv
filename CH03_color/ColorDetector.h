#ifndef COLOR_DETECTOR_H
#define COLOR_DETECTOR_H

#include<opencv2/core/core.hpp>
#include<iostream>

class ColorDetector{
public:
ColorDetector():minDist(100), targetColor(0,0,0){}
cv::Mat process(const cv::Mat& image);
void setColorDistanceThreshold(int distance){
    if(distance<0) distance=0;
    minDist=distance;
}
int getColorDistanceThreshold()const{
    return minDist;
}
void setTargetColor(uchar blue, uchar green, uchar red){
    targetColor = cv::Vec3b(blue, green, red);
}
void setTargetColor(cv::Vec3b color){targetColor = color; }
cv::Vec3b getTargetColor()const{ return targetColor; }

private:
    int minDist;
    cv::Vec3b targetColor;
    cv::Mat result;
    int getDistance(const cv::Vec3b &color) const{
        // return abs(color[0]-targetColor[0])+abs(color[1]-targetColor[1])+abs(color[2]-targetColor[2]);
        return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color[0]-targetColor[0],
                                                            color[1]-targetColor[1],
                                                            color[2]-targetColor[2])));                                                            
    }

};
cv::Mat ColorDetector::process(const cv::Mat &image){
    result.create(image.rows, image.cols, CV_8U);
    cv::Mat_<cv::Vec3b>::const_iterator it=
                            image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend=
                            image.end<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itout=
                            result.begin<cv::Vec3b>();
    std::cout<<minDist<<std::endl;
    for(; it!=itend; ++it, ++itout){
        if (getDistance(*it) <= minDist){
            *itout=255;
        }
        else{
            // std::cout<<getDistance(*it)<<std::endl;
            *itout = 0;
        }
    }
    return result;
}

#endif


// int main(){
//     cv::Mat img = cv::imread("/Users/xyx/Documents/workspace/clearning/learn_opencv/image/photo.jpg");
//     if(!img.data){
//         return 0;
//     }
//     ColorDetector cdetect;
//     cdetect.setTargetColor(230,190,130);
//     cv::namedWindow("result");
//     cv::Mat res = cdetect.process(img);
//     cv::imshow("result", res);
//     cv::waitKey();

//     return 0;
// }