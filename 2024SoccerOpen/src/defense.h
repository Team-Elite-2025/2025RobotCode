#ifndef DEFENSE_H
#define DEFENSE_H

#include <Arduino.h>
#include <calculation.h>

class Defense
{
public:
    Defense();
    int defenseCalc(int ballAngle, int goalAngle);
    int defenseOrientation(int ballAngle, int orientation, int initialOrientation);

private:
    int angleDiff;
    int defenseAngle;
    Calculation calculation;
    double robotAngleX;
    double robotAngleY;
    int theoreticalDir;
};

#endif