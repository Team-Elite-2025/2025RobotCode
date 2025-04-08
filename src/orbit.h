
#ifndef ORBIT_H
#define ORBIT_H

#include <trig.h>
#include <ultrasonic.h>

class Orbit
{

public:
    Orbit(int robotNum);
    double robotAngle;
    double CalculateRobotAngle(double ballAngle, double distance, double derivative, int sampleTime);
    double GetToPosition(int targetX, int targetY, int currentX, int currentY);
    bool inPos;
    bool inOrientation;

private:
    int multiplier;
    double homeAngle;
    Ultrasonic ultrasonic;
    unsigned long now;
    unsigned long lastTime;
    double kd;
    int lastAngle;
    double derivative;
    int physicalRobot;
};
#endif