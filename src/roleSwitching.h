
#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <bluetooth.h>
#include <elapsedMillis.h>
class RoleSwitch
{

public:
    RoleSwitch();
    void background(int ballDist, int role, int mateBallDist, bool connection);
    int getOurRole(); 

private:
    Bluetooth bluetooth;
    int ourRole;
    elapsedMillis timer;

};
#endif