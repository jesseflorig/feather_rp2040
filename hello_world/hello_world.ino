// Author: Jesse Florig
// License: MIT
// Board: Adafruit Feather RP2040
// Description: This sketch prints messages to the serial port

#include <Arduino.h>

void setup() {
  Serial.begin(115200);         // Start serial at 115200 baud
  while (!Serial);              // Wait for Serial Monitor to connect (important on USB-C boards)
  Serial.println("Hello, World!");
}

void loop() {
  Serial.println("Hello again!");
  delay(1000);                  // Wait 1 second
}
