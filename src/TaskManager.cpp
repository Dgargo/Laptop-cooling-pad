#include "taskManeger.h"

// Control speed
void Control_Speed(void *pvParameters)
{
   while (true)
   {
      Get_Temp(sensorTemp,temperature);
      Temp_To_Speed(newFanSpeed, temperature, minTemp, maxTemp, minSpeed, maxSpeed);
      Tick_Fan(newFanSpeed,fanSpeed, minSpeed, maxSpeed);
      Calc_Speed_Procent(speedProcent, fanSpeed, maxSpeed);
#ifdef DEBUG
      analogWrite(LED_DEBUG, fanSpeed);
      Serial.print("FanSpeed = ");
      Serial.println(fanSpeed);
#endif

      vTaskDelay(TASK_TIME_CONTROL_SPEED / portTICK_RATE_MS);
   }
}



// Show information in serial port
void Control_Serial(void *pvParameters)
{
   while (true)
   {
      Serial_Display(temperature, speedProcent, rpm1, rpm2);
      vTaskDelay(TASK_TIME_SERIAL_DISPLAY / portTICK_RATE_MS);
   }
}

//Calculation RPM 
void Tacho_Task(void *pvParameters)
{
  while(1)
  {
    CaclRPM(counterTacho1,counterTacho2,rpm1,rpm2);
    vTaskDelay(TASK_TIME_CALCULATE_RPM/portTICK_RATE_MS);
    
  }
  vTaskDelete(NULL);
}

