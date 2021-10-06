#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Bool.h"

class Saver
{
private:
    cv::VideoCapture videoCapture;
    cv::Size size;
    double rate;
    cv::VideoWriter writer;
    std::string filepath;
    int myFourCC = cv::VideoWriter::fourcc('m', 'p', '4', 'v');//mp4

    ros::NodeHandle n;
    ros::Subscriber sub;

    static void check(const std_msgs::Bool::ConstPtr &msg);

    static std::string currentDateToString();

public:
    static bool start;

    Saver(int index, const std::string &filepath);

    void saveVideo();

};