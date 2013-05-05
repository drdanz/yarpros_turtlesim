#include <yarp/os/all.h>
#include <iostream>

#include "Pose.h"


int main(int argc, char *argv[]) {
    yarp::os::Network yarp;

    // pose topic
    const std::string pose_port_name("/pose2bottle/turtle1/pose:i");
    const std::string pose_topic("topic://turtle1/pose");
    yarp::os::BufferedPort<Pose> pose_port;
    pose_port.open(pose_port_name.c_str());

    if (!yarp.connect(pose_topic.c_str(), pose_port_name.c_str())) {
        std::cout << "Error! Could not connect to topic " << pose_topic << std::endl;
        return -1;
    }



    yarp::os::BufferedPort<yarp::os::Bottle> out_pose_port;
    out_pose_port.open("/pose2bottle/turtle1/pose:o");

    while (1) {

        Pose *p = pose_port.read();
        if(p != NULL) {
            yarp::os::Bottle &b = out_pose_port.prepare();
            b.clear();
            b.addDouble(p->x);
            b.addDouble(p->y);
            b.addDouble(p->theta);
            b.addDouble(p->linear_velocity);
            b.addDouble(p->angular_velocity);
            out_pose_port.write();

        } else {
            std::cerr << "Couldn't read pose" << std::endl;
        }

    }
    return 0;
}
