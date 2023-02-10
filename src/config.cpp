#include "config.h"

// Set operating mode
uint32_t MIN_TEMP = 15;   // min. temperature
uint32_t MAX_TEMP = 60;   // max. temperature
uint32_t MIN_SPEED = 500; // (0-1022) min speed
uint32_t MAX_SPEED = 1023; // (1-1023) max speed
// varies for set speed fans
byte newFanSpeed = 0;
byte fanSpeed = 0;
float speedProcent = 0; // for display fan speed in procent

// varies for tachometer
uint32_t counterTacho1 = 0;
uint32_t counterTacho2 = 0;
uint32_t rpm1; // revolutions per minute
uint32_t rpm2;

float temperature;

// create classes for work with DS18B20
OneWire DS18(SET_TEMP);
DallasTemperature sensorTemp(&DS18);

