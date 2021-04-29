/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.27

    Description: Simple ros param demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_param book_param 1 
    ****************
*/

#include "ros/ros.h"
#include <cstdlib>

using namespace std;

int main(int argc,char** argv)
{
    //initial and name node
    ros::init(argc,argv,"node_param");
    if(argc!=2)
    {
        cout<<"Error command paramter! Please run command eg:\n"\
            <<"rosrun book_param book_param 1\n"\
            <<"help information:\n"\
            <<" 1 ------ set param mode(ros::param::set())\n"\
            <<" 2 ------ set param mode(ros::NodeHandle::setParam())\n"\
            <<" 3 ------ get param mode(ros::param::get())\n"\
            <<" 4 ------ get param mode(ros::NodeHandle::getParam())\n"\
            <<" 5 ------ get param mode(ros::NodeHandle::param())\n"\
            <<endl;
        return 1;
    }

    //create node handle
    ros::NodeHandle nh;
    //param variable
    int IntParam;
    string StrParam;
    bool isIntParam, isStrParam;
    //mode flag
    int flag = atoi(argv[1]);

    // set or get param with different ways
    switch(flag)
    {
        case 1:
            ROS_INFO("set param mode(ros::param::set()):");
            ros::param::set("IntParam",1);
            ros::param::set("StrParam","stringdemo");
            break;
        case 2:
            ROS_INFO("set param mode(ros::NodeHandle::setParam()):");
            nh.setParam("IntParam",1);
            nh.setParam("StrParam","stringdemo");
            break;
        case 3:
            ROS_INFO("get param mode(ros::param::get()):");
            isIntParam = ros::param::get("IntParam",IntParam);
            isStrParam = ros::param::get("StrParam",StrParam);

            if(isIntParam){
                ROS_INFO("The IntParam is:%d",IntParam);
            }else{
                ROS_INFO("Get IntParam fail!");
            }

            if(isIntParam){
                ROS_INFO("The StrParam is:%s",StrParam.c_str());
            }else{
                ROS_INFO("Get StrParam fail!");
            }
            break;
        case 4:
            ROS_INFO("get param mode(ros::NodeHandle::getParam()):");
            isIntParam = nh.getParam("IntParam",IntParam);
            isStrParam = nh.getParam("StrParam",StrParam);

            if(isIntParam){
                ROS_INFO("The IntParam is:%d",IntParam);
            }else{
                ROS_INFO("Get IntParam fail!");
            }

            if(isIntParam){
                ROS_INFO("The StrParam is:%s",StrParam.c_str());
            }else{
                ROS_INFO("Get StrParam fail!");
            }
            break;
        case 5:
            ROS_INFO("get param mode(ros::NodeHandle::param()):");
            //warning: this way will set default value when get no param!
            nh.param("IntParam",IntParam,11);
            // be careful when use ros::NodeHandle::param get string param!
            nh.param<std::string>("StrParam",StrParam,"stringdemo_default");
            ROS_INFO("\nThe IntParam is:%d\nThe StrParam is:%s",IntParam,StrParam.c_str());
            break;
        default:
            ROS_INFO("flag value is not in range: [1,5]");
    }
    return 0;
}