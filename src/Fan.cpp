#include "fan.h"


void Get_Temp(DallasTemperature sensorTemp , float &temperature)
{
  sensorTemp.requestTemperatures();
  temperature = sensorTemp.getTempCByIndex(0);
  #ifdef DEBUG
  Serial.print("temp");
  Serial.println(temperature);
  #endif
}

// Convert temperature from sensor in Speed
void Temp_To_Speed(u_int32_t &newFanSpeed, float temperature, u_int32_t minTemp, u_int32_t maxTemp, u_int32_t minSpeed, u_int32_t maxSpeed)
{
  newFanSpeed = map(temperature,minTemp,maxTemp,minSpeed,maxSpeed);
  newFanSpeed = constrain(newFanSpeed, minSpeed, maxSpeed);
  
}

// Smooth speed control
void Tick_Fan(u_int32_t newFanSpeed, u_int32_t &fanSpeed, u_int32_t minSpeed, u_int32_t maxSpeed)
{
  if (newFanSpeed > fanSpeed)
    fanSpeed += 4;
  if (newFanSpeed < fanSpeed)
    fanSpeed -= 4;
  fanSpeed = constrain(fanSpeed, minSpeed, maxSpeed);
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, fanSpeed));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, fanSpeed));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1));

}

// calculate speedProcent
void Calc_Speed_Procent(float &speedProcent, u_int32_t fanSpeed, u_int32_t maxSpeed)
{
  speedProcent = (fanSpeed * 100) / maxSpeed;
}

void CaclRPM(uint32_t &counterTacho1,uint32_t &counterTacho2,u_int32_t &rpm1,u_int32_t &rpm2)
{
    rpm1 = counterTacho1 * 30 ;
    rpm2 = counterTacho2 * 30 ;

    counterTacho1=0;
    counterTacho2=0;
}


