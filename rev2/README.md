# __Plant Sensor__
This proyect works with a esp8266 (esp32 implementation still in progress). It consists of a node that communicate with AWS IoT Core through MQTT and the data that it sends its readed from the board ADC. In this case the ADC is connected to a Analog Multiplexer(MAX328) so we can have more than 1 analog sensor.

it allows multiple configurations of wifi networks and endpoint through defines that can be found on the constants.h file. In fact all pins definitions and other information used during the set up must be changed on this file.

The sensorsControl library, as  its name imply, it's used to control the sensor multiplexor, initialize the sensors and get their samples as integers or percantege
