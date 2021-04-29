/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.27

    Description: Simple ros service client demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_service ClientForBeginner 123456
    ****************
*/

#include "ros/ros.h"
#include "book_service/PassWord.h"
#include <cstdlib>

using namespace std;
int main(int argc, char** argv)
{
    //initial and name node
    ros::init(argc,argv,"node_client");
    if(argc<2)
    {
        cout<<"Error paramster,please run eg: rosrun book_service ClientForBeginner 123456"<<endl;
        return 1;
    }
    //create nodehandle
    ros::NodeHandle nh;
    //create client
    ros::ServiceClient client = nh.serviceClient<book_service::PassWord>("pswserver",100);
    book_service::PassWord srv;
    //convert argv from char to int and pass value to service response
    srv.request.password = atoi(argv[1]);
    if(client.call(srv))
    {
        ROS_INFO("client connect success!");
        if(srv.response.result)
        {
            ROS_INFO("Welcom,correct password!");
        }else{
            ROS_INFO("Sorry,password error!");
        }
    }else{
        ROS_INFO("client connet fail!");
    }
    return 0;
}
