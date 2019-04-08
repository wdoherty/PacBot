from xbee import XBee
import serial
import time
import threading

serial_port = serial.Serial('/dev/ttyUSB0', 9600)

#class xbeeThread(threading.Thread):
#	def __init__(self, name='xbeeThread'):
#		self._stopevent = threading.Event()
#		threading.Thread.__init__(self, name=name)

def monitorState(lock):
	global state
	global killFlag
	killFlag = 0
	while not killFlag:
		try:
			time.sleep(0.001)
			if serial_port.in_waiting > 0:
#				print("read packet")
				x = serial_port.read().decode("utf-8")
#				print(x)
				if x == '$':
					lock.acquire()
					state = serial_port.read().decode("utf-8")
					localState = state
					lock.release()
					serial_port.write(localState.encode())
#					print("state is:{}".format(state))
				serial_port.reset_input_buffer()
		except KeyboardInterrupt:
			break

#	def join(self, timeout=None):
#		self.stopevent.set()
#		threading.Thread.join(self, timeout)

def mainTask():
	global state
	global killFlag
	state = 'P'
	lock = threading.Lock()

	t1 = threading.Thread(target=monitorState, args=(lock,))

	t1.start()

	for x in range(50000):
		try:
			lock.acquire()
			x = state
			lock.release()
			if x  == 'R': break
#			serial_port.write(x.encode())
		except KeyboardInterrupt:
			break
	killFlag=1
	t1.join()
	serial_port.close() 

if __name__ == "__main__":
	mainTask()
