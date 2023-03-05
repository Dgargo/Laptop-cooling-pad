
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <driver/ledc.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "fan.h"
#include "config.h"
#include "taskManeger.h"
#include "MQTT.h"
#ifdef DEBUG
#include "serial.h"
#endif

//interput for tachometr
static void IRAM_ATTR Intr_Handler_One(void *args)
{
    counterTacho1++;
}

static void IRAM_ATTR Intr_Handler_Two(void *args)
{
    counterTacho2++;
}

void setup()
{
  Serial.begin(115200);

#ifdef DEBUG
  pinMode(LED_DEBUG, OUTPUT);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif

  //sensor DS18B20 begin work
  sensorTemp.begin();

  //semaphore create 
  sema_MQTT_KeepAlive   = xSemaphoreCreateBinary();
  xSemaphoreGive( sema_MQTT_KeepAlive );

  //config interrupt
  gpio_set_intr_type(SET_TACHO_FIRST,GPIO_INTR_POSEDGE);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(SET_TACHO_FIRST,Intr_Handler_One,NULL);

  gpio_set_intr_type(SET_TACHO_SECOND,GPIO_INTR_POSEDGE);
  gpio_install_isr_service(1);
  gpio_isr_handler_add(SET_TACHO_SECOND,Intr_Handler_Two,NULL);

  //config timer for interrupt
  ledc_timer_config_t ledc_timer1 = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 25000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer1));

  ledc_timer_config_t ledc_timer2 = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER_1,
        .freq_hz          = 25000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer2));

  //config for PWM
  ledc_channel_config_t ledc_channel = {
        .gpio_num       = SET_FAN_FIRST,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = fanSpeed,
        .hpoint         = 0
    };
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));


  //config for PWM
  ledc_channel_config_t ledc_channe2 = {
        .gpio_num       = SET_FAN_SECOND,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_1,
        .timer_sel      = LEDC_TIMER_1,
        .duty           = fanSpeed,
        .hpoint         = 0
    };
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channe2));

  MQTT_Client.setCallback(Callback);
  

  //Create task
  //Task control fan speed
  xTaskCreate(Control_Speed_Task, "Control Speeed", 1024, NULL, 1, NULL);
  //Task control tacho fan
  xTaskCreate(Tacho_Task, "Tacho Task",2048,NULL,20,NULL);
  //Task connection MQTT
  xTaskCreatePinnedToCore( MQTT_Keep_Alive_Task, "MQTT_Keep_Alive_Task", 10000, NULL, 3, NULL, 1 );
  //Task subcribe topics 
  xTaskCreatePinnedToCore( Subscribe_Topics_Task, "Subscribe_Topics_Task", 10000, NULL, 3, NULL, 1);
  //Task Publish topics
  xTaskCreate(Publish_Task,"Publish_Task",4092,NULL,1,NULL);
#ifdef DEBUG
  xTaskCreate(Control_Serial_Task, "Control Serial", 2048, NULL, 1, NULL);
#endif

}

void loop()
{
}
