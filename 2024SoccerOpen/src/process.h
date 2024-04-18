#include <Arduino.h>
#include <trig.h>
#include <motor.h>
#include <lineDetection.h>
#include <Cam.h>
#include <orbit.h>
#include <Cam.h>
#include <calibration.h>
#ifndef OFFENSE_H
#define OFFENSE_H
class Process
{

    public:
        Process();
        void offense(double motorPower);

    private:
        LineDetection lineDetection;
        Motor motor;
        Cam cam;
        Orbit orbit;
        Calibration calbiration;
};
#endif