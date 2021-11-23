#include "LedSticks.h"
#include "Led.h"

// PINS
const int LEDStickPin1 = 5;
const int LEDStickPin2 = 6;

// Variables

LEDSticks ledSticks(LEDStickPin1, LEDStickPin2);

void setup() {
  // Create single instance of LEDSticks and scroll once
  ledSticks.begin();
  ledSticks.scroll();


}

void loop() {

}
