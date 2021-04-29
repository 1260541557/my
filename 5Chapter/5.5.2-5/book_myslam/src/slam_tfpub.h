#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_broadcaster.h"
#include "tf/tf.h"
#define pi 3.1415926

class TfMove
{
    public:
        TfMove(ros::NodeHandle& nh,ros::Rate& r);
        void VelCallback(const geometry_msgs::TwistPtr& vel);
        void init_sub();
    private:
        ros::NodeHandle nh_;
        ros::Subscriber sub_;
        tf::TransformBroadcaster tfbrd_;
        ros::Rate rate;
        double x,y,z,roll,pit,yaw;
};