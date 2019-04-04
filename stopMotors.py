#!/usr/bin/env python
import pigpio
from adafruit_motorkit import MotorKit

if __name__ == "__main__":

   import pigpio
   from adafruit_motorkit import MotorKit

   drive = MotorKit()

   drive.motor1.throttle = 0
   drive.motor2.throttle = 0
   drive.motor3.throttle = 0
   drive.motor4.throttle = 0