#include "LedSticks.h"

// THIS IS THE CLASS USED TO OPERATE THE SCROLLING LED STICKS
// THIS SHOULD BE RUN ON A SEPARATE ARDUINO FROM THE SKETCH LABELED 'Main'

const int LEDStickPin1 = 5;
const int LEDStickPin2 = 6;

LEDSticks ledSticks(LEDStickPin1, LEDStickPin2);

void setup() {
  ledSticks.begin();
}

void loop() {
  ledSticks.scroll();
}
