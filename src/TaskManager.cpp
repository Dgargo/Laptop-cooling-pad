#include "taskManeger.h"

// Control speed
void ControlSpeed(void *pvParameters)
{
   while (true)
   {
      getTemp(sensorTemp,temperature);
      tempToSpeed(newFanSpeed, temperature, MIN_TEMP, MAX_TEMP, MIN_SPEED, MAX_SPEED);
      TickFan(newFanSpeed,fanSpeed, MIN_SPEED, MAX_SPEED);
      CalcSpeedProcent(speedProcent, fanSpeed, MAX_SPEED);
#ifdef DEBUG
      analogWrite(LED_DEBUG, fanSpeed);
      Serial.print("FanSpeed = ");
      Serial.println(fanSpeed);
#endif

      vTaskDelay(TASK_TIME_CONTROL_SPEED / portTICK_RATE_MS);
   }
}



// Show information in serial port
void ControlSerial(void *pvParameters)
{
   while (true)
   {
      SerialDispelay(temperature, speedProcent, rpm1, rpm2);
      vTaskDelay(TASK_TIME_SERIAL_DISPLAY / portTICK_RATE_MS);
   }
}

//Calculation RPM 
void TachoTask(void *pvParameters)
{
  while(1)
  {
    CaclRPM(counterTacho1,counterTacho2,rpm1,rpm2);
    vTaskDelay(TASK_TIME_CALCULATE_RPM/portTICK_RATE_MS);
    
  }
  vTaskDelete(NULL);
}