#ifndef SENSORS_H
#define SENSORS_H


// --------------------
// SENSOR DATA
// --------------------

struct SensorData {

  float temperature;

  float humidity;

  int smokeValue;

  int flameValue;

};


// --------------------
// FUNCTIONS
// --------------------

void initSensors();

SensorData readSensors();


#endif