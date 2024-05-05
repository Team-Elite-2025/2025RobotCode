#include <defense.h>

Defense::Defense()
{
}

int Defense::defenseCalc(int ballAngle, int goalAngle)
{
    angleDiff = abs(ballAngle - goalAngle);
    if (angleDiff > 180)
    {
        angleDiff = 360 - angleDiff;
    }
    if (angleDiff <= 180 && angleDiff > 168)
    {
        defenseAngle = -1;
    }
    else
    {

        robotAngleX = calculation.getX(ballAngle) + calculation.getX(goalAngle);
        robotAngleY = calculation.getY(ballAngle) + calculation.getY(goalAngle);

        defenseAngle = calculation.getAngle(robotAngleX, robotAngleY);
        if (defenseAngle > 270 || defenseAngle < 90)
        {
            defenseAngle = calculation.projectionCalc(0, defenseAngle);
        }
    }
    return defenseAngle;
}

int Defense::defenseOrientation(int ballAngle, int orientation, int initialOrientation)
{
    if (ballAngle > 180)
    {
        ballAngle -= 360;
    }
    theoreticalDir = orientation + ballAngle;
    if (theoreticalDir >= 360)
    {
        theoreticalDir -= 360;
    }
    else if (theoreticalDir < 0)
    {
        theoreticalDir += 360;
    }
    int diff = abs(initialOrientation - theoreticalDir);
    if (diff > 180)
    {
        diff = 360 - diff;
    }

    if (diff > 90)
    {
        return initialOrientation;
    }
    return theoreticalDir;
}
