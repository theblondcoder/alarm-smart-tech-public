#include <Arduino.h>

#include "debug.h"


// --------------------
// PRINT SYSTEM DATA
// --------------------

void printSystemData(SensorData data, SystemState state) {

  Serial.println("--------------------------");

  Serial.print("Temperature: ");

  Serial.print(data.temperature);

  Serial.println(" C");

  Serial.print("Humidity: ");

  Serial.print(data.humidity);

  Serial.println(" %");

  Serial.print("Smoke/Gas: ");

  Serial.println(data.smokeValue);

  Serial.print("Flame: ");

  Serial.println(data.flameValue);

  Serial.print("State: ");

  switch (state) {

    case NORMAL:

      Serial.println("NORMAL");

      break;

    case WARNING:

      Serial.println("WARNING");

      break;

    case CRITICAL:

      Serial.println("CRITICAL");

      break;

    case OFF:

      Serial.println("OFF");

      break;
  }
}


// --------------------
// PRINT SYSTEM OFF
// --------------------

void printSystemOff() {

  Serial.println("--------------------------");

  Serial.println("State: OFF");
}