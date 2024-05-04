#include <orbit.h>

Orbit::Orbit()
{
    inPos = false;
}

double Orbit::CalculateRobotAngle(double ballAngle, double goalAngle, double distance)
{

        distance = distance/109;
        double dampenVal = min(1, 0.02 * exp(5.5 * distance));
        dampenVal = 1-dampenVal;
        // Serial.print("dampen val: ");
        // Serial.println(dampenVal);
        double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;
        // Serial.print("ballangle : ");
        // Serial.println(newballAngle);
        if (goalAngle == -5)
        {
            goalAngle = 0;
        }
        if (goalAngle > 180)
        {
            goalAngle = 360 - goalAngle;
        }

        multiplier = 0.05 * (goalAngle) + 1;
        double orbitvalue = min(90, 0.04 * exp(0.15 * newballAngle));
        // Serial.print("Orbit val before: ");
        // Serial.println(orbitvalue);
        // orbitvalue = orbitvalue * dampenVal;
        // Serial.print("Orbit val after: ");
        // Serial.println(orbitvalue);
        robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue*dampenVal);
        if (robotAngle > 360)
        {
            robotAngle -= 360;
        }
        Serial.print("robot Angle: ");
        Serial.println(robotAngle);
        return robotAngle;
    
}

double Orbit::GetToSpinShotPosition(bool linePresent, int goalAngle, int lineAngle)
{
// Serial.print("Orbit Line: ");
// Serial.println(lineAngle);
    // get to shooting position
    if(goalAngle == -5){
        return 0;
    }
    else if (goalAngle < 180)
    {
        double robotAngle;
        if (!linePresent)
        {
            inPos = false;
        }
        if (goalAngle > 30)
        {
            robotAngle = 91;
        }
        else if (goalAngle < 20)
        {
            robotAngle = 271;
        }

        else if (linePresent == false)
        {
            robotAngle = 25;
        }
        else if(lineAngle <45 || lineAngle>315)
        {
            inPos = true;
        }
        else{
            robotAngle = 0;
        }

        return robotAngle;
    }
    else
    {
        double robotAngle;
        if (!linePresent)
        {
            inPos = false;
        }
        if (goalAngle > 325)
        {
            robotAngle = 89;
        }
        else if (goalAngle < 315)
        {
            robotAngle = 269;
        }

        else if (linePresent == false)
        {
            robotAngle = 320;
        }
        else if(lineAngle <45 || lineAngle>315)
        {
            inPos = true;
        }
        else{
            robotAngle = 0;
        }

        return robotAngle;
    }
}

double Orbit::InOrientationSpinShot(double robotOrientation, int initialOrientation, double goalAngle)
{
    if (goalAngle < 180)
    {
        double orientation = initialOrientation + 40;
        if (orientation > 360)
        {
            orientation = orientation - 360;
        }
        double orientationVal = 0;
        orientationVal = abs(orientation - robotOrientation);

        // Serial.println(orientationVal);
        if (orientationVal > 180)
        {
            orientationVal = 360 - orientationVal;
        }
        if (robotOrientation < 180 && orientation > 180)
        {
            orientation = -1 * (360 - orientation);
        }
        else if (robotOrientation > 180 && orientation < 180)
        {
            orientation = (orientation + 360);
        }
        if (orientation < robotOrientation)
        {
            orientationVal = -1 * orientationVal;
        }
        if (orientationVal > -5 && orientationVal < 0)
        {
            orientationVal = 0;
            inOrientation = true;
        }
        else if (orientationVal < 5 && orientationVal > 0)
        {
            orientationVal = 0;
            inOrientation = true;
        }
        return orientationVal;
    }
    else
    {
              double orientation = initialOrientation - 40;
        if (orientation < 0)
        {
            orientation = orientation + 360;
        }
        double orientationVal = 0;
        orientationVal = abs(orientation - robotOrientation);

        // Serial.println(orientationVal);
        if (orientationVal > 180)
        {
            orientationVal = 360 - orientationVal;
        }
        if (robotOrientation < 180 && orientation > 180)
        {
            orientation = -1 * (360 - orientation);
        }
        else if (robotOrientation > 180 && orientation < 180)
        {
            orientation = (orientation + 360);
        }
        if (orientation < robotOrientation)
        {
            orientationVal = -1 * orientationVal;
        }
        if (orientationVal > -5 && orientationVal < 0)
        {
            orientationVal = 0;
            inOrientation = true;
        }
        else if (orientationVal < 5 && orientationVal > 0)
        {
            orientationVal = 0;
            inOrientation = true;
        }
        return orientationVal;
    }
}

double Orbit::GetToHomePositionOffense(double goalDistance, double goalAngle, bool disappear)
{
    if (!disappear)
    {
        return -1;
    }
    if (goalAngle == -5)
    {
        return 180;
    }

    if (goalAngle > 185)
    {
        xcomp = -1;
    }
    else if (goalAngle < 175)
    {
        xcomp = 1;
    }
    else
    {
        xcomp = 0;
    }

    if (goalDistance > 70)
    {
        ycomp = -1;
    }
    else if (goalDistance < 60)
    {
        ycomp = 1;
    }
    else
    {
        ycomp = 0;
    }
    if (xcomp == 0 && ycomp == 0)
        return -2;
    homeAngle = toDegrees(atan2(xcomp, ycomp));
    if (homeAngle < 0)
    {

        homeAngle = homeAngle + 360;
    }
    return homeAngle;
}
