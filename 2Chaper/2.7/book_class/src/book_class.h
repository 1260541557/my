#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int32.h"
#include "book_class/PassWord.h"
#include <cstdlib>

using namespace std;

class RosBasics
{
    public:
        RosBasics();
        RosBasics(ros::NodeHandle& nh);
        ~RosBasics();
        void initPublish();
        void initSubscribe();
        void initServer();
        bool serverCallback(book_class::PassWord::Request& req,
                            book_class::PassWord::Response& res);
        void msgCallback(const std_msgs::Float64& stdmsg);
        void paramTest();
    private:
        ros::NodeHandle nh_;
        ros::Publisher pub_;
        ros::Subscriber sub_;
        ros::ServiceServer serv_;
};