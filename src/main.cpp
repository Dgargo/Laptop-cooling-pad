#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>


//Set periphery
#define SET_TEMP 9 // Set DS18B20

#define SET_FAN_FIRST   5 // Set Fan 1
#define SET_FAN_SECOND  6 // Set Fan 2

#define SET_TACH_FIRST  2 //Set tachometer 1
#define SET_TACH_SECOND 3 //Set tachometer 2

//Set operating mode
#define MIN_TEMP 25     // min. temperature
#define MAX_TEMP 45     // max. temperature
#define MIN_SPEED 50    // (0-255) min speed
#define MAX_SPEED 255   // (0-255) max speed


//varies for set speed fans
int newFanSpeed = 0;
int fanSpeed = 0;
float speedProcent = 0;//for display fan speed in procent

//varies for tachometer
int count1 = 0;
int count2 = 0;
int rmp1;//revolutions per minute
int rmp2;

float temperature;

//varies for delay
unsigned long start_time;
unsigned int timeMillis = 1000;

//create classes for work with DS18B20
OneWire DS18(SET_TEMP);
DallasTemperature sensorTemp(&DS18);

//Convert temperature from sensor in Speed
void tempToSpeed(){
  newFanSpeed = map(temperature,MIN_TEMP,MAX_TEMP,MIN_SPEED,MAX_SPEED);
  newFanSpeed = constrain(newFanSpeed,MIN_SPEED,MAX_SPEED);
}

//Smooth speed control

void TickFan(){
  if(newFanSpeed > fanSpeed) fanSpeed +=2;
  if(newFanSpeed < fanSpeed) fanSpeed -=2;
  fanSpeed = constrain(fanSpeed,MIN_SPEED,MAX_SPEED);

  speedProcent = (fanSpeed*100)/MAX_SPEED;

  analogWrite(SET_FAN_FIRST,fanSpeed);
  analogWrite(SET_FAN_SECOND,fanSpeed);
}


//interrupt handling
void counter1()
{
  count1++;
}

void counter2()
{
  count2++;
}

//Show information in serial port
void SerialDispelay()
{
  Serial.print("Temp C: ");
  Serial.print(temperature);
  Serial.print("\tFan Speed: ");
  Serial.print(speedProcent);
  Serial.print(" %\t");
  Serial.print("RPM 1 : ");
  Serial.print(rmp1);
  Serial.print("\tRPM 2 : ");
  Serial.println(rmp2);
}

void setup() {

  Serial.begin(9600);


  pinMode(SET_FAN_FIRST,OUTPUT);
  pinMode(SET_FAN_SECOND,OUTPUT);

  sensorTemp.begin();
  sensorTemp.setResolution(12);// set the resolution of the sensor from 9 to 12 bits

  attachInterrupt(digitalPinToInterrupt(SET_TACH_FIRST),counter1,RISING);
  attachInterrupt(digitalPinToInterrupt(SET_TACH_SECOND),counter2,RISING);
}


void loop() {

  //read from the temperature sensor
  sensorTemp.requestTemperatures();
  temperature = sensorTemp.getTempCByIndex(0);

  //control speed
  tempToSpeed();
  TickFan();
  
  count1 = 0;
  count2 = 0;

  //make delay
  start_time = millis();
  while((millis()-start_time) < timeMillis){}

  //calculation of the number of revolutions
  rmp1 = count1 * 60/2;
  rmp2 = count2 * 60/2;

  //show info
  SerialDispelay();


}
