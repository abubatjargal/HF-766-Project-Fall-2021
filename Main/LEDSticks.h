#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

enum ScrollDirection { forward, backward };

#define NUMPIXELS 10 //Indicates that the LED stick has 10 addressable LEDs

// This class allows for controlling two LED stick modules simultaneously.
class LEDSticks {
  public:
    LEDSticks(int pin1, int pin2);
    void begin();
    void scroll();
    void on(int pixel);
    void off(int pixel);

  private:
    int _pin1;
    int _pin2;
    Adafruit_NeoPixel pixels1;
    Adafruit_NeoPixel pixels2;
    void scrollInDirection(ScrollDirection direction);
};

// PRIVATE METHODS

// Constructor method.
// Parameters: pin numbers for each LED stick
// Returns: LEDSticks instance
LEDSticks::LEDSticks(int pin1, int pin2) {
  _pin1 = pin1;
  _pin2 = pin2;
}

// Initializes both LED sticks
// Parameters: none
// Returns: none
void LEDSticks::begin() {
  pixels1 = Adafruit_NeoPixel(NUMPIXELS, _pin1, NEO_GRB + NEO_KHZ800);
  pixels2 = Adafruit_NeoPixel(NUMPIXELS, _pin2, NEO_GRB + NEO_KHZ800);

  pixels1.setBrightness(255);
  pixels2.setBrightness(255);

  pixels1.begin();
  pixels2.begin();
}

// Sequentially turns on and turns off the LEDs to create horizontal scrolling illusion.
// Parameters: none
// Returns: none
void LEDSticks::scroll() {
  // Scroll pixels
  scrollInDirection(forward);
  // Scroll pixels in opposite direction
  scrollInDirection(backward);
}

// PRIVATE METHODS

// Sequentially turn on and turn off LEDs based on the scroll direction
void LEDSticks::scrollInDirection(ScrollDirection direction) {
  int pixelCount = direction == forward ? 0 : 10;

  while(direction == forward ? (pixelCount < 10) : (pixelCount >= 0)) {
    on(pixelCount);
    pixelCount += direction == forward ? 1 : -1;
    delay(30);
  }

  pixelCount = direction == forward ? 0 : 10;

  while(direction == forward ? (pixelCount < 10) : (pixelCount >= 0)) {
    off(pixelCount);
    pixelCount += direction == forward ? 1 : -1;
    delay(30);
  }
}

void LEDSticks::on(int pixel) {
  pixels1.setPixelColor(pixel, pixels1.Color(255, 255, 255));
  pixels2.setPixelColor(pixel, pixels1.Color(255, 255, 255));
  pixels1.show();
  pixels2.show();
}

void LEDSticks::off(int pixel) {
  pixels1.setPixelColor(pixel, pixels1.Color(0, 0, 0));
  pixels2.setPixelColor(pixel, pixels1.Color(0, 0, 0));
  pixels1.show();
  pixels2.show();
}
