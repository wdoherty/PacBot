Adafruit_PWMServoDriver PWM = Adafruit_PWMServoDriver(PCA_I2C_ADDR);

int motorChannels[4][2] = { { M0_IN1, M0_IN2 }, { M1_IN1, M1_IN2 }, { M2_IN1, M2_IN2 }, { M3_IN1, M3_IN2 } };
int currentSpeeds[4] = { 0, 0, 0, 0 };


void setup_Drivers() {
  PWM.begin();
  PWM.setPWMFreq(1000);
  for (int i = 0; i < 16; i++) { PCA_analogWrite(i, 0); }
}


void set_Motor_Speed(int index, int pwm_val) {
  if (currentSpeeds[index] == pwm_val) return;
  currentSpeeds[index] = pwm_val;
  
  int writeChannel;
  pwm_val = constrain(pwm_val, -255, 255) * (reverseMotor[index] ? -1 : 1);
  if (pwm_val > MOTOR_PWM_DEADBAND) { 
    PCA_analogWrite(motorChannels[index][0], 0);
    PCA_analogWrite(motorChannels[index][1], abs(pwm_val));
  } else if (pwm_val < -MOTOR_PWM_DEADBAND) {
    PCA_analogWrite(motorChannels[index][1], 0);
    PCA_analogWrite(motorChannels[index][0], abs(pwm_val));
  } else {
    PCA_analogWrite(motorChannels[index][0], 0);
    PCA_analogWrite(motorChannels[index][1], 0);
  }
}


void PCA_analogWrite(int channel, int val) {
  val = constrain(val, 0, 255);
  if (val == 255) {
    PWM.setPWM(channel, 4096, 0);
  } else if (val == 0) {
    PWM.setPWM(channel, 0, 4096);
  } else {
    PWM.setPWM(channel, 0, constrain(map(val, 0, 255, 0, 4095), 0, 4095));
  }
}



