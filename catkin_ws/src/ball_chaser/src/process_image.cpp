#include "process_image.h"

ProcessImage::ProcessImage()
{
    ProcessImageMain();
}

void ProcessImage::ProcessImageMain()
{
    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);

    // Handle ROS communication events
    ros::spin();
}

// This function calls the command_robot service to drive the robot in the specified direction
void ProcessImage::drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void ProcessImage::process_image_callback(const sensor_msgs::Image img)
{
    pixel_falls = -1;
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    for(unsigned int  i = 0; i < img.height * img.step; i+=3)
    {
        if(img.data[i] == white_pixel and img.data[i+1] == white_pixel and img.data[i+2] == white_pixel)
        {
            pixel_falls = i;
            break;
        }
    }

    // Then, identify if this pixel falls in the left, mid, or right side of the image
    if(pixel_falls % img.step < img.step / 3) // LEFT
         drive_robot(0.3, 0.3);
    else if (pixel_falls % img.step > 2*img.step / 3) // RIGHT
        drive_robot(0.3, -0.3);
    else
        drive_robot(0.3, 0.0); // CENTER

    // Request a stop when there's no white ball seen by the camera
    if (pixel_falls < 0) {
        drive_robot(0.0, 0.0);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image
    ros::init(argc, argv, "process_image");

    ProcessImage processImage;

    return 0;
}
