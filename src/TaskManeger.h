#include "config.h"
#include "fan.h"
#include "serial.h"

// control Speed
void ControlSpeed(void *pvParameters);

// Show information in serial port
void ControlSerial(void *pvParameters);

void TachoTask(void *pvParameters);