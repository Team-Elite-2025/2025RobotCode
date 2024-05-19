#include <compassSensor.h>
CompassSensor::CompassSensor()
{
  bno = Adafruit_BNO055(55, 0x28, &Wire2);
  if (bno.begin())
  {
    //  bno.setExtCrystalUse(true);
  }
  else
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    while (1)
    {
      Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    }
  }
};
void CompassSensor::calibrate()
{
  uint8_t system, gyro, accel, mag = 0;

  while (mag < 3)
  {
    bno.getCalibration(&system, &gyro, &accel, &mag);
    Serial.println("Calibrate your compass sensor!");
    Serial.println(String(mag) + "/3 magnetometer");
    // Serial.println(String(gyro) + "/3 gyroscope");
    Serial.println();
    delay(100);
  }
  calibrated = true;
  Serial.print(calibrated);
};
int CompassSensor::getOrientation()
{
  bno.getEvent(&event);
  //   Serial.print("X: ");
  // Serial.println(event.orientation.x, 4);
  return event.orientation.x;
};
void CompassSensor::displayCalStatus(void)
{

  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  // Serial.print("\t");
  if (!system)
  {
    // Serial.print("! ");
  }

  // Serial.print("Sys:");
  // Serial.print(system, DEC);
  // Serial.print(" G:");
  // Serial.print(gyro, DEC);
  // Serial.print(" A:");
  // Serial.print(accel, DEC);
  // Serial.print(" M:");
  // Serial.print(mag, DEC);
};

void CompassSensor::displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
}

void CompassSensor::displaySensorStatus(void)
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);
}