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
}

int Ultrasonic::backSensor()
{ 
    digitalWrite(trig1Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);

    const unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = duration / 29 / 2;
    if (duration == 0)
    {
        Serial.println("Warning: no pulse from back sensor");
        return -1;
    }
    else
    {
        Serial.print("Back:");
        Serial.print(distance);
        Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::rightSensor()
{ 
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
        Serial.print("Right:");
        Serial.print(distance);
        Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::leftSensor()
{ 
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
        Serial.print("Left:");
        Serial.print(distance);
        Serial.println(" cm");
        return distance;
    }
}
int Ultrasonic::frontSensor()
{ 
    digitalWrite(trig4Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig4Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig4Pin, LOW);
    // pulseIn(echoPin, HIGH,100);
    const unsigned long duration = pulseIn(echoPin, HIGH,100000);
    int distance = duration / 29 / 2;
    if (duration == 0)
    {
        Serial.println("Warning: no pulse from right sensor");
        return -1;
    }
    else
    {
        Serial.print("Front:");
        Serial.print(distance);
        Serial.println(" cm");
        return distance;
    }
}

