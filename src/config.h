#pragma once
#include <Arduino.h>
#include<map>

// Set periphery
#define SET_TEMP GPIO_NUM_32  // Set DS18B20

#define SET_FAN_FIRST GPIO_NUM_16   // Set Fan 1
#define SET_FAN_SECOND GPIO_NUM_17  // Set Fan 2

#define SET_TACHO_FIRST GPIO_NUM_18  // Set tachometer 1
#define SET_TACHO_SECOND GPIO_NUM_19 // Set tachometer 2

#define TIME_PUBLISH 50 
// Set time for task Manager
#define TASK_TIME_CONTROL_SPEED 2000
#define TASK_TIME_CALCULATE_RPM 1000
#define TASK_TIME_SERIAL_DISPLAY 2000
#define TASK_TIME_SUBSCRIBE_TOPICS 5000
#define TASK_TIME_PUBLISH 5000
// Set time for connection networking 
#define TIME_CONNECT_WIFI 3000
#define TIME_CONNECT_MQTT 250
#define TIME_KEEP_ALIVE_MQTT 90
// for Debuging
#define DEBUG
#define LED_DEBUG GPIO_NUM_21

// Set operating mode
extern uint32_t minTemp;  // min. temperature
extern uint32_t maxTemp;  // max. temperature
extern uint32_t minSpeed; // (0-255) min speed
extern uint32_t maxSpeed; // (0-255) max speed

//variables for set speed fans
extern u_int32_t newFanSpeed;
extern u_int32_t fanSpeed;
extern float speedProcent; // for display fan speed in procent

//variables for tachometer
extern uint32_t counterTacho1;
extern uint32_t counterTacho2;
extern uint32_t rpm1; // revolutions per minute
extern uint32_t rpm2;

//variable for DS18B20
extern float temperature;


//variables for connection MQTT server
extern const char* wifi_ssid ;
extern const char* wifi_pass ;

extern const char* mqtt_ip ;
extern const int   mqtt_port ;

//creat semaphore variable for MQTT server
extern SemaphoreHandle_t sema_MQTT_KeepAlive;




