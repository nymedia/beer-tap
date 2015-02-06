#!/usr/bin/python

import datetime, time, sys, os
import urllib2
import base64
import json

def take():
  utc_datetime = datetime.datetime.utcnow()
  s = utc_datetime.strftime("%Y-%m-%d-%H%M%SZ")
  filename = 'IMG_' + s + '.jpg'
  os.system('raspistill -o ../../output/' + filename)
  send(filename);

def send(filename):
  url = "http://dev-beertap.pantheon.io/ctable/image"

  with open("../../output/" + filename, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read())
        data = {
            'image': encoded_string
        }
        req = urllib2.Request(url)
        response = urllib2.urlopen(req, json.dumps(data))
