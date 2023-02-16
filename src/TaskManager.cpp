#include "taskManeger.h"

#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>

// Control speed
void Task_Control_Speed(void *pvParameters)
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
void Task_Control_Serial(void *pvParameters)
{
   while (true)
   {
      Serial_Display(temperature, speedProcent, rpm1, rpm2);
      vTaskDelay(TASK_TIME_SERIAL_DISPLAY / portTICK_RATE_MS);
   }
}

//Calculation RPM 
void Task_Tacho(void *pvParameters)
{
  while(1)
  {
    CaclRPM(counterTacho1,counterTacho2,rpm1,rpm2);
    vTaskDelay(TASK_TIME_CALCULATE_RPM/portTICK_RATE_MS);
    
  }
  vTaskDelete(NULL);
}

//Connection to wifi and Blynk server
void Task_Blynk_Loop(void * pvParameters){
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  
  while (Blynk.connected() == false) {
  }
  Serial.println();
  Serial.println("Blynk Connected");
  Serial.println("Blynk Loop Task Started");
  while (1) {
     Blynk.run();
     delay(1);
  }
}

//Update data on Blynk
void Task_Update_Data(void *pvParameters)
{
   while(1)
   {
      if(Blynk.connected()==true)
      {
      Blynk.virtualWrite(V6,double(temperature));
      Blynk.virtualWrite(V9,double(speedProcent));
      Blynk.virtualWrite(V10,int(rpm1));
      Blynk.virtualWrite(V13,int(rpm2));
      }

      vTaskDelay(TASK_TIME_UPDATE_DATA/portTICK_RATE_MS);
   }
}

BLYNK_WRITE(V4)
{
    minTemp = param.asInt();
}

BLYNK_WRITE(V5)
{
    maxTemp = param.asInt();
}

BLYNK_WRITE(V7)
{
    minSpeed = param.asInt();
}


BLYNK_WRITE(V8)
{
    maxSpeed = param.asInt();
}