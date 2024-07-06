#include <roleSwitching.h>

RoleSwitch::RoleSwitch()
{
    ourRole = 1; // make 0 on other robot
}

void RoleSwitch::background(int ballDist, int mateRole, int mateBallDist, bool connection)
{
    if (connection)
    {
        if (mateRole == -1 && timer > 2000)
        {
            ourRole = 1;
        }
        else if(mateRole != -1){
            timer = 0;
        }
        
        else if (ourRole == 1 && mateRole == 1)
        { // we are slave
            ourRole = 0;
        }
        else if (ourRole == 0 && ballDist != -5 && mateBallDist != -5)
        { // we are master
            if (ballDist < 30 && mateBallDist > 50)
            {
                ourRole = 1;
            }
        }
    }
    else{
        ourRole = 1;
    }
}

int RoleSwitch::getOurRole()
{
    return ourRole;
}
