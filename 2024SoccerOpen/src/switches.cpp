#include <switches.h>
#include <Arduino.h>

Switch::Switch()
{

}

bool Switch::start(){
    if(digitalRead(40)==HIGH){
        return true;
    }
    return false;
}
bool Switch::switchSide(){
    if(digitalRead(38)==HIGH){
        return true;
    }
    return false;
}
bool Switch::switchRole(){
    if(digitalRead(36)==HIGH){
        return true;
    }
    return false;
}
bool Switch::calibration(){ 
    if(digitalRead(31)==HIGH){
        return true;
    }
    return false;
}