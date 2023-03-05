#include "config.h"
#include "WiFi.h"
#include "PubSubClient.h"


extern WiFiClient ESP_Client;
extern PubSubClient MQTT_Client;

//Wifi event 
void WiFiEvent(WiFiEvent_t event);

//connect to wifi
void connectToWiFi();

//connect to MQTT
void connectToMQTT();

//for processing parameters from the topic
void Change_configure(u_int32_t &parameter,byte* message,String name);

//callBacks 
void Callback(String topic, byte* message, unsigned int length);
