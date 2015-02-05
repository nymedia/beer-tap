#!/usr/bin/python

import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

TRIGGER = 13
ECHO_1 = 16

def get(sensor):

    if sensor == 0:
        GPIO.setup(TRIGGER,GPIO.OUT)
        GPIO.setup(ECHO_1,GPIO.IN)
        GPIO.output(TRIGGER, GPIO.LOW)

        time.sleep(0.3)

        GPIO.output(TRIGGER, True)
        time.sleep(0.00001)
        GPIO.output(TRIGGER, False)

        while GPIO.input(ECHO_1) == 0:
          signaloff = time.time()

        while GPIO.input(ECHO_1) == 1:
          signalon = time.time()

        timepassed = signalon - signaloff
        distance = timepassed * 17000
        return distance

    else:
        print "Incorrect usonic() function variable."
