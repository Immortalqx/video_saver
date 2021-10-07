# video_saver
这是一个从节点接受图像话题，并且保存这个图像话题的工具包。

## 使用方式

### 启动节点

**通过rosrun启动：**

```bash
# 指定所有参数
rosrun video_saver saver /robo_air/camera_control /d435i/color/image_raw /t265/fisheye2/image_raw ~ 1920 1080 848 800 30 30
# 指定部分参数
rosrun video_saver saver /robo_air/camera_control /d435i/color/image_raw /t265/fisheye2/image_raw ~
```

**通过roslaunch启动：**

```bash
roslaunch video_saver vstart.launch
```

### 发布控制话题

**开始录制**

```bash
rostopic pub /robo_air/camera_control std_msgs/Bool true
```

**结束录制**

```bash
rostopic pub /robo_air/camera_control std_msgs/Bool false
```

