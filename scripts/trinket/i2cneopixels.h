/************************
* VALUES YOU CAN CHANGE *
*************************/

// The I2C address that your Trinket will use
#define I2C_SLAVE_ADDRESS 0x4

// NeoPixel PIN, and pixel count
// Brightness MUST be 255 or colours can't be read back correctly from the strip
#define PIN 1 // Pin the strip is connected to
#define PIXELS 24 // Maximum of 85 pixels
#define PIXEL_COLOR_MODE NEO_GRB // You might want to change this to NEO_RGB if you're using anything but real NeoPixels

/************************
*    EVERYTHING ELSE    *
*************************/

// Only change this if you have modified in TinyWireS
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

#define __AVR_ATtiny85_

// These define the commands available when writing via i2c
#define CMD_ALL_OFF 0x00
#define CMD_CUSTOM_COLOR 0x01 // @todo
#define CMD_THEATER_CHASE 0x02
#define CMD_RAINBOW 0x03
#define CMD_RAINBOW_CYCLE 0x04
#define CMD_THEATER_CHASE_RAINBOW 0x05
#define CMD_COLOR_WIPE 0x06

void handleWrite(uint8_t NumBytes);
void handleCommand(uint8_t NumBytes);
void setup();
void loop();
