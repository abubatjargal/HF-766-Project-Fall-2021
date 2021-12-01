class VibrationMotor {
  public:
    VibrationMotor(int pin);
    void begin();
    void vibrationOn();
    void vibrationOff();

  private:
    int _pin;
};

VibrationMotor::VibrationMotor(int pin) {
  _pin = pin;
}

void VibrationMotor::begin() {
  pinMode(_pin, OUTPUT);
}


void VibrationMotor::vibrationOn() {
  digitalWrite(_pin, HIGH);
}

void VibrationMotor::vibrationOff() {
  digitalWrite(_pin, LOW);
}
