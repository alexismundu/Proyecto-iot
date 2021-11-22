#ifndef CONST_H
#define CONST_H

#include <ESP8266WiFi.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>


#define MSGPERIOD 5000
#define MQTTPORT 1883
#define ARCMANDO
//#define ESP32


//network setup
#ifdef ARCMANDO
//const char WIFI_SSID[] = "IoT";
//const char WIFI_PASSWORD[] = "1t3s0IoT18";
//const char AWS_IOT_ENDPOINT[] = "a1kznbi579ho46-ats.iot.us-east-2.amazonaws.com";
const char WIFI_SSID[] = "whitech";
const char WIFI_PASSWORD[] = "mando1502";
const IPAddress ENDPOINT(185,150,191,67);
const char SENSORTOPIC[] = "/home/sensors/plant";
#
#else 
const char WIFI_SSID[] = "whitech";
const char WIFI_PASSWORD[] = "mando1502";
const char AWS_IOT_ENDPOINT[] = "a1h6u03kfmgopw-ats.iot.us-east-1.amazonaws.com";
#endif


#ifdef ESP32

//Pins definitions
#define BLUE 4
#define GREEN 16
#define RED 17
#define MOISTURE 32
#define LIGHT 33
#define SETUP_BTN 19

//definitions for sensor adc value
#define DRY 4095
#define SOAKED 1700
#define MAXLIGHT 4095
#define NOLIGHT 1700
//definitions for PWM 
#define PWM_freq 5000
#define REDChannel 0
#define BLUEChannel 1
#define GREENChannel 2
#define PWM_resolution 8
#define RED_VAL 0x2A
#define GREEN_VAL 0x00
#define BLUE_VAL 0x33 
#define LEDC_TIMER_13_BIT 13


#else

#define ASENSOR A0
#define BLUE 4
#define GREEN 16
#define RED 17
#define SETUP_BTN 19
#define LIGHT_SW 9
#define MOISTURE_SW 10
#define DHTPIN 2     // what digital pin the DHT22 is conected to
#define DHTTYPE    DHT11
//definitions for sensor adc value
#define DRY 1023
#define SOAKED 500 
#define MAXLIGHT 1023 
#define NOLIGHT 500 

#endif


#endif
