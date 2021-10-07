#include "../include/video_saver/saver.h"

bool Saver::start = false;
std::stack<cv::Mat> Saver::frames_1;
std::stack<cv::Mat> Saver::frames_2;


int main(int argc, char **argv)
{
    ros::init(argc, argv, "VideoSaver");

    ros::NodeHandle nh;

    Saver *saver = Saver::getSaver(argc, argv);

    if (saver != nullptr)
    {
        ROS_INFO("VideoSaver Node Is Up!");
        saver->run();
    }
    else
        ROS_ERROR("ERROR: Check your param!");

    return 0;
}
