#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <driver/ledc.h>

// Set periphery
#define SET_TEMP GPIO_NUM_32  // Set DS18B20

#define SET_FAN_FIRST GPIO_NUM_16   // Set Fan 1
#define SET_FAN_SECOND GPIO_NUM_17  // Set Fan 2

#define SET_TACHO_FIRST GPIO_NUM_18  // Set tachometer 1
#define SET_TACHO_SECOND GPIO_NUM_19 // Set tachometer 2

// Set time for task Manager
#define TASK_TIME_CONTROL_SPEED 2000
#define TASK_TIME_CALCULATE_RPM 1000
#define TASK_TIME_SERIAL_DISPLAY 2000
// for Debuging
#define DEBUG
#define LED_DEBUG GPIO_NUM_21

// Set operating mode
extern uint32_t minTemp;  // min. temperature
extern uint32_t maxTemp;  // max. temperature
extern uint32_t minSpeed; // (0-255) min speed
extern uint32_t maxSpeed; // (0-255) max speed

// varies for set speed fans
extern u_int32_t newFanSpeed;
extern u_int32_t fanSpeed;
extern float speedProcent; // for display fan speed in procent

// varies for tachometer
extern uint32_t counterTacho1;
extern uint32_t counterTacho2;
extern uint32_t rpm1; // revolutions per minute
extern uint32_t rpm2;

extern float temperature;

// create classes for work with DS18B20
extern OneWire DS18;
extern DallasTemperature sensorTemp;

//varies for Wifi and Blynk connection
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Iot Laptop pad"
#define BLYNK_AUTH_TOKEN ""

//#define BLYNK_PRINT Serial

extern char ssid[];
extern char pass[];




