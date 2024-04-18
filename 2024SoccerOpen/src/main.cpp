#include <Arduino.h>
#include <process.h>



unsigned long myTime = 0;

Process process;


void setup() {
  Serial.begin(9600);

}

void loop() {

process.offense(0.5);


}

