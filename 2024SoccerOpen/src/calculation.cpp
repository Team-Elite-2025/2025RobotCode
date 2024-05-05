#include <calculation.h>

Calculation::Calculation()
{
}
int Calculation::projectionCalc(int anglebisc, int robotAngle)
{
    int lineAngle = anglebisc + 90;
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