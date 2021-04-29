/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.3.9

    Description: Simple ros tf transform listener demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_tfpub book_tflis
    ****************
*/

#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "geometry_msgs/PointStamped.h"

using namespace std;

int main(int argc,char** argv)
{
    //initial and name node
    ros::init(argc,argv,"tf_transformlis");
    //create nodehandle
    ros::NodeHandle nh;
    //create tf listener
    tf::TransformListener tflis;
    //create point in laser_link
    geometry_msgs::PointStamped plaser;
    plaser.header.frame_id="laser_link";
    plaser.point.x=1,plaser.point.y=0,plaser.point.z=0;
    //create point in base_link
    geometry_msgs::PointStamped pbase;
    //create frequency
    ros::Rate r(10);
    while(nh.ok())
    {
        cout<<"start listening"<<endl;
        tflis.waitForTransform("base_link","laser_link",ros::Time(0),ros::Duration(3));
        tflis.transformPoint("base_link",plaser,pbase);
        cout<<"pbase is:"<<"("
            <<pbase.point.x<<","
            <<pbase.point.y<<","
            <<pbase.point.z<<")"<<endl;
        r.sleep();

    }
    return 0;
}