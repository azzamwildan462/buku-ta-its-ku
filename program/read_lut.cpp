typedef struct
{
    float x;
    float y;
    float theta;
} pose2d_t;

typedef struct
{
    float x;
    float y;
} point2d_t;

typedef struct
{
    float r;
    float theta;
} polar2d_t;

void frameToWorld(point2d_t frame_pixel, point2d_t *world_point, polar2d_t *world_polar, pose2d_t *robot_pose, int16_t *LUTfr2lap)
{
    float dist_px = pythagoras(frame_pixel, {0, 0});
    float angle_px = atan2(frame_pixel.y, frame_pixel.x) RAD2DEG;

    if (angle_px >= 360)
        angle_px -= 360;
    else if (angle_px < 0)
        angle_px += 360;

    /* This is coordinate that just based on robot */
    world_polar->r = LUTfr2lap[(int)(angle_px) * 3200 + (int)(dist_px * 10)];
    world_polar->theta = angle_px + robot_pose->theta - 90;

    /* Turning ball coordinate based on robot into based on field */
    world_point->x = robot_pose->x + world_polar->r * cosf(world_polar->theta DEG2RAD);
    world_point->y = robot_pose->y + world_polar->r * sinf(world_polar->theta DEG2RAD);
}