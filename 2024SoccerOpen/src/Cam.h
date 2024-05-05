#ifndef CAM_H
#define CAM_H

#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Cam
{
public:
        Cam();
        double ball;
        double yellowGoal;
        double blueGoal;
        double ballDistance;
        double validDistance;
        double CamCalc();
        double FilterAngle(double angle, double validAngle);
        double ComplimentaryFilterAngle(double angle, double validAngle);
        double ComplimentaryFilterDistance(double dist, double validDist);
        std::string buffer;

private:
        char read;
        double previousBallAngle;
        double previousBlueAngle;
        double previousYellowAngle;
        double previousBallDistance;
};
#endif