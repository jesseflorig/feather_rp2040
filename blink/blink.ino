// Author: Jesse Florig
// License: MIT
// Board: Adafruit Feather RP2040
// Description: This sketch blinks the onboard NeoPixel with a random color every .5 seconds

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 16
#define NUMPIXELS    1

Adafruit_NeoPixel strip(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50);
}

void loop() {
  // Generate random RGB values (0–255)
  uint8_t r = random(0, 256);
  uint8_t g = random(0, 256);
  uint8_t b = random(0, 256);

  uint32_t randomColor = strip.Color(r,g,b);
  uint32_t offColor = strip.Color(0, 0, 0);
  
  strip.setPixelColor(0, randomColor);  // Random Color
  strip.show();
  delay(500);
  strip.setPixelColor(0, offColor);  // Off
  strip.show();
  delay(500);
}
