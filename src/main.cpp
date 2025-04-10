#include <Arduino.h>
#include <process.h>

double motorPower;
//1 = volmeter
//0 = no voltmeter
Process process(1);
CompassSensor compassSensor;
Motor motor(1);
Switch switches;
Cam cam;
Localization local;
// Calibration cal;
void setup()
{
  Serial.begin(19200);
  Serial2.begin(2000000);
  Serial7.begin(921600);
  // compassSensor.calibrate();  

}

void loop()
{
  // if (process.roleSwitch.getOurRole() == 1){
    // motorPower = 0.2;
    // process.offense(motorPower);
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
  //   motorPower = 0.35;
  //   process.defense(motorPower);
  // }
  // motor.motorFL(1, 100);
  
  // cam.CamCalc();
  // local.offenseLocalization(0, cam.yellowGoal, cam.blueGoal);
  process.offense(0.2);

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



