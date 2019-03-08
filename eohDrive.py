import time
import pygame
from adafruit_motorkit import MotorKit

kit = MotorKit()
pygame.init()

while(True):

    for event in pygame.event.get():
        print(event.key)
        print(event.type)
        if event.type == pygame.KEYDOWN:

            if event.key == pygame.K_w:
                print("up")
                kit.motor1.throttle = 0.5
                kit.motor3.throttle = 0.5
                kit.motor2.throttle = 0
                kit.motor4.throttle = 0
            elif event.key == pygame.K_s:
                print("down")
                kit.motor1.throttle = -0.5
                kit.motor3.throttle = -0.5
                kit.motor2.throttle = 0
                kit.motor4.throttle = 0
            elif event.key == pygame.K_a:
                print("left")
                kit.motor1.throttle = 0
                kit.motor3.throttle = 0
                kit.motor2.throttle = -0.5
                kit.motor4.throttle = -0.5
            elif event.key == pygame.K_d:
                print("right")
                kit.motor1.throttle = 0
                kit.motor3.throttle = 0
                kit.motor2.throttle = 0.5
                kit.motor4.throttle = 0.5
        elif event.type == pygmae.KEYUP:
            print("stopped")
            kit.motor1.throttle = 0
            kit.motor3.throttle = 0
            kit.motor2.throttle = 0
            kit.motor4.throttle = 0
