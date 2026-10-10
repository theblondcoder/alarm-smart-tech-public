#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "config.h"
#include "sensors.h"


// --------------------
// INITIALIZE OUTPUTS
// --------------------

void initOutputs();


// --------------------
// LCD
// --------------------

void updateLCD(SensorData data, SystemState state);

void updateLCDOff();


// --------------------
// RGB
// --------------------

void updateRGB(SystemState state);

void setAllLEDs(int red, int green, int blue);


// --------------------
// BUZZER
// --------------------

void updateBuzzer(SystemState state);


#endif