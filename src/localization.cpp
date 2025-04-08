#include <localization.h>

Localization::Localization()
{
    fieldXDist = 170;
    fieldYDist = 225;
    fieldYDistWithGoal = 215;
    goalPos = 100;
    correctionThreshold = 20;
    cameraXCoord = -5;
    cameraYCoord = -5;
    robotX = -5;
    robotY = -5;
}
int Localization::getRobotX()
{
    return robotX;
}
int Localization::getRobotY()
{
    return robotY;
}
int* Localization::absoluteBallPos(int ballAngle, int ballDist)
{
    if (ballAngle == -5)
    {
        absolutePos[0] = -5;
        absolutePos[1] = -5;
        return absolutePos;
    }
    int x = robotX + sin(toRadians(ballAngle)) * ballDist;
    int y = robotY + cos(toRadians(ballAngle)) * ballDist;
    absolutePos[0] = x;
    absolutePos[1] = y;
    // Serial.print("BallX: ");
    // Serial.println(x);
    // Serial.print("BallY: ");
    // Serial.println(y);
    return absolutePos;
}
void Localization::offenseLocalization(double correction, int awayGoal, int homeGoal)
{
    getXUltrasonic(correction);
    cameraLocalization(homeGoal, awayGoal, correction);
    Serial.print("cameraX: ");
    Serial.println(cameraXCoord);
    Serial.print("cameraY: ");
    Serial.println(cameraYCoord);
    double weight = max(0, ((-0.015 * xUncertainty) + 1));
    if (correction > correctionThreshold || correction < (-1 * correctionThreshold))
    {
        weight = 0.6;
    }
    robotX = calculation.complimentaryFilterDistance(ultrasonicXCoord, cameraXCoord, weight);
    getYUltrasonic(correction);
    weight = max(0, ((-0.015 * yUncertainty) + 1));
    if (correction > correctionThreshold || correction < (-1 * correctionThreshold))
    {
        weight = 0.6;
    }
    if(cameraUncertainty == 1){
        weight = 1;
        if(yUncertainty >= 20){
            ultrasonicYCoord = prevYUltrasonic;
        }
    }
    robotY = calculation.complimentaryFilterDistance(ultrasonicYCoord, cameraYCoord, weight);
    Serial.print("RobotX: ");
    Serial.println(robotX);
    Serial.print("robotY: ");
    Serial.println(robotY);
}
void Localization::defenseLocalization(double correction, int awayGoal, int homeGoal)
{
    getXUltrasonic(correction);
    cameraLocalization(homeGoal, awayGoal, correction);
    Serial.print("cameraX: ");
    Serial.println(cameraXCoord);
    Serial.print("cameraY: ");
    Serial.println(cameraYCoord);
    double weight = max(0, ((-0.015 * xUncertainty) + 1));
    if (correction > correctionThreshold || correction < (-1 * correctionThreshold))
    {
        weight = 0;
    }
    robotX = calculation.complimentaryFilterDistance(ultrasonicXCoord, cameraXCoord, weight);
    getYUltrasonicDefense(correction);
    weight = 1;
    if (correction > correctionThreshold || correction < (-1 * correctionThreshold))
    {
        weight = 0;
        if(cameraUncertainty == 1){
            weight = 1;
            ultrasonicYCoord = prevYUltrasonic;
        }
    }

    robotY = calculation.complimentaryFilterDistance(ultrasonicYCoord, cameraYCoord, weight);
    Serial.print("RobotX: ");
    Serial.println(robotX);
    Serial.print("robotY: ");
    Serial.println(robotY);
}
void Localization::getXUltrasonic(double correction) // Range: -70 - +70
{
    if (allowRight && offsetx >= 10)
    {
        rightDist = ultrasonic.rightSensor();
        offsetx = 0;
        allowRight = false;
    }
    else if (offsetx >= 5)
    {
        leftDist = ultrasonic.leftSensor();
        allowRight = true;
    }
    int total = leftDist + rightDist;
    Serial.print("total: ");
    Serial.println(total);
    xUncertainty = fieldXDist - total;
    if (xUncertainty < 0)
    {
        xUncertainty = 0;
    }
    if(total > 1000){
        xUncertainty = 1;
    }
    if (correction <= correctionThreshold && correction >= (-1 * correctionThreshold)){
        ultrasonicXCoord = (leftDist - rightDist) / 2.0;
        if(xUncertainty < 20){
            prevXUltrasonic = ultrasonicXCoord;
        }
    }
}
void Localization::getYUltrasonic(double correction) // Range: -85 - +85
{
    if (allowFront && offsety >= 20)
    {
        frontDist = ultrasonic.frontSensor();
        offsety = 0;
        allowFront = false;
    }
    else if (offsety >= 10)
    {
        backDist = ultrasonic.backSensor();
        allowFront = true;
    }
    int total = backDist + frontDist;
    if (robotX <= -23 || robotX >= 23)
    {
        yUncertainty = fieldYDist - total;
    }
    else
    {
        yUncertainty = fieldYDistWithGoal - total;
    }
    if (yUncertainty < 0)
    {
        yUncertainty = 0;
    }
    if(total > 1000){
        yUncertainty = 1;
    }
    if (correction <= correctionThreshold && correction >= (-1 * correctionThreshold))
    {
        ultrasonicYCoord = (backDist - frontDist) / 2.0;
        if(yUncertainty < 20){
            prevYUltrasonic = ultrasonicYCoord;
        }
    }
}
void Localization::getYUltrasonicDefense(double correction) // Range: -85 - +85
{
    backDist = ultrasonic.backSensor();
    if (robotX <= -23 || robotX >= 23)
    {
        ultrasonicYCoord = (-1 * (fieldYDist / 2)) + backDist;
    }
    else
    {
        ultrasonicYCoord = (-1 * (fieldYDistWithGoal / 2)) + backDist;
    }
    if (correction <= correctionThreshold && correction >= (-1 * correctionThreshold)){
        prevYUltrasonic = ultrasonicYCoord;
    }
}
void Localization::cameraLocalization(int homeGoal, int awayGoal, int correction)
{
    
    if (homeGoal == -5 || (homeGoal < 90 || homeGoal > 270))
    {
        homeGoal = prevHomeGoal;
    }
    if (awayGoal == -5 || (awayGoal > 90 && awayGoal < 270))
    {
        awayGoal = prevAwayGoal;
    }
    int goalAngleDiff = abs(homeGoal-awayGoal);
    if(goalAngleDiff > 180){
        homeGoal = prevHomeGoal;
        awayGoal = prevAwayGoal;
        goalAngleDiff = abs(homeGoal-awayGoal);
    }
    awayGoal = calculation.complimentaryFilterAngle(awayGoal,prevAwayGoal,0.7);
    homeGoal = calculation.complimentaryFilterAngle(homeGoal,prevHomeGoal,0.7);
    prevAwayGoal = awayGoal;
    prevHomeGoal = homeGoal;
    homeGoal += correction;
    awayGoal += correction;
    if (homeGoal >= 360)
    {
        homeGoal -= 360;
    }
    else if (homeGoal < 0)
    {
        homeGoal += 360;
    }
    if (awayGoal >= 360)
    {
        awayGoal -= 360;
    }
    else if (awayGoal < 0)
    {
        awayGoal += 360;
    }
    double awaySlope = 1 / tan(toRadians(awayGoal));
    double homeSlope = 1 / tan(toRadians(homeGoal));
    int awayGoalPos = goalPos;
    int homeGoalPos = (-1 * goalPos)-5; // change this
    cameraXCoord = (homeGoalPos - awayGoalPos) / (awaySlope - homeSlope);

    if(goalAngleDiff > 148){
        cameraUncertainty = 1;
    }
    else{
        cameraUncertainty = 0;
    }
    cameraYCoord = (awaySlope * cameraXCoord) + awayGoalPos;
}
