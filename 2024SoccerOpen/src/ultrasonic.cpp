#include <ultrasonic.h>

Ultrasonic::Ultrasonic(){
    echoPin = 34;
    trig1Pin = 33;
    trig2Pin = 35;
    trig3Pin = 37;
    trig4Pin = 39;
    pinMode(echoPin, INPUT);
    pinMode(trig1Pin, OUTPUT);
    pinMode(trig2Pin, OUTPUT);
    pinMode(trig3Pin, OUTPUT);
    pinMode(trig4Pin, OUTPUT);
}

int Ultrasonic::sensor1(){ // Left
    digitalWrite(trig1Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);

    const unsigned long duration= pulseIn(echoPin, HIGH);
    int distance= duration/29/2;
    if(duration==0){
        Serial.println("Warning: no pulse from sensor");
        return 0;
    }  
    else{
        Serial.print("distance to nearest object:");
        Serial.println(distance);
        Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::sensor2(){ // Back
    digitalWrite(trig2Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2Pin, LOW);

    const unsigned long duration= pulseIn(echoPin, HIGH);
    int distance= duration/29/2;
    if(duration==0){
        Serial.println("Warning: no pulse from sensor");
    }  
    else{
        Serial.print("distance to nearest object:");
        Serial.println(distance);
        Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::sensor3(){
    digitalWrite(trig3Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig3Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig3Pin, LOW);

    const unsigned long duration= pulseIn(echoPin, HIGH);
    int distance= duration/29/2;
    if(duration==0){
        Serial.println("Warning: no pulse from sensor");
    }  
    else{
        Serial.print("distance to nearest object:");
        Serial.println(distance);
        Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::sensor4(){ //RIGHT
    digitalWrite(trig4Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig4Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig4Pin, LOW);

    const unsigned long duration= pulseIn(echoPin, HIGH);
    int distance= duration/29/2;
    if(duration==0){
        Serial.println("Warning: no pulse from sensor");
    }  
    else{
        Serial.print("distance to nearest object:");
        Serial.println(distance);
        Serial.println(" cm");
        return distance;
    }
}