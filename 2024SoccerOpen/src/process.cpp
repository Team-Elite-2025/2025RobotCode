#include <process.h>

Process::Process()
{
}

void Process::offense(double motorPower)
{
    calbiration.calState(motor);
    goal.kickBackground();
    int lineAngle = lineDetection.Process(calbiration.calVal);
    if (lineDetection.linepresent && lineDetection.Chord() > 0.8)
    {
        motor.Move(lineAngle, motorPower, getOrientationOffense());
    }
    else
    {
        cam.CamCalc();
        if (cam.ball == -5)
            smoothMove(orbit.GetToPosition(0, 0), lineAngle, motorPower, motor.initialOrientation);
        else
        {
            goal.kickAllowed();
            smoothMove(orbit.CalculateRobotAngle(cam.ball, getGoal(), cam.ballDistance), lineAngle, motorPower, getOrientationOffense());
        }
    }
}

void Process::defense(double motorPower)
{
    calbiration.calState(motor);
    int lineAngle = lineDetection.Process(calbiration.calVal);
    if (lineDetection.linepresent && lineDetection.Chord() > 0.8)
    {
        motor.Move(lineAngle, motorPower, goalie.defenseOrientation(cam.ball, motor.getOrientation(), motor.initialOrientation));
    }
    else
    {
        cam.CamCalc();
        if (cam.ball = -5)
        {
            smoothMove(orbit.GetToPosition(0, -50), lineAngle, motorPower, motor.initialOrientation);
        }
        else
        {
            smoothMove(goalie.defenseCalc(cam.ball, getGoal()), lineAngle, motorPower, goalie.defenseOrientation(cam.ball, motor.getOrientation(), motor.initialOrientation));
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
double Process::getGoal()
{
    if (switches.switchSide())
        return cam.yellowGoal;
    else
        return cam.blueGoal;
}
int Process::getOrientationOffense()
{
    if (cam.ball < 45 || cam.ball > 315)
        return motor.initialOrientation;
    else
        return goal.scoreOrientation(motor.getOrientation(), getGoal(), motor.initialOrientation);
}
