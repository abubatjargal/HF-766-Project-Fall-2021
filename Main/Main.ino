#include "Led.h"
#include "VibrationMotor.h"
#include "LEDSticks.h"

/**
   THIS IS THE MAIN CONTROLLER FOR DETECTING INPUTS AND ALERTING THE USER
*/

// PINS
const int LEDPin1 = 4; // LEFT SIDE
const int LEDPin2 = 3; // RGIHT SIDE

const int LEDStickPin1 = 2; // LEFT SIDE
const int LEDStickPin2 = 6; // RIGHT SIDE

const int VibrationMotorPin1 = 5; // LEFT SIDE
const int VibrationMotorPin2 = 7; // RIGHT SIDE

// Variables
enum AlertSide { left, right };

LED led1(LEDPin1); // LEFT SIDE
LED led2(LEDPin2); // RIGHT SIDE

LEDSticks sticks = LEDSticks(LEDStickPin1, LEDStickPin2);

VibrationMotor vibrationMotor1(VibrationMotorPin1); // LEFT SIDE
VibrationMotor vibrationMotor2(VibrationMotorPin2); // RIGHT SIDE

unsigned long arc_millis; // Alert Right Count
unsigned long alc_millis; // Alert Left Count

// Timer variable used to track millisecond changes
unsigned long lsc_millis;

// Counters used to keep track of the number of times LED blinks and haptic motor activates
int arc = 0; // Alert Right Count
int alc = 0; // Alert Left Count

// Counter used to keep track of what LED Pixel is activated in LED Sticks
int lsc = 0; // Light Strip Count

bool ledEnabled = false;
bool vibrationEnabled = false;

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

// 1: Left
// 2: Right
// 3: LED Enabled
// 4: LED Disabled
// 5: Vibration Enabled
// 6: Vibration Disabled

void parseSerialInput() {
  // Parse incoming serial input from Processing UI
  if (Serial.available() > 0) {
    char state = Serial.read();
    switch(state) {
      case '1':
        alc = 1;
        break;
      case '2':
        arc = 1;
        break;
      case '3':
        ledEnabled = true;
        break;
      case '4':
        ledEnabled = false;
        break;
      case '5':
        vibrationEnabled = true;
        break;
      case '6':
        vibrationEnabled = false;
        break;
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
        if (ledEnabled) {
          led1.on();
        }        
        if (vibrationEnabled) {
          vibrationMotor1.vibrationOn();
        }
      } else {
        if (ledEnabled) {
          led1.off();
        }        
        if (vibrationEnabled) {
          vibrationMotor1.vibrationOff();
        }
      }
      break;
    case right:
      if (isOn) {
        if (ledEnabled) {
          led2.on();
        }        
        if (vibrationEnabled) {
          vibrationMotor2.vibrationOn();
        }
      } else {
        if (ledEnabled) {
          led2.off();
        }        
        if (vibrationEnabled) {
          vibrationMotor2.vibrationOff();
        }
      }
      break;
  }
}
