#!/usr/bin/python

import time, sys
import RPi.GPIO as GPIO

VALVE = 12

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(VALVE, GPIO.OUT)

def on():
	GPIO.output(VALVE, True)

def off():
	GPIO.output(VALVE, True)
