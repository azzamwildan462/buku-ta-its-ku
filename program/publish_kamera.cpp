//--Publish
static uint8_t cnt = 0;

if (cnt >= 6)
{
    Mat frame_bgr_display = frame_bgr_copy.clone();
    if (center_balls.size() > 0)
        circle(frame_bgr_display, Point(center_balls[0].x + CENTER_X, CENTER_Y - center_balls[0].y), 5, Scalar(255, 0, 0), -1);

    line(frame_bgr_display, Point(goalpost_data[0], 400), Point(goalpost_data[2], 400), Scalar(0, 255, 0), 2);

    Mat pcl_obs_frame = Mat::zeros(frame_bgr_copy.size(), CV_8UC3);
    for (uint16_t i = 0; i < pcl_obs.size(); i++)
    {
        circle(pcl_obs_frame, Point(pcl_obs[i].x + CENTER_X, CENTER_Y - pcl_obs[i].y), 2, Scalar(0, 0, 255), 2, LINE_8);
    }

    // make cross line in display with CENTER_X and CENTER_Y
    line(frame_bgr_display, Point(CENTER_X, 0), Point(CENTER_X, 720), Scalar(255, 0, 255), 1, LINE_8);
    line(frame_bgr_display, Point(0, CENTER_Y), Point(1280, CENTER_Y), Scalar(255, 0, 255), 1, LINE_8);

    addWeighted(frame_bgr_display, 1, pcl_obs_frame, 1, 0, frame_bgr_display);

    sensor_msgs::ImagePtr msg_pub_frame_display = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame_bgr_display).toImageMsg();
    pub_frame_display.publish(msg_pub_frame_display);
    sensor_msgs::ImagePtr msg_pub_frame_ball_debug = cv_bridge::CvImage(std_msgs::Header(), "mono8", threshold_ball).toImageMsg();
    pub_frame_ball_debug.publish(msg_pub_frame_ball_debug);
    sensor_msgs::ImagePtr msg_pub_frame_line_debug = cv_bridge::CvImage(std_msgs::Header(), "mono8", threshold_line).toImageMsg();
    pub_frame_line_debug.publish(msg_pub_frame_line_debug);
    sensor_msgs::ImagePtr msg_pub_frame_line_pcl_debug = cv_bridge::CvImage(std_msgs::Header(), "mono8", pcl_line_frame).toImageMsg();
    pub_frame_line_pcl_debug.publish(msg_pub_frame_line_pcl_debug);
    sensor_msgs::ImagePtr msg_pub_frame_obs_debug = cv_bridge::CvImage(std_msgs::Header(), "mono8", threshold_field).toImageMsg();
    pub_frame_obs_debug.publish(msg_pub_frame_obs_debug);
    cnt = 0;
}