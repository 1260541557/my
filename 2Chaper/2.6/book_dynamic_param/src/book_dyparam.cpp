/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.2.28

    Description: Simple ros dynamic parameter demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_dynamic_param book_dyparam
              
              rosrun rqt_reconfigure rqt_reconfigure
    ****************
*/

#include "ros/ros.h"
#include "dynamic_reconfigure/server.h"
#include "book_dynamic_param/DynamicParamConfig.h"

//define call back function
void paramCallback(book_dynamic_param::DynamicParamConfig& config,uint32_t level)
{
    ROS_INFO("Request: %d %f %s %s %s",
                config.IntDyParam,config.DouDyParam,
                config.StrDyParam.c_str(),
                config.BoolDyParam?"True":"False",
                config.StudentInfo.c_str());
}

int main(int argc, char** argv)
{
    //initial and name node
    ros::init(argc,argv,"node_DynamicParam");
    //create node handle
    dynamic_reconfigure::Server<book_dynamic_param::DynamicParamConfig> server;
    dynamic_reconfigure::Server<book_dynamic_param::DynamicParamConfig>::CallbackType f;

    f = boost::bind(&paramCallback,_1,_2);
    server.setCallback(f);
    ros::spin();
    return 0;
}