#!/usr/bin/env python
import pigpio
from adafruit_motorkit import MotorKit

class decoder:

   def __init__(self, pi, gpioA, gpioB, callback):

      self.pi = pi
      self.gpioA = gpioA
      self.gpioB = gpioB
      self.callback = callback

      self.levA = 0
      self.levB = 0

      self.lastGpio = None

      self.pi.set_mode(gpioA, pigpio.INPUT)
      self.pi.set_mode(gpioB, pigpio.INPUT)

      self.pi.set_pull_up_down(gpioA, pigpio.PUD_UP)
      self.pi.set_pull_up_down(gpioB, pigpio.PUD_UP)

      self.cbA = self.pi.callback(gpioA, pigpio.EITHER_EDGE, self._pulse)
      self.cbB = self.pi.callback(gpioB, pigpio.EITHER_EDGE, self._pulse)

   def _pulse(self, gpio, level, tick):

      """
      Decode the rotary encoder pulse.

                   +---------+         +---------+      0
                   |         |         |         |
         A         |         |         |         |
                   |         |         |         |
         +---------+         +---------+         +----- 1

             +---------+         +---------+            0
             |         |         |         |
         B   |         |         |         |
             |         |         |         |
         ----+         +---------+         +---------+  1
      """

      if gpio == self.gpioA:
         self.levA = level
      else:
         self.levB = level;

      if gpio != self.lastGpio: # debounce
         self.lastGpio = gpio

         if   gpio == self.gpioA and level == 1:
            if self.levB == 1:
	       #print("Backward tick")
               self.callback(1)
         elif gpio == self.gpioB and level == 1:
            if self.levA == 1:
	       #print("Forward tick")
               self.callback(-1)

   def cancel(self):

      """
      Cancel the rotary encoder decoder.
      """

      self.cbA.cancel()
      self.cbB.cancel()

if __name__ == "__main__":

   import time
   import pigpio
   from adafruit_motorkit import MotorKit

   import pigpioTest

   global pos
   global rotations
   global dist
   global wheelD
   global countsPer
   pos = 0
   rotations = 0
   dist = 0
   wheelD = 2.362
   countsPer = 155.0
   #actual_time = 0
   #past_time = time.time()
   #velocity = 0

   def callback(way):

      global pos
      global rotations
      global dist

      #global past_time
      #global time_actual
      #global velocity
      #actual_time = time.time()
      
      pos -= way
      rotations = (pos/countsPer)
      dist = rotations*wheelD

      #time = actual_time - past_time
      # velocity = 0.06283185307179587/time #linear movement of machine from each step of stepper motor
      #past_time = actual_time




   print("Setup")
   pi = pigpio.pi()
   drive = MotorKit()

   decoder = pigpioTest.decoder(pi, 4, 17, callback)

   #drive.motor1.throttle = 0.2


   while abs(rotations) < 3:
      drive.motor1.throttle = 0.4 * ((3 - abs(rotations))/3)
   
   drive.motor1.throttle = 0
   time.sleep(1)
   print("rotations={0}".format(rotations))




   decoder.cancel()

   pi.stop()