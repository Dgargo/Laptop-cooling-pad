#pragma once
#include "config.h"

// Convert temperature from sensor in Speed
byte tempToSpeed(byte newFanSpeed , float temperature , int MIN_TEMP , int MAX_TEMP , int MIN_SPEED , int MAX_SPEED);

// Smooth speed control
float TickFan(byte newFanSpeed, byte fanSpeed, int MIN_SPEED, int MAX_SPEED);

// calculate speedProcent
float CalcSpeedProcent(float speedProcent, float fanSpeed, int MAX_SPEED);
