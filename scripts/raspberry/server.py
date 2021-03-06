#!/usr/bin/python

import time, sys
import requests
import range
import valve
import neopixel
import sound
import camera

from user import User
from beer import Beer
from keg import Keg

RANGE = 8
TO_START = 5
MAX_TIME = 2

def start():
  # debug
  print 'Start'

  # turn on lights
  neopixel.throbber()

  # play music
  sound.play('vendor/private/foley_sports_drinking_bottle_fill_with_water_from_tap.mp3');

  # open valve
  valve.on()

  # start timer
  timer = time.time()
  is_t = 1
  is_r = 1

  # and wait...
  while (is_r and is_t):
    time.sleep(0.01)
    is_r = range.get(0) < RANGE
    # is_t = (time.time() - timer) < MAX_TIME

  stop()

def stop():
  # debug
  print 'Stop'

  # close valve
  valve.off()

  # play sound
  sound.play('vendor/private/smb_coin.wav');

  # change animation
  neopixel.close()

  # take picture
  camera.take()

  # turn off lights
  neopixel.off()


  # and go to main loop
  return True

def main():

  # set initial data
  i = 0
  stop()

  while True:

    val = range.get(0)

    if val == 1:

      # play animation
      neopixel.loading()

      # increment
      i += 1

    elif val < RANGE:
      # debug
      print 'Counting'

      # increment
      i += 1

    elif i > 0:
      # false alarm...
      # debug
      print 'Reset'

      # stop animation
      neopixel.off()

      # reset variable
      i = 0

    if i == TO_START:
      start()

if __name__ == "__main__":
   main()