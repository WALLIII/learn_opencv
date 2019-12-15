#ifndef MORPHOLOGY_FILTER_H
#define MORPHOLOGY_FILTER_H

#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include<iostream>

class MorphologyFilter{
public:
MorphologyFilter():threshold(-1), cross(5,5), diamond(5,5), square(5,5), x(5,5)
                        {cross <<
                            0,0,1,0,0,
                            0,0,1,0,0,
                            1,1,1,1,1,
                            0,0,1,0,0,
                            0,0,1,0,0;
                        diamond <<
                            0,0,1,0,0,
                            0,1,1,1,0,
                            1,1,1,1,1,
                            0,1,1,1,0,
                            0,0,1,0,0;
                        square <<
                            1,1,1,1,1,
                            1,1,1,1,1,
                            1,1,1,1,1,
                            1,1,1,1,1,
                            1,1,1,1,1;
                        x <<
                            1,0,0,0,1,
                            0,1,0,1,0,
                            0,0,1,0,0,
                            0,1,0,1,0,
                            1,0,0,0,1;
                    };
cv::Mat open_process(const cv::Mat& image, const int elementSize);
cv::Mat closed_process(const cv::Mat& image, const int elementSize);
cv::Mat contour_detector(const cv::Mat& image);
cv::Mat getCorners(const cv::Mat& image);
void setThreshold(int t) { threshold=t; }
int getThreshold() const { return threshold; }
void DrawOnImage(const cv::Mat& corners, cv::Mat& image);

private:
// for corner detection
int threshold;
cv::Mat_<uchar> cross;
cv::Mat_<uchar> diamond;
cv::Mat_<uchar> square;
cv::Mat_<uchar> x;
void applyThreshold(cv::Mat& result){
    if(threshold>0){
        cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY_INV);
    }
}
};

cv::Mat MorphologyFilter::open_process(const cv::Mat& image, const int elementSize){
    cv::Mat open_result;
    cv::Mat element(elementSize, elementSize, CV_8U, cv::Scalar(1));
    cv::morphologyEx(image, open_result, cv::MORPH_OPEN, element);
    return open_result;
}

cv::Mat MorphologyFilter::closed_process(const cv::Mat& image, const int elementSize){
    cv::Mat closed_result;
    cv::Mat element(elementSize, elementSize, CV_8U, cv::Scalar(1));
    cv::morphologyEx(image, closed_result, cv::MORPH_CLOSE, element);
    return closed_result;
}

cv::Mat MorphologyFilter::contour_detector(const cv::Mat& image){
    cv::Mat contour_result;
    cv::morphologyEx(image, contour_result, cv::MORPH_GRADIENT, cv::Mat());
    int threshold = 40;
    cv::threshold(contour_result, contour_result, threshold, 255, cv::THRESH_BINARY);
    return contour_result;
}
cv::Mat MorphologyFilter::getCorners(const cv::Mat& image){
    cv::Mat result1;
    cv::dilate(image, result1, cross);
    cv::erode(result1, result1, diamond);
    cv::Mat result2;
    cv::dilate(image, result2, x);
    cv::erode(result2, result2, square);
    cv::absdiff(result1, result2, result1);
    applyThreshold(result1);
    // std::cout<<result1<<std::endl;
    // cv::imshow("result1", result1);
    // cv::waitKey(0);
    return result1;
    
}
void MorphologyFilter::DrawOnImage(const cv::Mat& corners, cv::Mat& image){
        cv::Mat_<uchar>::const_iterator it= corners.begin<uchar>();
		cv::Mat_<uchar>::const_iterator itend= corners.end<uchar>();

        // for each pixel	
        for (int i=0; it!= itend; ++it,++i) {
            if (!*it)
                cv::circle(image,cv::Point(i%image.step,i/image.step),5,cv::Scalar(255,0,0));
        }    

}
#endif
