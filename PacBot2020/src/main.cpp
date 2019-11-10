#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Encoder.h>
#include "pins.h"

Adafruit_PWMServoDriver pwm;

encoder* enc1;
encoder* enc2;
encoder* enc3;
encoder* enc4;

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

  enc1 = new encoder(ENC1A, ENC1B);
  enc2 = new encoder(ENC2A, ENC2B);
  enc3 = new encoder(ENC3A, ENC3B);
  enc4 = new encoder(ENC4A, ENC4B);

  attachInterrupt(ENC1A, enc1->pin_change_a, CHANGE);
  attachInterrupt(ENC1B, enc1->pin_change_b, CHANGE);
  attachInterrupt(ENC2A, enc2->pin_change_a, CHANGE);
  attachInterrupt(ENC2B, enc2->pin_change_b, CHANGE);
  attachInterrupt(ENC3A, enc3->pin_change_a, CHANGE);
  attachInterrupt(ENC3B, enc3->pin_change_b, CHANGE);
  attachInterrupt(ENC4A, enc4->pin_change_a, CHANGE);
  attachInterrupt(ENC4B, enc4->pin_change_b, CHANGE);
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



