/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.27

    Description: Simple ros custom define message publisher demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_message Book_MyMsgPub LiLei 180 160 
    ****************
*/

#include "ros/ros.h"
#include "book_message/Student.h"
#include <cstdlib>

using namespace std;
int main(int argc,char** argv)
{
    //initial and name node
    ros::init(argc,argv,"node_MyMsgPub");
    if(argc!=4)
    {
        cout<<"Error command parameter!\n"\
        <<"Please run command eg:\n"\
        <<"rosrun book_messge Book_MyMsgPub LiLei 180 160"<<endl;
        return 1;
    }

    //create node handle
    ros::NodeHandle nh;

    //create message publisher
    ros::Publisher MyMsgPub =  nh.advertise<book_message::Student>("MyMsg",100);
    book_message::Student  sdtMsg;
    sdtMsg.name = argv[1];
    //convert string in argv to float and pass value to height, weight
    sdtMsg.height = atof(argv[2]);
    sdtMsg.weight = atof(argv[3]);

    ros::Rate rate(10);
    while(ros::ok())
    {
        MyMsgPub.publish(sdtMsg);
        rate.sleep();
    }

    return 0;
}