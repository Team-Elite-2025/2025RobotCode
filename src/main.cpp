#include <Arduino.h>
#include <process.h>

double motorPower;

Process process;
CompassSensor compassSensor;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(19200);
  Serial7.begin(38400);
  // compassSensor.calibrate();

}

void loop()
{
  // if (process.roleSwitch.getOurRole() == 1){
    motorPower = 0.25;
    process.offense(motorPower);
  // }
  // else{
  //   motorPower = 0.35;
  //   process.defense(motorPower);
  // }

  delay(500);
}
