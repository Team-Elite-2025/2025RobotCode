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
  motorPower = 0.25;

}

void loop()
{
  process.offense(motorPower);
  // if (process.roleSwitch.getOurRole() == 1)
  //   process.offense(motorPower);
  // else
  //   process.defense(motorPower);

  // delay(500);
}
