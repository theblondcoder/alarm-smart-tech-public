#include <Arduino.h>

#include <DHTesp.h>

#include "config.h"

#include "sensors.h"


// --------------------
// SENSOR OBJECTS
// --------------------

DHTesp dht;


// --------------------
// INITIALIZE SENSORS
// --------------------

void initSensors() {

  dht.setup(DHT_PIN, DHTesp::DHT11);

}


// --------------------
// READ SENSORS
// --------------------

SensorData readSensors() {

  SensorData data;

  data.temperature = dht.getTemperature();

  data.humidity = dht.getHumidity();

  data.smokeValue = analogRead(MQ_PIN);

  data.flameValue = analogRead(FLAME_PIN);

  return data;
}