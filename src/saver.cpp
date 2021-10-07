#include "../include/video_saver/saver.h"

Saver::Saver(const std::string &control_topic,
             const std::string &topic_1, const std::string &topic_2,
             const std::string &filepath,
             int width_1, int height_1,
             int width_2, int height_2,
             int rate_1, int rate_2)
{
    this->size_1 = cv::Size(width_1, height_1);
    this->size_2 = cv::Size(width_2, height_2);
    this->rate_1 = rate_1;
    this->rate_2 = rate_2;

    this->filepath = filepath;

    image_transport::ImageTransport it(n);

    this->sub_1 = it.subscribe(topic_1, 10, imageCallback_1);
    this->sub_2 = it.subscribe(topic_2, 10, imageCallback_2);
    this->sub = n.subscribe(control_topic, 10, check);
}

void Saver::run()
{
    while (ros::ok())
    {
        if (Saver::start)
        {
            std::string filename_1 = this->filepath + "/" + currentDateToString() + " topic1" + ".mp4";
            this->writer_1 = cv::VideoWriter(filename_1, myFourCC, this->rate_1, this->size_1, true);

            std::string filename_2 = filepath + "/" + currentDateToString() + " topic2" + ".mp4";
            this->writer_2 = cv::VideoWriter(filename_2, myFourCC, this->rate_2, this->size_2, true);

            while (Saver::start)
            {
                if (!Saver::frames_1.empty())
                {
                    ROS_INFO("Recording Topic1......");
                    this->writer_1 << Saver::frames_1.top();
                    Saver::frames_1.pop();
                }
                if (!Saver::frames_2.empty())
                {
                    ROS_INFO("Recording Topic2......");
                    this->writer_2 << Saver::frames_2.top();
                    Saver::frames_2.pop();
                }
                ros::spinOnce();
            }
            this->writer_1.release();
            this->writer_2.release();
            Saver::start = false;
        }
        ros::spinOnce();
    }
}

std::string Saver::currentDateToString()
{
    time_t raw_time;
    struct tm *time_info;
    char buffer[80];

    time(&raw_time);
    time_info = localtime(&raw_time);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
    std::string str(buffer);

    return str;
}

void Saver::check(const std_msgs::Bool::ConstPtr &msg)
{
    bool record = msg->data;
    if (record)
    {
        ROS_INFO_STREAM("==========Video starts saving!==========");
        Saver::start = true;
    }
    else
    {
        ROS_INFO_STREAM("==========End of video save!==========");
        Saver::start = false;
    }

}

void Saver::imageCallback_1(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
        if (Saver::start)
        {
            ROS_INFO("topic 1 received!");
            Saver::frames_1.push(cv_bridge::toCvShare(msg, "bgr8")->image);
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
        if (Saver::start)
        {
            ROS_INFO("topic 2 received!");
            Saver::frames_2.push(cv_bridge::toCvShare(msg, "bgr8")->image);
        }
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

Saver *Saver::getSaver(int argc, char **argv)
{
    if (argc < 5)
    {
        ROS_INFO("usage: "
                 "rosrun video_saver saver "
                 "[control_topic] [image_topic_1] [image_topic_2] [save_path]"
                 "[width_1] [height_1] [width_2] [height_2] [rate_1] [rate_2]");
        return nullptr;
    }

    Saver *saver = nullptr;

    if (argc == 5)
        saver = new Saver(argv[1], argv[2], argv[3], argv[4]);
    if (argc == 9)
        saver = new Saver(argv[1], argv[2], argv[3],
                          argv[4],
                          std::stoi(argv[5]), std::stoi(argv[6]),
                          std::stoi(argv[7]), std::stoi(argv[8]));
    if (argc == 11)
        saver = new Saver(argv[1], argv[2], argv[3],
                          argv[4],
                          std::stoi(argv[5]), std::stoi(argv[6]),
                          std::stoi(argv[7]), std::stoi(argv[8]),
                          std::stoi(argv[9]), std::stoi(argv[10]));
    return saver;
}
