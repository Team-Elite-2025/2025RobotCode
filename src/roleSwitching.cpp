#include <roleSwitching.h>

RoleSwitch::RoleSwitch(int robotNum)
{
    if (robotNum == 0)
        ourRole = 0; // make 0 on other robot
    else
        ourRole = 1;
}

void RoleSwitch::background(int ballAngle, int ballDist, int mateRole, int mateBallDist, bool connection)
{
    if (switches.start())
    {
        if (connection)
        {
            if (mateRole == -1 && timer >= 2000)
            {
                ourRole = 1;
            }
            else if (mateRole != -1)
            {
                timer = 0;
            }

            if (ourRole == 1 && mateRole == 1 && switchBack >= 1000)
            { // we are slave
                ourRole = 0;
            }
            else if (ourRole == 0 && ballDist != -5 && mateBallDist != -5)
            { // we are master
                if (ballDist < 30 && mateBallDist > 50 && (ballAngle < 130 || ballAngle > 230))
                {
                    switchBack = 0;
                    ourRole = 1;
                }
            }
        }
        else
        {
            ourRole = 1;
        }
    }
    else{
        timer = 0;
        switchBack = 0;
    }
}

int RoleSwitch::getOurRole()
{
    return ourRole;
}
