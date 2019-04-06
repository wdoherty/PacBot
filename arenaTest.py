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

	trims = [0.0355,-0.05,0,-0.03]

	topSpeed = 0.375
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
		return wheelDist

	def resetEncoders():
		ser.write(bytes([60]))
		for i in range(2):
			encoderVal = struct.unpack("<L", ser.read(4))[0]	

	def drivePID1(target, kp=_kp, ki=_ki, kd=_kd, timeout=10000):
		global error
		global lastError

		pos = 0
		rotations = 0
		dist = 0
		speed = 0
		startTime = int(round(time.time()*1000))
		integral = 0
		derivative = 0
		actualTimeout = timeout
#		if actualTimeout == -1:
#			actualTimeout = 0.75*(abs(target)/topSpeed)

		resetEncoders()

		while (int(round(time.time()*1000))-startTime)<actualTimeout:
#		while 1:
			dist = getDist1()
			#print(dist)
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
			drive.motor2.throttle = -(speed + (abs(target)/target)*trims[1]) 
			drive.motor3.throttle = -(speed + (abs(target)/target)*trims[2])
			if (abs(speed) <= minThrottle and abs(error) < 0.125):
				drive.motor2.throttle = 0;
				drive.motor3.throttle = 0;
				time.sleep(0.5)
				print("Dist={0}, Error={1}, Speed={2}".format(dist, error, speed))
				break
		print("rotations={0}".format(rotations))

	def drivePID2(target, kp=_kp, ki=_ki, kd=_kd, timeout=10000):
		global error
		global lastError

		pos = 0
		rotations = 0
		dist = 0
		speed = 0
		startTime = int(round(time.time()*1000))
		integral = 0
		derivative = 0
		actualTimeout = timeout
#		if actualTimeout == -1:
#			actualTimeout = 0.75*(abs(target)/topSpeed)
		resetEncoders()

		while (int(round(time.time()*1000))-startTime) < actualTimeout:
#		while 1:
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
			drive.motor1.throttle = -(speed + (abs(target)/target)*trims[0])
			drive.motor4.throttle = speed + (abs(target)/target)*trims[3]
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
		#-PID2 = left
		#+PID2 = right	
		#+PID1 = up
		#-PID1 = down

		#drivePID2(30, _kp, _ki, _kd)		

		drivePID2(-5.3, _kp, _ki, _kd, 1500)		
		drivePID1(12, _kp, _ki, _kd, 2000)
		drivePID1(-0.75, _kp, _ki, _kd, 500)
		drivePID2(1, _kp, _ki, _kd, 750)
		drivePID2(-41.75, _kp, _ki, _kd, 15000)
		drivePID1(-10.75, _kp, _ki, _kd)
		drivePID2(7.2, _kp, _ki, _kd, 5000)
		drivePID1(-10.75, _kp, _ki, _kd)
		drivePID2(10.75, _kp, _ki, _kd)
		drivePID2(-0.75, _kp, _ki, _kd, 750)
		drivePID1(-1.5, timeout=750)
		drivePID1(0.75, timeout=750)
		drivePID2(20, timeout=15000)
		drivePID2(-0.75, timeout = 750)
		drivePID1(-12.5)
		drivePID1(0.75, timeout=750)
		drivePID2(39.25, timeout = 25000)
		drivePID1(12.5)
		drivePID1(-0.75, timeout = 750)
		drivePID2(-17)
		drivePID2(0.75)
		drivePID1(10.5)
		drivePID1(-0.75)
		drivePID2(-10.5)
		drivePID2(0.75)
		drivePID1(20)

		pass



		
	finally:
		#print(getDist1())
		#print(getDist2())
		drive.motor1.throttle = 0
		drive.motor2.throttle = 0
		drive.motor3.throttle = 0
		drive.motor4.throttle = 0
		pi.stop()
		ser.close()
		
