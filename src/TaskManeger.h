#pragma once
#include "config.h"
#include "fan.h"
#include "serial.h"

// control Speed
void Control_Speed(void *pvParameters);

// Show information in serial port
void Control_Serial(void *pvParameters);

void Tacho_Task(void *pvParameters);

