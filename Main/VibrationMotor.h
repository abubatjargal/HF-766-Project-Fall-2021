class VibrationMotor {
  public:
    VibrationMotor(int pin);
    void begin();
    void vibrate(AlertPriority priority);
    void vibrationOn();
    void vibrationOff();

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

void VibrationMotor::vibrate(AlertPriority priority) {
  switch (priority) {
    case low:
      vibrateLow();
      break;
    case high:
      vibrateHigh();
      break;
  }
}

void VibrationMotor::vibrationOn() {
  digitalWrite(_pin, HIGH);
}

void VibrationMotor::vibrationOff() {
  digitalWrite(_pin, LOW);
}

void VibrationMotor::vibrateHigh() {
  digitalWrite(_pin, HIGH);
  delay(30);
  digitalWrite(_pin, LOW);
}

void VibrationMotor::vibrateLow() {
  digitalWrite(_pin, HIGH);
  delay(50);
  digitalWrite(_pin, LOW);
}
