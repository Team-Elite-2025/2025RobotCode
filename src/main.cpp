/*
#include <Arduino.h>
#include <process.h>

double motorPower;
//1 = Offense
//0 = Defense
int robot = 0;
Process process(robot);
CompassSensor compassSensor;
// Motor motor(0);
// Switch switches;
// Cam cam;
// Localization local;
// Calibration cal;
// LineDetection line;
void setup()
{
  Serial.begin(9600);
  Serial2.begin(2000000);
  Serial7.begin(921600);
  // pinMode(6, OUTPUT);
  compassSensor.calibrate(); 
  // pinMode(21, OUTPUT);
  // pinMode(20, OUTPUT);
  // pinMode(3, OUTPUT);
  
   

}

void loop()
{
  // line.GetValues();
  // Serial.println(digitalRead(5));
  // analogWrite(6, 255);
  // if (process.roleSwitch.getOurRole() == 1){
  if(robot == 0) {
    motorPower = 0.25;
    process.defense(motorPower);
  } else {
    motorPower = 0.2;
    process.offense(motorPower);
  }
    // while(switches.calibration()) {
    //   motor.initialOrientation = compassSensor.getOrientation();
    //   Serial.println("calibrating");
    // } if (!switches.calibration()) {
    //   motor.Move(45, .2, motor.initialOrientation);
    // } else {
    //   motor.Stop();
    // }
    // motor.spinMotors(-1);
  // }
  // else{
    // motorPower = 0.35;
    // process.defense(motorPower);
  // }
  // motor.motorRR(1, 20);
  
  // cam.CamCalc();
  // local.offenseLocalization(0, cam.yellowGoal, cam.blueGoal);
  // process.offense(0.2);
  // motor.spinMotors(1);
  // motor.motorRL(1, 5);

  // delay(500);
}


// #include <Arduino.h>
// #include<switches.h>
// // #include <process.h>

// // double motorPower;
// int kickerPin = 30;

// // Process process;
// // CompassSensor compassSensor;
// Switch switches;

// void setup()
// {
//   pinMode(kickerPin, OUTPUT);
//   // Serial.begin(9600);
//   // Serial2.begin(19200);
//   // Serial7.begin(38400);
//   // compassSensor.calibrate();
//   // motorPower = 0.3;

// }

// void loop()
// {
//   if(switches.start()){
//     digitalWrite(kickerPin, HIGH);
//   }
//   else{
//     digitalWrite(kickerPin, LOW);
//   }

// }

*/

#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);
  }
}


