#include <Arduino.h>
#include <process.h>



unsigned long myTime = 0;

Process process;
Switch switches;
CompassSensor compassSensor;



void setup() {
  Serial.begin(9600);
  Serial2.begin(19200);
  // compassSensor.calibrate();
}

void loop() {
    // process.offense(0.2);
    Serial.println(compassSensor.getOrientation());
    // delay(1000);
}

