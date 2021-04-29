/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.28

    Description: Simple ros class method demo by combining  message ,service and param for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_class book_class
              rostopic pub -r 10 /Topic1 std_msgs/Float64 1 (test message communication)
              rosservice call pwdcheck 123456 (test service communication)
    ****************
*/
#include "book_class.h"

RosBasics::RosBasics():nh_("~")
{
    initPublish();
    initServer();
    initSubscribe();
    paramTest();
}

RosBasics::RosBasics(ros::NodeHandle& nh):nh_(nh)
{
    initPublish();
    initServer();
    initSubscribe();
    paramTest();
}

RosBasics::~RosBasics()
{
}

void RosBasics::initPublish()
{
    ROS_INFO("publish initializing!");
    pub_ = nh_.advertise<std_msgs::Float64>("Topic2",100);
}

void RosBasics::initSubscribe()
{
    ROS_INFO("subscribe initializing!");
    sub_ = nh_.subscribe("Topic1",1,&RosBasics::msgCallback,this);
}

void RosBasics::initServer()
{
    ROS_INFO("server initializing!");
    serv_ = nh_.advertiseService("pwdcheck",&RosBasics::serverCallback,this);
}


bool RosBasics::serverCallback(book_class::PassWord::Request& req,
                               book_class::PassWord::Response& res)
{
    res.result = (req.password == 123456) ? true:false;
    if(res.result)
    {
        ROS_INFO("Welcom, password correct!");
    }else{
        ROS_INFO("Sorry, password error!");
    }
    return true;
}                               


//obtain message from Topic1 and add value then publish to Topic2
void RosBasics::msgCallback(const std_msgs::Float64& stdmsg)
{
    std_msgs::Float64 msgpub;
    msgpub.data = stdmsg.data + 2;
    ROS_INFO("Receive date from Topic1 content is:%f",stdmsg.data);
    ROS_INFO("Publish date with Topic2 content is:%f",msgpub.data);
    pub_.publish(msgpub);
}

//test ros param
void RosBasics::paramTest()
{
    int Age;
    bool checkAge;
    checkAge = nh_.getParam("Age",Age);
    if(checkAge)
    {
        ROS_INFO("Welcome,Get Param Success!");
        if(Age>=18)
        {
            ROS_INFO("You are adult!");
        }else{
            ROS_INFO("You are children!");
        }
    }else{
        ROS_INFO("Sorry,Get Param Fail!");
    }
}

int main(int argc,char** argv)
{
    //initial and name node
    ros::init(argc,argv,"node_classdemo");
    //create node handle
    ros::NodeHandle nh;
    //instantiate class object
    RosBasics classdemo(nh);
    ros::spin();
    return 0;
}