#include <math.h>

// Pin Setup
const int pwmPin = 6;  // Use a PWM-capable pin

const int resolution = 16;      // RP2040 is 16-bit
const uint16_t pwmMax = 65535;  // 2^16

// Transition config
const int steps = 256;
const int stepDelay = 10;

// Easing function that starts slow, speeds up in the middle, and ends slow
float easeInOutQuad(float idx) {
  return (idx < 0.5) ? 2.0 * idx * idx : -1.0 + (4.0 - 2.0 * idx) * idx;
}

void setPWM(float progress, int startVal, int targetVal) {
  float eased = easeInOutQuad(progress);
  float maxVal = max(startVal, targetVal) / 100;
  float minVal = min(startVal, targetVal) / 100;
  float percent = minVal + (eased * maxVal);
  int pwmVal = (int)(percent * pwmMax);
  analogWrite(pwmPin, pwmVal);
  delay(stepDelay);
}

void fade(int startVal, int targetVal){
  if (startVal == targetVal) return;
  
  if (startVal < targetVal) {  // Fade up
    for (int i = 0; i <= steps; i++) {
      float progress = (float)i / (float)steps;
      setPWM(progress, startVal, targetVal);
    }
  }
  else {                          // Fade down
    for (int i = steps; i >= 0; i--) {
      float progress = (float)i / (float)steps;
      setPWM(progress, startVal, targetVal);
    }
  }
}

void setup() {
  analogWriteResolution(resolution);
  pinMode(pwmPin, OUTPUT);
}

// TODO: Get percentages less than 100 working :/
void loop() {
  fade(0, 100);  // Turn on
  delay(1000);   // Wait
  fade(100, 0);  // Turn off
  delay(1000);   // Wait
}
