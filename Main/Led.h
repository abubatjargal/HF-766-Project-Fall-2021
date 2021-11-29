enum AlertPriority { low, high };

class LED {
  public:
    LED(int pin);
    void begin();
    void blink(AlertPriority priority);
    void on();
    void off();

  private:
    int _pin;
    int ledBlink(int pin, int onDuration);
};

// PUBLIC METHODS

LED::LED(int pin) {
  _pin = pin;
}

void LED::begin() {
  pinMode(_pin, OUTPUT);
}

void LED::blink(AlertPriority priority) {
  switch (priority) {
    case low:
      ledBlink(_pin, 200);
      break;
    case high:
      ledBlink(_pin, 30);
      break;
  }
}

void LED::on() {
  digitalWrite(_pin, HIGH);
}

void LED::off() {
  digitalWrite(_pin, LOW);
}

// PRIVATE METHODS

int LED::ledBlink(int pin, int onDuration) {

  // Input Validations
  if (pin < 2 || pin > 8 || onDuration < 0) {
    return 0;
  }

  digitalWrite(pin, HIGH);
  delay(onDuration);
  digitalWrite(pin, LOW);

  return 1;
}
