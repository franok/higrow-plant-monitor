// sensor functions

String getSensorDataAsJson() {

  float humidity = readHumidity();

  float tempC = readTemperatureInC();

  float humanPerceivedTempC = calculateHeatIndex(tempC, humidity);

  uint16_t soilMoisture = getRelativeSoilMoisture();


  const int capacity = 128; // calculated with https://arduinojson.org/v6/assistant
  StaticJsonDocument<capacity> doc;

  doc["timestamp"] = getCurrentTimeAsIsoString();
  doc["humidityInPercent"] = humidity;
  doc["temperatureInCelsius"] = tempC;
  doc["perceivedTemperatureInCelsius"] = humanPerceivedTempC;
  doc["soilMoistureInPercent"] = soilMoisture;
  
  String jsonString = "";  // the JSON document is appended to the String, it doesn’t replace it
  serializeJson(doc, jsonString);

  // serializeJsonPretty(doc, Serial); // debug
  // Serial.println();

  // debugSensorData();

  return jsonString;
}

uint16_t readSoilRaw() {
  return analogRead(SOIL_PIN);
}

float readHumidity() {
  float humidity;
  while (isnan(humidity = dht.readHumidity())) {
    delay(100);
  }
  return humidity;
}

float readTemperatureInC() {
  // Read temperature as Celsius //dht.readTemperature(boolean isFahrenheit); default = false
  float temperatureC;
  while (isnan(temperatureC = dht.readTemperature())) {
    delay(100);
  }
  return temperatureC;
}

uint16_t getRelativeSoilMoisture() {
  uint16_t soil = readSoilRaw();
  if (soil > SOIL_MAX)
  {
    soil = SOIL_MAX; // prevent overflow
    Serial.println("overflow in soil_max (dry)");
    // Todo: send warning log to server
  }
  
  uint16_t soil_mapped = map(soil, SOIL_MIN, SOIL_MAX, 100, 0);
  return soil_mapped;
}

// char getTemperatureInC() {
//   char celsiusString[7];
//   floatToString(readTemperatureInC(), 6, 2, celsiusString);
//   return celsiusString;
// }

// char getHumidity() {
//   char humidityString[7];
//   floatToString(readTemperatureInC(), 6, 2, humidityString);
//   return humidityString;
// }


/*
* heat index is the human-perceived temperature, aka felt air temperature
*/
float calculateHeatIndex(float temperatureInC, float humidity) {
  return dht.computeHeatIndex(temperatureInC, humidity, false);
}


void debugSensorData() {
  // float humidity = atof(getHumidity());
  float humidity = readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %");

  // float tempC = atof(getTemperatureInC());
  float tempC = readTemperatureInC();
  Serial.print("\t Temperature: ");
  Serial.print(tempC);
  Serial.print(" *C ");
  
  Serial.print("\t Felt air temperature: ");
  Serial.print(calculateHeatIndex(tempC, humidity));
  Serial.print(" *C ");

  Serial.print("\t Soil: ");
  Serial.print(getRelativeSoilMoisture());
  Serial.print(" %");

  Serial.print("\t Soil raw: ");
  Serial.print(readSoilRaw());

  Serial.println();
  Serial.println();
   
  delay(1000);
}
