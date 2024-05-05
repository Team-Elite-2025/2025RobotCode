#ifndef GOAL_H
#define GOAL_H

#include <Arduino.h>
#include <elapsedMillis.h>
#include <switches.h>
#include <ultrasonic.h>
class Goal
{
public:
    Goal();
    int scoreOrientation(int orientation, int goalAngle, int initialOrientation);
    void kickAllowed();
    void kickBackground();

private:
    int kickerPin;
    elapsedMillis timer;
    elapsedMillis active;
    int kickHold;
    Switch switches;
    Ultrasonic ultrasonic;
    void kick();
};

#endif