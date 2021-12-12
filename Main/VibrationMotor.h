class VibrationMotor {
  public:
    VibrationMotor(int pin);
    void begin();
    void on();
    void off();
    bool isOn();

  private:
    bool _onState;
    int _pin;
};

VibrationMotor::VibrationMotor(int pin) {
  _pin = pin;
}

bool VibrationMotor::isOn() {
  return _onState;
}

void VibrationMotor::begin() {
  pinMode(_pin, OUTPUT);
}

void VibrationMotor::on() {
  digitalWrite(_pin, HIGH);
  _onState = true;
}

void VibrationMotor::off() {
  digitalWrite(_pin, LOW);
  _onState = false;
}
