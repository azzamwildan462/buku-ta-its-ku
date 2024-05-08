cap.open(camera_path);

if (!cap.isOpened())
{
    ROS_ERROR("CAPTURE ERROR : Camera cannot be opened");
    ros::shutdown();
}

cap.set(CAP_V4L2, 1);
cap.set(CAP_PROP_FRAME_WIDTH, 1280);
cap.set(CAP_PROP_FRAME_HEIGHT, 720);
cap.set(CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
cap.set(CAP_PROP_FPS, 60);

setCameraConfig(camera_path, "brightness", camera_params[0]);
setCameraConfig(camera_path, "contrast", camera_params[1]);
setCameraConfig(camera_path, "saturation", camera_params[2]);
setCameraConfig(camera_path, "power_line_frequency", 1);
setCameraConfig(camera_path, "white_balance_temperature_auto", 0);
setCameraConfig(camera_path, "exposure_auto", 3);
setCameraConfig(camera_path, "exposure_auto_priority", 0);
setCameraConfig(camera_path, "backlight_compensation", 0);
setCameraConfig(camera_path, "zoom_absolute", 100);