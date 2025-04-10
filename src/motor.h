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
  Motor(int robotNum);
  void Move(double intended_angle, double motor_power, double robotOrientation);
  void Stop();
  double RecordDirection();
  double FindCorrection(double orientation, double robotOrientation);
  double getOrientation();
  bool spin(int target);
  double speedControl(int ballDist, double initialSpee, int role);
  CompassSensor compassSensor;
  int dirAngle;
  double correction;
  bool defenseStop;
  Switch switches;
  double initialOrientation = 0;
  double orientationVal;
  PID myPID;
  void motorFR(double control, int speed);
  void motorRR(double control, int speed);
  void motorRL(double control, int speed);
  void motorFL(double control, int speed);
  void spinMotors(double direction);


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
  double currentSpeed;
  double Setpoint, Input, Output;
  elapsedMillis speedTimer;
  int physicalRobot;

};

#endif