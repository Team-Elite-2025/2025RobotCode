#include <switches.h>
#include <Arduino.h>

Switch::Switch()
{
    pinMode(ledPin, OUTPUT);
    pinMode(recieverPin, INPUT);
    analogWriteFrequency(ledPin, 38000);
    delay(100);
    analogWrite(ledPin, 127);
}

bool Switch::start()
{
    if (digitalRead(40) == HIGH)
    {
        return true;
    }
    return false;
}
bool Switch::switchSide()
{
    if (digitalRead(38) == HIGH)
    {
        return true;
    }
    return false;
}
bool Switch::switchRole()
{
    if (digitalRead(36) == HIGH)
    {
        return true;
    }
    return false;
}
bool Switch::calibration()
{
    if (digitalRead(31) == HIGH)
    {
        return true;
    }
    return false;
}
bool Switch::lightgate()
{
    Serial.print("Lightgate: ");
    Serial.println(analogRead(recieverPin));
    if (analogRead(recieverPin) < 700)
    {
        return false;
    }
    else
    {
        return true;
    }
}