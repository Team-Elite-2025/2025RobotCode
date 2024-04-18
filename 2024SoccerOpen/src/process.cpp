#include <process.h>

Process::Process()
{

}

void Process::offense(double motorPower){
    calbiration.calState();
            if (lineDetection.linepresent)
        {
            motor.Move(lineDetection.Process(calbiration.calVal), motorPower , motor.initialOrientation);
        }
        else
        {
            motor.Move(orbit.CalculateRobotAngle(cam.ball,cam.yellowGoal,cam.ballDistance), motorPower, motor.initialOrientation);
        }
}