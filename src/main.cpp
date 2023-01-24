#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Fan.h"
#include "config.h"

#ifdef DEBUG
#include "Serial.h"
#endif

// create classes for work with DS18B20
OneWire DS18(SET_TEMP);
DallasTemperature sensorTemp(&DS18);

// interrupt handling
void counter1()
{
  count1++;
}

void counter2()
{
  count2++;
}

void setup()
{

#ifdef DEBUG
  Serial.begin(115200);
  pinMode(LED_DEBUG, OUTPUT);
#endif
  pinMode(SET_FAN_FIRST, OUTPUT);
  pinMode(SET_FAN_SECOND, OUTPUT);

  sensorTemp.begin();
  sensorTemp.setResolution(12); // set the resolution of the sensor from 9 to 12 bits

  attachInterrupt(digitalPinToInterrupt(SET_TACH_FIRST), counter1, RISING);
  attachInterrupt(digitalPinToInterrupt(SET_TACH_SECOND), counter2, RISING);
}

void loop()
{
  // control speed
  uint16_t ms1 = millis() & 0xFFFF;
  if (ms1 - timerOne > timeFan)
  {
    timerOne = ms1;
    // read from the temperature sensor
    sensorTemp.requestTemperatures();
    temperature = sensorTemp.getTempCByIndex(0);

    newFanSpeed = tempToSpeed(newFanSpeed, temperature, MIN_TEMP, MAX_TEMP, MIN_SPEED, MAX_SPEED);
    fanSpeed = TickFan(newFanSpeed, fanSpeed, MIN_SPEED, MAX_SPEED);
    speedProcent = CalcSpeedProcent(speedProcent, fanSpeed, MAX_SPEED);
    count1 = 0;
    count2 = 0;

#ifdef DEBUG
    analogWrite(LED_DEBUG, fanSpeed);
    Serial.print("FanSpeed = ");
    Serial.println(fanSpeed);
#endif
// calculation of the number of revolutions
    rmp1 = count1 * 60 / 2;
    rmp2 = count2 * 60 / 2;
  }

  // show info
  uint16_t ms2 = millis() & 0xFFFF;
  if (ms2 - timerTwo > timeDisplay)
  {

    timerTwo = ms2;
#ifdef DEBUG
    SerialDispelay(temperature, speedProcent, rmp1, rmp2);
#endif
  }
}
