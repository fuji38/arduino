/*-----------------------------------------------------------------------
This sketch changes LED color in NeoPixle LEDs
   - if USB Boarduino, select Arduino Duemilanove w/ ATmega328
   - if Japanino, (3.3V ATmega168)
   - uses Adafruit_NeoPixel library

2013-04-02 by Y.Fujisawa
   - initial code

2013-11-23 by Y.Fujisawa
   - updated color loop

-----------------------------------------------------------------------*/

#include "Adafruit_NeoPixel.h"

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

// const int LED_max = 16;          // number of LEDs
const int LED_max = 30;          // number of LEDs
const int Pin = 6;               // arduino pin#
const int Bright_max = 50;      // max brightness, less than 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_max, Pin, NEO_GRB + NEO_KHZ800);

void setup() {
   strip.begin();
   strip.show();  // Initialize all pixels to 'off'
   color_wipe(strip.Color(Bright_max, 0, 0), 50);
   color_wipe(strip.Color(0, Bright_max, 0), 50);
   color_wipe(strip.Color(0, 0, Bright_max), 50);
   color_wipe(strip.Color(0, 0, 0), 50);
}
   
   
void loop() {
   int i;
   int pos;
   uint32_t  color;
   int bright_r;
   int bright_g;
   int bright_b;

   // bright_r = 50;
   // bright_g = 0;
   // bright_b = 0;
   bright_r = 20 + random(80);
   bright_g = 20 + random(80);
   bright_b = 10 + random(80);
   for (pos=0; pos < (strip.numPixels() + 10); pos++) {
      for (i=0; i < strip.numPixels(); i++) {
         if (i == pos) {
            color = strip.Color(bright_r, bright_g, bright_b);
            strip.setPixelColor(i, color);
         } else if (i == pos-1) {
            color = strip.Color(bright_r * 4/5, bright_g * 4/5, bright_b * 4/5);
            strip.setPixelColor(i, color);
         } else if (i == pos-2) {
            color = strip.Color(bright_r * 3/5, bright_g * 3/5, bright_b * 3/5);
            strip.setPixelColor(i, color);
         } else if (i == pos-3) {
            color = strip.Color(bright_r * 2/5, bright_g * 2/5, bright_b * 2/5);
            strip.setPixelColor(i, color);
         } else if (i == pos-4) {
            color = strip.Color(bright_r * 1/5, bright_g * 1/5, bright_b * 1/5);
            strip.setPixelColor(i, color);
         } else {
            strip.setPixelColor(i, strip.Color(0,0,0));
         }
         strip.show();
      }
      delay(0);
   }
   delay(random(2000, 20000));
}


void loop_green() {
   int i;
   int color;

   // color = strip.Color(Bright_max, Bright_max, Bright_max);
   for (i = 0; i < Bright_max; i++) {
      color_wipe(strip.Color(0, i, 0), 0);
      strip.show();
      delay(50);
   }
}


void loop_green2() {
   int i;
   int color;

   // color = strip.Color(Bright_max, Bright_max, Bright_max);
   for (i = 0; i < Bright_max; i++) {
      color_wipe(strip.Color(0, i, 0), 2);
   }
}

void loop_rainbow() {
   rainbowCycle(5);
}
   

void loop_1() {
   int i;
   int prev = 0;

   for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(prev, 0, 0, 0);
      strip.setPixelColor(i, Bright_max, Bright_max, Bright_max);
      prev = i;
      strip.show();
      delay(50);
   }
   for (i = strip.numPixels(); i >= 0; i--) {
      strip.setPixelColor(prev, 0, 0, 0);
      strip.setPixelColor(i, Bright_max, Bright_max, Bright_max);
      prev = i;
      strip.show();
      delay(50);
   }
}


// fill the dots one after the other with said color
// good for testing purposes
void color_wipe(uint32_t c, uint8_t wait) {
   int i;

   for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
   }
}


void loop_old() {
   // Some example procedures showing how to display to the pixels:
   colorWipe(strip.Color(255, 0, 0), 50); // Red
   colorWipe(strip.Color(0, 255, 0), 50); // Green
   colorWipe(strip.Color(0, 0, 255), 50); // Blue
   rainbow(20);
   rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
   for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
   }
}

void rainbow(uint8_t wait) {
   uint16_t i, j;

   for(j=0; j<256; j++) {
      for(i=0; i<strip.numPixels(); i++) {
         strip.setPixelColor(i, Wheel((i+j) & 255));
      }
      strip.show();
      delay(wait);
   }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
   uint16_t i, j;

   for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      for(i=0; i< strip.numPixels(); i++) {
         strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      strip.show();
      delay(wait);
   }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
   if(WheelPos < 85) {
      return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
   } else if(WheelPos < 170) {
      WheelPos -= 85;
      return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
   } else {
      WheelPos -= 170;
      return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
   }
}

// vim: et ts=3 sw=3 syntax=cpp
