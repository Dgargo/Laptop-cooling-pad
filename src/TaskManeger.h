#pragma once
#include "config.h"
#include "fan.h"
#include "serial.h"

// control Speed
void Task_Control_Speed(void *pvParameters);

// Show information in serial port
void Task_Control_Serial(void *pvParameters);

//Calculation RPM 
void Task_Tacho(void *pvParameters);

//Connection to wifi and Blynk server
void Task_Blynk_Loop(void * pvParameters);

//Update data on Blynk
void Task_Update_Data(void *pvParameters);

