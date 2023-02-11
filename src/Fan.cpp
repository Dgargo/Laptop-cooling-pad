#include "fan.h"


void getTemp(DallasTemperature sensorTemp , float &temperature)
{
  sensorTemp.requestTemperatures();
  temperature = sensorTemp.getTempCByIndex(0);
  #ifdef DEBUG
  Serial.print("temp");
  Serial.println(temperature);
  #endif
}

// Convert temperature from sensor in Speed
void tempToSpeed(u_int32_t &newFanSpeed, float temperature, u_int32_t MIN_TEMP, u_int32_t MAX_TEMP, u_int32_t MIN_SPEED, u_int32_t MAX_SPEED)
{
  newFanSpeed = map(temperature,MIN_TEMP,MAX_TEMP,MIN_SPEED,MAX_SPEED);
  newFanSpeed = constrain(newFanSpeed, MIN_SPEED, MAX_SPEED);
  
}

// Smooth speed control
void TickFan(u_int32_t newFanSpeed, u_int32_t &fanSpeed, u_int32_t MIN_SPEED, u_int32_t MAX_SPEED)
{
  if (newFanSpeed > fanSpeed)
    fanSpeed += 4;
  if (newFanSpeed < fanSpeed)
    fanSpeed -= 4;
  fanSpeed = constrain(fanSpeed, MIN_SPEED, MAX_SPEED);
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, fanSpeed));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, fanSpeed));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1));

}

// calculate speedProcent
void CalcSpeedProcent(float &speedProcent, u_int32_t fanSpeed, u_int32_t MAX_SPEED)
{
  speedProcent = (fanSpeed * 100) / MAX_SPEED;
}

void CaclRPM(uint32_t &counterTacho1,uint32_t &counterTacho2,u_int32_t &rpm1,u_int32_t &rpm2)
{
    rpm1 = counterTacho1 * 30 ;
    rpm2 = counterTacho2 * 30 ;

    counterTacho1=0;
    counterTacho2=0;
}