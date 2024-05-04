#include <process.h>

Process::Process()
{
}

void Process::offense(double motorPower)
{
    calbiration.calState(motor);
    double lineAngle = lineDetection.Process(calbiration.calVal);
    if (lineDetection.linepresent && lineDetection.Chord()>0.8)
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
        if(lineDetection.linepresent){
            motor.Move(motor.projectionCalc(lineAngle, orbit.CalculateRobotAngle(cam.ball, goal, cam.ballDistance)), motorPower, motor.initialOrientation);
        }
        else{
            motor.Move(orbit.CalculateRobotAngle(cam.ball, goal, cam.ballDistance), motorPower, motor.initialOrientation);
        }
    }
}