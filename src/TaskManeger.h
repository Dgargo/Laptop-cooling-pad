#pragma once
#include "config.h"
#include "fan.h"
#include "serial.h"

// Control Speed
void Control_Speed_Task(void *pvParameters);

// Show information in serial port
void Control_Serial_Task(void *pvParameters);

// Read from tachometr
void Tacho_Task(void *pvParameters);

// Keep alive MQTT server
void MQTT_Keep_Alive_Task( void *pvParameters );

// Subscribe on topic 
void Subscribe_Topics_Task(void *pvParameters);

//Publish our value  to MQTT server
void Publish_Task(void *pvParametrs);

