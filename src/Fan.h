#pragma once
#include "config.h"

// read from the temperature sensor
void getTemp(DallasTemperature sensorTemp , float &temperature);

// Convert temperature from sensor in Speed
void tempToSpeed(byte &newFanSpeed, float temperature, int MIN_TEMP, int MAX_TEMP, int MIN_SPEED, int MAX_SPEED);

// Smooth speed control
void TickFan(byte newFanSpeed, byte &fanSpeed, int MIN_SPEED, int MAX_SPEED);

// calculate speedProcent
void CalcSpeedProcent(float &speedProcent, float fanSpeed, int MAX_SPEED);
