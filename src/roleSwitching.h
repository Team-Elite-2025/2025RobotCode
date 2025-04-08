
#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <bluetooth.h>
#include <elapsedMillis.h>
#include <switches.h>
class RoleSwitch
{

public:
    RoleSwitch(int robotNum);
    void background(int ballAngle, int ballDist, int role, int mateBallDist, bool connection);
    int getOurRole(); 

private:
    Bluetooth bluetooth;
    int ourRole;
    elapsedMillis timer;
    elapsedMillis switchBack;
    Switch switches;

};
#endif