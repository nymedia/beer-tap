#!/usr/bin/env python

# define I2C address of PCF8575 (0x20 to 0x27 are valid)
I2C_ADDRESS = 0x04

# import libraries
import smbus as smbus
import sys

#configure I2C bus for functions
i2c = smbus.SMBus(1)

def send(command):
  error = 1
  while error == 1:
    try:
       print 'Sending data: ', command
       i2c.write_i2c_block_data(I2C_ADDRESS, 0xFF, [command])
       error = 0
    except:
       print "Unexpected error: ", sys.exc_info()[0]
       error = 1


def loading():
  send(0x02)

def throbber():
  send(0x06)

def close():
  send(0x05)

def off():
  send(0x00)
