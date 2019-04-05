#!/usr/bin/env python
import pigpio
from adafruit_motorkit import MotorKit

if __name__ == "__main__":

	import time
	import pigpio
	from adafruit_motorkit import MotorKit

	def driveTime(runtime, axis, direction):
		#axis=0 for front/back, axis=1 for left/right
		#direction=0 for backwards motion, direction=1 for forwards motion
		startTime = int(round(time.time()*1000))
		if axis == 0:
			if direction == 0:
				drive.motor1.throttle = -0.4
				drive.motor4.throttle = 0.4
			else:
				drive.motor1.throttle = 0.4
				drive.motor4.throttle = -0.4
		elif axis == 1:
			if direction == 0:
				drive.motor2.throttle = -0.4
				drive.motor3.throttle = -0.4
			else:
				drive.motor2.throttle = 0.4
				drive.motor3.throttle = 0.4

		while (int(round(time.time()*1000)) - startTime) < runtime:
			 pass
		drive.motor1.throttle = 0
		drive.motor3.throttle = 0
		drive.motor2.throttle = 0
		drive.motor4.throttle = 0		

	pi = pigpio.pi()
	drive = MotorKit()

	#0,0 - Pi is forward on bot, drives forward
	#1,0 - Pi is forward on bot, drives left

	driveTime(1500, 0, 0)
	#driveTime(500, 0, 1)
	driveTime(1500, 1, 0)
	#driveTime(500, 1, 1)

	pi.stop()