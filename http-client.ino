// http client functions

// initialize wifi client for https
WiFiClientSecure client;

void httpsPost(String path, String jsonPayload) {
    client.setCACert(rootCACertificate);
    // client.setInsecure();
    

    Serial.println("\nStarting connection to server...");
    if (!client.connect(serverUrl.c_str(), serverPort)) {
        Serial.println("Connection failed!");
        char err_buf[100];
        if (client.lastError(err_buf, 100) < 0) {
            Serial.println(err_buf);
        } else {
            Serial.println("Connection error");
        }
    } else {
        Serial.println("Connected to server!");
        
        String data = jsonPayload;
        Serial.print("Sending POST request with payload length ");
        Serial.print(data.length());
        Serial.println(" ...");

        // Make a HTTP request:
        client.println("POST " + path + " HTTP/1.1");
        client.println("Host: " + serverUrl);
        client.println("User-Agent: ESP32");
        client.println("Connection: close");
        client.println("Content-Type: application/json");
        client.print("Authorization: Basic ");
        client.println(base64auth);
        client.print("Content-Length: ");
        client.println(data.length());
        client.println();
        client.println(data);

        while (client.connected()) {
            String line = client.readStringUntil('\n');
            if (line == "\r") {
                Serial.println("response headers received");
                break;
            }
        }
        
        // read and print incoming bytes from server
        Serial.print("Server response: ");
        while (client.available()) {
            String response = client.readStringUntil('\n');
            Serial.println(response);
            if (response.startsWith("debug")) {
                debugEnabled = true;
            }
        }

        client.stop();
    }
    Serial.println();
    Serial.println();
}
