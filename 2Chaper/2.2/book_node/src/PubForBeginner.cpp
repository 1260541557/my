/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.26

    Description: Simple ros publish demo for beginning learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_node PubForBeginner
    ****************
*/
#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc,char** argv)
{
    //initialize and name node
    ros::init(argc,argv,"publisher");
    //create nodehandle
    ros::NodeHandle nh;
    //create publisher
    ros::Publisher simplepub = nh.advertise<std_msgs::String>("string_topic",100);
    // publish frequency
    ros::Rate rate(10);
    //message for publish
    std_msgs::String pubinfo;
    pubinfo.data="Hello, I'm Publisher!";
    while(ros::ok())
    {   
        simplepub.publish(pubinfo);
        rate.sleep();
    }
    return 0;
}