
#include "config.h"
#include "sensors.h"
#include "system_state.h"
#include "outputs.h"
#include "debug.h"
#include "network.h"

SystemState currentState = NORMAL;
SystemState lastSentState = OFF;
unsigned long lastStatusSent = 0;

// --------------------

// SETUP

// --------------------

void setup() {

  Serial.begin(115200);

  //Conecting to the WIFI
    initNetwork();

  // Sensors
    initSensors();

  //Outputs
    initOutputs();

  //Switch

    pinMode(SWITCH_PIN, INPUT_PULLUP);

  Serial.println("Fire Detection System started");

  delay(1000);

}


// --------------------

// LOOP

// --------------------

void loop() {

  // Read switch state
    int switchState = digitalRead(SWITCH_PIN);


  //Save how many seconds since the ESP was turned ON in that moment
  unsigned long currentTime = millis();


  // --------------------
  // SYSTEM OFF
  // --------------------

    if (switchState == LOW) {

      currentState = OFF;

      // Turn off RGB LEDs

        updateRGB(currentState);

      // Turn off buzzer

        updateBuzzer(currentState);

      // Show OFF message on LCD

        updateLCDOff();

      //Show OFF messade on Serial Monitor

        printSystemOff(); 



      // Send immediately if state changed
      // or periodically as heartbeat

      if (
        currentState != lastSentState ||
        currentTime - lastStatusSent >= STATUS_INTERVAL
      ) {

        sendOffStatus();

        lastSentState = currentState;

        lastStatusSent = currentTime;
      }

      delay(200);

      return;
    }


  // --------------------
  // SYSTEM ACTIVE
  // --------------------

    // Read sensors

      SensorData data = readSensors();


    // Determine system state

      currentState = determineState(data);


    // Update LCD

      updateLCD(data, currentState);


    // Update RGB LEDs

      updateRGB(currentState);


    // Update Buzzer

      updateBuzzer(currentState);


    // Serial Monitor

      printSystemData(data, currentState);

    // Send immediately if state changed
    // or periodically as heartbeat

      if (
        currentState != lastSentState ||
        currentTime - lastStatusSent >= STATUS_INTERVAL
      ) {

        sendSystemStatus(data, currentState);

        lastSentState = currentState;

        lastStatusSent = currentTime;
      }


  delay(2000);
}





