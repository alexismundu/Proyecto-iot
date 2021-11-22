#include "constants.h"
#include "sensorControl.h"
#include "wifi.h"
#include "mqtt.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

sensorControl sensors;
wifi internet;
mqtt mosquitto;

char msg[512];

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  // inicializamos el led del esp8266
  pinMode(LED_BUILTIN, OUTPUT);
  internet.init();
  mosquitto.init();
  sensors.init();
  delay(1000);
}
void loop() {
 mosquitto.loop();
StaticJsonDocument<200> doc;
doc["luz"] = sensors.getLightAvg();
doc["humedad"] = sensors.getMoistureAvg();
doc["temperatura"] = sensors.getTemp();
serializeJson(doc, msg);
 mosquitto.publishPeriodically(msg,SENSORTOPIC,MSGPERIOD);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(100); // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  delay(100); // wait for a second
  ESP.deepSleep(6e7);
}
