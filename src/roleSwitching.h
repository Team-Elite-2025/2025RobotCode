
#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <bluetooth.h>
class RoleSwitch
{

public:
    RoleSwitch();
    void background(int ballDist, int role, int mateBallDist);
    int getOurRole(); 

private:
    Bluetooth bluetooth;
    int ourRole;

};
#endif