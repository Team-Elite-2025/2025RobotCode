#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <trig.h>
#include <orbit.h>
#include <switches.h>
#include <compassSensor.h>
#include <PID_v1.h>

class Motor
{

public:
  Motor();
  void Move(double intended_angle, double motor_power, double robotOrientation);
  void Stop();
  double RecordDirection();
  double FindCorrection(double orientation, double robotOrientation);
  double getOrientation();
  CompassSensor compassSensor;
  int dirAngle;
  double correction;
  bool defenseStop;
  Switch switches;
  double initialOrientation = 0;

private:
  double max_power;
  double powerFR;
  double powerFL;
  double powerRR;
  double powerRL;

  double speedFR;
  double speedFL;
  double speedRR;
  double speedRL;
  int controlFR;
  int controlFL;
  int controlRR;
  int controlRL;

  int controlFRA;
  int controlFLA;
  int controlRRA;
  int controlRLA;

  int controlFRB;
  int controlFLB;
  int controlRRB;
  int controlRLB;

  int pinspeedFR;
  int pinspeedFL;
  int pinspeedRR;
  int pinspeedRL;
  int pincontrolFRA;
  int pincontrolFLA;
  int pincontrolRRA;
  int pincontrolRLA;
  int pincontrolFRB;
  int pincontrolFLB;
  int pincontrolRRB;
  int pincontrolRLB;

  double orientationVal;
  int stopTime;
  bool setTime;
  double vectorX;
  double vectorY;
  double dotProduct;
  double denominator;
  double robotAngleX;
  double robotAngleY;
  bool projection;
  int goalAAngleSide;

  double Setpoint, Input, Output;
  PID myPID;
};

#endif