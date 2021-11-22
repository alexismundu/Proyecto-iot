#include "sensorControl.h"
#include "constants.h"
#include "Arduino.h"

bool sensorControl::init(void){
#ifndef ESP32
    pinMode(MOISTURE_SW,OUTPUT);
    pinMode(LIGHT_SW,OUTPUT);
    digitalWrite(MOISTURE_SW,HIGH);
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
    digitalWrite(LIGHT_SW,LOW);
    return analogRead(ASENSOR);
#else
    return analogRead(MOISTURE);
#endif
}
int sensorControl::getLight() {
#ifndef ESP32
    digitalWrite(LIGHT_SW,HIGH);
    return analogRead(ASENSOR);

#else
    return analogRead(MOISTURE);
#endif
}
int sensorControl::getMoistureAvg() {
#ifndef ESP32
    int moisture = getMoisture();
    moisture = (moisture * 100)/SOAKED;
    Serial.print("Moisture average =");
    Serial.println(moisture);
    return moisture;
#else
    return analogRead(MOISTURE);
#endif
}
int sensorControl::getLightAvg() {
#ifndef ESP32
    int light = getLight();
    light = (light * 100)/MAXLIGHT;
    light = 100 - light;
    Serial.print("Light average =");
    Serial.println(light);
    return light;
#else
    return analogRead(MOISTURE);
#endif
}
