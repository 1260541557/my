#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

//ros::Time current_time;
void odomCallback(const nav_msgs::Odometry::ConstPtr& vrepodom){
    //current_time = ros::Time::now();
    tf::TransformBroadcaster odom_broad;
    //tf::Transform transform;
    geometry_msgs::TransformStamped odom_trans;

    double x = vrepodom->pose.pose.position.x;
    double y = vrepodom->pose.pose.position.y;
    geometry_msgs::Quaternion odom_quat = vrepodom->pose.pose.orientation;


    odom_trans.header.stamp = ros::Time::now();
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";
    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0;
    odom_trans.transform.rotation = odom_quat;
    odom_broad.sendTransform(odom_trans);
    //ros::spinOnce();
    //r.sleep();
}

int main(int argc, char *argv[])
{
    /* code for main function */
    ros::init(argc, argv, "vrp_odomtf_pub");
    ros::NodeHandle nh;
    ros::Rate r(20);
    ros::Subscriber sub = nh.subscribe("/odom", 10, odomCallback);
    ros::spin();
    return 0;
}
