#include <trig.h>
#include <math.h>
#include <motor.h>

#ifndef ESC_H
#define ESC_H

class ESC
{
private:
     double tick1;
     int tick2;
     double gradspeed1;
     double gradspeed2;
     int motorPin;
     int threshold;
     int takeBackAngle;
     Motor motor;

public:
    ESC();
    void dribbler(int speed);
    void runDribbler(double ballAngle,double dist, bool capture);
    int takeBack(int ballAngle, int goalAngle, int orbitAngle, bool capture, int correction);
};

#endif