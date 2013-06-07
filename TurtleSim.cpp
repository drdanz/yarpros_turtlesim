#include "TurtleSim.h"

#include "EmptyIn.h"
#include "EmptyOut.h"
#include "KillIn.h"
#include "KillOut.h"
#include "SetPenIn.h"
#include "SetPenOut.h"
#include "SpawnIn.h"
#include "SpawnOut.h"
#include "TeleportAbsoluteIn.h"
#include "TeleportAbsoluteOut.h"
#include "TeleportRelativeIn.h"
#include "TeleportRelativeOut.h"


#include <yarp/os/Port.h>

#include <iostream>
#include <cmath>

static const std::string portBaseName("/yarpros_turtlesim/");
static const std::string nodeBaseName("/turtlesim#/");

TurtleSim::TurtleSim(const std::string& name) :
        name(name)
{
}

TurtleSim::~TurtleSim()
{
}

bool TurtleSim::teleportAbsolute(yarp::os::NetFloat32 x,
                                 yarp::os::NetFloat32 y,
                                 yarp::os::NetFloat32 theta)
{
    // teleport_absolute service
    yarp::os::Port teleportAbsolutePort;
    std::string teleport_absolute_port_name(portBaseName + name + "/teleport_absolute");
    std::string teleport_absolute_service(nodeBaseName + name + "/teleport_absolute");
    teleportAbsolutePort.openFake(teleport_absolute_port_name.c_str());
    teleportAbsolutePort.addOutput(teleport_absolute_service.c_str());

    TeleportAbsoluteIn teleportAbsoluteIn;
    teleportAbsoluteIn.x = x;
    teleportAbsoluteIn.y = y;
    teleportAbsoluteIn.theta = theta;
    TeleportAbsoluteOut teleportAbsoluteOut;
    return teleportAbsolutePort.write(teleportAbsoluteIn, teleportAbsoluteOut);
}

bool TurtleSim::teleportRelative(yarp::os::NetFloat32 linear,
                                 yarp::os::NetFloat32 angular)
{
    // teleport_relative service
    yarp::os::Port teleportRelativePort;
    std::string teleport_relative_port_name(portBaseName + name + "/teleport_relative");
    std::string teleport_relative_service(nodeBaseName + name + "/teleport_relative");
    teleportRelativePort.openFake(teleport_relative_port_name.c_str());
    teleportRelativePort.addOutput(teleport_relative_service.c_str());

    TeleportRelativeIn teleportRelativeIn;
    teleportRelativeIn.linear = linear;
    teleportRelativeIn.angular = angular;
    TeleportRelativeOut teleportRelativeOut;
    return teleportRelativePort.write(teleportRelativeIn, teleportRelativeOut);
}

bool TurtleSim::setPen(unsigned char r,
                       unsigned char g,
                       unsigned char b,
                       unsigned char width,
                       unsigned char off)
{
    // set_pen service
    yarp::os::Port setPenPort;

    std::string set_pen_port_name(portBaseName + name + "/set_pen");
    std::string set_pen_service(nodeBaseName + name + "/set_pen");
    setPenPort.openFake(set_pen_port_name.c_str());
    setPenPort.addOutput(set_pen_service.c_str());

    SetPenIn setPenIn;
    setPenIn.r = r;
    setPenIn.g = g;
    setPenIn.b = b;
    setPenIn.width = width;
    setPenIn.off = off;
    SetPenOut setPenOut;
    return setPenPort.write(setPenIn, setPenOut);
}

bool TurtleSim::reset()
{
    // reset service
    const std::string reset_port_name(portBaseName + "reset");
    const std::string reset_service(nodeBaseName + "reset");

    yarp::os::Port reset_port;
    reset_port.openFake(reset_port_name.c_str());
    reset_port.addOutput(reset_service.c_str());

    EmptyIn resetIn;
    EmptyOut resetOut;
    return reset_port.write(resetIn, resetOut);
}


bool TurtleSim::kill(const std::string& name)
{
    // kill service
    const std::string kill_port_name(portBaseName + "kill");
    const std::string kill_service(nodeBaseName + "kill");
    yarp::os::Port kill_port;
    kill_port.openFake(kill_port_name.c_str());
    kill_port.addOutput(kill_service.c_str());

    KillIn killIn;
    KillOut killOut;
    killIn.name = name;
    return kill_port.write(killIn, killOut);
}

std::string TurtleSim::spawn(yarp::os::NetFloat32 x,
                             yarp::os::NetFloat32 y,
                             yarp::os::NetFloat32 theta,
                             const std::string& name)
{
    // spawn service
    const std::string spawn_port_name(portBaseName + "spawn");
    const std::string spawn_service(nodeBaseName + "spawn");
    yarp::os::Port spawn_port;
    spawn_port.openFake(spawn_port_name.c_str());
    spawn_port.addOutput(spawn_service.c_str());

    SpawnIn spawnIn;
    SpawnOut spawnOut;
    spawnIn.x = x;
    spawnIn.y = y;
    spawnIn.theta = theta;
    spawnIn.name = name;
    spawn_port.write(spawnIn, spawnOut);

    std::cout << "New turtle name = " << spawnOut.name << std::endl;
    return spawnOut.name;
}

bool TurtleSim::clear()
{
    // clear service
    const std::string clear_port_name(portBaseName + "clear");
    const std::string clear_service(nodeBaseName + "clear");

    yarp::os::Port clear_port;
    clear_port.openFake(clear_port_name.c_str());
    clear_port.addOutput(clear_service.c_str());

    EmptyIn clearIn;
    EmptyOut clearOut;
    return clear_port.write(clearIn, clearOut);
}
