#ifndef GOAL_H
#define GOAL_H

#include <Arduino.h>
#include <elapsedMillis.h>
#include <switches.h>
#include <ultrasonic.h>
#include <calculation.h>
class Goal
{
public:
    Goal();
    int scoreOrientation(int orientation, int goalAngle, int initialOrientation);
    void kickAllowed(int y, int correction);
    void kickBackground();
    int ballAngleCheck(int ballAngle, int initialOrientation, int orientation);

private:
    int kickerPin;
    elapsedMillis timer;
    elapsedMillis active;
    int kickHold;
    Switch switches;
    Ultrasonic ultrasonic;
    void kick();
    int previousScoreAngle;
    Calculation calculation;
};

#endif