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
    if (angleDiff <= 180 && angleDiff > 160)
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
    Serial.print("defense Angle: ");
    Serial.println(defenseAngle);
    return defenseAngle;
}

int Defense::defenseOrientation(int goalAngle, int orientation, int initialOrientation)
{
    goalAngle = calculation.complimentaryFilterAngle(goalAngle, previousGoalAngle, 0.7);
    goalAngle += 180;
    if(goalAngle > 360){
        goalAngle -= 360;
    }
    if (goalAngle > 180)
    {
        goalAngle -= 360;
    }
    theoreticalDir = orientation + goalAngle;
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
    previousGoalAngle = goalAngle;
    return theoreticalDir;
}
