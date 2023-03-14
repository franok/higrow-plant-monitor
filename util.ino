// variables should be defined globally at beginning of main .ino file
// PIN_LED_BLUE = 16 // on-board LED
// ON = LOW // LOW or 0 is power on for my board's blue LED
// OFF = HIGH // HIGH or 1 is power off for my board's blue LED

void blink(int ledPinNumber, int onDurationDelay, int offDurationDelay) {
  digitalWrite(ledPinNumber, ON);
  delay(onDurationDelay);
  digitalWrite(ledPinNumber, OFF);
  delay(offDurationDelay);
}

void blinkBlue(int onDurationDelay, int offDurationDelay) {
  blink(PIN_LED_BLUE, onDurationDelay, offDurationDelay);
}

/*
* deepsleep causes the esp32 controller to restart after specified time
* this means, it will run the setup method again
*/
void deepSleep() {

  digitalWrite(POWER_CTRL, LOW);
  //digitalWrite(dhtpowerpin, LOW);
  disconnectWifi();
  Serial.print("ESP32 MAC address: ");
  Serial.println(WiFi.macAddress());
  
  Serial.print("\n"); // empty line
  uint64_t sleepDurationInSeconds = DEEPSLEEP_SECONDS + DEEPSLEEP_CALIBRATION_SECONDS;
  if (debugEnabled == true) {
    Serial.println("DEBUG mode is active!");
    sleepDurationInSeconds = 10;
    Serial.print("Sleeptime reduced to ");
    Serial.print(sleepDurationInSeconds);
    Serial.println(" seconds.\n");
  } else {
    Serial.println("Going to deep sleep Zzzz...\n");
  }

  // Configure timer to wake up from deep sleep!
  esp_sleep_enable_timer_wakeup(sleepDurationInSeconds * uS_TO_S_FACTOR);

  // Go to sleep! Zzzz
  esp_deep_sleep_start();
}

void printCurrentTime() {
  struct tm currentTime;
  if(!getLocalTime(&currentTime)) {
    Serial.println("Failed to obtain current time");
    return;
  }
  Serial.println(&currentTime, "%A, %B %d %Y %H:%M:%S");
}

String getCurrentTimeAsIsoString() {
  
  time_t     now = time(0);
  struct tm currentTime;
  char       isoTime[80];
  currentTime = *localtime(&now);
  strftime(isoTime, sizeof(isoTime), "%Y-%m-%dT%H:%M:%S", &currentTime);

  // Serial.println(isoTime); // debug

  return isoTime;
}

void floatToString(float floatValue, int floatStringCharacters, int decimalDigits, char* resultVar) {
  dtostrf(floatValue, floatStringCharacters, decimalDigits, resultVar);
}
