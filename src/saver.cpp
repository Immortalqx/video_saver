#include "../include/video_saver/saver.h"

Saver::Saver(int index, const std::string &filepath)
{
    videoCapture.open(index);

    int i = 0;
    while (!videoCapture.isOpened())
    {
        ROS_ERROR("Can't open camera by index: %d", index);
        ROS_ERROR("Waiting......");
        videoCapture.open(index);
        sleep(2);
        i++;
        if (i > 3)
            abort();
    }

    videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    videoCapture.set(cv::CAP_PROP_FPS, 30);
    size = cv::Size(640, 480);
    rate = 30;

    this->filepath = filepath;

    sub = n.subscribe("/robo_air/camera_control", 10, check);
}

void Saver::saveVideo()
{
    cv::Mat frame;
    while (ros::ok() && videoCapture.isOpened())
    {
        if (start)
        {
            std::string filename = filepath + "/" + currentDateToString() + ".mp4";
            writer = cv::VideoWriter(filename, myFourCC, rate, size, true);

            while (start)
            {
                if (videoCapture.read(frame))
                {

                    ROS_INFO("Recording......");

                    writer << frame;
                }
                else
                    break;

                ros::spinOnce();
            }
            cv::destroyAllWindows();
            writer.release();
            start = false;
        }
        ros::spinOnce();
    }
}

std::string Saver::currentDateToString()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    std::string str(buffer);

    return str;
}

void Saver::check(const std_msgs::Bool::ConstPtr &msg)
{
    bool record = msg->data;
    if (record)
    {
        ROS_INFO_STREAM("Video starts saving!");
        start = true;
    }
    else
    {
        ROS_INFO_STREAM("End of video save!");
        start = false;
    }

}

