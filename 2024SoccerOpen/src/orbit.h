#include <trig.h>
#include <lineDetection.h>
#ifndef ORBIT_H
#define ORBIT_H
class Orbit {

    public: 
        Orbit();
        double validBallAngle;
        double highestValue; // highest of the sensor values
        double robotAngle;
        bool capture = false;
        int kickState = 1;
        void kickButton();
        bool ballpresent = false;
        int realhighestVal;
        int xbeeHighVal;
        double CalculateRobotAngle(double ballAngle, double goalAngle, double distance);
        double GetToSpinShotPosition(bool linePresent, int goalAngle, int lineAngle);
        double InOrientationSpinShot(double robotOrientation, int initialOrientation, double goalAngle);
        double GetToHomePositionOffense(double goalDistance, double goalAngle, bool disappear);
        bool inPos;
        bool inOrientation;
    private:
        int multiplier;
        double xcomp, ycomp;
        double homeAngle;

         
        
};
#endif