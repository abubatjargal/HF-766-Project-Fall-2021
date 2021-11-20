#include "LedStick.h"
#include "Led.h"

LedStick* ledStick;

void setup() {
  // Create single instance of ledStick and start scrolling
  ledStick = new LedStick(5);
  ledStick->startScroll();

}

void loop() {

  
}
