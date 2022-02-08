#include <ros/ros.h>
#include <crawler_msgs/LiveTexture.h>
#include <tf/transform_listener.h>
#include "nav_msgs/MapMetaData.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include "vector"
#include <stdio.h>
#include <math.h>
#include <fstream>

using namespace std;


#define PI 3.14159265

class Exporter

{
protected:

    unsigned int rows;
    unsigned int cols;
    image_transport::Publisher texturePub;
    ros::Subscriber textureSub;
    ros::NodeHandle n;
    image_transport::Subscriber imageSub;
    image_transport::ImageTransport it;


    void img_callback(const crawler_msgs::LiveTexture::ConstPtr& msg)
    {
        texturePub.publish(msg->texture);
    }






public:
    Exporter() : n("~"), it(n) {
        ros::Duration(0.5).sleep();
        std::string transport = "raw";
        n.param("transport",transport,transport);

        texturePub = it.advertise("texture_img", 1);
        textureSub=n.subscribe<crawler_msgs::LiveTexture>("/texture",1,&Exporter::img_callback,this);
    }
};


int main(int argc, char * argv[]){
    ros::init(argc, argv, "bw2_texture_export");
    Exporter var;
    ros::spin();

}

