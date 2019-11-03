#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#define ENC1 36
#define ENC2 39

Adafruit_PWMServoDriver pwm;

void updatePin1()
{
  Serial.println("Pin1");
}

void updatePin2()
{
  Serial.println("Pin2");
}

void setup() {
  // put your setup code here, to run once:
  pwm = Adafruit_PWMServoDriver(0x48);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(500);  // This is the maximum PWM frequency
  pinMode(ENC1, INPUT);
  pinMode(ENC2, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC1), updatePin1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2), updatePin2, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    pwm.setPWM(0, 0, 2048);
    pwm.setPWM(1, 0, 0);
    delay(2000);
    pwm.setPWM(0, 0, 0);
    delay(2000);
  }
}



