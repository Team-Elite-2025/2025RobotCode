#include <orbit.h>

Orbit::Orbit()
{
    kd = 0.1;
    inPos = false;
    SampleTime = 34;
    lastTime = millis() - SampleTime;
    double SampleTimeInSec = ((double)SampleTime)/1000;
    kd = kd / SampleTimeInSec;
}

double Orbit::CalculateRobotAngle(double ballAngle, double goalAngle, double distance)
{
    now = millis();
    unsigned long timeChange = (now - lastTime);

    if (timeChange >= SampleTime)
    {

        double dInput = sin(toRadians(ballAngle)) - sin(toRadians(lastAngle));
        derivative = -1*(kd*dInput);
        Serial.print("Derivative: ");
        Serial.println(derivative);


        distance = distance / 150;
        if (distance > 1)
        {
            distance = 1;
        }
        distance = 1 - distance;
        // Serial.print("calculated distance: ");
        // Serial.println(distance);
        double dampenVal = min(1, 0.025 * exp(4.5 * distance));
        // Serial.print("dampen val: ");
        // Serial.println(dampenVal);

        double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;
        double orbitValue;
        if (ballAngle >= 180)
            orbitValue = min(90, 7.5 * exp(0.042 * newballAngle));
        else
        {
            orbitValue = min(90, 7.5 * exp(0.042 * newballAngle));
        }
        if (newballAngle < 20)
        {
            orbitValue = 0;
        }
        // Serial.print("Orbit val before: ");
        // Serial.println(orbitvalue);
        // orbitvalue = orbitvalue * dampenVal;
        // Serial.print("Orbit val after: ");
        // Serial.println(orbitvalue);
        robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitValue * dampenVal);
        if (robotAngle > 360)
        {
            robotAngle -= 360;
        }
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
    if (distance <= 15)
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
