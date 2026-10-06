#include <Arduino.h>
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

//HardwareSerial gpsSerial(2);

connectionManager conManagerr;

Preferences pref;

// The TinyGPSPlus object
TinyGPSPlus gps;


/* constructor implementation */

void appManager_ctor(appManager * const me) {

      
    // Start I2C on custom pins (for ESP32)
 // Wire.begin(SDA, SCL);
  // Serial2.begin(9600, SERIAL_8N1, RX_GPS, TX_GPS); // Serial for GPS module on ESP32  
  Serial.println("NEO-6M GPS initialized. Waiting for satellite lock...");

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

 void displayInfo(appManager* appMgr)
{ 
  if (gps.location.isValid()) {
    Serial.print(F("Latitude: ")); 
    Serial.println(gps.location.lat(), 6);
    Serial.print(F("Longitude: ")); 
    Serial.println(gps.location.lng(), 6);
    Serial.print(F("Altitude: ")); 
    Serial.println(gps.altitude.meters());
      // Increase size for time string
      StaticJsonDocument<512> doc;  
      
      doc["UID"] = UNIQUE_ID;
      doc["Lat"] = gps.location.lat();
      doc["Lng"] = gps.location.lng();
      doc["Alt"] = gps.altitude.meters();
    

      char jsonBuffer[512]; // Increased buffer size
      serializeJson(doc, jsonBuffer); // print to client
      
      if(!(appMgr->conManager->client.connected())) {

           connectAWS(appMgr->conManager); 
      }
        if (appMgr->publish_check) {
         publishOnMqtt(jsonBuffer, appMgr->conManager);

        } 

  } else {
    Serial.print(F("Location: Not Available (Searching for satellites...)"));
  }
  Serial.println();
  delay(1000);

          //          Serial.print("Published : ");
        //  Serial.println(appMgr->publish_check);
        
}



 void getGPSdata(appManager* appMgr) {
  // Read incoming data from GPS module
  while(Serial2.available() > 0) {
    //  char c = Serial2.read();
    //   Serial.write(c); // Uncomment this line to see raw GPS data in Serial Monitor
      gps.encode(Serial2.read()); // Feed byte to the parser
      displayInfo(appMgr);
    
  }

  // If 5 seconds pass with no data
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS data received: check wiring"));
    //delay(5000);
  }
 }
 
 void initBoard() {  
  // Configuring Board pins

  Serial.println();
  Serial.println(F("Done."));

 }
 
 
 
 



 


 
