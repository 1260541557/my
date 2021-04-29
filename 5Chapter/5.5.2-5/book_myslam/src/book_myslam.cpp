/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.3.12

    Description: Simple ros map building demo for beginnner learners

    MailBox: taomanl@163.com

    HowToRun: 1. rostopic pub -r 10 /cmd_vel geometry_msgs/Twist '{linear: {x: 0.003, y: 0, z: 0}, angular: {x: 0, y: 0, z: 0}}'
              2. rosrun book_myslam slam_tfpub
              3. rosrun book_myslam slam_laser
              4. rosrun book_myslam book_myslam
              5. rosrun rviz rviz
              *-> you can also add 2-4 to a launch file then run：
                roslaunch book_myslam myslam.launch
    ****************
*/

#include "book_myslam.h"

MySlam::MySlam(ros::NodeHandle& nh,double mapreso,double mposx,double mposy,
               double mposz,double morientx,double morienty,double morientz,
               double morientw,int mwidth,int mheight):nh_(nh),mapreso(mapreso),
               mposx(mposx),mposy(mposy),mposz(mposz),morientx(morientx),
               morienty(morienty),morientz(morientz),morientw(morientw),
               mwidth(mwidth),mheight(mheight)
{
    mapdata_init();
    mappub_init();
    lasersub_init();

}

MySlam::~MySlam()
{
}

//laser data cllback
void MySlam::lasercallback(const sensor_msgs::LaserScanConstPtr& laserdata)
{
    /*lookupTransform (const std::string &target_frame, const std::string &source_frame, 
                       const ros::Time &time, StampedTransform &transform) 
      get transfrom map --- target frame , base_link --- source frame
    */
    if(scan_count %scan_reso == 0)
    {
        try{
            tflistener_.waitForTransform("map","base_link",ros::Time(0),ros::Duration(3.0));
            tflistener_.lookupTransform("map","base_link",ros::Time(0),base2map);
        }
        catch(tf::TransformException& ex)
        {
            ROS_INFO("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        boost::mutex::scoped_lock map_lock(map_mutex);

        //get angle in x direction
        quat = base2map.getRotation();
        theta = quat.getAngle();
        //get transform distance in x,y direction
        trans_base2map = base2map.getOrigin();
        tx = trans_base2map.getX();
        ty = trans_base2map.getY();
        //laser origin coordination in map frame
        basex0 = int(tx/mapreso);
        basey0 = int(ty/mapreso);
        laserNum = laserdata->ranges.size();
        fopen.open("data.txt",ios::app);//save points data for problem check
        if(fopen.is_open())
        {
            cout<<"open file successsful!"<<endl;
        }else
        {
            cout<<"open file fail"<<endl;
        }
        for(int i=0;i<laserNum;i++)
        {
            beamsAngle = laserdata->angle_min+i*laserdata->angle_increment;
            //end point coordination in base from
            basex = laserdata->ranges[i]*cos(beamsAngle);
            basey = laserdata->ranges[i]*sin(beamsAngle);
            //end point coordination in map frame
            mapx = basex*cos(theta) + basey*sin(theta) + tx;
            mapy = basey*cos(theta) - basex*sin(theta) + ty;
            //points grid coordination
            nx = int(mapx/mapreso);
            ny = int(mapy/mapreso);
            mapxn = nx+1;//
            mapyn = ny+1;//
            endpoint.x = mapxn;
            endpoint.y = mapyn;

            fopen<<endpoint.x<<" "<<endpoint.y<<"\n";
            endpoints.push_back(endpoint);
        }
        fopen.close();

        for(vector<MapPoint>::iterator iter = endpoints.begin();iter!=endpoints.end();iter++)
        {
            mappoints = MySlam::bresenham(basex0,basey0,(*iter).x,(*iter).y);
            cout<<"scan numbers are: "<<endpoints.size()<<endl;
            cout<<"bresenham point nums are:"<<mappoints.size()<<endl;
            cout<<"x0,yo is "<<basex0<<" "<<basey0<<endl;
            cout<<"angle is "<<theta<<endl;
            for(vector<MapPoint>::iterator iter1 = mappoints.begin();iter1!=mappoints.end();iter1++)
            {
                idx = mwidth*(*iter1).y+(*iter1).x;
                cout<<"idx is"<<(*iter1).x<<" "<<(*iter1).y<<endl;
                mapdata_.data[idx] = 0;
            }
            mappoints.clear();
        }
        endpoints.clear();
        mappub_.publish(mapdata_);
    }
    scan_count++;
}

// bresenham algorithm obtain int points in line
vector<MapPoint> MySlam::bresenham(int x0,int y0,int x1,int y1)
{
    vector<MapPoint> pp;
    MapPoint p;
    int dx, dy, h, a, b, x, y, flag, t;
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    if (x1 > x0) a = 1; else a = -1;
    if (y1 > y0) b = 1; else b = -1;
    x = x0;
    y = y0;
    if (dx >= dy) {
        //0< |k| <=1
        flag = 0;
    } else {
        //|k|>1,exchange dx，dy
        t = dx;
        dx = dy;
        dy = t;
        flag = 1;
    }
    h = 2 * dy - dx;
    for (int i = 1; i <= dx; ++i) {
        p.x = x,p.y=y;
        //cout<<"x,y is "<<x<<" "<<y<<endl;
        pp.push_back(p);
        if (h >= 0) {
            if (flag == 0) y = y + b;
            else x = x + a;
            h = h - 2 * dx;
        }
        if (flag == 0) x = x + a;
        else y = y + b;
        h = h + 2 * dy;

    }
    return pp;
}

// map publisher init
void MySlam::mappub_init()
{
    mappub_ = nh_.advertise<nav_msgs::OccupancyGrid>("map",100);
}

// laser data subscriber init
void MySlam::lasersub_init()
{
    lasersub_ = nh_.subscribe("scan",1,&MySlam::lasercallback,this);
}

//map data initialize
void MySlam::mapdata_init()
{
    scan_count = 0;
    scan_reso = 1;
    ros::Time currtime = ros::Time::now();
    mapdata_.header.stamp = currtime;
    mapdata_.header.frame_id = "map";
    mapdata_.info.resolution = mapreso;
    mapdata_.info.width = mwidth;
    mapdata_.info.height = mheight;
    mapdata_.info.origin.position.x = mposx;
    mapdata_.info.origin.position.y = mposy;
    mapdata_.info.origin.position.z = mposz;
    mapdata_.info.origin.orientation.x = morientx;
    mapdata_.info.origin.orientation.y = morienty;
    mapdata_.info.origin.orientation.z = morientz;
    mapdata_.info.origin.orientation.w = morientw;
    int dataszie = mwidth*mheight;
    mapdata_.data.resize(dataszie);
    for(int i=0;i<dataszie;i++)
    {
        mapdata_.data[i]=-1;
    }
}


int main(int argc,char** argv)
{
    //init and name node 
    ros::init(argc,argv,"MySlam");
    //create ros node handle 
    ros::NodeHandle nh;
    //map param
    double mapreso=0.05,mposx=0,mposy=0,mposz=0,morientx=0,
           morienty=0,morientz=0,morientw=1;
    int mwidth=300,mheight=300;
    //Myslam instantiate object
    MySlam myslam(nh,mapreso,mposx,mposy,mposz,morientx,morienty,
                  morientz,morientw,mwidth,mheight);
    ros::spin();
    return 0;
}