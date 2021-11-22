#include "constants.h"
#include "sensorControl.h"
#include <ArduinoJson.h>
#include "FS.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
 
  int light = 0;
  int moisture = 0;
  
 // Actualiza con base a los valores de tu coneccion 
const char * ssid = WIFI_SSID;
const char * password = WIFI_PASSWORD;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
sensorControl sensors;
void callback(char * topic, byte * payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}

WiFiClientSecure espClient;
PubSubClient client(AWS_IOT_ENDPOINT, 8883, callback, espClient); //MQTT port 8883 - standard
long lastMsg = 0;
char msg[512];
int value = 0;
void setup_wifi() {
  delay(10);
  // Inicializamos Wifi
  espClient.setBufferSizes(512, 512);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  espClient.setX509Time(timeClient.getEpochTime());
}
void reconnect() {
  // Reconeccion si es necesario
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("espthinsfjle")) {
      Serial.println("connected");

      client.publish("outTopic", "hello world");
      
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      char buf[256];
      espClient.getLastSSLError(buf, 256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
    sensors.init();
  // inicializamos el led del esp8266
  pinMode(LED_BUILTIN, OUTPUT);
  setup_wifi();
  delay(1000);
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.print("Heap: ");
  Serial.println(ESP.getFreeHeap());
#ifdef ARCMANDO
    SPIFFS.remove("/cert_alexis.der");
    SPIFFS.remove("/ca_alexis.der");
    SPIFFS.remove("/private_alexis.der");
  // Cargamos los certificados
  File cert = SPIFFS.open("/cert.der", "r"); //verifica
  if (!cert) {
    Serial.println("Failed to open cert file");
  } else
    Serial.println("Success to open cert file");
  delay(1000);
  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");
  // Cargamos llave privada
  File private_key = SPIFFS.open("/private.der", "r"); 
  if (!private_key) {
    Serial.println("Failed to open private cert file");
  } else
    Serial.println("Success to open private cert file");
  delay(1000);
  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");
  // Cargamos CA 
  File ca = SPIFFS.open("/ca.der", "r"); 
  if (!ca) {
    Serial.println("Failed to open ca ");
  } else
    Serial.println("Success to open ca");
  delay(1000);
  if (espClient.loadCACert(ca))
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");
    Serial.println("connected to first AWS");
#else
    SPIFFS.remove("/cert.der");
    SPIFFS.remove("/ca.der");
    SPIFFS.remove("/private.der");
  // Cargamos los certificados
  File cert = SPIFFS.open("/cert_alexis.der", "r"); //verifica
  if (!cert) {
    Serial.println("Failed to open 2 cert file");
  } else
    Serial.println("Success to open 2 cert file");
  delay(1000);
  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");
  // Cargamos llave privada
  File private_key = SPIFFS.open("/private_alexis.der", "r"); 
  if (!private_key) {
    Serial.println("Failed to open 2 private cert file");
  } else
    Serial.println("Success to open 2 private cert file");
  delay(1000);
  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");
  // Cargamos CA 
  File ca = SPIFFS.open("/ca_alexis.der", "r"); 
  if (!ca) {
    Serial.println("Failed to 2 open ca ");
  } else
    Serial.println("Success to 2 open ca");
  delay(1000);
  if (espClient.loadCACert(ca))
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");
    Serial.println("connected to second AWS");
#endif
  Serial.print("Heap: ");
  Serial.println(ESP.getFreeHeap());
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > MSGPERIOD) {
    lastMsg = now;
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
    Serial.print("Heap: ");
    Serial.println(ESP.getFreeHeap());
  }
  StaticJsonDocument<200> doc;
  doc["Message"]["L"] = sensors.getLightAvg();
  doc["Message"]["M"] = sensors.getMoistureAvg();
  serializeJson(doc, msg);
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(100); // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  delay(100); // wait for a second
}
