#ifndef LINEDETECTION_H
#define LINEDETECTION_H
#include <Arduino.h>
#include <MCP3XXX.h>

class LineDetection
{
public:
    int initialAngle;
    LineDetection();
    int *GetValues();
    double GetAngle(int *calibrateVal);
    double Process(int *calibrateVal, int orientation, int initialOrient);
    double dotProduct[48];
    int anglebisc;
    bool linepresent;
    int avoidanceAngle;
    double Chord();
    bool outOfBounds;
    bool lineSwitch;
    double sensorAngles[24];


private:
    int *lineValues;
    MCP3008 adc1;
    MCP3008 adc2;
    MCP3008 adc3;
    // MCP3008 adc4;
    // MCP3008 adc5;
    // MCP3008 adc6;
    double sinValues[24];
    double cosValues[24];
    int sensorAngle;
    int currentAngle;
    int angleDiff;
};

#endif