#!/usr/bin/python

import time, sys
import requests
import range

from user import User
from beer import Beer
from keg import Keg

RANGE = 9
TO_START = 5

def start():
  # debug
  print 'Start'

  # play music

  # turn on lights

  # open valve


  # and wait...
  while range.get(0) < RANGE:
    time.sleep(0.01)

  stop()

def stop():
  # debug
  print 'Stop'

  # close valve

  # change animation

  # play music

  # turn off lights


  # and go to main loop
  return True

def main(argv):

  # set initial data
  i = 0

  while True:

    val = range.get(0)
    if val < RANGE:
      # debug
      print 'Counting'

      # play animation

      # increment
      i += 1

    elif i > 0:
      # false alarm...
      # debug
      print 'Reset'

      # stop animation

      # reset variable
      i = 0

    if i == TO_START:
      start()

if __name__ == "__main__":
   main(sys.argv[1:])