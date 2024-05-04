
#ifndef SWITCH_H
#define SWITCH_H

class Switch
{
    public:
    Switch();
    bool start();
    bool switchSide();
    bool switchRole();
    bool calibration();
    private:
    int ledPin = 0;
    int recieverPin = 41;
    bool lightgate();
};
#endif