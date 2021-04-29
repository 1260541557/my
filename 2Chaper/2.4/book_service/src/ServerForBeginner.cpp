/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.27

    Description: Simple ros service server demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_service ServerForBeginner
    ****************
*/

#include "ros/ros.h"
#include "book_service/PassWord.h"

// server callback function
bool serverCallback(book_service::PassWord::Request& req,
                    book_service::PassWord::Response& res)
{
    //if password = 123456, result is true, or result is false
    res.result = (req.password == 123456) ? true:false;
    return true;
}

int main(int argc,char** argv)
{
    //initial and name node
    ros::init(argc,argv,"server_node");
    //create nodehandle
    ros::NodeHandle nh;
    //create service server
    ros::ServiceServer serv = nh.advertiseService("pswserver",&serverCallback);
    ros::spin();
    return 0;
}