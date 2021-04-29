#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class LaserScanPub
{
    public:
        LaserScanPub(ros::NodeHandle& nh,
                    double minAngle,double maxAngle,double scanTime,
                    double minRange,double maxRange,double scanNums);
        ~LaserScanPub();
        void scanpub_init();
        void laserdata_init();
    private:
        ros::NodeHandle nh_;
        ros::Publisher scanpub_;
        sensor_msgs::LaserScan laserdata_;
        double minAngle,maxAngle;
        double minRange,maxRange;
        double scanTime,scanNums;
};