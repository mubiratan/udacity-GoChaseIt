#ifndef DRIVE_BOT_CORE_H
#define DRIVE_BOT_CORE_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

class Drive_Bot {

    private:
        // ROS::Publisher motor commands;
        ros::Publisher motor_command_publisher;
        ros::NodeHandle n;

    public:
        Drive_Bot() {
            drive_bot_main();
        }

        bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
                                  ball_chaser::DriveToTarget::Response& res);
        void drive_bot_main();
};


#endif // DRIVE_BOT_H
