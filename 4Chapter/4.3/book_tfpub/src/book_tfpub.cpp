/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.3.9

    Description: Simple ros tf transform publish demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_tfpub book_tfpub 
    ****************
*/

#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "geometry_msgs/Point.h"
#include "tf/tf.h"

int main(int argc,char** argv)
{
    //initialize node and name
    ros::init(argc,argv,"tf_transformpub");
    //create node handle
    ros::NodeHandle nh;
    //create transform broadcast
    static tf::TransformBroadcaster transfpub;
    //create transform
    tf::Transform base2laser;
    //set translation
    base2laser.setOrigin(tf::Vector3(1,0,0));
    //create transform quaternion 0 degree
    tf::Quaternion q;
    q.setRPY(0,0,0);
    //set transform
    base2laser.setRotation(q);
    ros::Rate rate(10);

    while(nh.ok())
    {
        //loop pub transform
        transfpub.sendTransform(tf::StampedTransform(base2laser,ros::Time::now(),"base_link","laser_link"));
        rate.sleep();
    }

    return 0;

}