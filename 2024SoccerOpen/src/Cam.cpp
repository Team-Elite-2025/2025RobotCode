
#include <Cam.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
Cam::Cam()
{
  ball = 0;
  yellowGoal = 0;
  blueGoal = 0;
  buffer = "";
}
double Cam::CamCalc()
{
  // Serial.print(Serial2.available());
  if (Serial2.available() > 0)
  {
    for (int i = 0; i < Serial2.available(); i++)
    {
      read = Serial2.read();
      if (read == 'b')
      {
        ball = strtod(buffer.c_str(), NULL);
        ball = FilterAngle(ball, previousBallAngle);
        buffer = "";
        Serial.print("ball: ");
        Serial.println(ball);
        previousBallAngle = ball;
      }

      else if (read == 'c')
      {
        blueGoal = strtod(buffer.c_str(), NULL);
        blueGoal = FilterAngle(blueGoal, previousBallAngle);
        Serial.print("blue: ");
        Serial.println(blueGoal);
        buffer = "";
        previousBlueAngle = blueGoal;
      }
      else if (read == 'd')
      {
        yellowGoal = strtod(buffer.c_str(), NULL);
        yellowGoal = FilterAngle(yellowGoal, previousYellowAngle);
        Serial.print("yellow: ");
        Serial.println(yellowGoal);
        buffer = "";
        previousYellowAngle = yellowGoal;
      }
      else if (read == 'a')
      {
        ballDistance = strtod(buffer.c_str(), NULL);
        if (ballDistance < 480)
        {
          ballDistance = 563.356 * exp(0.000285648 * ballDistance) - 570.65;
        }
        else
        {
          ballDistance = 0.219569 * ballDistance - 17.2009;
        }
        Serial.print("Distance: ");
        Serial.println(ballDistance);
        buffer = "";
        previousBallDistance = ballDistance;
      }
      else
      {
        buffer += read;
      }
    }
    return 0;
  }
}
double Cam::FilterAngle(double angle, double previousAngle)
{
  if (angle == -5)
  {
    return -5;
  }
  if (angle == 0)
  {
    return previousAngle;
  }
  if (angle > 360 || angle < 0)
  {
    return previousAngle;
  }
  else
  {
    return angle;
  }
}
