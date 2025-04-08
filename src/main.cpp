#include <Arduino.h>
#include <process.h>

double motorPower;
//1 = volmeter
//0 = no voltmeter
Process process(1);
CompassSensor compassSensor;

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
    motorPower = 0.2;
    process.offense(motorPower);
  // }
  // else{
  //   motorPower = 0.35;
  //   process.defense(motorPower);
  // }

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



