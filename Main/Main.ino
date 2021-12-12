#include "Led.h"
#include "VibrationMotor.h"
#include "LEDSticks.h"

/**
   THIS IS THE MAIN CONTROLLER FOR DETECTING INPUTS AND ALERTING THE USER
*/

// PINS
const int LEDPin1 = 8; // LEFT SIDE
const int LEDPin2 = 4; // RGIHT SIDE

const int LEDStickPin1 = 7; // LEFT SIDE
const int LEDStickPin2 = 3; // RIGHT SIDE

const int VibrationMotorPin1 = 6; // LEFT SIDE
const int VibrationMotorPin2 = 2; // RIGHT SIDE

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
        alc = 0;
        arc = 0;
        break;
      case '4':
        ledEnabled = false;
        alc = 0;
        arc = 0;
        break;
      case '5':
        vibrationEnabled = true;
        alc = 0;
        arc = 0;
        break;
      case '6':
        vibrationEnabled = false;
        alc = 0;
        arc = 0;
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
      alertLed(right, true);
      alertVibration(right, true);
    }

    if (millis() > arc_millis + 50) {

      if (ledEnabled && vibrationEnabled) {
        arc++;
        alertLed(right, led2.isOn());
        alertVibration(right, vibrationMotor2.isOn());
      } else if (ledEnabled) {
        arc++;
        alertLed(right, led2.isOn());        
      } else if (vibrationEnabled) {
        arc++;
        alertVibration(right, vibrationMotor2.isOn());
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
      alertLed(left, true);
      alertVibration(left, true);
    }

    if (millis() > alc_millis + 50) {

      if (ledEnabled && vibrationEnabled) {
        alc++;
        alertLed(left, led1.isOn());
        alertVibration(left, vibrationMotor1.isOn());
      } else if (ledEnabled) {
        alc++;
        alertLed(left, led1.isOn());
      } else if (vibrationEnabled) {
        alc++;
        alertVibration(left, vibrationMotor1.isOn());
      }

      alc_millis = millis();
    }
  }
}

void alertLed(AlertSide side, bool isOn) {
  switch (side) {
    case left:
      if (isOn) {
        led1.off();
      } else {
        led1.on();
      }
      break;
    case right:
      if (isOn) {
        led2.off();
      } else {
        led2.on();
      }
      break;            
  }
}

void alertVibration(AlertSide side, bool isOn) {
  switch (side) {
    case left:
      if (isOn) {
        vibrationMotor1.off();
      } else {
        vibrationMotor1.on();
      }
      break;
    case right:
      if (isOn) {
        vibrationMotor2.off();
      } else {
        vibrationMotor2.on();
      }
      break;
  }
}