#include "taskManeger.h"
#include "MQTT.h"
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Control speed
void Control_Speed_Task(void *pvParameters)
{
   while (true)
   {
      Get_Temp(sensorTemp,temperature);
      Temp_To_Speed(newFanSpeed, temperature, minTemp, maxTemp, minSpeed, maxSpeed);
      Tick_Fan(newFanSpeed,fanSpeed, minSpeed, maxSpeed);
      Calc_Speed_Procent(speedProcent, fanSpeed, maxSpeed);
      
      vTaskDelay(TASK_TIME_CONTROL_SPEED / portTICK_RATE_MS);
   }
}



// Show information in serial port
void Control_Serial_Task(void *pvParameters)
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
  while(true)
  {
    CaclRPM(counterTacho1,counterTacho2,rpm1,rpm2);
    vTaskDelay(TASK_TIME_CALCULATE_RPM/portTICK_RATE_MS);
    
  }
  vTaskDelete(NULL);
}

// Keep alive MQTT server
void MQTT_Keep_Alive_Task( void *pvParameters )
{
  MQTT_Client.setKeepAlive( TIME_KEEP_ALIVE_MQTT ); 
  while(true)
  {
    
    if ( (ESP_Client.connected()) && (WiFi.status() == WL_CONNECTED) )
    {
      xSemaphoreTake( sema_MQTT_KeepAlive, portMAX_DELAY );
      MQTT_Client.loop();
      xSemaphoreGive( sema_MQTT_KeepAlive );
    }
    else {
    
      if ( !(WiFi.status() == WL_CONNECTED) )
      {
        connectToWiFi();
      }
      connectToMQTT();
    }
    vTaskDelay( TIME_CONNECT_MQTT / portTICK_RATE_MS); 
  }
  vTaskDelete ( NULL );
}

// Subscribe on topic
void Subscribe_Topics_Task(void *pvParameters)
{
  while(true)
  {
     xSemaphoreTake( sema_MQTT_KeepAlive, portMAX_DELAY );
     if (MQTT_Client.connect("Node-red")) { 
      MQTT_Client.subscribe("Led_Control");

      MQTT_Client.subscribe("min_temperature");
      MQTT_Client.subscribe("max_temperature");
      MQTT_Client.subscribe("min_speed");
      MQTT_Client.subscribe("max_speed");

    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTT_Client.state());
      Serial.println(" try again in 5 seconds");
      vTaskDelay(TASK_TIME_SUBSCRIBE_TOPICS);
  }
  xSemaphoreGive( sema_MQTT_KeepAlive );

  vTaskDelay(TASK_TIME_SUBSCRIBE_TOPICS/ portTICK_RATE_MS);
  }
  vTaskDelete ( NULL );
}

//Publish our value  to MQTT server
void Publish_Task(void *pvParametrs)
{
  while (true)
  {
    xSemaphoreTake( sema_MQTT_KeepAlive, portMAX_DELAY );
    if ( MQTT_Client.connected() )
    {
      MQTT_Client.publish( "temperature", String(temperature).c_str() );
      vTaskDelay( TIME_PUBLISH );
      MQTT_Client.publish("speed",String(speedProcent).c_str());
      vTaskDelay(TIME_PUBLISH);
      MQTT_Client.publish("RMP1",String(rpm1).c_str());
      vTaskDelay(TIME_PUBLISH);
      MQTT_Client.publish("RMP2",String(speedProcent).c_str());
      vTaskDelay(TIME_PUBLISH);

    }
    xSemaphoreGive( sema_MQTT_KeepAlive );
    
    vTaskDelay(TASK_TIME_PUBLISH / portTICK_RATE_MS);
  }
}