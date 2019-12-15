#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

 
int main(){
    cv::Mat image = cv::imread("/Users/xyx/Documents/workspace/deeplearning/yolov3_darknet/dataset23/image/DE_BBBR667_2015-04-24_12-50-00-958489_k0.png");
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    std::cout << "type of gray image is :" << image.type() <<std::endl;
    cv::Mat sobelx, sobely;
    double sobmin, sobmax;
    cv::Sobel(image, sobelx, CV_16S, 1, 0, 3, CV_SCHARR);
    cv::minMaxLoc(sobelx, &sobmin, &sobmax);
    std::cout << "sobel min:" << sobmin << "sobel max" <<sobmax << std::endl;
    // cv::imshow("sobelx", sobelx);
    cv::Sobel(image, sobely, CV_16S, 0, 1, 3, CV_SCHARR);
    // cv::imshow("sobely", sobely);
    cv::minMaxLoc(sobely, &sobmin, &sobmax);
    std::cout << "sobel min:" << sobmin << "sobel max" <<sobmax << std::endl;
    cv::Mat sobel_res;
    sobel_res = abs(sobelx) + abs(sobely);
    cv::minMaxLoc(sobel_res, &sobmin, &sobmax);
    std::cout << "sobel min:" << sobmin << "sobel max" <<sobmax << std::endl;
    cv::Mat sobelImage;
    sobel_res.convertTo(sobelImage, CV_8U, -255./sobmax, 255);
    cv::Mat sobelThresholded;
    // cv::threshold(sobelImage, sobelThresholded, 200, 255, cv::THRESH_BINARY);
    cv::imshow("sobelImage", sobelImage);
    cv::waitKey(0);
    
    return 0;
}