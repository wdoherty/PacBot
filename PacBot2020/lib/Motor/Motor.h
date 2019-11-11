#include "../Adafruit_PWM_Servo_Driver_Library/Adafruit_PWMServoDriver.h"

#ifndef MOTOR_H
#define MOTOR_H

/* max speed in percent of full voltage*/
#define MAX_SPEED       75

/* kv of the mabuchi motor */
#define MOTOR_KV        1920

/* max voltage [volts] */
#define V_MAX       12

/* pwm resolution */
#define PWM_RESOLUTION  4095

class Motor {
    public:
        Motor(int pin_a, int pin_b, Adafruit_PWMServoDriver* pwm);
        void set_pwm_speed(double speed);

    private:
        Adafruit_PWMServoDriver* _pwm;
        int _requested_pwm = 0;
        int _pin_a;
<<<<<<< HEAD
        int _pin_b

=======
        int _pin_b;
>>>>>>> 84fb7f7f028e25b344d0c102fc21b3e321c7ac3b
};

#endif
