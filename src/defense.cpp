#include <defense.h>

Defense::Defense()
{
}

int Defense::defenseCalc(int ballAngle, int goalAngle, int ballDistance, int correction)
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
    angleThreshold = max(15, -0.18 * ballDistance + 40);
    angleThreshold = 180 - angleThreshold;
    angleDiff = abs(ballAngle - goalAngle);
    if (angleDiff > 180)
    {
        angleDiff = 360 - angleDiff;
    }
    if ((angleDiff <= 180 && angleDiff > angleThreshold) || (rotatedGoal < 115 && (rotatedBall > 115 && rotatedBall < 260)) || (rotatedGoal > 245 && (rotatedBall < 245 && rotatedBall > 100)))
    {
        if (angleDiff > 170 && hardStop <= 100)
        {
            defenseAngle += 180;
            if (defenseAngle >= 360)
            {
                defenseAngle -= 360;
            }
            else if (defenseAngle < 0)
            {
                defenseAngle += 360;
            }
        }
        else{
            hardStop = 200;
            defenseAngle = -1;
        }
    }
    else
    {
        hardStop = 0;
        robotAngleX = calculation.getX(ballAngle) + calculation.getX(goalAngle);
        robotAngleY = calculation.getY(ballAngle) + calculation.getY(goalAngle);

        defenseAngle = calculation.getAngle(robotAngleX, robotAngleY);
        int updatedHorizontal = 180 + (-1* correction);
        if (updatedHorizontal >= 360)
        {
            updatedHorizontal -= 360;
        }
        else if (updatedHorizontal < 0)
        {
            updatedHorizontal += 360;
        }
        defenseAngle = calculation.projectionCalc(updatedHorizontal, defenseAngle);
    }
    Serial.print("defense Angle: ");
    Serial.println(defenseAngle);
    return defenseAngle;
}

int Defense::defenseOrientation(int goalAngle, int orientation, int initialOrientation)
{
    if (goalAngle > 270 || goalAngle < 90)
    {
        return previousGoalAngle;
    }
    goalAngle += 180;
    if (goalAngle > 360)
    {
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
    if (defenseAngle != -1)
    {
        theoreticalDir = calculation.complimentaryFilterAngle(theoreticalDir, previousGoalAngle, 0.5);
        previousGoalAngle = theoreticalDir;
    }
    Serial.println("Defense orientation: ");
    Serial.println(theoreticalDir);
    return theoreticalDir;
}
