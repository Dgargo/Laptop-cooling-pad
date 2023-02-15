#include "serial.h"

#include <Arduino.h>

// Show information in serial port
void Serial_Display(float temperature, float speedProcent, int rpm1, int rpm2)
{
  Serial.print(F("Temp C: "));
  Serial.print(temperature);
  Serial.print(F("\tFan Speed: "));
  Serial.print(speedProcent);
  Serial.print(F(" %\tRPM 1 : "));
  Serial.print(rpm1);
  Serial.print(F("\tRPM 2 : "));
  Serial.println(rpm2);
}
