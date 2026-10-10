#ifndef CONFIG_H
#define CONFIG_H


// --------------------
// PINS
// --------------------

const int DHT_PIN = 13;

const int SDA_PIN = 21;

const int SCL_PIN = 22;

const int BUZZER_PIN = 18;

const int MQ_PIN = 34;

const int FLAME_PIN = 35;

const int SWITCH_PIN = 19;


// --------------------
// RGB LED MODULE
// --------------------

#define LEDS_COUNT 8

#define LEDS_PIN 2

#define CHANNEL 0


// --------------------
// SYSTEM STATES
// --------------------

enum SystemState {

  NORMAL,

  WARNING,

  CRITICAL,

  OFF

};


// --------------------
// TEMPORARY THRESHOLDS
// --------------------

const float TEMP_WARNING = 25.0;

const float TEMP_CRITICAL = 27.0;

const int SMOKE_WARNING = 20;

const int SMOKE_CRITICAL = 60;

const int FLAME_WARNING = 1500;

const int FLAME_CRITICAL = 100;

// --------------------
//MAXIMUN INTERVAL TO UPDATE DATA IN RASPBERRY
// --------------------
const unsigned long STATUS_INTERVAL = 10000;


#endif