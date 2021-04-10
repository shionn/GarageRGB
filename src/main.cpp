#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define BUTTON 13

#define STRIP_COUNT 80

Adafruit_NeoPixel strip[3];
uint8_t value = 1;

void setup()
{
  for (uint8_t i = 0; i < 3; i++)
  {
    strip[i] = Adafruit_NeoPixel(STRIP_COUNT, 4 + i, NEO_GRB + NEO_KHZ800);
    strip[i].begin();
  }
  pinMode(BUTTON, INPUT_PULLUP);
}

void waitButtonState(uint8_t but, uint8_t state)
{
  uint8_t b = digitalRead(but);
  while (b != state)
  {
    delai(100);
    b = digitalRead(but);
  }
}

void loop()
{
  for (uint8_t i = 0; i < 3; i++)
  {
    for (uint8_t j = 0; j < STRIP_COUNT; j++)
    {
      if (value)
      {
        strip[i].setPixelColor(j, 255, 255, 255);
      }
      else
      {
        strip[i].setPixelColor(j, 0, 0, 0);
      }
    }
    strip.show();
  }

  waitButtonState(BUTTON, 0);
  value = !value;
  waitButtonState(BUTTON, 1);
}