#include <ultrasonic.h>

Ultrasonic::Ultrasonic()
{
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
    allowRight = true;
    allowFront = true;
}

int Ultrasonic::leftSensor()
{ // Left
    digitalWrite(trig1Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);

    const unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = duration / 29 / 2;
    if (duration == 0)
    {
        Serial.println("Warning: no pulse from left sensor");
        return -1;
    }
    else
    {
        // Serial.print("Left:");
        // Serial.print(distance);
        // Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::backSensor()
{ // Back
    digitalWrite(trig2Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2Pin, LOW);

    const unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = duration / 29 / 2;
    if (duration == 0)
    {
        Serial.println("Warning: no pulse from back sensor");
        return -1;
    }
    else
    {
        // Serial.print("Back:");
        // Serial.print(distance);
        // Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::frontSensor()
{ // FRONT
    digitalWrite(trig3Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig3Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig3Pin, LOW);

    const unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = duration / 29 / 2;
    if (duration == 0)
    {
        Serial.println("Warning: no pulse from front sensor");
        return -1;
    }
    else
    {
        // Serial.print("Front:");
        // Serial.print(distance);
        // Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::rightSensor()
{ // RIGHT
    digitalWrite(trig4Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig4Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig4Pin, LOW);

    const unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = duration / 29 / 2;
    if (duration == 0)
    {
        Serial.println("Warning: no pulse from right sensor");
        return -1;
    }
    else
    {
        // Serial.print("Right:");
        // Serial.print(distance);
        // Serial.println(" cm");
        return distance;
    }
}
void Ultrasonic::localization(int correction){
    getY(correction);
}
void Ultrasonic::localizationDefense(int correction){
    getX(correction);
    backDefense = backSensor();
    if(correction <= 0.25){
        prevYDefense = backDefense;
    }

}
int Ultrasonic::getXCoordinate(){
    return prevX;
}
int Ultrasonic::getYCoordinate(){
    return prevY;
}
int Ultrasonic::getYCoordinateDefense(){
    return prevYDefense;
}
int Ultrasonic::getX(int correction) // Range: -70 - +70
{   

    if(allowRight){
        right = rightSensor();
        allowRight = false;
    }
    else if(offsetx >= 5){
        left = leftSensor();
        offsetx = 0;
        allowRight = true;
    }
    int total = left + right;
    if (total <= 185 && total >= 165 && correction <= 0.25)
        prevX = (left - right) / 2.0;
    return prevX;
}
int Ultrasonic::getY(int correction) // Range: -85 - +85
{
    getX(correction);
    
    if(allowFront){
        front = frontSensor();
        allowFront = false;
    }
    else if(offsety >= 15){
        back = backSensor();
        offsety = 0;
        allowFront = true;
    }
    int total = back + front;
    // Serial.print("total: ");
    // Serial.println(total);
    if (prevX <= -23 || prevX >= 23)
    {
        if (total <= 245 && total >= 225 && correction <= 0.25)
            prevY = (back - front) / 2.0;
    }
    else
    {
        // 5.2 Doff
        if (total <= (245 - 11.2) && total >= (225 - 11.2))
            prevY = (back - front) / 2.0;
    }
    return prevY;
}
