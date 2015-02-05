#include <TinyWireS.h>
#include <Adafruit_NeoPixel.h>

// Open this header file to configure the NeoPixel i2c driver
#include "i2cneopixels.h"

// Neo KHZ400 is necessary on the 8Mhz Trinket
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, PIXEL_COLOR_MODE + NEO_KHZ800);

// Tracks the current register pointer position
// There are 3x as many "registers" as pixels, RGB*PIXELS
volatile uint8_t current_register = 0;
volatile uint8_t mode = 0;

// Make a room for custom values;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

// Break program if need
bool interrupt = false;

// Handles each Write request
void handleWrite(uint8_t NumBytes)
{
  // Exit if there is no data or more data than the buffer should ever allow
  if (NumBytes < 1 || NumBytes > TWI_RX_BUFFER_SIZE) return;
  
  // Always treat the first byte as the address
  current_register = TinyWireS.receive();
  NumBytes--;
  
  if( current_register == 255 && NumBytes )
  {
    handleCommand(NumBytes);
  }
}

void handleCommand(uint8_t NumBytes)
{
  mode = TinyWireS.receive();
  
  if (mode == CMD_ALL_OFF) interrupt = true;
  
  NumBytes--;
  
  // Consume any leftover bytes
  while (NumBytes--)
  {
    TinyWireS.receive();
  }
}

void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onReceive(handleWrite);

    strip.begin();
    strip.show();
}

void loop()
{
//    TinyWireS_stop_check();
    switch (mode) {
      case CMD_COLOR_WIPE:
        // Some example procedures showing how to display to the pixels:
        colorWipe(strip.Color(255, 0, 0), 50); // Red
        colorWipe(strip.Color(0, 255, 0), 50); // Green
        colorWipe(strip.Color(0, 0, 255), 50); // Blue
        break;
      case CMD_THEATER_CHASE:
        // Send a theater pixel chase in...
        theaterChase(strip.Color(127, 127, 127), 50); // White
        theaterChase(strip.Color(127,   0,   0), 50); // Red
        theaterChase(strip.Color(  0,   0, 127), 50); // Blue
        break;
      case CMD_RAINBOW:
        rainbow(50);
        break;
      case CMD_RAINBOW_CYCLE:
        rainbowCycle(50);
        break;
      case CMD_THEATER_CHASE_RAINBOW:
        theaterChaseRainbow(50);
        break;
      case CMD_CUSTOM_COLOR:
        colorWipe(strip.Color(r, g, b), 1);
        break;
      case CMD_ALL_OFF:
      default:
        colorWipe(strip.Color(0, 0, 0), 20);
        break;
    }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      
      delay(wait);
      
      TinyWireS_stop_check();
      if (interrupt == true) {
        interrupt = false;
        return;
      }
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
        
    TinyWireS_stop_check();
    if (interrupt == true) {
      interrupt = false;
      return;
    }
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
        
        
    TinyWireS_stop_check();
    if (interrupt == true) {
      interrupt = false;
      return;
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
        
        
      TinyWireS_stop_check();
      if (interrupt == true) {
        interrupt = false;
        return;
      }
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
        
        delay(wait);
            
        TinyWireS_stop_check();
        if (interrupt == true) {
          interrupt = false;
          return;
        }
        
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
