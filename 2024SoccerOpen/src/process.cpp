#include <process.h>

Process::Process()
{
}

void Process::offense(double motorPower)
{
    calbiration.calState(motor, lineDetection);
    goal.kickBackground();
    ultrasonic.localization(motor.correction);
    int lineAngle = lineDetection.Process(calbiration.calVal);

    if ((lineDetection.linepresent && lineDetection.Chord() > 0.8) || lineDetection.outOfBounds)
    {
        motor.Move(lineAngle, motorPower, getOrientationOffense());
    }
    else
    {
        cam.CamCalc();
        if (cam.ball == -5)
            smoothMove(orbit.GetToPosition(0, 0, ultrasonic.getXCoordinate(), ultrasonic.getYCoordinate()), lineAngle, motorPower, motor.initialOrientation);
        else
        {
            goal.kickAllowed(ultrasonic.getYCoordinate());
            smoothMove(orbit.CalculateRobotAngle(cam.ball, getGoal(), cam.ballDistance), lineAngle, motorPower, getOrientationOffense());
        }
    }
}

void Process::defense(double motorPower)
{
    calbiration.calState(motor, lineDetection);
    int lineAngle = lineDetection.Process(calbiration.calVal);
    ultrasonic.localizationDefense(motor.correction);
    Serial.println(lineDetection.outOfBounds);
    if ((lineDetection.linepresent && lineDetection.Chord() > 0.8) || lineDetection.outOfBounds)
    {
        motor.Move(lineAngle, motorPower, goalie.defenseOrientation(cam.ball, motor.getOrientation(), motor.initialOrientation));
    }
    else
    {
        cam.CamCalc();
        if (cam.ball == -5)
        {
            smoothMove(orbit.GetToPosition(0, 40, ultrasonic.getXCoordinate(), ultrasonic.getYCoordinateDefense()), lineAngle, motorPower, motor.initialOrientation);
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
    if(switches.lightgate()){
        return goal.scoreOrientation(motor.getOrientation(), getGoal(), motor.initialOrientation);
    }
    if (ultrasonic.frontSensor() < 80 && (cam.ball < 70 || cam.ball > 290) && cam.ballDistance < 45)
        return goal.scoreOrientation(motor.getOrientation(), getGoal(), motor.initialOrientation);
    else
        return motor.initialOrientation;
}
