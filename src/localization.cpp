#include <localization.h>

Localization::Localization(){
    fieldXDist = 170;
    fieldYDist = 225;
    fieldYDistWithGoal = 215;
    goalPos = 100;
    correctionThreshold = 0.25;
}
int Localization::getRobotX(){
    return robotX;
}
int Localization::getRobotY(){
    return robotY;
}
int* Localization::absoluteBallPos(int ballAngle, int ballDist){
    int absolutePos[2];
    if(ballAngle == -5){
        absolutePos[0] = -5;
        absolutePos[1] = -5;
        return absolutePos;
    }
    int x = robotX + sin(toRadians(ballAngle))*ballDist;
    int y = robotY + cos(toRadians(ballAngle))*ballDist;
    absolutePos[0] = x;
    absolutePos[1] = y;
    return absolutePos;
}
void Localization::offenseLocalization(double correction, int awayGoal, int homeGoal){
    // getXUltrasonic(correction);
    // cameraLocalization(awayGoal, homeGoal);
    // double weight = (-0.02*xUncertainty) + 1;
    // if(correction > correctionThreshold){
    //     weight = 0.6;
    // }
    // robotX = calculation.complimentaryFilter(ultrasonicXCoord,cameraXCoord, weight);
    getYUltrasonic(correction);
    Serial.print("YCoord: ");
    Serial.println(ultrasonicYCoord);
    // weight = (-0.02*yUncertainty) + 1;
    // if(correction > correctionThreshold){
    //     weight = 0.6;
    // }
    // robotY = calculation.complimentaryFilter(ultrasonicYCoord,cameraYCoord, weight);
}
void Localization::defenseLocalization(double correction, int awayGoal, int homeGoal){
    getXUltrasonic(correction);
    cameraLocalization(awayGoal, homeGoal);
    double weight = (-0.02*xUncertainty) + 1;
    if(correction > correctionThreshold){
        weight = 0;
    }
    robotX = calculation.complimentaryFilter(ultrasonicXCoord,cameraXCoord, weight);
    getYUltrasonicDefense(correction);
    weight = 1;
    if(correction > correctionThreshold){
        weight = 0;
    }
    robotY = calculation.complimentaryFilter(ultrasonicYCoord,cameraYCoord, weight);
}
void Localization::getXUltrasonic(double correction) // Range: -70 - +70
{
    if(allowRight && offsetx >= 10){
        rightDist = ultrasonic.rightSensor();
        offsetx = 0;
        allowRight = false;
    }
    else if(offsetx >= 5){
        leftDist = ultrasonic.leftSensor();
        allowRight = true;
    }
    int total = leftDist + rightDist;
    xUncertainty = total- fieldXDist;
    if(xUncertainty < 0){
        xUncertainty = 0;
    }
    if(correction <= correctionThreshold)
        ultrasonicXCoord = (leftDist - rightDist) / 2.0;
}
void Localization::getYUltrasonic(double correction) // Range: -85 - +85
{
    if(allowFront && offsety >= 20){
        frontDist = ultrasonic.frontSensor();
        offsety = 0;
        allowFront = false;
    }
    else if(offsety >= 10){
        backDist = ultrasonic.backSensor();
        allowFront = true;
    }
    int total = backDist + frontDist;
    if (robotX <= -23 || robotX >= 23)
    {
        yUncertainty = total - fieldYDist;
    }
    else
    {
        yUncertainty = total - fieldYDistWithGoal;
    }
    if(yUncertainty < 0){
        yUncertainty = 0;
    }
    if(correction <= correctionThreshold){
        ultrasonicYCoord = (backDist - frontDist) / 2.0;
    }
}
void Localization::getYUltrasonicDefense(double correction) // Range: -85 - +85
{
    backDist = ultrasonic.backSensor();
    if (robotX <= -23 || robotX >= 23)
    {
        ultrasonicYCoord = (-1*(fieldYDist/2)) + backDist;
    }
    else
    {
        ultrasonicYCoord = (-1*(fieldYDistWithGoal/2)) + backDist;
    }
}
void Localization::cameraLocalization(int homeGoal, int awayGoal){
    if(homeGoal == -5){
        homeGoal = prevHomeGoal;
    }
    if(awayGoal == -5){
        awayGoal = prevAwayGoal;
    }
    prevHomeGoal = homeGoal;
    prevAwayGoal = awayGoal;
    double awaySlope = 1/tan(toRadians(awayGoal));
    double homeSlope = 1/tan(toRadians(homeGoal));
    int awayGoalPos = goalPos;
    int homeGoalPos = -1*goalPos;
    cameraXCoord = (awayGoalPos-homeGoalPos)/(awaySlope-homeSlope);
    cameraYCoord = (awaySlope*cameraXCoord) + awayGoalPos;
}

