#include <process.h>

Process::Process()
{
}

void Process::general()
{
    orientation = motor.getOrientation();
    if (!switches.start())
        lineDetection.lineSwitch = false;
    calbiration.calState(motor, lineDetection);
    lineAngle = lineDetection.Process(calbiration.calVal, orientation, motor.initialOrientation);
    cam.CamCalc();
    bluetooth.readData();
    roleSwitch.background(cam.ballDistance, bluetooth.getRole(),bluetooth.getDistance());
    int* ballPos = localization.absoluteBallPos(cam.ball,cam.ballDistance);//run this only after localization
    bluetooth.sendData(ballPos[0], ballPos[1], cam.ballDistance, roleSwitch.getOurRole());
    if (cam.ball == -5)
        cam.ballNotFound(bluetooth.getXCoord(), bluetooth.getYCoord(),localization.getRobotX(), localization.getRobotY());
}
void Process::offense(double motorPower)
{
    goal.kickBackground();
    localization.offenseLocalization(motor.correction, getAwayGoal(), getHomeGoal());
    // general();
    // if ((lineDetection.linepresent && lineDetection.Chord() > 0.8) || lineDetection.outOfBounds)
    // {
    //     motor.Move(lineAngle, motorPower, getOrientationOffense());
    // }
    // else
    // {
    //     if (cam.ball == -5)
    //         smoothMove(orbit.GetToPosition(0, 0, localization.getRobotX(), localization.getRobotY()), lineAngle, motorPower, motor.initialOrientation);
    //     else
    //     {
    //         // goal.kickAllowed(localization.getRobotY());
    //         smoothMove(orbit.CalculateRobotAngle(cam.ball, getAwayGoal(), cam.ballDistance), lineAngle, motorPower, getOrientationOffense());
    //     }
    // }
}

void Process::defense(double motorPower)
{
    localization.defenseLocalization(motor.correction,getAwayGoal(),getHomeGoal());
    general();

    if ((lineDetection.linepresent && lineDetection.Chord() > 0.8) || lineDetection.outOfBounds)
    {
        motor.Move(lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
    }
    else
    {
        if (cam.ball == -5)
        {
            smoothMove(orbit.GetToPosition(0, -70, localization.getRobotX(), localization.getRobotY()), lineAngle, motorPower, motor.initialOrientation);
        }
        else
        {
            if(localization.getRobotY() > -20)
                smoothMove(180, lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
            else
                smoothMove(goalie.defenseCalc(cam.ball, getHomeGoal()), lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
        }
    }
}

void Process::smoothMove(int moveAngle, int lineAngle, double motorPower, int orientation)
{

    if (moveAngle == -1)
    {
        motor.Stop();
    }
    else if (lineDetection.linepresent)
    {
        motor.Move(calculation.projectionCalc(lineAngle, moveAngle), motorPower, orientation);
    }
    else
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
    if (cam.ballDistance < 45 && (ballCheck < 70 || ballCheck > 290))
        return goal.scoreOrientation(orientation, getAwayGoal(), motor.initialOrientation);
    else
        return motor.initialOrientation;
}
