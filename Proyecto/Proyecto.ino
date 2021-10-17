#include "EspMQTTClient.h"
#include "Wifi.h"

#include <NewPing.h>
#include <DHT.h>

#define TRIGGER_PIN 22
#define ECHO_PIN 23
#define MAX_DISTANCE 200

#define DHTPIN 32
#define DHTTYPE DHT11

#define LED1 5

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Acre";
const char* password = "53A554EAkt6D5ch9";

void setup()
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);

  WiFi.begin(ssid, password);
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("Conectado a internet, mi IP es:");
  // Print the IP address
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop()
{
  delay(2000);
  int distance = sonar.ping_cm();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  float hic = dht.computeHeatIndex(t, h, false);

  if(distance <= 5) {
    digitalWrite(LED1, HIGH);
  }else{
    digitalWrite(LED1, LOW);
  }

  Serial.print("Temperatura: ");
  Serial.println(String(t, 2));
  Serial.print("Humedad: ");
  Serial.println(String(h, 2));
  Serial.print("Sensacion Termica: ");
  Serial.println(String(hic, 2));
  Serial.print("Luz: ");
  Serial.println(String(distance));
}
