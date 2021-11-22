#ifndef CONST_H
#define CONST_H


#define ARCMANDO
//#define ESP32


//network setup
#ifdef ARCMANDO
const char WIFI_SSID[] = "whitech";
const char WIFI_PASSWORD[] = "mando1502";
const char AWS_IOT_ENDPOINT[] = "a1kznbi579ho46-ats.iot.us-east-2.amazonaws.com";
#else 
const char WIFI_SSID[] = "whitech";
const char WIFI_PASSWORD[] = "mando1502";
const char AWS_IOT_ENDPOINT[] = "a1h6u03kfmgopw-ats.iot.us-east-1.amazonaws.com";
#endif

#define MSGPERIOD 5000

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
#define LIGHT_SW 10
#define MOISTURE_SW 9
//definitions for sensor adc value
#define DRY 1023
#define SOAKED 1700
#define MAXLIGHT 1023 
#define NOLIGHT 1700

#endif


#endif
