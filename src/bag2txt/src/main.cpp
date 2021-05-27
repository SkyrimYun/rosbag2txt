#include <ros/ros.h>
#include <dvs_msgs/EventArray.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/PoseStamped.h>
#include <fstream>

std::ofstream ofs_event;
std::ofstream ofs_imu_angular;
std::ofstream ofs_pose_gt;

void eventsCallback(const dvs_msgs::EventArray::ConstPtr &msg)
{
    for (dvs_msgs::Event ev : msg->events)
    {
        ofs_event << ev.ts.toSec() << " " << ev.x << " " << ev.y << " " << int(ev.polarity) << std::endl;
    }
};

void imuCallback(const sensor_msgs::Imu::ConstPtr &msg)
{
    geometry_msgs::Vector3 avel = msg->angular_velocity;
    ofs_imu_angular << msg->header.stamp.toSec() << " " << avel.x << " " << avel.y << " " << avel.z << std::endl;
};

void poseCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    geometry_msgs::Quaternion q = msg->pose.orientation;
    ofs_pose_gt << msg->header.stamp.toSec() << " " << q.w << " " << q.x << " " << q.y << " " << q.z << std::endl;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "bag2txt");
    ros::NodeHandle nh("~");
    std::string output_path;
    nh.param<std::string>("output_path", output_path, "");

    ros::Subscriber event_sub = nh.subscribe("/events", 0, eventsCallback);
    ros::Subscriber imu_sub = nh.subscribe("/imu", 0, imuCallback);
    ros::Subscriber pose_sub = nh.subscribe("/pose", 0, poseCallback);

    ofs_event.open(output_path + "events.txt");
    ofs_imu_angular.open(output_path + "imu_angular.txt");
    ofs_pose_gt.open(output_path + "pose_gt.txt");

    ros::spin();
}