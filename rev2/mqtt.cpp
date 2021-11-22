#include "mqtt.h"
#include "constants.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

WiFiClient _espClient;
PubSubClient _client;

static long lastMsg = 0;

void callback(char * topic, byte * payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}
bool mqtt::setup_mqtt(){
 _client.setServer(ENDPOINT, MQTTPORT);
 _client.setCallback(callback);
 _client.setClient(_espClient);
 reconnect_mqtt();
}

bool mqtt::init(){
    while(!setup_mqtt()){
        setup_mqtt();
    }
 }

bool mqtt::reconnect_mqtt() {
  // Reconeccion si es necesario
  while (!_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (_client.connect("espthinsfjle")) {
      Serial.println("connected");
      _client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  return true;
}

 void mqtt::publish(const char *message, const char* topic)
{
    delay(1000);
    _client.publish(topic, message);
    delay(1000);
}

 void mqtt::publishPeriodically(const char *message, const char* topic, long period)
{
  long now = millis();
     if (now - lastMsg > MSGPERIOD) {
    Serial.print("Publish message: ");
    Serial.println(message);
    _client.publish(topic,message);
    lastMsg = now;
  }
}
void mqtt::loop(void)
{
  if (!_client.connected()) {
    reconnect_mqtt();
  }
  _client.loop();

}
