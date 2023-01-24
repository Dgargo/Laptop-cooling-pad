#include "config.h"

// Set operating mode
int MIN_TEMP = 20;   // min. temperature
int MAX_TEMP = 40;   // max. temperature
int MIN_SPEED = 25;  // (0-255) min speed
int MAX_SPEED = 255; // (0-255) max speed
// varies for set speed fans
byte newFanSpeed = 0;
byte fanSpeed = 0;
float speedProcent = 0; // for display fan speed in procent

// varies for tachometer
int count1 = 0;
int count2 = 0;
int rmp1; // revolutions per minute
int rmp2;

float temperature;

// varies for timer
uint16_t timerOne, timerTwo;
int timeFan = 500;
int timeDisplay = 2000;