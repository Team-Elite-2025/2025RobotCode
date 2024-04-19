#ifndef CALIBRATION_H
#define CALIBRATION_H


#include <lineDetection.h>
#include <switches.h>



class Calibration{

public:
Calibration();
void calibrate(int *lineVal);
void calState();
int *calVal;


private:
LineDetection lineDetection;
Switch switches;
};
#endif