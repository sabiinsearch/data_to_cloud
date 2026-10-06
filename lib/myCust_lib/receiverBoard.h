#include <Arduino.h>

#ifndef __RECEIVER_BOARD_H__
#define __RECEIVER_BOARD_H__

// Sensors Config


#define RX_GPS                16
#define TX_GPS                17

// #define RGB LEDs
#define HEARTBEAT_LED       27         // Red
#define WIFI_LED            14         // Green
#define MQTT_LED            26         // Blue

unsigned long int getBoard_ID();

#endif