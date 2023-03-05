#include "config.h"


// Set operating mode
uint32_t minTemp = 20;   // min. temperature
uint32_t maxTemp = 60;   // max. temperature
uint32_t minSpeed = 500; // (0-1022) min speed
uint32_t maxSpeed = 1023; // (1-1023) max speed

//variables for set speed fans
u_int32_t newFanSpeed = 0;
u_int32_t fanSpeed = 100;
float speedProcent = 0; // for display fan speed in procent

//variables for tachometer
uint32_t counterTacho1 = 0;
uint32_t counterTacho2 = 0;
uint32_t rpm1; // revolutions per minute
uint32_t rpm2;

float temperature;

//variables for connection MQTT server
const char* wifi_ssid = "";
const char* wifi_pass = "";

const char* mqtt_ip = "";
const int   mqtt_port =0 ;

//creat semaphore variable for MQTT server
SemaphoreHandle_t sema_MQTT_KeepAlive;



