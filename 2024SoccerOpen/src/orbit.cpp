#include <orbit.h>

Orbit::Orbit()
{
    inPos = false;
}

double Orbit::CalculateRobotAngle(double ballAngle, double goalAngle, double distance)
{

    distance = distance / 109;
    double dampenVal = min(1, 0.02 * exp(5.5 * distance));
    dampenVal = 1 - dampenVal;
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
    robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue * dampenVal);
    if (robotAngle > 360)
    {
        robotAngle -= 360;
    }
    Serial.print("robot Angle: ");
    Serial.println(robotAngle);
    return robotAngle;
}

double Orbit::GetToPosition(int x, int y)
{

    int relativex = -1;
    int relativey = -1;
    relativex = x - ultrasonic.getX();
    relativey = y - ultrasonic.getY();
    double distance = sqrt(pow(relativex, 2) + pow(relativey, 2));
    if (distance <= 5)
    {
        return -1;
    }
    homeAngle = toDegrees(atan2(relativex, relativey));
    if (homeAngle < 0)
    {
        homeAngle = homeAngle + 360;
    }
    return homeAngle;
}
