#include "wifi.h"
#include "constants.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
 
const char * _ssid = WIFI_SSID;
const char * _password = WIFI_PASSWORD;

WiFiUDP _ntpUDP;
NTPClient _timeClient(_ntpUDP, "pool.ntp.org");

bool wifi::reconnect_wifi(void)
{
    setup_wifi();
}
bool wifi::setup_wifi() {
  delay(10);
  // Inicializamos Wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(_ssid);
  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  _timeClient.begin();
  while (!_timeClient.update()) {
    _timeClient.forceUpdate();
  }
}
bool wifi::init(void)
{
    if (setup_wifi())
        return true;
    return false;
}

