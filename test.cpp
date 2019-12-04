#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>

int main(){
    cv::Mat img = cv::imread("/Users/xyx/Documents/workspace/clearning/opencv_pro/images/000007.jpg");
    cv::imshow("img", img);
    cv::waitKey(0);
    return 0;
}