#pragma once
#include "config.h"
#include <DallasTemperature.h>
#include <OneWire.h>

// create classes for work with DS18B20
extern OneWire DS18;
extern DallasTemperature sensorTemp;
// read from the temperature sensor
void Get_Temp(DallasTemperature sensorTemp , float &temperature);

// Convert temperature from sensor in Speed
void Temp_To_Speed(u_int32_t &newFanSpeed, float temperature, u_int32_t minTemp, u_int32_t maxTemp, u_int32_t minSpeed, u_int32_t maxSpeed);

// Smooth speed control
void Tick_Fan(u_int32_t newFanSpeed, u_int32_t &fanSpeed, u_int32_t minSpeed, u_int32_t maxSpeed);

// calculate speedProcent
void Calc_Speed_Procent(float &speedProcent, u_int32_t fanSpeed, u_int32_t maxSpeed);

void CaclRPM(uint32_t &counterTacho1,uint32_t &counterTacho2,u_int32_t &rpm1,u_int32_t &rpm2);