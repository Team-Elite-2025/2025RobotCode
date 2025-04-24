#include <ESC.h>

ESC::ESC()
{
    motorPin = 6;
    tick1 = 0;
    tick2 = 0;
    gradspeed1 = 0;
    gradspeed2 = 0;
    // pinMode(motorPin, OUTPUT);
    threshold = 60;
    isTakeBack = false;
}

void ESC::dribbler(int speed)
{
    // analogWrite(motorPin, speed);
}
void ESC::runDribbler(double ballAngle, double dist, bool capture)
{
    isTakeBack = false;
    if (isTakeBack == false && ballAngle == -5)
    {
        if ((ballAngle < threshold || ballAngle > 360 - threshold) && switches.start())
        {
            if (dist < 60 || capture)
            {
                dribbler(20);
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
}
int ESC::takeBack(int ballAngle, int goalAngle, int orbitAngle, int correction, Motor &motor)
{
    Serial.print("orientation Val: ");
    Serial.println(correction);
    int rotatedGoal = goalAngle + correction;
    dribbler(255);
    if (rotatedGoal >= 360)
    {
        rotatedGoal -= 360;
    }
    if (rotatedGoal < 0)
    {
        rotatedGoal += 360;
    }
    if (!switches.lightgate())
    {
        return orbitAngle;
    }
    else
    {
        if (rotatedGoal > 180)
        {
            takeBackAngle = 225;
            if (rotatedGoal > 280)
            {
                takeBackAngle = -2;
                if (motor.spin(goalAngle))
                {
                    takeBackAngle = -1;
                }
            }
            Serial.print("takeback: ");
            Serial.println(takeBackAngle);
            return takeBackAngle;
        }
        else
        {
            takeBackAngle = 135;
            if (rotatedGoal < 80)
            {
                takeBackAngle = -2;
                if (motor.spin(goalAngle))
                {
                    takeBackAngle = -1;
                }
            }
            return takeBackAngle;
        }
    }
}

bool ESC::needTakeBack(int goalAngle, int ballAngle, int correction)
{
    int rotatedBall = ballAngle + correction;
    int rotatedGoal = goalAngle + correction;
    if (rotatedBall >= 360)
    {
        rotatedBall -= 360;
    }
    if (rotatedBall < 0)
    {
        rotatedBall += 360;
    }
    if (rotatedGoal >= 360)
    {
        rotatedGoal -= 360;
    }
    if (rotatedGoal < 0)
    {
        rotatedGoal += 360;
    }
    if(isTakeBack == true && switches.lightgate())
    {
            isTakeBack = true;
            return true;
    }
    if (((rotatedGoal > 60 && rotatedGoal < 90) || (rotatedGoal < 300 && rotatedGoal > 270)))
    {
        if (rotatedBall > 315 || rotatedBall < 45 || switches.lightgate())
        {
            isTakeBack = true;
            return true;
        }
    }
    isTakeBack = false;
    return false;
}
