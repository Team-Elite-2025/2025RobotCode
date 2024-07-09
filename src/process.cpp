#include <process.h>

Process::Process()
{
}

void Process::general(int role)
{
    orientation = motor.getOrientation();
    calbiration.calState(motor, lineDetection);
    lineAngle = lineDetection.Process(calbiration.calVal, orientation, motor.initialOrientation);
    cam.CamCalc();
    motor.FindCorrection(motor.getOrientation(), motor.initialOrientation);
    if(role == 1){
        localization.offenseLocalization(motor.orientationVal, getAwayGoal(), getHomeGoal());
        motor.myPID.SetTunings(0.35, 0, 0.00005);
    }
    else{
        localization.defenseLocalization(motor.orientationVal,getAwayGoal(),getHomeGoal());
        motor.myPID.SetTunings(0.22,0,0);
    }
//     bluetooth.readData();
//     roleSwitch.background(cam.ballDistance, bluetooth.getRole(),bluetooth.getDistance(), bluetooth.getState());
    int* ballPos = localization.absoluteBallPos(cam.ball,cam.ballDistance);//run this only after localization
//     if(switches.start())
//         bluetooth.sendData(ballPos[0], ballPos[1], cam.ballDistance, roleSwitch.getOurRole());
//     if (cam.ball == -5)
//         cam.ballNotFound(bluetooth.getXCoord(), bluetooth.getYCoord(),localization.getRobotX(), localization.getRobotY());
}
void Process::offense(double motorPower)
{
    goal.kickBackground();
    general(1);
    if (lineDetection.linepresent && (lineDetection.Chord() > 0.8 || motorPower > 0.25))
    {
        motor.Move(lineAngle, motorPower, getOrientationOffense());
    }
    else
    {
        if (cam.ball == -5)
            smoothMove(orbit.GetToPosition(0, 0, localization.getRobotX(), localization.getRobotY()), lineAngle, motorPower, motor.initialOrientation);
        else
        {
            if((ballPos[0] >= 25 || ballPos[0] <= -25) && ballPos[1] > 80){
                smoothMove(esc.takeBack(cam.ball,getAwayGoal(),orbit.CalculateRobotAngle(cam.ball, getAwayGoal(), cam.ballDistance),switches.lightgate(),motor.orientationVal), lineAngle, 0.18, motor.initialOrientation);
            }
            else{
                smoothMove(orbit.CalculateRobotAngle(cam.ball, getAwayGoal(), cam.ballDistance), lineAngle, motorPower, getOrientationOffense());
                goal.kickAllowed(localization.getRobotY(), motor.orientationVal);
                esc.runDribbler(cam.ball,cam.ballDistance,switches.lightgate());
            }
        }
    }
}

void Process::defense(double motorPower)
{
    general(0);
    if ((lineDetection.linepresent && lineDetection.Chord() > 0.8) || lineDetection.outOfBounds)
    {
        motor.Move(lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
    }
    else
    {
        if (cam.ball == -5)
        {
            smoothMove(orbit.GetToPosition(0, -60, localization.getRobotX(), localization.getRobotY()), lineAngle, motorPower, motor.initialOrientation);
        }
        else
        {
            // if(localization.getRobotY() > 0)
            //     smoothMove(180, lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
            // else
                smoothMove(goalie.defenseCalc(cam.ball, getHomeGoal(), cam.ballDistance, motor.orientationVal), lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
        }
    }
}

void Process::smoothMove(int moveAngle, int lineAngle, double motorPower, int orientation)
{
    motorPower = motor.speedControl(cam.ballDistance,motorPower, moveAngle);

    if (moveAngle == -1)
    {
        goal.kickAllowed(localization.getRobotY(), 0);
        motor.Stop();
    }
    else if (lineDetection.linepresent)
    {
        motor.Move(calculation.projectionCalc(lineAngle, moveAngle), motorPower, orientation);
    }
    else if(moveAngle >= 0)
    {
        motor.Move(moveAngle, motorPower, orientation);
    }
}

double Process::getHomeGoal()
{
    if (switches.switchSide())
        return cam.yellowGoal;
    else
        return cam.blueGoal;
}
double Process::getAwayGoal()
{
    if (switches.switchSide())
        return cam.blueGoal;
    else
        return cam.yellowGoal;
}
int Process::getOrientationOffense()
{
    if (switches.lightgate())
    {
        return goal.scoreOrientation(orientation, getAwayGoal(), motor.initialOrientation);
    }
    int ballCheck = goal.ballAngleCheck(cam.ball, motor.initialOrientation, orientation);
    if (cam.ballDistance < 60 && (ballCheck < 70 || ballCheck > 290))
        return goal.scoreOrientation(orientation, getAwayGoal(), motor.initialOrientation);
    else
        return motor.initialOrientation;
}
