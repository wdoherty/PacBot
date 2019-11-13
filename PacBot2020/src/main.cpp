#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Encoder.h>
#include <Motor.h>
#include "pins.h"

Adafruit_PWMServoDriver pwm;
Encoder* enca;
Motor* mota;

void IRAM_ATTR enc1a_change() {
  enca->pin_change_a();
  //Serial.print('A');
}
void IRAM_ATTR enc1b_change() {
  enca->pin_change_b();
  //Serial.print('B');
}

void setup() {
  pwm = Adafruit_PWMServoDriver(0x48);
  Serial.begin(1000000);
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

  mota = new Motor(8, 9, &pwm);
  enca = new Encoder(ENC1A, ENC1B);
  attachInterrupt(ENC1A, enc1a_change, CHANGE);
  attachInterrupt(ENC1B, enc1b_change, CHANGE);
  for (int i = 5; i > 0; i--) Serial.println(i);
  mota->set_pwm_speed(85);

}

void loop() {
  delay(50);
  /*Serial.printf("X:%ld\tV:%f\n", enca->get_ticks(), enca->get_velocity());*/
  Serial.printf("%f\n", enca->get_velocity());
  //Serial.printf("%ld\n", enca->get_ticks());
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



