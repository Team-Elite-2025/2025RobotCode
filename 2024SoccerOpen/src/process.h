#ifndef PROCESS_H
#define PROCESS_H
#include <Arduino.h>
#include <trig.h>
#include <motor.h>
#include <lineDetection.h>
#include <Cam.h>
#include <orbit.h>
#include <Cam.h>
#include <calibration.h>
#include <goal.h>
#include <calculation.h>
#include <defense.h>

class Process
{

public:
    Process();
    void offense(double motorPower);
    void defense(double motorPower);

private:
    LineDetection lineDetection;
    Motor motor;
    Cam cam;
    Orbit orbit;
    Calibration calbiration;
    Switch switches;
    Goal goal;
    Calculation calculation;
    Defense goalie;
    Ultrasonic ultrasonic;
    double getGoal();
    void smoothMove(int moveAngle, int lineAngle, double motorPower, int orientation);
    int getOrientationOffense();
};
#endif