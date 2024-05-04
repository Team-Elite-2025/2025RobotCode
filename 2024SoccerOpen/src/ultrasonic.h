#include <Arduino.h>
#include <trig.h>

#ifndef ULTRASONIC_H
#define ULTRASONIC_H
class Ultrasonic
{

    public:
        Ultrasonic();
        int sensor1();
        int sensor2();
        int sensor3();
        int sensor4();
    private:
        int echoPin;
        int trig1Pin;
        int trig2Pin;
        int trig3Pin;
        int trig4Pin;
};
#endif