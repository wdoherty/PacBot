#include "Motor.h"
#include "../Helpers/Helpers.h"

Motor::Motor(int pin_a, int pin_b, Adafruit_PWMServoDriver* pwm, int reversed, QueueHandle_t* pca_queue) {
    if (reversed) {
        _pin_a = pin_b;
        _pin_b = pin_a;
    } else {
        _pin_a = pin_a;                                             // store the pin numbers on the PCA chip for this motor driver
        _pin_b = pin_b;
    }

    current.pin_a = _pin_a;
    current.pin_b = _pin_b;
    _pca_queue = pca_queue;
    _pwm = pwm;                                                 // keep a copy of the pca9685 driver to set pwm later
}


/* set_pwm_speed
*   INPUTS: double speed - speed in Wheel RPM (fully theoretical)
*   OUTPUTS: None
*   SIDE EFFECTS: Modifies the channels on the PCA driver to set the voltages to theoretically set the requested RPM
*/
void Motor::set_pwm_speed(double speed) {
    int speed_percent = 100 * speed * GEAR_RATIO / ((double)MOTOR_KV * (double)V_MAX);

    //Serial.printf("S:%d\n",speed_percent);
    _requested_pwm = constrain(speed_percent,-MAX_SPEED_PERCENT, MAX_SPEED_PERCENT);    // constrain input to [-MAX_SPEED_PERCENT, MAX_SPEED_PERCENT]

    float magnitude = abs(_requested_pwm) / (float)100.0;                // get magnitude 0-1 scalar
    int dir = (_requested_pwm > 0) ? 1 : -1;                    // get direction to spin

    
    //Serial.printf("M:%f\n",magnitude);
    int pin_a_val = 0;
    int pin_b_val = 0;

    if (dir == 1) {                                             // if spin forwards, leave pin b at 0, and set pin a to the correct pwm value
        pin_a_val = (PWM_RESOLUTION * magnitude);
    } else {
        pin_b_val = (PWM_RESOLUTION * magnitude);
    }
    Serial.printf("PWM:%d\t%d\n",pin_a_val, pin_b_val);

    current.pin_a_val = pin_a_val;
    current.pin_b_val = pin_b_val;
    xQueueSend(_pca_queue, &current, 0);

    // _pwm->setPWM(_pin_a, pin_a_val);                            // set the pwm values of those pins on the PCA9685
    // _pwm->setPWM(_pin_b, pin_b_val);
}