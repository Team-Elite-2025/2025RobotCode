
#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <trig.h>
#include <ultrasonic.h>
#include <calculation.h>

class Localization
{

public:
    Localization();
    int* absoluteBallPos(int ballAngle, int ballDist);
    void offenseLocalization(double correction, int awayGoal, int homeGoal);
    void defenseLocalization(double correction, int awayGoal, int homeGoal);
    int getRobotX();
    int getRobotY();
private:
    Ultrasonic ultrasonic;
    Calculation calculation;
    elapsedMillis offsetx;
    bool allowRight;
    bool allowFront;
    elapsedMillis offsety;
    void getXUltrasonic(double correction);
    void getYUltrasonic(double correction);
    void getYUltrasonicDefense(double correction);
    void cameraLocalization(int homeGoal, int awayGoal);
    int cameraXCoord;
    int cameraYCoord;
    int rightDist;
    int leftDist;
    int frontDist;
    int backDist;
    int ultrasonicXCoord;
    int ultrasonicYCoord;
    int xUncertainty;
    int yUncertainty;
    int fieldXDist;
    int fieldYDist;
    int fieldYDistWithGoal;
    double correctionThreshold;
    int goalPos;
    int robotX;
    int robotY;
    int prevHomeGoal;
    int prevAwayGoal;
};
#endif