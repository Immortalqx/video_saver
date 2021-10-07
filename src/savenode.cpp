#include "../include/video_saver/saver.h"

bool Saver::start = false;
std::stack<cv::Mat> Saver::frames_1;
std::stack<cv::Mat> Saver::frames_2;

std::string param_info[10] = {
        "control_topic", "image_topic_1", "image_topic_2", "save_path",
        "width_1", "height_1", "width_2", "height_2", "rate_1", "rate_2"
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "VideoSaver");

    ros::NodeHandle nh;

    ROS_INFO("param number:%s", std::to_string(argc).c_str());

    for (int i = 1; i < argc; i++)
        ROS_INFO("%s:%s", param_info[i - 1].c_str(), argv[i]);

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
