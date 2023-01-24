#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// Set periphery
#define SET_TEMP 21 // Set DS18B20

#define SET_FAN_FIRST 16  // Set Fan 1
#define SET_FAN_SECOND 17 // Set Fan 2

#define SET_TACH_FIRST 18  // Set tachometer 1
#define SET_TACH_SECOND 19 // Set tachometer 2

// Set time for task Manager
#define TASK_TIME_CONTROL_SPEED 1000
#define TASK_TIME_SERIAL_DISPLAY 2000
// for Debuging
#define DEBUG
#define LED_DEBUG

// Set operating mode
extern int MIN_TEMP;  // min. temperature
extern int MAX_TEMP;  // max. temperature
extern int MIN_SPEED; // (0-255) min speed
extern int MAX_SPEED; // (0-255) max speed

// varies for set speed fans
extern byte newFanSpeed;
extern byte fanSpeed;
extern float speedProcent; // for display fan speed in procent

// varies for tachometer
extern int count1;
extern int count2;
extern int rmp1; // revolutions per minute
extern int rmp2;

extern float temperature;

// varies for timer
extern uint16_t timerOne, timerTwo;
extern int timeFan;
extern int timeDisplay;
