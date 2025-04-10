#include <calibration.h>
#include <Arduino.h>

Calibration::Calibration()
{
    calVal = new int[24];
    for (int i = 0; i < 24; i++)
    {
        calVal[i] = 50;
    }
}

void Calibration::calibrate(int *lineVal)
{

    for (int i = 0; i < 24; i++)
    {
        if (calVal[i] < lineVal[i])
        {
            calVal[i] = lineVal[i];
        }
    }
}

void Calibration::calState(Motor &motor, LineDetection &lineDetection)
{
    if (switches.calibration())
    {
        calibrate(lineDetection.GetValues());
        motor.RecordDirection();
        Serial.println("calibrating");

    }
}