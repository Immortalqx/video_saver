#include "../include/video_saver/saver.h"

Saver::Saver(const std::string &filepath, const std::string &topic_1, const std::string &topic_2)
{
    this->filepath = filepath;
    image_transport::ImageTransport it(n);
    sub_1 = it.subscribe(topic_1, 10, imageCallback_1);
    sub_2 = it.subscribe(topic_2, 10, imageCallback_2);
    sub = n.subscribe("/robo_air/camera_control", 10, check);
}

void Saver::run()
{
    int rate = 30;
    cv::Size size_1 = cv::Size(640, 480);
    cv::Size size_2 = cv::Size(848, 800);
    while (ros::ok())
    {
        if (start)
        {
            std::string filename_1 = filepath + "/" + currentDateToString() + "topic1" + ".mp4";
            writer_1 = cv::VideoWriter(filename_1, myFourCC, rate, size_1, true);

            std::string filename_2 = filepath + "/" + currentDateToString() + "topic2" + ".mp4";
            writer_2 = cv::VideoWriter(filename_2, myFourCC, rate, size_2, true);

            while (start)
            {
                if (!frames_1.empty())
                {
                    ROS_INFO("Recording Topic1......");
                    writer_1 << frames_1.top();
                    frames_1.pop();
                }
                if (!frames_2.empty())
                {
                    ROS_INFO("Recording Topic2......");
                    writer_2 << frames_2.top();
                    frames_2.pop();
                }
                ros::spinOnce();
            }
            cv::destroyAllWindows();
            writer_1.release();
            writer_2.release();
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

void Saver::imageCallback_1(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
        if (start)
        {
            ROS_INFO("topic 1 received!");
            frames_1.push(cv_bridge::toCvShare(msg, "bgr8")->image);
        }
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void Saver::imageCallback_2(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
        if (start)
        {
            ROS_INFO("topic 2 received!");
            frames_2.push(cv_bridge::toCvShare(msg, "bgr8")->image);
        }
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}