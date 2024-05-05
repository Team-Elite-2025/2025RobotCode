#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <lineDetection.h>
#include <switches.h>
#include <motor.h>

class Calibration
{

public:
    Calibration();
    void calibrate(int *lineVal);
    void calState(Motor &Motor);
    int *calVal;

private:
    LineDetection lineDetection;
    Switch switches;
};
#endif