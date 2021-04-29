/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.26

    Description: simple ros subscriber demo for beginning learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_node SubForBeginner
    ****************
*/ 

#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace std;

void subCallback(const std_msgs::String& submsg)
{
    string subinfo;
    subinfo = submsg.data;
    ROS_INFO("The message subscribed is: %s",subinfo.c_str());
}
int main(int argc,char** argv)
{
    //initial and name node
    ros::init(argc,argv,"subscriber");
    //create nodehandle
    ros::NodeHandle nh;
    //create subscriber
    ros::Subscriber sub = nh.subscribe("string_topic",1000,&subCallback);
    ros::spin();
    return 0;
}