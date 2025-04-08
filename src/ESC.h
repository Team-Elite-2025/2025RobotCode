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
     Switch switches;
     

public:
    ESC();
    void dribbler(int speed);
    void runDribbler(double ballAngle,double dist, bool capture);
    int takeBack(int ballAngle, int goalAngle, int orbitAngle, int correction, Motor &motor);
    bool needTakeBack(int goalAngle, int ballAngle, int correction);
    bool isTakeBack;
};

#endif