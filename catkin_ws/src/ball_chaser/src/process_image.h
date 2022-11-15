#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H

#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ProcessImage {
    private:
        ros::ServiceClient client;
        ros::NodeHandle n;
        const unsigned char white_pixel = 255;
        int pixel_falls = -1;

        void drive_robot(float lin_x, float ang_z);
        void ProcessImageMain();

    public:
        ProcessImage();
        void process_image_callback(const sensor_msgs::Image img);
};

#endif // PROCESS_IMAGE_H
