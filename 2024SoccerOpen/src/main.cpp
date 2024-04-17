#include <Arduino.h>
#include <motor.h>
#include <lineDetection.h>

#include <orbit.h>




LineDetection lineDetection;
// Motor motor;
// Orbit orbit;
// LRF lrf;
unsigned long myTime = 0;




void setup() {
  Serial.begin(9600);

}

void loop() {
  lineDetection.GetValues();
  delay(1000);
  // motor.Move(orbit.CalculateRobotAngle(ballAngle,0,1),0.5,motor.initialOrientation);
  Serial.println("HI");


}

