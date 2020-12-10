#include "../include/video_saver/saver.h"

Saver::Saver(int index, const std::string &filepath)
{
    videoCapture.open(index);
    size = cv::Size(videoCapture.get(cv::CAP_PROP_FRAME_WIDTH), videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
    rate = videoCapture.get(cv::CAP_PROP_FPS);

    this->filepath = filepath;
}

void Saver::saveVideo()
{
    cv::Mat frame;
    while (ros::ok() && videoCapture.isOpened())
    {
        bool start = check();
        if (start)
        {
            std::string filename = filepath + currentDateToString() + ".mp4";
            writer = cv::VideoWriter(filename, myFourCC, rate, size, true);

            while (check())
            {
                if (videoCapture.read(frame))
                {
                    cv::imshow("frame", frame);//TODO 功能实现并且检查完毕后要注释掉这句话
                    writer << frame;
                    if (cv::waitKey(20) >= 0) break;
                }
                else
                    break;

            }
            writer.release();
            start = false;
        }
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

bool Saver::check()
{
    //TODO
    // 增加一个判断函数，用于动态的开启和关闭 视频保存 功能
    // 接受ROS节点的消息，通过true false判断开启和关闭
    // 内嵌于saveVideo函数中
    // 后续可能还得把saveVideo改成回调函数并且加入动态的视频名称

    return false;
}

