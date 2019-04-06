from xbee import XBee
import serial
import time

serial_port = serial.Serial('/dev/ttyUSB0', 9600)


#def xbeeCallback(xbee_message):
#	print(xbee_message)

#xbee = XBee(serial_port, callback=xbeeCallback)

while True:
	try:
		time.sleep(0.001)
#		while serial_port.in_waiting > 0:
#			x = serial_port.read()
#			serial_port.write(x)
#			print(x)
		if serial_port.in_waiting > 0:
			print("read packet")
			x = serial_port.read().decode("utf-8")
			print(x)
			if x == '$':
				state = serial_port.read().decode("utf-8")
				serial_port.write(state.encode())
				print("state is:{}".format(state))
			serial_port.reset_input_buffer()


#		serial_port.write(8)
	except KeyboardInterrupt:
		break
#print("closing")
#xbee.halt()
serial_port.close() 
