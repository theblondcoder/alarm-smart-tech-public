#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#include "network.h"
#include "secrets.h"
#include "certificates.h"


void initNetwork() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// --------------------
// CONVERT STATE TO STRING
// --------------------

String stateToString(SystemState state) {

  switch (state) {

    case NORMAL:
      return "NORMAL";

    case WARNING:
      return "WARNING";

    case CRITICAL:
      return "CRITICAL";

    case OFF:
      return "OFF";
  }

  return "UNKNOWN";
}


// --------------------
// SEND RUNNING STATUS
// --------------------

bool sendSystemStatus(SensorData data, SystemState state) {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi not connected");

    return false;
  }


  WiFiClientSecure client;

  
  //CA that we are going to trust

  client.setCACert(ISRG_ROOT_X1);


  HTTPClient http;

  if (!http.begin(client, API_URL)) {

    Serial.println("Failed to initialize HTTPS connection");

    return false;
  }


  http.addHeader("Content-Type", "application/json");

  http.addHeader("X-API-Key", API_KEY);


  String json = "{";

  json += "\"system\":\"RUNNING\",";

  json += "\"state\":\"";
  json += stateToString(state);
  json += "\",";

  json += "\"temperature\":";
  json += String(data.temperature, 1);
  json += ",";

  json += "\"humidity\":";
  json += String(data.humidity, 1);
  json += ",";

  json += "\"smoke\":";
  json += String(data.smokeValue);
  json += ",";

  json += "\"flame\":";
  json += String(data.flameValue);

  json += "}";


  int responseCode = http.POST(json);


  Serial.print("API response: ");

  Serial.println(responseCode);


  if (responseCode > 0) {

    String response = http.getString();

    Serial.print("API message: ");

    Serial.println(response);
  }


  http.end();


  return responseCode == 200;
}

// --------------------
// SEND OFF STATUS
// --------------------

bool sendOffStatus() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi not connected");

    return false;
  }


  WiFiClientSecure client;


  client.setCACert(ISRG_ROOT_X1);


  HTTPClient http;

  if (!http.begin(client, API_URL)) {

    Serial.println("Failed to initialize HTTPS connection");

    return false;
  }


  http.addHeader("Content-Type", "application/json");

  http.addHeader("X-API-Key", API_KEY);


  String json = "{";
  json += "\"system\":\"OFF\",";
  json += "\"state\":\"OFF\"";
  json += "}";


  int responseCode = http.POST(json);


  Serial.print("OFF API response: ");

  Serial.println(responseCode);


  http.end();


  return responseCode == 200;
}


