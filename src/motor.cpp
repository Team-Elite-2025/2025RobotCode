#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

Motor::Motor(int robotNum) : myPID(&Input, &Output, &Setpoint, .35, 0, 0.00005, REVERSE)
{
    physicalRobot = robotNum;
    // corresponding pin values on teensy
    if (robotNum == 0)
    {
        pincontrolRRA = 22;
        pincontrolRRB = 23;
        pinspeedRR = 2;
        pincontrolFRA = 20;
        pincontrolFRB = 21;
        pinspeedFR = 3;
        pincontrolFLA = 18;
        pincontrolFLB = 19;
        pinspeedFL = 4;
        pincontrolRLA = 9;
        pincontrolRLB = 10;
        pinspeedRL = 5;
    }
    else
    {
        pincontrolRLA = 22;
        pincontrolRLB = 23;
        pinspeedRL = 2;
        pincontrolFRA = 20;
        pincontrolFRB = 21;
        pinspeedFR = 3;
        pincontrolFLA = 18;
        pincontrolFLB = 19;
        pinspeedFL = 4;
        pincontrolRRA = 9;
        pincontrolRRB = 10;
        pinspeedRR = 5;
    }

    defenseStop = false;
    currentSpeed = 0;

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
    pinMode(6, OUTPUT);
    max_power = 0;

    // PID Loop
    Setpoint = 0;
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0, 100);
    myPID.SetSampleTime(2);
};

void Motor::Move(double intended_angle, double motor_power, double initialOrientation)
{
    speedRR = 0;
    speedRL = 0;
    speedFL = 0;
    speedFR = 0;
    controlRR = 0;
    controlFR = 0;
    controlFL = 0;
    controlRL = 0;

    powerFR = sin(toRadians(intended_angle - 55));
    powerRR = sin(toRadians(intended_angle - 125));
    powerRL = sin(toRadians(intended_angle - 235));
    powerFL = sin(toRadians(intended_angle - 305));
    // find max_power among motors to scale
    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));
    FindCorrection(compassSensor.getOrientation(), initialOrientation);
    // add correction to account for rotation needed

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    powerFR += correction;
    powerFL += correction;
    powerRR += correction;
    powerRL += correction;
    // Serial.println(powerFR);
    // Serial.println(powerFL);
    // Serial.println(powerRR);
    // Serial.println(powerRL);

    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    speedFR = abs(powerFR);
    speedFL = abs(powerFL);
    speedRR = abs(powerRR);
    speedRL = abs(powerRL);
    int multiplier = 255;

    if(motor_power > 1){
        motor_power = 1;
    }
    else if(motor_power < 0){
        motor_power = 0;
    }
    int intspeedFR = (int)((speedFR * multiplier) * motor_power);
    int intspeedFL = (int)((speedFL * multiplier) * motor_power);
    int intspeedRR = (int)((speedRR * multiplier) * motor_power);
    int intspeedRL = (int)((speedRL * multiplier) * motor_power);
    if (defenseStop)
    {
        Stop();
    }
    else if (switches.start())
    {
        motorFR(powerFR, intspeedFR);
        motorFL(powerFL, intspeedFL);
        motorRR(powerRR, intspeedRR);
        motorRL(powerRL, intspeedRL);
        analogWrite(6, 255);
    }
    else
    {
        Stop();
        analogWrite(6, 0);

    }
}

void Motor::Stop()
{
    analogWrite(pinspeedFR, 0);
    analogWrite(pinspeedFL, 0);
    analogWrite(pinspeedRR, 0);
    analogWrite(pinspeedRL, 0);
    analogWrite(6, 0);
    digitalWrite(pincontrolFLA, HIGH);
    digitalWrite(pincontrolFLB, HIGH);
    digitalWrite(pincontrolFRA, HIGH);
    digitalWrite(pincontrolFRB, HIGH);
    digitalWrite(pincontrolRRA, HIGH);
    digitalWrite(pincontrolRRB, HIGH);
    digitalWrite(pincontrolRLA, HIGH);
    digitalWrite(pincontrolRLB, HIGH);
}
double Motor::RecordDirection()
{

    initialOrientation = compassSensor.getOrientation();
    return initialOrientation;
}

double Motor::getOrientation()
{
    return compassSensor.getOrientation();
}

double Motor::FindCorrection(double orientation, double initialOrientation)
{

    orientationVal = abs(orientation - initialOrientation);
    bool obtuse = false;
    if (orientationVal > 180)
    {
        orientationVal = 360 - orientationVal;
        obtuse = true;
    }

    if (obtuse && initialOrientation < 180 && orientation > 180)
    {
        orientation = -1 * (360 - orientation);
    }
    else if (obtuse && initialOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    if (orientation < initialOrientation)
    {
        orientationVal = -1 * orientationVal;
    }
    Input = abs(orientationVal);
    myPID.Compute();

    if (orientationVal > 0)
    {
        correction = -1 * (Output / 100);
    }
    else
    {
        correction = (Output / 100);
    }

    if (orientationVal > -5 && orientationVal <= 0)
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
    Serial.print("correction: ");
    Serial.println(correction);
    return correction;
}
void Motor::motorFL(double control, int speed){
    if (physicalRobot == 0){
        controlFL = control < 0 ? LOW : HIGH;
    }
    else{
        controlFL = control < 0 ? HIGH : LOW;
    }
    if (controlFL == LOW)
    {
        controlFLA = LOW;
        controlFLB = HIGH;
    }
    else
    {
        controlFLA = HIGH;
        controlFLB = LOW;
    }
    analogWrite(pinspeedFL, speed);
    digitalWrite(pincontrolFLA, controlFLA);
    digitalWrite(pincontrolFLB, controlFLB);
}
void Motor::motorFR(double control, int speed){
    if (physicalRobot == 0){
        controlFR = control > 0 ? HIGH : LOW;
    }
    else{
        controlFR = control < 0 ? HIGH : LOW;
    }
    if (controlFR == LOW)
    {
        controlFRA = LOW;
        controlFRB = HIGH;
    }
    else
    {
        controlFRA = HIGH;
        controlFRB = LOW;
    }
    analogWrite(pinspeedFR, speed);
    digitalWrite(pincontrolFRA, controlFRA);
    digitalWrite(pincontrolFRB, controlFRB);
}
void Motor::motorRR(double control, int speed){
    if (physicalRobot == 0){
        controlRR = control < 0 ? LOW : HIGH;
    }
    else{
        controlRR = control > 0 ? HIGH : LOW;
    }
    if (controlRR == LOW)
    {
        controlRRA = LOW;
        controlRRB = HIGH;
    }
    else
    {
        controlRRA = HIGH;
        controlRRB = LOW;
    }
    analogWrite(pinspeedRR, speed);
    digitalWrite(pincontrolRRA, controlRRA);
    digitalWrite(pincontrolRRB, controlRRB);
}
void Motor::motorRL(double control, int speed){
    if (physicalRobot == 0){
        controlRL = control > 0 ? HIGH : LOW;
    }
    else{
        controlRL = control < 0 ? HIGH : LOW;
    }
    if (controlRL == LOW)
    {
        controlRLA = LOW;
        controlRLB = HIGH;
    }
    else
    {
        controlRLA = HIGH;
        controlRLB = LOW;
    }
    analogWrite(pinspeedRL, speed);
    digitalWrite(pincontrolRLA, controlRLA);
    digitalWrite(pincontrolRLB, controlRLB);
}

bool Motor::spin(int target)
{
    if(target > 350 || target < 10){
        return true;
    }
    if(target > 180){
        target = -1;
    }
    else{
        target = 1;
    }
    spinMotors(target);
    return false;
}
void Motor::spinMotors(double direction)
{
    motorFL(direction,25);
    motorFR(direction,25);
    motorRR(direction,25);
    motorRL(direction,25);
}

double Motor::speedControl(int ballDist, double initialSpeed, int role)
{
    if (!(switches.start()) || ballDist == -5 || role == 0)
    {
        currentSpeed = initialSpeed;
        speedTimer = 0;
        return initialSpeed;
    }
    else if (currentSpeed > initialSpeed && ballDist < 70)
    {
        currentSpeed = initialSpeed;
        speedTimer = 0;
        return initialSpeed;
    }
    else if (ballDist >= 70)
    {
        currentSpeed = initialSpeed;
        currentSpeed += min(1-initialSpeed,((pow((3.33 * (speedTimer / 1000.0)), 2)) / 100.0));
        return currentSpeed;
    }
    else
    {
        speedTimer = 0;
        return initialSpeed;
    }
}