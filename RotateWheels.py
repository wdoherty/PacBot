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

   import RotateWheels

   global pos
   global rotations
   global dist
   global wheelD
   global countsPer
   global topSpeed
   topSpeed = 0.3
   pos = 0
   rotations = 0
   dist = 0
   wheelD = 2.362
   countsPer = 155.0/31  #155.0

   global error
   global lastError
   error = 0
   lastError = 0
   _kp = 0.10	#0.145	#0.165	#0.275 	#0.16 	0.0925  0.078
   _ki = 0.005	#0.015	#0.02	#0.05	#0.0 	0.005   0.00
   _kd = 0.1	#0.21	#0.175	#0.5 	#0.2  	0.0225 	0.045

   minThrottle = 0.25
   startThrottle = 0.8
   startThrottleTime = 0.05

   #actual_time = 0
   #past_time = time.time()
   #velocity = 0

   global encoderTicks
   global updateResolution

   updateResolution = 31
   encoderTicks = 0

   def callback(way):
      global encoderTicks
      global updateResolution
      encoderTicks += 1
      if (encoderTicks % updateResolution == 0):
         encoderTicks = 0


         global pos
         global rotations
         global dist

         #global past_time
         #global time_actual
         #global velocity
         #actual_time = time.time()
      
         pos -= way
         rotations = (pos/countsPer)
         dist = rotations*wheelD*3.14159

         #time = actual_time - past_time
         # velocity = 0.06283185307179587/time #linear movement of machine from each step of stepper motor
         #past_time = actual_time
         #print("Callback: " + str(way))



   def drivePID1(target, kp, ki, kd):
      global pos
      global rotations
      global dist
      global error
      global lastError

      pos = 0
      rotations = 0
      dist = 0
      speed = 0

      integral = 0
      derivative = 0

      while(1):
         time.sleep(0.05)
         lastError = error
         error = target - dist
         integral += error
         derivative = error - lastError
         speed = ((kp*error) + (ki*integral) + (kd*derivative))
         #print("Dist={0}, Error={1}, Speed={2}".format(dist, error, speed))
  
         
         if speed > topSpeed:
            speed = topSpeed
         elif speed < -topSpeed:
            speed = -topSpeed
         else:
            if (abs(speed) < minThrottle and speed > 0):
                speed = minThrottle
            elif (abs(speed) < minThrottle and speed < 0):
                speed = -minThrottle 

         #print(speed)

         #if (abs(speed) < minThrottle):
         #   #print("Start")
         #   drive.motor1.throttle = startThrottle * (-1 if speed < 0 else 1)
         #   time.sleep(startThrottleTime)

         drive.motor1.throttle = -speed
         drive.motor3.throttle = -speed
         if (abs(speed) < minThrottle and abs(error) < 0.75):
            drive.motor3.throttle = 0;
            drive.motor1.throttle = 0;
            time.sleep(0.5)
            print("Dist={0}, Error={1}, Speed={2}".format(dist, error, speed))
            break

      print("rotations={0}".format(rotations))

   pi = pigpio.pi()
   drive = MotorKit()

   decoder = RotateWheels.decoder(pi, 4, 17, callback)

   drivePID1(12, _kp, _ki, _kd)

   decoder.cancel()

   pi.stop()