#include "fan.h"


void getTemp(DallasTemperature sensorTemp , float &temperature)
{
  sensorTemp.requestTemperatures();
  temperature = sensorTemp.getTempCByIndex(0);
}

// Convert temperature from sensor in Speed
void tempToSpeed(byte &newFanSpeed, float temperature, int MIN_TEMP, int MAX_TEMP, int MIN_SPEED, int MAX_SPEED)
{
  newFanSpeed = map(temperature, MIN_TEMP, MAX_TEMP, MIN_SPEED, MAX_SPEED);
  newFanSpeed = constrain(newFanSpeed, MIN_SPEED, MAX_SPEED);
}

// Smooth speed control
void TickFan(byte newFanSpeed, byte &fanSpeed, int MIN_SPEED, int MAX_SPEED)
{
  if (newFanSpeed > fanSpeed)
    fanSpeed += 2;
  if (newFanSpeed < fanSpeed)
    fanSpeed -= 2;
  fanSpeed = constrain(fanSpeed, MIN_SPEED, MAX_SPEED);
  analogWrite(SET_FAN_FIRST, fanSpeed);
  analogWrite(SET_FAN_SECOND, fanSpeed);

}

// calculate speedProcent
void CalcSpeedProcent(float &speedProcent, float fanSpeed, int MAX_SPEED)
{
  speedProcent = (fanSpeed * 100) / MAX_SPEED;
}
