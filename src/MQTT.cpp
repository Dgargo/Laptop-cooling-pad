#include "MQTT.h"
#include <string>
WiFiClient ESP_Client;
PubSubClient MQTT_Client(ESP_Client);


//Wifi event 
void WiFiEvent(WiFiEvent_t event)
{
  switch (event) {
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println("Connected to access point");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected from WiFi access point");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      Serial.println("WiFi client disconnected");
      break;
    default: break;
  }
}

//connect to Wifi
void connectToWiFi()
{
  Serial.println( "connect to wifi" );
  while ( WiFi.status() != WL_CONNECTED )
  {
    WiFi.disconnect();
    WiFi.begin( wifi_ssid, wifi_pass );
    Serial.println(" waiting on wifi connection" );
    vTaskDelay( TIME_CONNECT_WIFI );
  }
  Serial.println( "Connected to WiFi" );
  WiFi.onEvent( WiFiEvent );
}

//connect to MQTT
void connectToMQTT()
{
  Serial.print( "connect to mqtt as client %s");
  while ( !MQTT_Client.connected() )
  {
	MQTT_Client.setServer(mqtt_ip, mqtt_port);
    MQTT_Client.connect("Node-red");
    Serial.println( "connecting to MQTT" );
    vTaskDelay( TIME_CONNECT_MQTT );
  }
  Serial.println("MQTT Connected");
}

//for processing parameters from the topic
void Change_configure(u_int32_t &parameter,byte* message,String name,u_int32_t mediumParameter,u_int32_t maxValue)
{
  Serial.print("Changing");
  Serial.print(name);
  Serial.print(" to : ");
  u_int32_t newParameter = atof((char*)message);
  
  //sometimes from topic can publish wrong value ,in such cases, we set the parameter to the medium value
  if(newParameter > maxValue )
  {
    Serial.println("Error value from MQTT!!! ");
    Serial.print(name);
    Serial.print("stand to medium value :");
    Serial.println(mediumParameter);
    parameter = mediumParameter;
  }
  else
  {
    parameter = newParameter;
    Serial.print("Changing");
    Serial.print(name);
    Serial.print(" to : ");
    Serial.println(parameter);
  }
}

//callBacks 
void Callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if(topic == "Led_Control"){
    Serial.print("Changing led debug to ");
      if(messageTemp == "On"){
        digitalWrite(LED_DEBUG, HIGH);
        Serial.print("On");
      }
      else if(messageTemp == "Off"){
        digitalWrite(LED_DEBUG, LOW);
        Serial.print("Off\n");
      }
  }
  else if (topic =="min_temperature" ){
    Change_configure(minTemp,message,"min temperature",15,35);
  }
  else if (topic == "max_temperature"){
    Change_configure(maxTemp,message,"max temperature",50,80);
  }
  else if (topic == "min_speed"){
    Change_configure(minSpeed,message,"min speed",400,1000);
  }
  else if (topic =="max_speed"){
    Change_configure(maxSpeed,message,"max speed",700,1600);
  }
  
}

