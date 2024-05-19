#include <Goal.h>
Goal::Goal()
{
    kickerPin = 30;
    pinMode(kickerPin, OUTPUT);
    kickHold = 1000;
}

int Goal::scoreOrientation(int orientation, int goalAngle, int initialOrientation)
{
    if (goalAngle == -5)
    {
        return previousScoreAngle;
    }
    else
    {
        if (goalAngle > 180)
            goalAngle -= 360;

        if (goalAngle <= 5 && goalAngle >= -5)
            goalAngle = 0;

        goalAngle += orientation;

        if (goalAngle >= 360)
            goalAngle -= 360;

        else if (goalAngle < 0)
            goalAngle += 360;
    }

    goalAngle = complimentaryFilter(goalAngle, previousScoreAngle);
    previousScoreAngle = goalAngle;
    Serial.print("Goal Orientation: ");
    Serial.println(goalAngle);
    return goalAngle;
}

void Goal::kick()
{
    if (timer > (kickHold + 20000))
    {
        timer = 0;
    }
    if (timer <= kickHold)
    {
        digitalWrite(kickerPin, HIGH);
    }
    else
    {
        digitalWrite(kickerPin, LOW);
    }
    active = 0;
}
void Goal::kickBackground()
{
    if (active > 2 && timer > kickHold)
    {
        digitalWrite(kickerPin, LOW);
    }
}
void Goal::kickAllowed(int y)
{
    if (switches.lightgate() && y > 20)
    {
        kick();
    }
}

int Goal::complimentaryFilter(int angle, int prevAngle)
{
    angleDiff = abs(angle - prevAngle);
    if(angleDiff >= 180){
        angleDiff = 360-angleDiff;
        if(angle > prevAngle)
            angle = prevAngle - angleDiff;
        else
            angle = prevAngle + angleDiff;
    }

    int weightedValue = ((0.95 * angle) + (0.05 * prevAngle));
    if(weightedValue >= 360)
        weightedValue -= 360;
    if(weightedValue < 0){
        weightedValue += 360;
    }
    return weightedValue;
}