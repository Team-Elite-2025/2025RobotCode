#include <bluetooth.h>

Bluetooth::Bluetooth()
{
    statePin = 17;
    pinMode(statePin, INPUT);
}

void Bluetooth::readData()
{
    role = -1;
    if (Serial7.available() > 0)
    {
        for (int i = 0; i < Serial7.available(); i++)
        {
            read = Serial7.read();
            if (read == 'x')
            {
                xCoord = strtod(buffer.c_str(), NULL);
                buffer = "";
                Serial.print("X: ");
                Serial.println(xCoord);
            }

            else if (read == 'y')
            {
                yCoord = strtod(buffer.c_str(), NULL);
                Serial.print("Y: ");
                Serial.println(yCoord);
                buffer = "";
            }
            else if (read == 'd')
            {
                ballDist = strtod(buffer.c_str(), NULL);
                Serial.print("mateBallDist: ");
                Serial.println(ballDist);
                buffer = "";
            }
            else if (read == 'r')
            {
                role = strtod(buffer.c_str(), NULL);
                Serial.print("mateRole: ");
                Serial.println(role);
                buffer = "";
            }
            else
            {
                buffer += read;
            }
        }
    }
    else
    {
        xCoord = -5;
        yCoord = -5;
        ballDist = -5;
        role = -1;
    }
}

void Bluetooth::sendData(int x, int y, int ballDist, int ourRole)
{
    if (sendQueue >= 100)
    {
        Serial7.print(String(x) + 'x' + String(y) + 'y' + String(ballDist) + 'd' + String(ourRole) + 'r');
        sendQueue = 0;
    }
}
int Bluetooth::getRole()
{
    return role;
}
int Bluetooth::getXCoord()
{
    return xCoord;
}
int Bluetooth::getYCoord()
{
    return yCoord;
}
int Bluetooth::getDistance()
{
    return ballDist;
}
bool Bluetooth::getState()
{
    if (digitalRead(statePin) == HIGH)
    {
        return true;
    }
    return false;
}
