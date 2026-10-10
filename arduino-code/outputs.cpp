#include <Arduino.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include "Freenove_WS2812_Lib_for_ESP32.h"

#include "outputs.h"


// --------------------
// OUTPUT OBJECTS
// --------------------

LiquidCrystal_I2C lcd(0x27, 16, 2);

Freenove_ESP32_WS2812 strip =
  Freenove_ESP32_WS2812(
    LEDS_COUNT,
    LEDS_PIN,
    CHANNEL,
    TYPE_GRB
  );


// --------------------
// INITIALIZE OUTPUTS
// --------------------

void initOutputs() {

  // LCD

  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.init();

  lcd.backlight();


  // RGB LEDs

  strip.begin();

  strip.setBrightness(20);


  // Buzzer

  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);


  // Starting message

  lcd.setCursor(0, 0);

  lcd.print("System starting");

}


// --------------------
// UPDATE LCD
// --------------------

void updateLCD(SensorData data, SystemState state) {

  lcd.clear();

  // First row

  lcd.setCursor(0, 0);

  lcd.print("T:");

  lcd.print(data.temperature, 1);

  lcd.print("C ");

  lcd.print("H:");

  lcd.print(data.humidity, 0);

  lcd.print("%");


  // Second row

  lcd.setCursor(0, 1);

  switch (state) {

    case NORMAL:

      lcd.print("State: NORMAL");

      break;

    case WARNING:

      lcd.print("State: WARNING");

      break;

    case CRITICAL:

      lcd.print("State: CRITICAL");

      break;

    case OFF:

      lcd.print("State: OFF");

      break;
  }
}


// --------------------
// UPDATE LCD OFF
// --------------------

void updateLCDOff() {

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("SYSTEM OFF");
}


// --------------------
// UPDATE RGB
// --------------------

void updateRGB(SystemState state) {

  switch (state) {

    case NORMAL:

      setAllLEDs(0, 255, 0);

      break;

    case WARNING:

      setAllLEDs(255, 255, 0);

      break;

    case CRITICAL:

      setAllLEDs(255, 0, 0);

      break;

    case OFF:

      setAllLEDs(0, 0, 0);

      break;
  }
}


// --------------------
// SET ALL RGB LEDS
// --------------------

void setAllLEDs(int red, int green, int blue) {

  for (int i = 0; i < LEDS_COUNT; i++) {

    strip.setLedColorData(i, red, green, blue);

  }

  strip.show();
}


// --------------------
// UPDATE BUZZER
// --------------------

void updateBuzzer(SystemState state) {

  if (state == CRITICAL) {

    digitalWrite(BUZZER_PIN, HIGH);

  }

  else {

    digitalWrite(BUZZER_PIN, LOW);

  }
}