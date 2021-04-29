/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.3.12

    Description: Simple ros tf  demo with frame movefor beginnner learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_myslam slam_tfpub
    ****************
*/

#include "slam_tfpub.h"

//TfMove initialize
TfMove::TfMove(ros::NodeHandle& nh,ros::Rate& r):nh_(nh),rate(r),
                                                 x(0),y(0),z(0),
                                                 roll(0),
                                                 pit(0),
                                                 yaw(0)
{
    init_sub();
}

//velocity sub callback and send tansform between odom and base_link
void TfMove::VelCallback(const geometry_msgs::TwistPtr& vel)
{
    // linear change
    x = x+vel->linear.x;
    y = y+vel->linear.y;
    z = z+vel->linear.z;
    //angular change
    roll = roll+vel->angular.x/pi*180;
    pit = pit+vel->angular.y/pi*180;
    yaw = yaw+vel->angular.z/pi*180;
    // transform between odom and base_link
    tf::Transform trans;
    trans.setOrigin(tf::Vector3(x,y,z));
    tf::Quaternion q;
    q.setRPY(roll,pit,yaw);
    trans.setRotation(q);
    //send transform  map --- parent frame , base_link --- child frame
    tfbrd_.sendTransform(tf::StampedTransform(trans,ros::Time::now(),"map","base_link"));
    rate.sleep();

}

//initial sub
void TfMove::init_sub()
{
    sub_ = nh_.subscribe("cmd_vel",1,&TfMove::VelCallback,this);
    ros::spin();
}

int main(int argc,char** argv)
{
    //initialize and name mode
    ros::init(argc,argv,"myslam_tfpub");
    //create node handle
    ros::NodeHandle nh;
    // sleep rate
    ros::Rate rate(10);
    //TfMove object instantiate
    TfMove tfmove(nh,rate);
    return 0;
}