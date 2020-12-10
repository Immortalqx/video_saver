#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "ros/ros.h"

class Saver
{
private:
    cv::VideoCapture videoCapture;
    cv::Size size;
    double rate;
    cv::VideoWriter writer;
    std::string filepath;
    int myFourCC = cv::VideoWriter::fourcc('m', 'p', '4', 'v');//mp4

    int count = -999;

    static std::string currentDateToString();

    bool check();

public:
    Saver(int index, const std::string &filepath);

    void saveVideo();

};