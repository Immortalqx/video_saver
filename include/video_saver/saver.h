#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <stack>

class Saver
{
private:
    cv::VideoWriter writer_1;
    cv::VideoWriter writer_2;
    std::string filepath;
    int myFourCC = cv::VideoWriter::fourcc('m', 'p', '4', 'v');//mp4

    ros::NodeHandle n;
    ros::Subscriber sub;
    image_transport::Subscriber sub_1;
    image_transport::Subscriber sub_2;

    static void check(const std_msgs::Bool::ConstPtr &msg);

    static void imageCallback_1(const sensor_msgs::ImageConstPtr &msg);

    static void imageCallback_2(const sensor_msgs::ImageConstPtr &msg);

    static std::string currentDateToString();

public:
    static bool start;
    static std::stack<cv::Mat> frames_1;
    static std::stack<cv::Mat> frames_2;

    Saver(const std::string &filepath, const std::string &topic_1, const std::string &topic_2);

    void run();

};