#include <math.h>

// Pin Setup
const int pwmPinA = 6;  // Use a PWM-capable pin

const int resolution = 16;      // RP2040 is 16-bit
const uint16_t pwmMax = 65535;  // 2^16

// Gamma correction factor
const float gammaCorrection = 2.2;

// Number of steps in the fade
const int steps = 256;

void setup() {
  analogWriteResolution(resolution);
  pinMode(pwmPinA, OUTPUT);
}

void loop() {
  // Fade up
  for (int i = 1; i <= steps; i++) {
    float brightness = pow((float)i / steps, gammaCorrection);  
    uint16_t pwmValue = (uint16_t)(brightness * pwmMax);
    analogWrite(pwmPinA, pwmValue);
    delay(10);
  }

  // Fade down
  for (int i = steps; i >= 1; i--) {
    float brightness = pow((float)i / steps, gammaCorrection);  
    uint16_t pwmValue = (uint16_t)(brightness * pwmMax);
    analogWrite(pwmPinA, pwmValue);
    delay(10);
  }
}
