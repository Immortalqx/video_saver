#include "../include/video_saver/saver.h"

bool Saver::start = false;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "VideoSaver");

    Saver saver(std::stoi(argv[1]), argv[2]);

    saver.saveVideo();

    return 0;
}
