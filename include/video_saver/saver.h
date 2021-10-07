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
    //single or double
    int topic_num = 1;

    //image size from topic 1
    cv::Size size_1;
    //image size from topic 2
    cv::Size size_2;

    //image fps from topic 1
    int rate_1;
    //image fps from topic 2
    int rate_2;

    //video writer, save the video from topic 1
    cv::VideoWriter writer_1;
    //video writer, save the video from topic 2
    cv::VideoWriter writer_2;

    //save path
    std::string filepath;
    //mp4 flag
    int myFourCC = cv::VideoWriter::fourcc('m', 'p', '4', 'v');

    //some subscriber
    ros::NodeHandle n;
    ros::Subscriber sub;
    image_transport::Subscriber sub_1;
    image_transport::Subscriber sub_2;

    //check when should start record video
    static void check(const std_msgs::Bool::ConstPtr &msg);

    //get image from topic 1
    static void imageCallback_1(const sensor_msgs::ImageConstPtr &msg);

    //get image from topic 2
    static void imageCallback_2(const sensor_msgs::ImageConstPtr &msg);

    //get current data
    static std::string currentDateToString();

    //save video from single topic
    void single_run();

    //save video from single topic
    void double_run();

public:
    static bool start;
    static std::stack<cv::Mat> frames_1;
    static std::stack<cv::Mat> frames_2;

    Saver(int topic_num,
          const std::string &control_topic,
          const std::string &topic_1, const std::string &topic_2,
          const std::string &filepath,
          int width_1 = 640, int height_1 = 480,
          int width_2 = 848, int height_2 = 800,
          int rate_1 = 30, int rate_2 = 30);

    Saver(int topic_num,
          const std::string &control_topic,
          const std::string &topic_1,
          const std::string &filepath,
          int width_1 = 640, int height_1 = 480, int rate_1 = 30);

    static Saver *getSaver(int argc, char **argv);

    void run();
};