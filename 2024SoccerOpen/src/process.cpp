#include <process.h>

Process::Process()
{
}

void Process::offense(double motorPower)
{
    calbiration.calState(motor);
    double lineAngle = lineDetection.Process(calbiration.calVal);
    if (lineDetection.linepresent)
    {
        motor.Move(lineAngle, motorPower, motor.initialOrientation);
    }
    else
    {
        cam.CamCalc();
        if (switches.switchSide())
        {
            goal = cam.yellowGoal;
        }
        else
        {
            goal = cam.blueGoal;
        }
        motor.Move(orbit.CalculateRobotAngle(cam.ball, goal, cam.ballDistance), motorPower, motor.initialOrientation);
    }
}