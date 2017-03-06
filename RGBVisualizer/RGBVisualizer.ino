#include "FastLED.h"

#define NUM_LEDS 150
#define DATA_PIN 5

char val;

int array[16] =    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int arraytemp[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int i, j, k, r;

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

 void loop() {

  if (Serial.read() == 0xff) {
    for (i = 0; i < 16; i++) {
      array[i] = Serial.read();
    }
    delay(20);
    for (j = 0; j < 16; j++) {
      if (array[j] != arraytemp[j]) {
        switch (array[j]) {
          case 0:
          setLeds(CRGB::Black, 0, 150);
          break;
          case 1:
          setLeds(CRGB::Orange, 0, 10);
          break;
          case 2:
          setLeds(CRGB::Green, 11, 20);
          break;
          case 3:
          setLeds(CRGB::Blue, 21, 30);
          break;
          case 4:
          setLeds(CRGB::Pink, 31, 40);
          break;
          case 5:
          setLeds(CRGB::White, 41, 50);
          break;
          case 6:
          setLeds(CRGB::Orange, 51, 60);
          break;
          case 7:
          setLeds(CRGB::Blue, 61, 70);
          break;
          case 8:
          setLeds(CRGB::Orange, 71, 80);
          break;
          case 9:
          setLeds(CRGB::Blue, 81, 90);
          break;
          case 10:
          setLeds(CRGB::Orange, 91, 100);
          break;
          case 11:
          setLeds(CRGB::Blue, 101, 110);
          break;
          case 12:
          setLeds(CRGB::Orange, 111, 120);
          break;
          case 13:
          setLeds(CRGB::Blue, 121, 130);
          break;
          case 14:
          setLeds(CRGB::Orange, 131, 140);
          break;
          case 15:
          setLeds(CRGB::Blue, 141, 145);
          break;
          case 16:
          setLeds(CRGB::Orange, 146, 150);
          break;
        }

        arraytemp[j] = array[j];

      }
    }

  }
  //delay(1000);
}

void setLeds(int color, int begin, int end) {
  for (int i = begin; i < end; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

