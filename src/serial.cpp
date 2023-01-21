#include "Serial.h"

// Show information in serial port
void SerialDispelay(float temperature , float speedProcent , int rmp1 , int rmp2)
{
  Serial.print(F("Temp C: "));
  Serial.print(temperature);
  Serial.print(F("\tFan Speed: "));
  Serial.print(speedProcent);
  Serial.print(F(" %\tRPM 1 : "));
  Serial.print(rmp1);
  Serial.print(F("\tRPM 2 : "));
  Serial.println(rmp2);
}
