#include <roleSwitching.h>

RoleSwitch::RoleSwitch(){
    ourRole = 1; //make 0 on other robot
}

void RoleSwitch::background(int ballDist, int mateRole, int mateBallDist){
    if(ourRole == 1 && mateRole == 1){ //we are slave
        ourRole = 0;
    }
    if(ourRole == 0 && ballDist != -5){ //we are master
        if(ballDist < 30 && mateBallDist > 50){
            ourRole = 1;
        }
    } 
}

int RoleSwitch::getOurRole(){
    return ourRole;
}


