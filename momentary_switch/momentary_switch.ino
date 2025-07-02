// Author: Jesse Florig
// License: MIT
// Board: Adafruit Feather RP2040
// Description: Uses a momentary NO switch to change the onboard NeoPixel color:
//              green when open, red when closed.

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const int switchPin = 6;           // Momentary switch input
#define NEOPIXEL_PIN 16            // Feather RP2040 onboard NeoPixel pin
#define NUMPIXELS    1

Adafruit_NeoPixel pixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pixel.begin();
  pixel.setBrightness(50);
  pixel.show();
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    // Switch open — green
    pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  } else {
    // Switch pressed — red
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  }

  pixel.show();
  delay(10);  // Small delay to stabilize reading
}
