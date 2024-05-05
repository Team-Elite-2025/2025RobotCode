#include <lineDetection.h>
#include <math.h>
#include <trig.h>

LineDetection::LineDetection()
{
    // Constructor
    lineValues = new int[48];
    adc1.begin(0, 11, 12, 13);
    adc2.begin(1, 11, 12, 13);
    adc3.begin(26, 11, 12, 13);
    adc4.begin(27, 11, 12, 13);
    adc5.begin(14, 11, 12, 13);
    adc6.begin(15, 11, 12, 13);
    int counter = 0;
    for (int i = 22; i < 48; i++)
    {
        sensorAngles[i] = counter * 7.5;
        counter++;
    }
    for (int i = 0; i < 22; i++)
    {
        sensorAngles[i] = counter * 7.5;
        counter++;
    }
    for (int i = 0; i < 48; i++)
    {
        cosValues[i] = cos(toRadians(sensorAngles[i]));
        sinValues[i] = sin(toRadians(sensorAngles[i]));
    }
    initialAngle = -1;
    lineSwitch = false;
    outOfBounds = false;
}

int *LineDetection::GetValues()
{
    for (int i = 0; i < 48; i++)
    {
        int adcNumber = i / 8;
        int val = 0;
        int channel = i % 8;

        switch (adcNumber)
        {
        case (0):
            val = adc1.analogRead(channel);
            break;
        case (1):
            val = adc2.analogRead(channel);
            break;
        case (2):
            val = adc3.analogRead(channel);
            break;
        case (3):
            val = adc4.analogRead(channel);
            break;
        case (4):
            val = adc5.analogRead(channel);
            break;
        case (5):
            val = adc6.analogRead(channel);
            break;
        default:
            break;
        }
        lineValues[i] = val;
    }
    // for(int i = 0; i < 8; i++){
    //     Serial.print(i);
    //     Serial.print(": ");
    //     Serial.println(lineValues[i]);
    // }
    return lineValues;
};

double LineDetection::GetAngle(int *calibrateVal)
{
    lineValues = GetValues();
    linepresent = false;
    double totalCos = 0;
    double totalSin = 0;

    for (int i = 0; i < 48; i++)
    {
        if (lineValues[i] < calibrateVal[i] + 40)
        {
            lineValues[i] = 0;
            dotProduct[i] = 0;
        }
        else
        {
            lineValues[i] = 1;
            linepresent = true;
            dotProduct[i] = sensorAngles[i];
        }
    }

    double lowestDot = 2;
    int firstAngle = 0, secondAngle = 0;
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            if (dotProduct[i] != 0 && dotProduct[j] != 0)
            {
                double dot = (sinValues[i] * sinValues[j]) + (cosValues[i] * cosValues[j]);
                if (dot < lowestDot)
                {
                    lowestDot = dot;
                    firstAngle = i;
                    secondAngle = j;
                }
            }
        }
    }

    totalCos = cosValues[firstAngle] + cosValues[secondAngle];
    totalSin = sinValues[firstAngle] + sinValues[secondAngle];

    anglebisc = toDegrees(atan2(totalCos, totalSin));
    sensorAngle = abs(sensorAngles[firstAngle] - sensorAngles[secondAngle]);
    if (sensorAngle > 180)
    {
        sensorAngle = 360 - sensorAngle;
    }
    if (totalCos == 0 && totalSin == 0)
    {
        anglebisc = initialAngle;
    }
    if (anglebisc < 0)
        anglebisc = 360 + anglebisc;
    return anglebisc; // returns direction the line is in
}

double LineDetection::Chord()
{
    if (lineSwitch == true)
    {
        return 2 - (1 * sin(toRadians(sensorAngle / 2)));
    }
    return (1 * sin(toRadians(sensorAngle / 2)));
}

double LineDetection::Process(int *calibrateVal)
{
    // MAKE SURE YOU CALL THE PREVIOUS METHOD OTHERWISE NOTHING HAPPENS
    GetAngle(calibrateVal);
    if (linepresent == true)
    {

        if (initialAngle == -1)
        {
            initialAngle = anglebisc;
        }
        currentAngle = anglebisc;
        angleDiff = abs(currentAngle - initialAngle);
        initialAngle = currentAngle;
        if (angleDiff > 180)
        {
            angleDiff = 360 - angleDiff;
        }
        if (angleDiff > 100 && lineSwitch == false)
        {
            lineSwitch = true;
            angleDiff = 0;
        }
        if (lineSwitch == true)
        {
            avoidanceAngle = anglebisc;
            if (angleDiff > 100)
            {
                lineSwitch = false;
            }
        }
        if (lineSwitch == false)
        {
            avoidanceAngle = anglebisc + 180;
            if (avoidanceAngle > 360)
            {
                avoidanceAngle = avoidanceAngle - 360;
            }
        }
    }
    else if (linepresent == false)
    {
        initialAngle = -1;
        avoidanceAngle = -1;
        lineSwitch = false;
    }
    // Serial.print("line: ");
    // Serial.println(avoidanceAngle);
    return avoidanceAngle;
};