#include <process.h>

Process::Process(int physicalRobot):roleSwitch(physicalRobot), motor(physicalRobot), orbit(physicalRobot)
{

}

void Process::general(int role)
{
    Serial.println("beign general");
    orientation = motor.getOrientation();
    calbiration.calState(motor, lineDetection);
    lineAngle = lineDetection.Process(calbiration.calVal, orientation, motor.initialOrientation);
    cam.CamCalc();
    motor.FindCorrection(motor.getOrientation(), motor.initialOrientation);
    if(role == 1){
        localization.offenseLocalization(motor.orientationVal, getAwayGoal(), getHomeGoal());
        motor.myPID.SetTunings(0.28, 0, 0.00005);
    }
    else{
        localization.defenseLocalization(motor.orientationVal,getAwayGoal(),getHomeGoal());
        motor.myPID.SetTunings(0.22,0,0);
    }
    // bluetooth.readData();
    // roleSwitch.background(cam.ball, cam.ballDistance, bluetooth.getRole(),bluetooth.getDistance(), bluetooth.getState());
    ballPos = localization.absoluteBallPos(cam.ball,cam.ballDistance);//run this only after localization
    // if(switches.start())
    //     bluetooth.sendData(*ballPos, *(ballPos+1), cam.ballDistance, roleSwitch.getOurRole());
    // if (cam.ball == -5)
    //     cam.ballNotFound(bluetooth.getXCoord(), bluetooth.getYCoord(),localization.getRobotX(), localization.getRobotY());
    if(role == 1){
        esc.runDribbler(cam.ball,cam.ballDistance,switches.lightgate());
    }
}
void Process::offense(double motorPower)
{
    goal.kickBackground();
    Serial.println("run general");
    general(1);
    // motorPower = motor.speedControl(cam.ballDistance,motorPower, 1);
    double offenseOrientation=0;
    if (lineDetection.linepresent && (lineDetection.Chord() > 0.2 || motorPower > 0.2))
    {
        motor.Move(lineAngle, 0.2, motor.initialOrientation);
    }
    else
    {
        if (cam.ball == -5)
            smoothMove(-1, lineAngle, 0.5, motor.initialOrientation);
        else
        {
            // if(esc.needTakeBack(getAwayGoal(),cam.ball, motor.orientationVal)){
            //     Serial.println("takeback: ");
            //     smoothMove(esc.takeBack(cam.ball,getAwayGoal(),orbit.CalculateRobotAngle(cam.ball, cam.ballDistance, cam.derivative, cam.sampleTime),motor.orientationVal, motor), lineAngle, 0.1, motor.initialOrientation);
            // }
            // else{
                double moveAngle = orbit.CalculateRobotAngle(cam.ball, cam.ballDistance, cam.derivative, cam.sampleTime);
                offenseOrientation = getOrientationOffense(moveAngle);
                smoothMove(moveAngle, lineAngle, motorPower, offenseOrientation);
                // motor.Move(orbit.CalculateRobotAngle(cam.ball, cam.ballDistance, cam.derivative, cam.sampleTime), motorPower, motor.initialOrientation);

            // }
        }
    }
    goal.kickAllowed(localization.getRobotY(), motor.orientationVal- offenseOrientation, getAwayGoal());
}

void Process::defense(double motorPower)
{
    general(0);
    goal.kickBackground();
    motorPower = motor.speedControl(cam.ballDistance,motorPower, 0);
    if (lineDetection.linepresent && (lineDetection.Chord() > 0.3 ))
    {
        motor.Move(lineAngle, motorPower, motor.initialOrientation);
    }
    else
    {
        if (cam.ball == -5)
        {
            // smoothMove(orbit.GetToPosition(0, -60, localization.getRobotX(), localization.getRobotY()), lineAngle, motorPower, motor.initialOrientation);
            motor.Stop();
        }
        else
        {
            // if(localization.getRobotY() > 0)
            //     smoothMove(180, lineAngle, motorPower, goalie.defenseOrientation(getHomeGoal(), orientation, motor.initialOrientation));
            // else
                smoothMove(goalie.defenseCalc(cam.ball, getHomeGoal(), cam.ballDistance, motor.orientationVal), lineAngle, motorPower, motor.initialOrientation);
        }
    }
}

void Process::smoothMove(int moveAngle, int lineAngle, double motorPower, int orientation)
{


    if (moveAngle == -1)
    {
        goal.kickAllowed(50, 0, 0);
        motor.Stop();
    }
    else if (lineDetection.linepresent)
    {
        motor.Move(calculation.projectionCalc(lineAngle, moveAngle), motorPower, orientation);
        // motor.Move(calculation.projectionCalc(lineAngle, moveAngle), 0.2, orientation);
    }
    else if(moveAngle >= 0)
    {
        motor.Move(moveAngle, motorPower, orientation);
    }
}

double Process::getAwayGoal()
{
    if (switches.switchSide())
        return cam.yellowGoal;
    else
        return cam.blueGoal;
}
double Process::getHomeGoal()
{
    if (switches.switchSide())
        return cam.blueGoal;
    else
        return cam.yellowGoal;
}
int Process::getOrientationOffense(double moveAngle)
{
    if (switches.lightgate() || (cam.ballDistance <= 25 && ((moveAngle > 0 && moveAngle < 10) || (moveAngle > 350 && moveAngle < 360))))
    {
        return goal.scoreOrientation(orientation, getAwayGoal(), motor.initialOrientation);
    }
    // int ballCheck = goal.ballAngleCheck(cam.ball, motor.initialOrientation, orientation);
    // if (cam.ballDistance < 60 && (ballCheck < 70 || ballCheck > 290))
    //     return goal.scoreOrientation(orientation, getAwayGoal(), motor.initialOrientation);
    else
        return goal.scoreOrientation(orientation, getAwayGoal(), motor.correction);
}
