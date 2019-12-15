#ifndef LINE_FINDER_H
#define LINE_FINDER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#define PI 3.1415926
class LineFinder
{
public:
    LineFinder() : deltaRho(1), deltaTheta(PI / 180), minVote(10),
                   minLength(0.), maxGap(0.) {}
    void setAccResolution(double dRho, double dTheta)
    {
        deltaRho = dRho;
        deltaTheta = dTheta;
    }
    void setMinVote(int minv)
    {
        minVote = minv;
    }
    void setLineLengthAndGap(double mlength, double mgap)
    {
        minLength = mlength;
        maxGap = mgap;
    }
    std::vector<cv::Vec4i> findLines(cv::Mat &binary)
    {
        lines.clear();
        cv::HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);
        return lines;
    }
    void drawDetectedLines(cv::Mat &image, cv::Scalar color = cv::Scalar(255.255, 255));

private:
    cv::Mat img;
    // houghLinesP return Vec4i, line segment not line
    std::vector<cv::Vec4i> lines;
    double deltaRho;
    double deltaTheta;
    int minVote;
    double minLength;
    double maxGap;
};
void LineFinder::drawDetectedLines(cv::Mat &image, cv::Scalar color)
{
    std::vector<cv::Vec4i>::const_iterator it2 =
        lines.begin();
    while (it2 != lines.end())
    {
        cv::Point pt1((*it2)[0], (*it2)[1]);
        cv::Point pt2((*it2)[2], (*it2)[3]);

        cv::line(image, pt1, pt2, color);

        ++it2;
    }
}
#endif