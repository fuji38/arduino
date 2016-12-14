/*-----------------------------------------------------------------------
This sketch controls WS2801 LED string
   - if USB Boarduino, select "Arduino Duemilanove w/ ATmega328"
   - if Japanino, select "3.3V ATmega168"

2012-11-18 by Y.Fujisawa
   - initial code

2012-12-03 by Y.Fujisawa
   - added brightness control

2012-12-05 by Y.Fujisawa
   - changed color_wheel calculation

2016-12-08 by Y.Fujisawa
   - changed color pattern

2016-12-14 by Y.Fujisawa
   - changed color randomly every 1 min.


-----------------------------------------------------------------------*/

#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!

  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
// Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);


const int LED_max = 25;                   // number of LEDs
const int Bright_max = 180;               // max brightness, less than 255



void rainbow(uint8_t wait) {
   int i, j;
   
   for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
      for (i=0; i < strip.numPixels(); i++) {
         // strip.setPixelColor(i, Wheel( (i + j) % 255));
         strip.setPixelColor(i, color_wheel(j, 100));
      }  
      strip.show();   // write all the pixels out
      delay(wait);
   }
}


void rainbow_cycle(uint8_t wait) {
   int i, j;
  
   for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
      for (i=0; i < strip.numPixels(); i++) {
         // tricky math! we use each pixel as a fraction of the full 96-color wheel
         // (thats the i / strip.numPixels() part)
         // Then add in j which makes the colors go around per pixel
         // the % 96 is to make the wheel cycle around
         // strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
         strip.setPixelColor(i, color_wheel(((i * 256 / strip.numPixels()) + j) % 256, 100));
      }  
      strip.show();   // write all the pixels out
      delay(wait);
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


/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return (c);
}


// returns a color value.
//    wheel_pos: 0 to 255 for a color
//    bright: 0 to 255 for brightness
// The colours are a transition r - g -b - back to r
// originally divided to 85, 85, 85 (256 / 3 = 85)
// changed to 128, 64, 64; to enhance Red and Green
uint32_t color_wheel(byte wheel_pos, byte bright)
{
   byte r, g, b;

   if (wheel_pos < 128) {
      r = (wheel_pos * 2) * bright / 255;
      g = (255 - wheel_pos * 2) * bright / 255;
      b = 0;
      return color(r, g, b);
   } else if (wheel_pos < 192) {
      wheel_pos -= 128;
      r = (255 - wheel_pos * 4) * bright / 255;
      g = 0;
      b = (wheel_pos * 4) * bright / 255;
      return color(r, g, b);
   } else {
      wheel_pos -= 192; 
      r = 0;
      g = (wheel_pos * 4) * bright / 255;
      b = (255 - wheel_pos * 4) * bright / 255;
      return color(r, g, b);
   }
}


// RGB LED test at start-up
void setup() {
   int wait=40;

   strip.begin();
   strip.show();        // Update LED contents, to start they are all 'off'
   color_wipe(color(150, 0, 0), wait);
   color_wipe(color(0, 150, 0), wait);
   color_wipe(color(0, 0, 150), wait);
   // color_wipe(color(0, 0, 0),   wait);    // all off
   rainbow(40);      // full color test
}


// procedures showing display
void loop() {
   int wait=40;

   color_wipe(color(90 + random(70), 90 + random(70), random(70)), wait);
   delay(60 * 1000);   // wait for 1 min.
}

// vim:ts=3 sw=3 et syntax=cpp
