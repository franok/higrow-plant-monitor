// wifi functions

void connectWifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, wifiPassword);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED)
  {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    blinkBlue(250, 250); // replaces delay(500) --> 500ms
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void disconnectWifi(){
  Serial.println("Disconnect WiFi...");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  //btStop();
}
