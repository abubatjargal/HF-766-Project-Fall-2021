#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#define NUMPIXELS 10 //Indicates that the LED stick has 10 addressable LEDs

class LedStick {
    
  public:
    int ledPin;
    int shouldScroll;
    Adafruit_NeoPixel pixels;

    // Initialize LedStick instance
    // parameter: int representing the pin number of the led stick
    LedStick(int pin) {
      ledPin = pin;
      pixels = Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800);
      pixels.setBrightness(255);
      pixels.begin();
    }

    // Starts light scrolling by setting shouldScroll variable to true
    void startScroll() {
      shouldScroll = 1;
      scroll();
      Serial.print("started scrolling");
    }

    // Stops light scrolling by setting shouldScroll variable to false
    void stopScroll() {
      shouldScroll = 0;
      Serial.println("Going to try stopping");
      Serial.println("ShouldScroll: " + shouldScroll);
    }

    // Scroll lights by sequentially turning leds on and turning them off.
    void scroll() {
      // Sequentially turn on LEDs
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));
        pixels.show();
        delay(40);
      }

      delay(500);

      // Sequentially turn off LEDs
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(40);
      }

      // If scroll should continue, call the function again. Otherwise do nothing.
      if (shouldScroll == 1) {
        scroll();
      }
    }
};
