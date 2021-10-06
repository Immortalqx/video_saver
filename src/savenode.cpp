#include "../include/video_saver/saver.h"

bool Saver::start = false;
std::stack<cv::Mat> Saver::frames_1;
std::stack<cv::Mat> Saver::frames_2;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "VideoSaver");

    ros::NodeHandle nh;

    auto *saver = new Saver(argv[1], argv[2], argv[3]);

    saver->run();

    return 0;
}
