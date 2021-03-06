#include "FastLED.h"
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];
#define PIN 6

void setup()
{
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}

void loop()
{
  HalloweenEyes(0xff, 0x00, 0x00,
                random(1, 3), random(4, 10),
                //                2, 8,
                true, random(5, 50), random(50, 150),
                random(100, 1000));
}

void HalloweenEyes(byte red, byte green, byte blue,
                   int EyeWidth, int EyeSpace,
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause)
{
  randomSeed(analogRead(0));

  int i;
  int StartPoint = random(0, NUM_LEDS - (2 * EyeWidth) - EyeSpace);
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;

  for (i = 0; i < EyeWidth; i++)
  {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }

  showStrip();

  if (Fade == true)
  {
    float r, g, b;

    for (int j = Steps; j >= 0; j--)
    {
      r = j * (red / Steps);
      g = j * (green / Steps);
      b = j * (blue / Steps);

      for (i = 0; i < EyeWidth; i++)
      {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }

      showStrip();
      delay(FadeDelay);
    }
  }

  setAll(0, 0, 0); // Set all black

  delay(EndPause);
}

void showStrip()
{
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setPixel(int Pixel, byte red, byte green, byte blue)
{
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

void setAll(byte red, byte green, byte blue)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
  showStrip();
}