#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

Motor::Motor() : myPID(&Input, &Output, &Setpoint, 0.34, 0, 0.003, REVERSE)
{
    // corresponding pin values on teensy
    pinspeedRL = 4;
    pinspeedRR = 3;
    pinspeedFL = 2;
    pinspeedFR = 5;

    pincontrolRLA = 18;
    pincontrolRRA = 20;
    pincontrolFLA = 22;
    pincontrolFRA = 9;

    pincontrolRLB = 19;
    pincontrolRRB = 21;
    pincontrolFLB = 23;
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

    // PID Loop
    Setpoint = 0;
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0, 100);
};

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

    controlRL = powerRL > 0 ? LOW : HIGH;
    controlRR = powerRR > 0 ? LOW : HIGH;
    controlFL = powerFL < 0 ? LOW : HIGH;
    controlFR = powerFR > 0 ? LOW : HIGH;
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

    if (defenseStop)
    {
        Stop();
    }
    else if (switches.start())
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
    analogWrite(pinspeedRR, 0);
    analogWrite(pinspeedRL, 0);
    digitalWrite(pincontrolFLA, HIGH);
    digitalWrite(pincontrolFLB, LOW);
    digitalWrite(pincontrolFRA, HIGH);
    digitalWrite(pincontrolFRB, LOW);
    digitalWrite(pincontrolRRA, HIGH);
    digitalWrite(pincontrolRRB, LOW);
    digitalWrite(pincontrolRLA, HIGH);
    digitalWrite(pincontrolRLB, LOW);
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
    Serial.println(compassSensor.getOrientation());
    return compassSensor.getOrientation();
}

double Motor::FindCorrection(double orientation, double robotOrientation)
{

    orientationVal = abs(orientation - robotOrientation);

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

    if (orientationVal > -5 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 5 && orientationVal > 0)
    {
        correction = 0;
    }
    else if (orientationVal > 110)
    {
        correction = -1;
    }
    else if (orientationVal < -110)
    {
        correction = 1;
    }

    return correction;
}
