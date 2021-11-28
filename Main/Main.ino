#include "Led.h"
#include "VibrationMotor.h"

/**
 * THIS IS THE MAIN CONTROLLER FOR DETECTING INPUTS AND ALERTING THE USER
 */

// PINS
const int LEDPin1 = 4; // LEFT SIDE
const int LEDPin2 = 3; // RGIHT SIDE

const int VibrationMotorPin1 = 5; // LEFT SIDE
const int VibrationMotorPin2 = 7; // RIGHT SIDE

// Variables
LED led1(LEDPin1); // LEFT SIDE
LED led2(LEDPin2); // RIGHT SIDE

VibrationMotor vibrationMotor1(VibrationMotorPin1); // LEFT SIDE
VibrationMotor vibrationMotor2(VibrationMotorPin2); // RIGHT SIDE

void setup() {
  // Init serial comm
  Serial.begin(9600);

  // Init modules

  led1.begin();
  led2.begin();

  vibrationMotor1.begin();
  vibrationMotor2.begin();
}

void loop() {
  // Parse incoming serial input from Processing UI
  if (Serial.available() > 0) {
    char state = Serial.read();
    if (state == '1') {
      // ALERT LEFT
      alertLeft();
    } else if (state == '2') {
      // ALERT RIGHT
      alertRight();
    }
  }
}

/**
 * Because Arduino cannot do a series of LED blinks and series of 
 * haptic vibrations simultaneously, we need to repeat the single 
 * calls to each module.
**/

void alertRight() {
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 5; i++) {
      led2.blink(high);
      vibrationMotor2.vibrate(high);
    }
    delay(100);
  }
}

void alertLeft() {
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 5; i++) {
      led1.blink(high);
      vibrationMotor1.vibrate(high);
    }
    delay(100);
  }
}
