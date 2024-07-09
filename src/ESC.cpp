#include <ESC.h>

ESC::ESC()
{
    motorPin = 6;
    tick1 = 0;
    tick2 = 0;
    gradspeed1 = 0;
    gradspeed2 = 0;
    pinMode(motorPin, OUTPUT);
    threshold = 40;
}

void ESC::dribbler(int speed)
{
    analogWrite(motorPin, speed);
}
void ESC::runDribbler(double ballAngle, double dist, bool capture)
{
    if (ballAngle < threshold || ballAngle > 360 - threshold)
    {
        if (dist < 40 || capture)
        {
            dribbler(150);
        }
        else
        {
            dribbler(0);
        }
    }
    else
    {
        dribbler(0);
    }
}
int ESC::takeBack(int ballAngle, int goalAngle, int orbitAngle, bool capture, int correction)
{
    int rotatedGoal = goalAngle + correction;
    if (rotatedGoal >= 360)
    {
        rotatedGoal -= 360;
    }
    if (rotatedGoal < 0)
    {
        rotatedGoal += 360;
    }
    if (!capture)
    {
        dribbler(255);
        return orbitAngle;
    }
    else
    {
        dribbler(255);
        if (rotatedGoal > 180)
        {
            takeBackAngle = 225;
            if (rotatedGoal > 320)
            {
                takeBackAngle = -2;
                if(motor.spin(goalAngle)){
                    takeBackAngle = -1;
                }
            }
        }
        else
        {
            takeBackAngle = 135;
            if (rotatedGoal < 40)
            {
                takeBackAngle = -2;
                if(motor.spin(goalAngle)){
                    takeBackAngle = -1;
                }
            }
        }
    }
}