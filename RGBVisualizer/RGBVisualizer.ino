#include "FastLED.h"

#define NUM_LEDS 150
#define DATA_PIN 5

char val;

int array[3] =    {0, 0, 0};
int arraytemp[3] = {1, 1, 1};
int i, j, k, r;

float low_multiplier = .8;
float mid_multiplier = 1;
float high_multiplier = 1;

//CRGB leds[NUM_LEDS];
CRGBArray<150> leds;
//CRGB *realleds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  //FastLED.setBrightness(200);
}

 void loop() {

  if (Serial.read() == 0xff) {
    for (i = 0; i < 3; i++) {
      array[i] = (int) Serial.read();
    }
    for (j = 0; j < 3; j++) {
      if (array[j] != arraytemp[j] && ( array[j] > 0 && array[j] <= 255)) {
        switch (j) {
          case 0:
          Serial.write(0xcc);
          Serial.write(array[j] + 1);
          setColorLeds(0, 0, array[j] + 1, 0, 50);
          //FastLED.setBrightness(array[j]);
          break;  
          case 1:
          Serial.write(array[j] + 1);
          setColorLeds(0, array[j] + 1, 0, 51, 100);
          //FastLED.setBrightness(array[j] * mid_multiplier);   
          break;
          case 2:
          Serial.write(array[j] + 1);
          setColorLeds(array[j] + 1, 0, 0, 101, 149);
          //FastLED.setBrightness(array[j]);  
          break; 
        }
        //FastLED.setBrightness(array[0] * low_multiplier);
        arraytemp[j] = array[j];

      }
    }
    FastLED.show();
    delay(18);
    //setColorLeds(0, 0, 0, 0, 149);
  }
  //delay(1000);
}

void setLeds(CRGB color, int begin, int end) {
  for (int i = begin; i < end; i++) {
    leds[i] = color;
  }
}

void setColorLeds(int red, int green, int blue, int low, int high) {
  
  for(CRGB & pixel : leds(low,high)) { pixel = CRGB(red, green, blue); } 
}

