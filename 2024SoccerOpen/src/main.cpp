#include <Arduino.h>
#include <process.h>



unsigned long myTime = 0;

Process process;
Switch switches;


void setup() {
  Serial.begin(9600);
  Serial2.begin(19200);
}

void loop() {
    process.offense(0.2);
    // delay(1000);

}

