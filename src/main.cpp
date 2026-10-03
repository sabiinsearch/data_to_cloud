// Libraries for AWS
#include "secrets.h"             //  for AWS Certificates and Keys
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "app_config.h"     // for Custom Configration

// Others
//#include <TinyGPSPlus.h>

// my libraries
#include "appManager.h"
#include "receiverBoard.h"
#include "sensor.h"

int publish_counter=0;
// my Managers
appManager managr;


// DHT dht(DHTPIN, DHTTYPE);

// WiFiClientSecure net = WiFiClientSecure();
// PubSubClient client(net);


void setup()
{

  // Change from 2048 to 4096 or higher
//xTaskCreate(TaskFunction, "ScaleTask", 4096, NULL, 1, NULL);

  Serial.begin(115200);
 
    // Initiating Manager
  //Serial.println("Initializing App Manager..");
  appManager_ctor(&managr);
  
  Serial.println("All Systems Initialized..");
 
}

void loop()
{
    
 // getSensorData_print_update(&managr);
   if(publish_counter>PUBLILISH_INTERVAL) {      
      managr.publish_check = true;
      publish_counter = 0;
   } else {
      
      managr.publish_check = false;
   }
   publish_counter++;

   getGPSdata(&managr);
   
  
  
  loop_mgr(&managr);
  Serial.println(F("==>> in loop() : main.cpp"));
  //delay(1000);
}