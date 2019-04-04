#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

RoAPin = 4    # pin4
RoBPin = 17    # pin17
RoSPin = 24    # pin24

globalCounter = 0

flag = 0
Last_RoB_Status = 0
Current_RoB_Status = 0

def setup():
    print("setup")
    GPIO.setmode(GPIO.BCM)       # Numbers GPIOs by Broadcom numbering
    GPIO.setup(RoAPin, GPIO.IN)    # input mode
    GPIO.setup(RoBPin, GPIO.IN)
    GPIO.setup(RoSPin,GPIO.IN,pull_up_down=GPIO.PUD_UP)
    rotaryClear()

def rotaryDeal():
    global flag
    global Last_RoB_Status
    global Current_RoB_Status
    global globalCounter
    Last_RoB_Status = GPIO.input(RoBPin)
    while(not GPIO.input(RoAPin)):
        Current_RoB_Status = GPIO.input(RoBPin)
        flag = 1
    if flag == 1:
        flag = 0
        if (Last_RoB_Status == 0) and (Current_RoB_Status == 1):
            globalCounter = globalCounter + 1
            # print ('globalCounter = %d' % globalCounter)
            print("globalCounter = ", globalCounter)
        if (Last_RoB_Status == 1) and (Current_RoB_Status == 0):
            globalCounter = globalCounter - 1
            # print ('globalCounter = %d' % globalCounter)
            print("globalCounter = ", globalCounter)

def clear(ev=None):
    globalCounter = 0
    # print ('globalCounter = %d' % globalCounter)
    print("globalCounter = ", globalCounter)
    time.sleep(1)

def rotaryClear():
    GPIO.add_event_detect(RoSPin, GPIO.FALLING, callback=clear) # wait for falling


def loop():
    global globalCounter
    while True:
        rotaryDeal()
        # print ('globalCounter = %d' % globalCounter)
        print("globalCounter = ", globalCounter)

def destroy():
    GPIO.cleanup()             # Release resource

if __name__ == '__main__':     # Program start from here
    print("starting")
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
        destroy()
