// https://github.com/LilyGO/higrowopen/blob/master/HiGrowEsp32/HiGrowEsp32.ino
/*
   Rui Santos
   Complete Project Details http://randomnerdtutorials.com
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <base64.h>
#include "time.h"
#include <ArduinoJson.h>
#include "DHT.h"

#include "credentials.h" // do not change order
#include "config.h" // do not change order
#include "global.h" // do not change order

// Initialize DHT sensor.
DHT dht(DHT_PIN, DHTTYPE);


void setup() {
  // Initialize serial
  Serial.begin(115200);
  Serial.println("\n ---------------------");
  Serial.println("Setup HiGrow board...");


  setupOnboardLED();

  initializeSensors();

  connectWifi();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("Finished Setup!");
  Serial.println();
}

void loop() {

  String sensorData = getSensorDataAsJson();
  
  httpsPost("/pilea/1", sensorData);

  blinkBlue(2000, 2000);

  deepSleep();

}

/***********************************/
/* ******** SETUP methods ******** */

void setupOnboardLED() {
  pinMode(PIN_LED_BLUE, OUTPUT);
  digitalWrite(PIN_LED_BLUE, OFF);
}

void initializeSensors() {
  // initialize the DHT sensor
  // DHT dht(DHT_PIN, DHTTYPE);
  dht.begin();
}

/* ******** END of SETUP methods ******** */
/******************************************/


