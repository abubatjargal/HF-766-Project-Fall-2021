#include "Led.h"
#include "VibrationMotor.h"
#include "LEDStick.h"

/**
   THIS IS THE MAIN CONTROLLER FOR DETECTING INPUTS AND ALERTING THE USER
*/

// PINS
const int LEDPin1 = 4; // LEFT SIDE
const int LEDPin2 = 3; // RGIHT SIDE

const int VibrationMotorPin1 = 5; // LEFT SIDE
const int VibrationMotorPin2 = 7; // RIGHT SIDE

const int LEDStickPin1 = 2;
const int LEDStickPin2 = 6;

// Variables
enum AlertSide { left, right };

LED led1(LEDPin1); // LEFT SIDE
LED led2(LEDPin2); // RIGHT SIDE

LEDSticks sticks = LEDSticks(LEDStickPin1, LEDStickPin2);

VibrationMotor vibrationMotor1(VibrationMotorPin1); // LEFT SIDE
VibrationMotor vibrationMotor2(VibrationMotorPin2); // RIGHT SIDE

unsigned long arc_millis;
unsigned long alc_millis;

// Timer variable used to track millisecond changes
unsigned long lsc_millis;

// Counters used to keep track of the number of times LED blinks and haptic motor activates
int arc = 0;
int alc = 0;

// Counter used to keep track of what LED Pixel is activated in LED Sticks
int lsc = 0;

void setup() {
  // Init serial comm
  Serial.begin(9600);

  // Init modules

  led1.begin();
  led2.begin();

  vibrationMotor1.begin();
  vibrationMotor2.begin();

  sticks.begin();

  arc_millis = millis();
  alc_millis = millis();
  lsc_millis  = millis();
}

void loop() {
  scrollLEDSticks();

  parseSerialInput();

  shouldAlertRight();
  shouldAlertLeft();
}

void parseSerialInput() {
  // Parse incoming serial input from Processing UI
  if (Serial.available() > 0) {
    char state = Serial.read();
    if (state == '1') {
      // ALERT LEFT
      alc = 1;
    } else if (state == '2') {
      // ALERT RIGHT
      arc = 1;
    }
  }
}

void scrollLEDSticks() {
  if (lsc >= 0) {
    if (lsc == 11) {
      lsc = 0;
    }

    if (millis() > lsc_millis + 20) {
      sticks.on(lsc);

      if (lsc - 1 >= 0) {
        sticks.off(lsc - 1);
      }

      lsc_millis = millis();
      lsc++;
    }
  }
}

void shouldAlertRight() {
  // Alert Right
  if (arc > 0) {

    if (arc == 11) {
      arc = 0;
      alert(right, false);
    }

    if (millis() > arc_millis + 50) {

      if (led2.isOff()) {
        arc++;
        alert(right, true);
      } else {
        arc++;
        alert(right, false);
      }

      arc_millis = millis();
    }
  }
}

void shouldAlertLeft() {
  // Alert Left
  if (alc > 0) {

    if (alc == 11) {
      alc = 0;
      alert(left, false);
    }

    if (millis() > alc_millis + 50) {

      if (led1.isOff()) {
        alc++;
        alert(left, true);
      } else {
        alc++;
        alert(left, false);
      }

      alc_millis = millis();
    }
  }
}

void alert(AlertSide side, bool isOn) {
  switch (side) {
    case left:
      if (isOn) {
        led1.on();
        vibrationMotor1.vibrationOn();
      } else {
        led1.off();
        vibrationMotor1.vibrationOff();
      }
      break;
    case right:
      if (isOn) {
        led2.on();
        vibrationMotor2.vibrationOn();
      } else {
        led2.off();
        vibrationMotor2.vibrationOff();
      }
      break;
  }
}
