#include "../include/video_saver/saver.h"

bool Saver::start = false;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "VideoSaver");

    Saver saver(2, argv[1]);

    saver.saveVideo();

    return 0;
}
