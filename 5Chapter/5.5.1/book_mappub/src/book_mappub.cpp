/*
    ****************
    Author: Tomanlon

    Copyright: Tomanlon

    Date: 2019.3.11

    Description: simple ros map data create by customer for beginning learners

    MailBox: taomanl@163.com

    HowToRun: rosrun book_mappub book_mappub
    ****************
*/

#include "book_mappub.h"

MapPub::MapPub(ros::NodeHandle& nh,double map_reso,
                int map_width,int map_height,
                double posx,double posy,double posz,
                double orientx,double orienty,
                double orientz,double orientw):
                nh_(nh),map_reso(map_reso),map_width(map_width),
                map_height(map_height),posx(posx),posy(posy),posz(posz),
                orientx(orientx),orienty(orienty),orientz(orientz),
                orientw(orientw)
{
    mapdata_init();
    mappub_init();
}

MapPub::~MapPub()
{
}

void MapPub::mapdata_init()
{
    //nav_msgs::MapMetaData datainfo_ fill
    ros::Time maptime = ros::Time::now();
    datainfo_.resolution = map_reso;
    datainfo_.width = map_width;
    datainfo_.height = map_height;
    datainfo_.origin.position.x = posx;
    datainfo_.origin.position.y = posy;
    datainfo_.origin.position.z = posz;
    datainfo_.origin.orientation.x = orientx;
    datainfo_.origin.orientation.y = orienty;
    datainfo_.origin.orientation.z = orientz;
    datainfo_.origin.orientation.w = orientw;

    int datasize = map_width*map_height;
    // nav_msgs::OccupancyGrid mapdata_ fill
    mapdata_.header.stamp = maptime;
    mapdata_.header.frame_id = "map";
    mapdata_.info = datainfo_;
    mapdata_.data.resize(datasize);

    /*
        Flowing params are obstacles information
        Map shape like below:
        obsx3_min                               obsx3_max
        *****************************************
        *                                       *
        *      obsx2_min                        *
        *      **********************************obsx2_max
        *                          obsy_max     *
        *              obsx1_max  *             *
        ****************          *             *
        *obsx1_min                *             *
        *                         *             *
        *                         *             *                                  
        ***************************************** 
        obsx1_max                               obsx1_min
    */

    int obsx1_min = map_height/3*2*map_width + map_width/4;
    int obsx1_max = map_height/3*2*map_width + map_width;
    int obsx2_min = map_height/3*map_width;
    int obsx2_max = map_height/3*map_width + map_width/3;
    int obsx3_min = (map_height-1)*map_width;
    int obsx3_max = map_height*map_width;
    int obsy_max = map_width*map_height/2+map_width/3*2;
    int obsy = map_width/3*2;
    //mapdata_ data fill
    for(int i=0;i<datasize;i++)
    {
        int flag = i%map_width;

        if((i>=0 && i<=map_width) || (i>=obsx3_min && i<=obsx3_max) ||
           (i>=obsx1_min && i<=obsx1_max) || (i>=obsx2_min && i<=obsx2_max))
        {
            mapdata_.data[i] = 100;
        }else if(flag==0 || flag==(map_height-1) || (flag==obsy && i<=obsy_max))
        {
            mapdata_.data[i] = 100;
        }
        else{
            mapdata_.data[i] = 0;
        }
    }
}

void MapPub::mappub_init()
{
    ros::Rate rate(10);
    // map publisher initializer
    mappub_ = nh_.advertise<nav_msgs::OccupancyGrid>("map",1000);
    while(nh_.ok())
    {
        // publish map topic
        mappub_.publish(mapdata_);
        rate.sleep();
    }
}  

int main(int argc,char** argv)
{
    //init and name node
    ros::init(argc, argv, "mappub_demo");
    //create ros node handle
    ros::NodeHandle nh_;
    // map param info
    double resol = 0.05;
    int mapw = 200,maph = 200;
    double psx=0,psy=0,psz=0;
    double rx=0,ry=0,rz=0,rw=1;
    //MapPub instantiate object
    MapPub mappub(nh_,resol,mapw,maph,psx,psy,psz,rx,ry,rz,rw);
    return 0;
}