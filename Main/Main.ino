#include "LedSticks.h"
#include "Led.h"
#include "VibrationMotor.h"

// PINS
const int LEDStickPin1 = 5;
const int LEDStickPin2 = 6;

const int VibrationMotorPin1 = 3;

// Variables

LEDSticks ledSticks(LEDStickPin1, LEDStickPin2);

VibrationMotor vibrationMotor1(VibrationMotorPin1);

void setup() {
  Serial.begin(9600);
  
  ledSticks.begin();
  vibrationMotor1.begin();
}

void loop() {

  if (Serial.available() > 0) {
    Serial.println("Serial Available");
    char state = Serial.read();

    Serial.println(state);
    
    if (state == '1') {
      Serial.println("Detected 1!");
      vibrationMotor1.vibrate(low);
    }

    while (Serial.available()) Serial.read();
  }
  
  ledSticks.scroll();
}
