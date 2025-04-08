
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <iostream>
class Bluetooth
{

public:
    Bluetooth();
    void readData();
    void sendData(int x, int y, int ballDist, int role);
    int getYCoord();
    int getXCoord();
    int getRole();
    int getDistance();
    bool getState();

private:
    int statePin;
    char read;
    String buffer;
    int xCoord;
    int yCoord;
    int ballDist;
    int role; //1 = offense; 0 = defense
    elapsedMillis sendQueue;
};
#endif