class LED {
  public:
    LED(int pin);
    void begin();
    void on();
    void off();
    bool isOn();
    bool isOff();

  private:
    bool _onState;
    int _pin;
};

// PUBLIC METHODS

LED::LED(int pin) {
  _pin = pin;
  _onState = false;
}

void LED::begin() {
  pinMode(_pin, OUTPUT);
}

void LED::on() {
  digitalWrite(_pin, HIGH);
  _onState = true;
}

void LED::off() {
  digitalWrite(_pin, LOW);
  _onState = false;
}

bool LED::isOn() {
  return _onState;
}

bool LED::isOff() {
  return !_onState;
}
