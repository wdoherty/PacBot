#!/usr/bin/env python
import time
import pigpio
from adafruit_motorkit import MotorKit
#from xbee import XBee
import serial
import struct

if __name__ == "__main__":
	global pos
	global rotations
	global dist
	global wheelD
	global countsPer
	global topSpeed
	topSpeed = 0.4
	pos = 0
	rotations = 0
	dist = 0
	wheelD = 2.3622 #2.362
	countsPer = 142.0 #83.1978*2 #151.0

	ser = serial.Serial(port='/dev/ttyS0',baudrate = 115200)

	global error
	global lastError
	error = 0
	lastError = 0
	_kp = 1.90	#0.10	#0.145	#0.165	#0.275 	#0.16 	0.0925  0.078
	_ki = 0.0	#0.005	#0.015	#0.02	#0.05	#0.0 	0.005   0.00
	_kd = 1.05	#0.1	#0.21	#0.175	#0.5 	#0.2  	0.0225 	0.045

	minThrottle = 0.25
	startThrottle = 0.8
	startThrottleTime = 0.05

	def getDist1():
		global wheelD
		global countsPer

		ser.write(bytes([0x02]))
		wheelTicks = 0
		wheelRotations = 0
		wheelDist = 0
		for i in range(2):
			encoderVal = struct.unpack("<L", ser.read(4))[0]
			encoderVal = encoderVal & 0xffffffff
			encoderValSigned = (encoderVal ^ 0x80000000) - 0x80000000
			if i == 0:
				wheelTicks = encoderValSigned
		wheelRotations = wheelTicks/countsPer
		wheelDist = wheelRotations*wheelD*3.14159
		return wheelDist

	def getDist2():
		global wheelD
		global countsPer

		ser.write(bytes([0x02]))
		wheelTicks = 0
		wheelRotations = 0
		wheelDist = 0
		for i in range(2):
			encoderVal = struct.unpack("<L", ser.read(4))[0]
			encoderVal = encoderVal & 0xffffffff
			encoderValSigned = (encoderVal ^ 0x80000000) - 0x80000000
			if i == 1:
				wheelTicks = encoderValSigned
		wheelRotations = wheelTicks/countsPer
		wheelDist = wheelRotations*wheelD*3.14159
		return -wheelDist

	def resetEncoders():
		ser.write(bytes([60]))
		for i in range(2):
			encoderVal = struct.unpack("<L", ser.read(4))[0]	

	def drivePID1(target, kp, ki, kd):
		global error
		global lastError

		pos = 0
		rotations = 0
		dist = 0
		speed = 0

		integral = 0
		derivative = 0

		resetEncoders()

		while(1):
			dist = getDist1()
			#print(dist)
			#time.sleep(0.05)
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
			drive.motor2.throttle = -speed
			drive.motor3.throttle = -speed
			if (abs(speed) <= minThrottle and abs(error) < 0.125):
				drive.motor2.throttle = 0;
				drive.motor3.throttle = 0;
				time.sleep(0.5)
				print("Dist={0}, Error={1}, Speed={2}".format(dist, error, speed))
				break
		print("rotations={0}".format(rotations))

	def drivePID2(target, kp, ki, kd):
		global error
		global lastError

		pos = 0
		rotations = 0
		dist = 0
		speed = 0

		integral = 0
		derivative = 0

		resetEncoders()

		while(1):
			dist = getDist2()
			#print(dist)
			#time.sleep(0.05)
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
			drive.motor1.throttle = -speed
			drive.motor4.throttle = speed
			if (abs(speed) <= minThrottle and abs(error) < 0.125):
				drive.motor1.throttle = 0;
				drive.motor4.throttle = 0;
				time.sleep(0.5)
				print("Dist={0}, Error={1}, Speed={2}".format(dist, error, speed))
				break
		print("rotations={0}".format(rotations))

	pi = pigpio.pi()
	drive = MotorKit()

	try:
		#drivePID1(12, _kp, _ki, _kd)
		drivePID2(-10.75, _kp, _ki, _kd)

		#time.sleep(3)
	finally:
		#print(getDist1())
		print(getDist2())
		drive.motor1.throttle = 0
		drive.motor2.throttle = 0
		drive.motor3.throttle = 0
		drive.motor4.throttle = 0
		pi.stop()
		ser.close()
		