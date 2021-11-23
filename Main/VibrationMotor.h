enum VibrationPriority {
  low,
  high
};

class VibrationMotor {
  public:
    VibrationMotor(int pin);
    void begin();
    void vibrate(VibrationPriority priority);

  private:
    int _pin;
    void vibrateHigh();
    void vibrateLow();
};

VibrationMotor::VibrationMotor(int pin) {
  _pin = pin;
}

void VibrationMotor::begin() {
  pinMode(_pin, OUTPUT);
}

void VibrationMotor::vibrate(VibrationPriority priority) {
  switch (priority) {
    case low:
      vibrateLow();
      break;
    case high:
      vibrateHigh();
      break;
  }
}

void VibrationMotor::vibrateHigh() {
  for(int i = 0; i < 10; i++) {
    digitalWrite(_pin, HIGH);
    delay(30);

    digitalWrite(_pin, LOW);
    delay(40);
  }
}

void VibrationMotor::vibrateLow() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(_pin, HIGH);
    delay(50);

    digitalWrite(_pin, LOW);
    delay(300);
  }
}
