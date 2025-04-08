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
#include <bluetooth.h>
#include <localization.h>
#include <roleSwitching.h>
#include <ESC.h>

class Process
{

public:
    Process(int physicalRobot);
    void offense(double motorPower);
    void defense(double motorPower);
    RoleSwitch roleSwitch;

private:
    // int physicalRobot = 1;
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
    Bluetooth bluetooth;
    Localization localization;
    ESC esc;
    double getHomeGoal();
    double getAwayGoal();
    void smoothMove(int moveAngle, int lineAngle, double motorPower, int orientation);
    int getOrientationOffense();
    void general(int role);
    int lineAngle;
    int orientation;
    int* ballPos;
};
#endif