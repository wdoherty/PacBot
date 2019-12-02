#ifndef MOTOR_H
#define MOTOR_H

#include "../Adafruit_PWM_Servo_Driver_Library/Adafruit_PWMServoDriver.h"

/* max speed in percent of full voltage*/
#define MAX_SPEED_PERCENT       75

#define MIN_RPM         90

/* kv of the mabuchi motor */
#define MOTOR_KV        1920

#define GEAR_RATIO      100

/* max voltage [volts] */
#define V_MAX       12

/* pwm resolution */
#define PWM_RESOLUTION  4095

class Motor {
    public:
        Motor(int pin_a, int pin_b, Adafruit_PWMServoDriver* pwm, int reversed);
        void set_pwm_speed(double speed);

    private:
        Adafruit_PWMServoDriver* _pwm;
        int _requested_pwm = 0;
        int _pin_a;
        int _pin_b;
};

#endif
