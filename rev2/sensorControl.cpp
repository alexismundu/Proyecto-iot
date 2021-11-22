#include "sensorControl.h"
#include "constants.h"
#include "Arduino.h"
#include "DHT.h"


DHT dht(DHTPIN, DHTTYPE);

bool sensorControl::init(void){
#ifndef ESP32
    pinMode(MOISTURE_SW,OUTPUT);
    pinMode(LIGHT_SW,OUTPUT);
    digitalWrite(LIGHT_SW,HIGH);
    dht.begin();
    return true;
#else
    pinMode(MOISTURE_SW,OUTPUT);
    pinMode(LIGHT_SW,OUTPUT);
    return true;
#endif
    return false;
}

int sensorControl::getMoisture() {
#ifndef ESP32
    digitalWrite(MOISTURE_SW,HIGH);
    return analogRead(ASENSOR);
#else
    return analogRead(MOISTURE);
#endif
}
int sensorControl::getLight() {
#ifndef ESP32
    digitalWrite(MOISTURE_SW,LOW);
    return analogRead(ASENSOR);
#else
    return analogRead(MOISTURE);
#endif
}
float sensorControl::getTemp() {
#ifndef ESP32
    return dht.readTemperature();
#else
    return dht.readTemperature();

#endif
}

int sensorControl::getMoistureAvg() {
#ifndef ESP32
    int moisture = getMoisture();
    moisture = (moisture * 100)/DRY;
    moisture = 100 - moisture;
    return moisture;
#else
    return analogRead(MOISTURE);
#endif
}
int sensorControl::getLightAvg() {
#ifndef ESP32
    int light = getLight();
    light = (light * 100)/MAXLIGHT;
    return light;
#else
    return analogRead(MOISTURE);
#endif
}
