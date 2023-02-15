
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <driver/ledc.h>

#include "fan.h"
#include "config.h"
#include "taskManeger.h"
#ifdef DEBUG
#include "serial.h"
#endif

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

#ifdef DEBUG
  Serial.begin(115200);
  pinMode(LED_DEBUG, OUTPUT);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#endif

  pinMode(SET_FAN_FIRST, OUTPUT);
  pinMode(SET_FAN_SECOND, OUTPUT);

  sensorTemp.begin();
  //sensorTemp.setResolution(12); // set the resolution of the sensor from 9 to 12 bits

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
        .gpio_num       = SET_FAN_FIRST,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_1,
        .timer_sel      = LEDC_TIMER_1,
        .duty           = fanSpeed,
        .hpoint         = 0
    };
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channe2));

  xTaskCreate(Control_Speed, "Control Speeed", 1024, NULL, 1, NULL);

  xTaskCreate(Tacho_Task, "Tacho Task",2048,NULL,20,NULL);
#ifdef DEBUG
  xTaskCreate(Control_Serial, "Control Serial", 2048, NULL, 1, NULL);
#endif

}

void loop()
{
}
