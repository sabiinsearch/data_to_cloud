
#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include "Arduino.h"


#define UNIQUE_ID "device_001"  // change this for each device

#define BAT_MIN_THRESHOLD       7  // Voltage threshold for high battery
#define BAT_MAX_THRESHOLD       15  // Voltage threshold for low battery

#define voltageDividerRatio     0.0909  // Adjust this based on your voltage divider circuit
#define referenceVoltage        3.6  // Reference voltage for ADC (ESP32 typically uses 3.3V)
#define adcResolution           4095 // 12-bit ADC resolution for ESP32
#define calibrationFactor       0.9563   // Adjust this based on your calibration

/******* Staging Credentials sending data to cloud  *******/
   #define SERVER_NAME_STAGING   "https://staging-api.dairysaathi.com/devices/readings"  // Staging server URL
   #define API_KEY_STAGING        "dc687b313365c2b96aa86ddc5d1b280159de27cb19a81071264218c422380164"  // Staging

/******************************* Do Not Edit / update these values      **************************************/
//  Mqtt Configurations 
    #define THINGNAME               "GPS_Device"        // Change this
    #define WIFI_SSID               "hukam"                    //change this
    #define WIFI_PASSWORD           "guest@13"                 //change this
    #define AWS_ENDPOINT            "am2i6420agb0f-ats.iot.ap-south-1.amazonaws.com"   // AWS MQTT Broker URL  
    #define AWS_IOT_PUBLISH_TOPIC   "Device/GPS_data_frm"           //change this
    #define AWS_IOT_SUBSCRIBE_TOPIC "Device/GPS_data_to"           //change this

    #define PUBLILISH_INTERVAL  200       // seconds  // actually 16 seconds 
    #define TIMEOUT_INTERVAL    120       // seconds
    #define DISPLAY_TIME        10000      // milliseconds  
#endif