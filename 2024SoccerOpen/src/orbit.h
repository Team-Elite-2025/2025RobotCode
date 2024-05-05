
#ifndef ORBIT_H
#define ORBIT_H

#include <trig.h>
#include <ultrasonic.h>

class Orbit
{

public:
    Orbit();
    double robotAngle;
    double CalculateRobotAngle(double ballAngle, double goalAngle, double distance);
    double GetToPosition(int x, int y);
    bool inPos;
    bool inOrientation;

private:
    int multiplier;
    double homeAngle;
    Ultrasonic ultrasonic;
};
#endif