#include <Arduino.h>
#include <MCP3XXX.h>
#ifndef LINEDETECTION_H
#define LINEDETECTION_H
class LineDetection{
    public:
        int initialAngle;
        LineDetection();
        int *GetValues();
        double GetAngle(int *calibrateVal);
        double Process(int *calibrateVal);
        double dotProduct[48];
        int anglebisc;
        bool linepresent;
        int avoidanceAngle;
        double Chord();
     
    private:
        int *lineValues;
        MCP3008 adc1;
        MCP3008 adc2;
        MCP3008 adc3;
        MCP3008 adc4;
        MCP3008 adc5;
        MCP3008 adc6;
        bool lineSwitch;
        double sensorAngles[48];
        double sinValues[48];
        double cosValues[48];
        int sensorAngle;
        bool outOfBounds;
        int currentAngle;
        int angleDiff;

};

#endif