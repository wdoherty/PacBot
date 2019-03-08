from pynput import keyboard
from adafruit_motorkit import MotorKit
import time

# kit = MotorKit()

def on_press(key):
    try:
        if key.char == 'w':
            print("up")
            # kit.motor1.throttle = 0.5
            # kit.motor3.throttle = 0.5
            # kit.motor2.throttle = 0
            # kit.motor4.throttle = 0
        elif key.char == 's':
            print("down")
            # kit.motor1.throttle = -0.5
            # kit.motor3.throttle = -0.5
            # kit.motor2.throttle = 0
            # kit.motor4.throttle = 0
        elif key.char == 'a':
            print("left")
            # kit.motor1.throttle = 0
            # kit.motor3.throttle = 0
            # kit.motor2.throttle = -0.5
            # kit.motor4.throttle = -0.5
        elif key.char == 'd':
            print("right")
            # kit.motor1.throttle = 0
            # kit.motor3.throttle = 0
            # kit.motor2.throttle = 0.5
            # kit.motor4.throttle = 0.5
    except AttributeError:
        print('special key {0} pressed'.format(
            key))
        print("stopped")
        # kit.motor1.throttle = 0
        # kit.motor3.throttle = 0
        # kit.motor2.throttle = 0
        # kit.motor4.throttle = 0
def on_release(key):
    print("stopped")
    # kit.motor1.throttle = 0
    # kit.motor3.throttle = 0
    # kit.motor2.throttle = 0
    # kit.motor4.throttle = 0
    if key == keyboard.Key.esc:
        # Stop listener
        return False
with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
