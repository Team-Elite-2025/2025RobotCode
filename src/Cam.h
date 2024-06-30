#ifndef CAM_H
#define CAM_H

#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>
#include <trig.h>

class Cam
{
public:
        Cam();
        double ball;
        double yellowGoal;
        double blueGoal;
        double ballDistance;
        double CamCalc();
        double FilterAngle(double angle, double validAngle);
        std::string buffer;
        void ballNotFound(int ballX, int ballY, int robotX, int robotY);

private:
        char read;
        double previousBallAngle;
        double previousBlueAngle;
        double previousYellowAngle;
        double previousBallDistance;
};
#endif