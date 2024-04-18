#include <lineDetection.h>



class Calibration{

public:
Calibration();
void calibrate(int *lineVal);
void calState();
int *calVal;


private:
LineDetection lineDetection;
};