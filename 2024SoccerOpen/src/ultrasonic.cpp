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

int Ultrasonic::leftSensor(){ // Left
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
int Ultrasonic::backSensor(){ // Back
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
int Ultrasonic::frontSensor(){ // FRONT
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
int Ultrasonic::rightSensor(){ //RIGHT
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
int Ultrasonic::getX(){
    if(leftSensor() + rightSensor() < 187 && leftSensor() + rightSensor() > 177)
        prevX = (leftSensor()-rightSensor())/2.0;
    return prevX;
}
int Ultrasonic::getY(){
    if(getX() <-30 || getX() > 30) {
        if(backSensor() + frontSensor() < 187 && backSensor() + frontSensor() > 177)
            prevY = (backSensor()-frontSensor())/2.0;
    } else {
        if(backSensor() + frontSensor() < 177 && backSensor() + frontSensor() > 167)
            prevY = (backSensor()-frontSensor())/2.0;
    }
    return prevY;
}
