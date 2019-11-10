#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Encoder.h>
#include "pins.h"

Adafruit_PWMServoDriver pwm;

void setup() {
  pwm = Adafruit_PWMServoDriver(0x48);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(500);  // This is the maximum PWM frequency
  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);
  pinMode(ENC2A, INPUT);
  pinMode(ENC2B, INPUT);
  pinMode(ENC3A, INPUT);
  pinMode(ENC3B, INPUT);
  pinMode(ENC4A, INPUT);
  pinMode(ENC4B, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  // while(1)
  // {
  //   pwm.setPWM(0, 0, 2048);
  //   pwm.setPWM(1, 0, 0);
  //   delay(2000);
  //   pwm.setPWM(0, 0, 0);
  //   delay(2000);
  // }
}



