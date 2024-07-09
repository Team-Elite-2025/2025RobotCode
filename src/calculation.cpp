#include <calculation.h>

Calculation::Calculation()
{
}
int Calculation::projectionCalc(int anglebisc, int robotAngle)
{
    int lineAngle = anglebisc + 180;
    if (lineAngle >= 360)
    {
        lineAngle = lineAngle - 360;
    }
    int angleDiff = abs(robotAngle-lineAngle);
    if (angleDiff > 180)
    {
        angleDiff = 360 - angleDiff;
    }
    if(angleDiff > 90){
        return robotAngle;
    }
    lineAngle = anglebisc + 90;
    if (lineAngle > 360)
    {
        lineAngle = lineAngle - 360;
    }
    vectorX = getX(lineAngle);
    vectorY = getY(lineAngle);
    robotAngleX = getX(robotAngle);
    robotAngleY = getY(robotAngle);
    dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
    denominator = pow(vectorX, 2) + pow(vectorY, 2);
    robotAngleX = (dotProduct / denominator) * vectorX;
    robotAngleY = (dotProduct / denominator) * vectorY;

    return getAngle(robotAngleX, robotAngleY);
}
double Calculation::getAngle(double x, double y)
{
    double angle = toDegrees(atan2(x, y));
    if (angle < 0)
    {
        angle = angle + 360;
    }
    return angle;
}
double Calculation::getX(int angle)
{
    return sin(toRadians(angle));
}
double Calculation::getY(int angle)
{
    return cos(toRadians(angle));
}
int Calculation::complimentaryFilterAngle(int angle, int prevAngle, double weight)
{
    angleDiff = abs(angle - prevAngle);
    if(angleDiff >= 180){
        angleDiff = 360-angleDiff;
        if(angle > prevAngle)
            angle = prevAngle - angleDiff;
        else
            angle = prevAngle + angleDiff;
    }

    int weightedValue = ((weight * angle) + ((1-weight) * prevAngle));
    if(weightedValue >= 360){
        weightedValue -= 360;
    }
    else if(weightedValue < 0){
        weightedValue += 360;
    }
    return weightedValue;
}
int Calculation::complimentaryFilterDistance(int currentDist, int prevDist, double weight)
{
    angleDiff = abs(currentDist - prevDist);
    if(angleDiff >= 180){
        angleDiff = 360-angleDiff;
        if(currentDist > prevDist)
            currentDist = prevDist - angleDiff;
        else
            currentDist = prevDist + angleDiff;
    }

    int weightedValue = ((weight * currentDist) + ((1-weight) * prevDist));
    return weightedValue;
}