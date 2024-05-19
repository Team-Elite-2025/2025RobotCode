#include <Arduino.h>
#include <process.h>

double motorPower;

Process process;
CompassSensor compassSensor;
Switch switches;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(19200);
  compassSensor.calibrate();
  motorPower = 0.25;
}

void loop()
{
  if (switches.switchRole())
    process.offense(motorPower);
  else
    process.defense(motorPower);

// delay(500);
}

