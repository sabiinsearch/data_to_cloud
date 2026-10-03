#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ArduinoJson.h>
#include <time.h>

// libraries for Display
#include <Wire.h>

// Library for GPS
#include <TinyGPSPlus.h>
 #include "Preferences.h"


// Custom Libraries
//#include "app_config.h"
#include "appManager.h"
#include "connectionManager.h"

#include "receiverBoard.h"
// #include "sensor.h"
// Libraries for Load Cell
#include <Arduino.h> 
#include "EEPROM.h"
#include "Preferences.h"
// #include "HX711.h"
#include "soc/rtc.h"
#include "esp32-hal-cpu.h"


connectionManager conManagerr;

Preferences pref;

// A sample NMEA stream.
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
  "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
  "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
  "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
  "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
  "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";

// The TinyGPSPlus object
TinyGPSPlus gps;


/* constructor implementation */

void appManager_ctor(appManager * const me) {

      
    // Start I2C on custom pins (for ESP32)
  Wire.begin(SDA, SCL);

 // initBoard();
  Serial.println("Board Initialized..");


  Serial.println("Sensor Initialized..");

   Serial.println("Gyro Sensor Initialized..");


   me->conManager = connectionManager_ctor(&conManagerr);
  Serial.println("Connection Manager set with App Manager");
}
  
/* Function Implementation */


void connectCloud(appManager* appMgr) {
      connectWiFi(appMgr->conManager);
}


void loop_mgr(appManager* appMgr) {
     loop_con(appMgr->conManager);
}


//function to get sensor data and update appManager

void getSensorData_print_update(appManager* appMgr) {
   
  // get data from sensors
/*
 
  if (updateNeeded) {

      // Increase size for time string
      StaticJsonDocument<512> doc;  
      
      doc["UID"] = UNIQUE_ID;
      
      // Get current time
      struct tm timeinfo;
      if(getLocalTime(&timeinfo)){
        char timeStringBuff[50];
        strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
        doc["time"] = timeStringBuff;
      } else {
        doc["time"] = "NTP_SYNC_FAILED";
      }
      
      
      doc["humidity"] = hum_Buff;
      doc["temperature"] = temp_Buff;
      doc["Load"] = load_Buff;
    

      char jsonBuffer[512]; // Increased buffer size
      serializeJson(doc, jsonBuffer); // print to client

      if(!(appMgr->conManager->client.connected())) {

           connectAWS(appMgr->conManager); 
      }
         publishOnMqtt(jsonBuffer, appMgr->conManager);
         Serial.println("Published ");
         updateNeeded = false;
      
      
      // client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
      //appMgr->conManager-> client .publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  checkGyro(appMgr);
  displayDataOnScreen(appMgr);      

  } else {
      //Serial.println("No significant change in sensor data. Skipping publish.");
  }

    if(((millis()-displayOn_start) > DISPLAY_TIME) && screen_state) {
     
//     displayOn_start = 0; 
     displayOn_start = 0; // reset display timer
     displayOn = false;     // set Display off     
     screen_state = false;
     screen.clearDisplay();  // Clear Display
     screen.display();

    }   
*/ 
}

void initRGB(){
  pinMode(HEARTBEAT_LED, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);
  pinMode(MQTT_LED, OUTPUT);
  
  digitalWrite(HEARTBEAT_LED,HIGH);
  digitalWrite(WIFI_LED,HIGH);
  digitalWrite(MQTT_LED,HIGH);

  //Serial.println("InitRGB : appManager.cpp");
  
 }

 // Function to display GPS info

 void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

 void getGPSdata(appManager* appMgr) {
  while (*gpsStream)
    if (gps.encode(*gpsStream++))
      displayInfo();    
 }
 
 void initBoard() {  
  // Configuring Board pins

   while (*gpsStream)
    if (gps.encode(*gpsStream++))
      displayInfo();

  Serial.println();
  Serial.println(F("Done."));

 }
 
 
 
 



 


 
