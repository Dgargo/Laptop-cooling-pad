#include "TaskManeger.h"

// Control speed
void ControlSpeed(void *pvParameters)
{
   while (true)
   {
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

      vTaskDelay(TASK_TIME_CONTROL_SPEED / portTICK_RATE_MS);
   }
}

// Control interrupt for tacho sensor
void ControlInterrupt(void *pvParameters)
{
}

// Show information in serial port
void ControlSerial(void *pvParameters)
{
   while (true)
   {
      SerialDispelay(temperature, speedProcent, rmp1, rmp2);
      vTaskDelay(TASK_TIME_SERIAL_DISPLAY / portTICK_RATE_MS);
   }
}