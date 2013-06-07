#include <yarp/os/all.h>
#include <iostream>
#include <cmath>

#include "TurtleSim.h"

#include "Velocity.h"
#include "Pose.h"



int main(int argc, char *argv[]) {
    yarp::os::Network yarp;

    TurtleSim::reset();

    TurtleSim turtleSim1("turtle1");

#if 0
    turtleSim1.teleportAbsolute(5.0, 5.0, 0.0);

    yarp::os::Time::delay(1);

    turtleSim1.teleportRelative(-1, -M_PI/2);

    yarp::os::Time::delay(1);

    TurtleSim::clear();
    std::string turtle = TurtleSim::spawn(3.0, 3.0, M_PI*5.0/6.0);
    TurtleSim::kill(turtle);
#endif // 0

    // command_velocity topic
    const std::string command_velocity_port_name("/yarpros_turtlesim/turtle1/command_velocity");
    const std::string command_velocity_topic("topic://turtle1/command_velocity");
    yarp::os::Port command_velocity_port;
    command_velocity_port.open(command_velocity_port_name.c_str());

    if (!yarp.connect(command_velocity_port_name.c_str(), command_velocity_topic.c_str())) {
        std::cout << "Error! Could not connect to topic " << command_velocity_topic << std::endl;
        return -1;
    }

#if 0
    Velocity v;
    v.linear = 2.0;
    v.angular = 0;
    command_velocity_port.write(v);




    // set_pen service
    turtleSim1.setPen(0, 255, 0, 1, 0);



    yarp::os::BufferedPort<yarp::os::Bottle> out_pose_port;
    out_pose_port.open("/yarpros_turtlesim/debug");


// Now try to write YARP

//     // reset
//     TurtleSim::reset();
//     // kill turtle1
//     TurtleSim::kill("turtle1");
//     // re-spawn turtle1
//     std::string turtle1 = TurtleSim::spawn(3.0, 3.0, 2.0 * M_PI * 5.0 / 6.0, "turtle1");
// 
//     std::cout << "New turtle name = " << turtle1 << std::endl;

//     // move
//     v.linear = 4.0;
//     v.angular = 0;
//     command_velocity_port.write(v);
//     yarp::os::Time::delay(1);

#endif // 0

    while (1) {

//         if (!turtleSim1.teleportAbsolute(3.0, 3.0, M_PI / 2.0))
//             std::cerr << "Cannot teleport!" << std::endl;
        yarp::os::Time::delay(0.2);
        if (!TurtleSim::clear())
            std::cerr << "Cannot clear!" << std::endl;
        if (!turtleSim1.setPen(0, 255, 0, 1, 0))
            std::cerr << "Cannot set pen!" << std::endl;

        float i = 0;
        while (1) {
            Velocity v;
            v.linear = 2.0;
            v.angular = 1 + cos(i);
            command_velocity_port.write(v);
            i += M_PI/32;
            yarp::os::Time::delay(1.0/32);
        }


        // Draw a flower
        for (int i=0; i<15; i++) {
            Velocity v;
            v.linear = 4.0;
            v.angular = 0.5;
            command_velocity_port.write(v);

            yarp::os::Time::delay(1);

            v.linear = 1.5;
            v.angular = 3.0;
            command_velocity_port.write(v);

            yarp::os::Time::delay(1);
        }

        turtleSim1.teleportAbsolute(6.0, 6.0, M_PI);
        yarp::os::Time::delay(0.2);
        TurtleSim::clear();
        turtleSim1.setPen(255, 0, 0, 1, 0);
        yarp::os::Time::delay(1);

        // Draw a flower
        for (int i=0; i<1; i++) {
            Velocity v;
            v.linear = 3.5;
            v.angular = 0.8;
            command_velocity_port.write(v);

            yarp::os::Time::delay(1);

            v.linear = 1.7;
            v.angular = 2.5;
            command_velocity_port.write(v);

            yarp::os::Time::delay(1);
        }

        turtleSim1.teleportAbsolute(8.0, 5.0, 0);
        yarp::os::Time::delay(0.2);
        TurtleSim::clear();
        turtleSim1.setPen(0, 0, 255, 1, 0);
        yarp::os::Time::delay(1);

        // Draw a flower
        for (int i=0; i<15; i++) {
            Velocity v;
            v.linear = 2.5;
            v.angular = 1.5;
            command_velocity_port.write(v);

            yarp::os::Time::delay(1);

            v.linear = 1.5;
            v.angular = 4.5;
            command_velocity_port.write(v);

            yarp::os::Time::delay(1);
        }
#if 0
        Pose *p = pose_port.read();
        if(p != NULL) {
//             if(p.linear_velocity == 0 && p.angular_velocity == 0) {
            std::cout << "pose: x = "            << p->x
                      << ", y = "                << p->y
                      << ", theta = "            << p->theta
                      << ", linear_velocity = "  << p->linear_velocity
                      << ", angular_velocity = " << p->angular_velocity
                      << std::endl;
//             }
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
#endif // 0
    }

    return 0;
}
