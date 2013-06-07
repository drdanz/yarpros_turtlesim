
#include <string>
#include <yarp/os/NetFloat32.h>

#include <yarp/os/Port.h>

class TurtleSim
{
public:

    TurtleSim(const std::string &name);
    virtual ~TurtleSim();

    bool teleportAbsolute(yarp::os::NetFloat32 x,
                          yarp::os::NetFloat32 y,
                          yarp::os::NetFloat32 theta);
    bool teleportRelative(yarp::os::NetFloat32 linear,
                          yarp::os::NetFloat32 angular);
    bool setPen(unsigned char r,
                unsigned char g,
                unsigned char b,
                unsigned char width,
                unsigned char off);

    static bool reset();
    static bool clear();
    static bool kill(const std::string &name);
    static std::string spawn(yarp::os::NetFloat32 x,
                             yarp::os::NetFloat32 y,
                             yarp::os::NetFloat32 theta,
                             const std::string &name = std::string());

private:
    std::string name;

};