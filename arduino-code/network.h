#ifndef NETWORK_H
#define NETWORK_H

#include "config.h"
#include "sensors.h"

void initNetwork();

bool sendSystemStatus(SensorData data, SystemState state);

bool sendOffStatus();

#endif