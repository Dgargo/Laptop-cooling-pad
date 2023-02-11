#pragma once
#include "config.h"

// read from the temperature sensor
void getTemp(DallasTemperature sensorTemp , float &temperature);

// Convert temperature from sensor in Speed
void tempToSpeed(u_int32_t &newFanSpeed, float temperature, u_int32_t MIN_TEMP, u_int32_t MAX_TEMP, u_int32_t MIN_SPEED, u_int32_t MAX_SPEED);

// Smooth speed control
void TickFan(u_int32_t newFanSpeed, u_int32_t &fanSpeed, u_int32_t MIN_SPEED, u_int32_t MAX_SPEED);

// calculate speedProcent
void CalcSpeedProcent(float &speedProcent, u_int32_t fanSpeed, u_int32_t MAX_SPEED);

void CaclRPM(uint32_t &counterTacho1,uint32_t &counterTacho2,u_int32_t &rpm1,u_int32_t &rpm2);