/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.3.12

    Description: simple ros laser data create by customer for beginning learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_myslam slam_laser
    ****************
*/ 

/*
    Laser data in ros
    rosmsg show sensor_msgs/LaserScan(check laser data msg)
    std_msgs/Header header      <------>    header information
        uint32 seq
        time stamp              <------>    time stamped
        string frame_id         <------>    frame_id
    float32 angle_min           <------>    laser beam start
    float32 angle_max           <------>    laser beam end
    float32 angle_increment     <------>    angle between each beam
    float32 time_increment      <------>    time increment
    float32 scan_time           <------>    time between every two scans
    float32 range_min           <------>    laser beam min distance [m]
    float32 range_max           <------>    laser beam max distance [m]
    float32[] ranges            <------>    laser beam real distance [m]
    float32[] intensities       <------>    laser beam intensities leave it empty if device has no support
*/

#include "slam_laser.h"

//LaserScanPub initialize
LaserScanPub::LaserScanPub(ros::NodeHandle& nh,
                    double minAngle,double maxAngle,double scanTime,
                    double minRange,double maxRange,double scanNums):
                    nh_(nh),minAngle(minAngle),maxAngle(maxAngle),minRange(minRange),
                    maxRange(maxRange),scanNums(scanNums),scanTime(scanTime)
{
    //laserdata_init();
    scanpub_init();
}

LaserScanPub::~LaserScanPub()
{
}

//laserdata init 
void LaserScanPub::laserdata_init()
{
    //create laser data
    ros::Time scantime = ros::Time::now();
    laserdata_.header.stamp = scantime;
    laserdata_.header.frame_id = "base_link";
    laserdata_.range_min = minRange;
    laserdata_.range_max = maxRange;
    laserdata_.scan_time = scanTime;
    laserdata_.angle_increment = (maxAngle-minAngle)/scanNums;
    laserdata_.time_increment = scanTime/scanNums;
    laserdata_.ranges.resize(scanNums);
    laserdata_.intensities.resize(scanNums);
    for(int i=0;i<scanNums;i++)
    {
        laserdata_.ranges[i] = 5;
        laserdata_.intensities[i] = 100;
    }

}

// init scanpub
void LaserScanPub::scanpub_init()
{
    scanpub_ = nh_.advertise<sensor_msgs::LaserScan>("scan",100);
    ros::Rate rate(10);
    while(nh_.ok())
    {
        laserdata_init();
        //publish laser data
        scanpub_.publish(laserdata_);
        rate.sleep();
    }
}

int main(int argc,char**argv)
{
    //init and name node
    ros::init(argc,argv,"myslam_laser");
    //create ros node handle
    ros::NodeHandle nh;
    // 0 ---> 0 degree and 1.57 ---> 90 degree
    LaserScanPub scanpub(nh,0,1.57,0.01,0,10,100);
    return 0;
}