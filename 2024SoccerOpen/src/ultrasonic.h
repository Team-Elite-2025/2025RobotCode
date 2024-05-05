#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include <trig.h>
class Ultrasonic
{

public:
    Ultrasonic();
    int frontSensor();
    int backSensor();
    int leftSensor();
    int rightSensor();
    int getX();
    int getY();

private:
    int echoPin;
    int trig1Pin;
    int trig2Pin;
    int trig3Pin;
    int trig4Pin;
    int prevX;
    int prevY;
};
#endif