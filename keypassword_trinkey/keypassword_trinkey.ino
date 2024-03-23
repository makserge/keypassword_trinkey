#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "HID-Project.h"

#define PASSWORD1 "Password1"
#define PASSWORD2 "Password2"

#define NEOPIXEL1 0
#define NEOPIXEL2 1

#define NEOPIXEL_OFF_BRIGHTNESS 20
#define NEOPIXEL_ON_BRIGHTNESS 100

#define NEOPIXEL1_RED_COLOR 0
#define NEOPIXEL1_GREEN_COLOR 255
#define NEOPIXEL1_BLUE_COLOR 0

#define NEOPIXEL2_RED_COLOR 0
#define NEOPIXEL2_GREEN_COLOR 0
#define NEOPIXEL2_BLUE_COLOR 255

#define TOUCH1_PIN 1
#define TOUCH2_PIN 2

#define TOUCH_DELAY 250

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
Adafruit_FreeTouch qt1 = Adafruit_FreeTouch(TOUCH1_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt2 = Adafruit_FreeTouch(TOUCH2_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

void setup() {
  strip.begin();
  strip.setBrightness(NEOPIXEL_OFF_BRIGHTNESS);
  strip.show();
  
  qt1.begin();
  qt2.begin();

  Keyboard.begin();
}

void sendKeyboardMessage(String message) {
  Keyboard.print(message);
  Keyboard.write(KEY_RETURN);
}

void loop() {
  strip.setPixelColor(NEOPIXEL1, 0, 0, 0);
  strip.setPixelColor(NEOPIXEL2, 0, 0, 0);
  strip.setBrightness(NEOPIXEL_OFF_BRIGHTNESS);
  strip.show();

  uint16_t touch1 = qt1.measure();
  uint16_t touch2 = qt2.measure();

  if (touch1 > 300) {
    strip.setPixelColor(NEOPIXEL1, NEOPIXEL1_RED_COLOR, NEOPIXEL1_GREEN_COLOR, NEOPIXEL1_BLUE_COLOR);
    strip.setBrightness(NEOPIXEL_ON_BRIGHTNESS);
    strip.show();
    sendKeyboardMessage(PASSWORD1);
    delay(TOUCH_DELAY);
  } else if (touch2 > 300) {
    strip.setPixelColor(NEOPIXEL2, NEOPIXEL2_RED_COLOR, NEOPIXEL2_GREEN_COLOR, NEOPIXEL2_BLUE_COLOR);
    strip.setBrightness(NEOPIXEL_ON_BRIGHTNESS);
    strip.show();
    sendKeyboardMessage(PASSWORD2);
    delay(TOUCH_DELAY);
  }
}