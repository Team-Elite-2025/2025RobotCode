#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include <trig.h>
#include <elapsedMillis.h>
class Ultrasonic
{

public:
    Ultrasonic();
    int frontSensor();
    int backSensor();
    int leftSensor();
    int rightSensor();
private:
    int echoPin;
    int trig1Pin;
    int trig2Pin;
    int trig3Pin;
    int trig4Pin;
};
#endif