#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

Motor::Motor()
{
    // corresponding pin values on teensy
    pinspeedRL = 2;
    pinspeedRR = 3;
    pinspeedFL = 4;
    pinspeedFR = 5;

    pincontrolRLA = 22;
    pincontrolRRA = 20;
    pincontrolFLA = 18;
    pincontrolFRA = 9;

    pincontrolRLB = 23;
    pincontrolRRB = 21;
    pincontrolFLB = 19;
    pincontrolFRB = 10;

    defenseStop = false;

    pinMode(pinspeedFR, OUTPUT);
    pinMode(pinspeedFL, OUTPUT);
    pinMode(pinspeedRR, OUTPUT);
    pinMode(pinspeedRL, OUTPUT);
    pinMode(pincontrolFLA, OUTPUT);
    pinMode(pincontrolFRA, OUTPUT);
    pinMode(pincontrolRRA, OUTPUT);
    pinMode(pincontrolRLA, OUTPUT);
    pinMode(pincontrolFLB, OUTPUT);
    pinMode(pincontrolFRB, OUTPUT);
    pinMode(pincontrolRRB, OUTPUT);
    pinMode(pincontrolRLB, OUTPUT);
    max_power = 0;
    RecordDirection();
};

void Motor::Process(double intended_angle, double motor_power, double lineAngle, double robotOrientation, Orbit &orbit, bool backGate, int goalAngle, double Chord, bool linePresent, int anglebisc, double homeAngle, int ballDistance, int ballAngle, bool defense)
{
    Move(intended_angle,motor_power,initialOrientation);
}

int Motor::projectionCalc(int anglebisc, int robotAngle)
{

    int lineAngle = anglebisc + 90;
    if (lineAngle > 360)
    {
        lineAngle = lineAngle - 360;
    }
    vectorX = sin(toRadians(lineAngle));
    vectorY = cos(toRadians(lineAngle));
    robotAngleX = sin(toRadians(robotAngle));
    robotAngleY = cos(toRadians(robotAngle));
    dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
    denominator = pow(vectorX, 2) + pow(vectorY, 2);
    robotAngleX = (dotProduct / denominator) * vectorX;
    robotAngleY = (dotProduct / denominator) * vectorY;

    double projectionAngle = toDegrees(atan2(robotAngleX, robotAngleY));
    if (projectionAngle < 0)
    {
        projectionAngle = projectionAngle + 360;
    }
    return projectionAngle;
}
void Motor::Move(double intended_angle, double motor_power, double robotOrientation)
{
    speedRR = 0;
    speedRL = 0;
    speedFL = 0;
    speedFR = 0;
    controlRR = 0;
    controlFR = 0;
    controlFL = 0;
    controlRL = 0;

    powerFR = sin(toRadians(intended_angle - 45));
    powerRR = sin(toRadians(intended_angle - 135));
    powerRL = sin(toRadians(intended_angle - 225));
    powerFL = sin(toRadians(intended_angle - 315));
    // find max_power among motors to scale
    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));


    FindCorrection(compassSensor.getOrientation(), robotOrientation);
    // add correction to account for rotation needed


    // Serial.println(powerFR);
    // Serial.println(powerFL);
    // Serial.println(powerRR);
    // Serial.println(powerRL);
    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    powerFR += correction;
    powerFL += correction;
    powerRR += correction;
    powerRL += correction;

    controlRL = powerRL < 0 ? LOW : HIGH;
    controlRR = powerRR > 0 ? LOW : HIGH;
    controlFL = powerFL < 0 ? LOW : HIGH;
    controlFR = powerFR > 0 ? LOW : HIGH;

    if(controlRL == LOW){
        controlRLA == LOW;
        controlRLB == HIGH;
    }
    if(controlRR == LOW){
        controlRRA == LOW;
        controlRRB == HIGH;
    }
    if(controlFL == LOW){
        controlFLA == LOW;
        controlFLB == HIGH;
    }
    if(controlFL == LOW){
        controlFLA == LOW;
        controlFLB == HIGH;
    }

    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));

    speedFR = abs(powerFR) / max_power;
    speedFL = abs(powerFL) / max_power;
    speedRR = abs(powerRR) / max_power;
    speedRL = abs(powerRL) / max_power;

    int multiplier = 255;
    int intspeedFR = (int)((speedFR * multiplier) * motor_power);
    int intspeedFL = (int)((speedFL * multiplier) * motor_power);
    int intspeedRR = (int)((speedRR * multiplier) * motor_power);
    int intspeedRL = (int)((speedRL * multiplier) * motor_power);

    int motor_switch = 0;
    motor_switch = digitalRead(38);
    if (defenseStop)
    {
        Stop();
    }
    else if (motor_switch == HIGH)
    {
        analogWrite(pinspeedFR, intspeedFR);
        analogWrite(pinspeedFL, intspeedFL);
        analogWrite(pinspeedRR, intspeedRR);
        analogWrite(pinspeedRL, intspeedRL);
        digitalWrite(pincontrolFLA, controlFLA);
        digitalWrite(pincontrolFLB, controlFLB);
        digitalWrite(pincontrolFRA, controlFRA);
        digitalWrite(pincontrolFRB, controlFRB);
        digitalWrite(pincontrolRRA, controlRRA);
        digitalWrite(pincontrolRRB, controlRRB);
        digitalWrite(pincontrolRLA, controlRLA);
        digitalWrite(pincontrolRLB, controlRLB);
    }
    else
    {
        Stop();
    }
}

void Motor::Stop()
{
    analogWrite(pinspeedFR, 0);
    analogWrite(pinspeedFL, 0);
    analogWrite(pinspeedRL, 0);
    analogWrite(pinspeedRR, 0);
}
double Motor::RecordDirection()
{
    if (digitalRead(36) == LOW)
    {
        initialOrientation = compassSensor.getOrientation();
    }
    return initialOrientation;
}

double Motor::getOrientation()
{
    return compassSensor.getOrientation();
}

double Motor::FindCorrection(double orientation, double robotOrientation)
{

    orientationVal = abs(orientation - robotOrientation);

    // Serial.println(orientationVal);
    if (orientationVal > 180)
    {
        orientationVal = 360 - orientationVal;
    }
    if (robotOrientation < 180 && orientation > 180)
    {
        orientation = -1 * (360 - orientation);
    }
    else if (robotOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    if (orientation < robotOrientation)
    {
        orientationVal = -1 * orientationVal;
    }

    correction = -1 * (sin(toRadians(orientationVal)));
    correction *= 0.55;

    if (orientationVal > -5 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 5 && orientationVal > 0)
    {
        correction = 0;
    }
    else if (orientationVal > 90)
    {
        correction = -1;
    }
    else if (orientationVal < -90)
    {
        correction = 1;
    }

    Serial.println("Correction : ");
    Serial.println(correction);

    return correction;
}

void Motor::Spin(double speed, int direction)
{
    Serial.println("hello");
    speed *= 255;
    if (digitalRead(39) == HIGH)
    {
        controlRL = direction < 0 ? LOW : HIGH;
        controlRR = direction > 0 ? LOW : HIGH;
        controlFL = direction < 0 ? LOW : HIGH;
        controlFR = direction > 0 ? LOW : HIGH;
        analogWrite(pinspeedFR, speed);
        analogWrite(pinspeedFL, speed);
        analogWrite(pinspeedRR, speed);
        analogWrite(pinspeedRL, speed);
        digitalWrite(pincontrolFLA, controlFLA);
        digitalWrite(pincontrolFLB, controlFLB);
        digitalWrite(pincontrolFRA, controlFRA);
        digitalWrite(pincontrolFRB, controlFRB);
        digitalWrite(pincontrolRRA, controlRRA);
        digitalWrite(pincontrolRRB, controlRRB);
        digitalWrite(pincontrolRLA, controlRLA);
        digitalWrite(pincontrolRLB, controlRLB);
    }
    else
    {
        Stop();
    }
}

void Motor::FinalSpin(double speed, int direction)
{
    speed *= 255;
    if (digitalRead(39) == HIGH)
    {
        controlRL = direction < 0 ? LOW : HIGH;
        controlRR = direction > 0 ? LOW : HIGH;
        controlFL = direction < 0 ? LOW : HIGH;
        controlFR = direction > 0 ? LOW : HIGH;
        analogWrite(pinspeedFR, speed);
        analogWrite(pinspeedFL, speed);
        analogWrite(pinspeedRR, speed);
        analogWrite(pinspeedRL, speed);
        digitalWrite(pincontrolFLA, controlFLA);
        digitalWrite(pincontrolFLB, controlFLB);
        digitalWrite(pincontrolFRA, controlFRA);
        digitalWrite(pincontrolFRB, controlFRB);
        digitalWrite(pincontrolRRA, controlRRA);
        digitalWrite(pincontrolRRB, controlRRB);
        digitalWrite(pincontrolRLA, controlRLA);
        digitalWrite(pincontrolRLB, controlRLB);
        delay(300);
        Stop();
        delay(1000);
    }
    else
    {
        Stop();
    }
}

double Motor::slowDown(int ballDistance, int ballAngle, double motorPower){
    if(ballAngle<195 && ballAngle>165 && ballDistance < 20){
        return 0.36;
    }
    else{
        return motorPower;
    }
}
