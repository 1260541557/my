/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.27

    Description: Simple ros custom define message subscriber demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_message Book_MyMsgSub
    ****************
*/

#include "ros/ros.h"
#include "book_message/Student.h"

// custom defined message callback function
void MyMsgCallback(const book_message::Student& sdtInfo)
{
    ROS_INFO("The student information is:\n name:%s---height:%f---weight:%f",
                sdtInfo.name.c_str(),
                sdtInfo.height,
                sdtInfo.weight);
}

int main(int argc, char** argv)
{
    //initial and name node
    ros::init(argc,argv,"node_MyMsgSub");
    //create node handle
    ros::NodeHandle nh;
    //create subscriber
    ros::Subscriber MyMsgSub = nh.subscribe("MyMsg",1000,&MyMsgCallback);
    ros::spin();
    return 0;
}