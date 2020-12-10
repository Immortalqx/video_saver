#include "../include/video_saver/saver.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "video_saver");
    ros::NodeHandle n;

    Saver saver(2, argv[1]);

    saver.saveVideo();

    return 0;
}
