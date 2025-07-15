#include <goal.h>
Goal::Goal()
{
    kickerPin = 30;
    pinMode(kickerPin, OUTPUT);
    kickHold = 1000;
    previousScoreAngle = -1;
}
int Goal::ballAngleCheck(int ballAngle, int initialOrientation, int orientation){

    int angleDiff = abs(orientation - initialOrientation);
    bool obtuse = false;
    if (angleDiff > 180)
    {
        angleDiff = 360 - angleDiff;
        obtuse = true;
    }
    if (obtuse && initialOrientation < 180 && orientation > 180)
    {
        orientation = -1 * (360 - orientation);
    }
    else if (obtuse && initialOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    if (orientation < initialOrientation)
    {
        angleDiff = -1 * angleDiff;
    }


    ballAngle += angleDiff;
    if(ballAngle >= 360){
        ballAngle -= 360;
    }
    if(ballAngle < 0){
        ballAngle += 360;
    }
    // Serial.print("calculated ballAngle: ");
    // Serial.println(ballAngle);
    return ballAngle;
}
int Goal::scoreOrientation(int orientation, int goalAngle, int initialOrientation)
{
    if (goalAngle == -5)
    {
        return initialOrientation;
    }
    else
    {
        // goalAngle = -1 * goalAngle;

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

    goalAngle = calculation.complimentaryFilterAngle(goalAngle, previousScoreAngle, 0.8);
    previousScoreAngle = goalAngle;
    Serial.print("Goal Orientation: ");
    Serial.println(goalAngle);
    return goalAngle;
}

void Goal::kick()
{
    if (timer > (kickHold + 2000))
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
void Goal::kickAllowed(int y, int correction, int goalAngle)
{
    if (switches.lightgate() && ((goalAngle > 350 && goalAngle < 360) || (goalAngle < 10 && goalAngle > 0)))
    {
        kick();
    }
}
