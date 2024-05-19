#include <orbit.h>

Orbit::Orbit()
{
    inPos = false;
}

double Orbit::CalculateRobotAngle(double ballAngle, double goalAngle, double distance)
{

    distance = distance / 95;
    if(distance > 1){
        distance = 1;
    }
    distance = 1- distance;
    Serial.print("calculated distance: ");
    Serial.println(distance);
    double dampenVal = min(1, 0.02 * exp(5.45 * distance));
    Serial.print("dampen val: ");
    Serial.println(dampenVal);
    double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;
    double leftOrbitValue = min(90, 1.7 * exp(0.103 * newballAngle));
    double rightOrbitvalue = min(90, 0.001 * exp(0.19 * newballAngle)); // final
    // Serial.print("Orbit val before: ");
    // Serial.println(orbitvalue);
    // orbitvalue = orbitvalue * dampenVal;
    // Serial.print("Orbit val after: ");
    // Serial.println(orbitvalue);
    if(ballAngle<=180)
        robotAngle = ballAngle  + (rightOrbitvalue * dampenVal);
    else
        robotAngle = ballAngle + (-1* leftOrbitValue * dampenVal);
    if (robotAngle > 360)
    {
        robotAngle -= 360;
    }
    Serial.print("robot Angle: ");
    Serial.println(robotAngle);
    return robotAngle;
}

double Orbit::GetToPosition(int targetX, int targetY, int currentX, int currentY)
{

    int relativex = -1;
    int relativey = -1;
    relativex = targetX - currentX;
    relativey = targetY - currentY;
    double distance = sqrt(pow(relativex, 2) + pow(relativey, 2));
    if (distance <= 10)
    {
        return -1;
    }
    homeAngle = toDegrees(atan2(relativex, relativey));
    if (homeAngle < 0)
    {
        homeAngle = homeAngle + 360;
    }
    Serial.print("home Angle: ");
    Serial.println(homeAngle);
    return homeAngle;
}
