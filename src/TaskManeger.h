#include "config.h"
#include "Fan.h"
#include "Serial.h"

//control Speed
void ControlSpeed(void *pvParameters);

//Control interrupt for tacho sensor
void ControlInterrupt(void *pvParameters);

// Show information in serial port
void ControlSerial(void *pvParameters);
