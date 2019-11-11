#include "Drive.h"
#include "../Helpers/Helpers.h"
#include "../Include/pins.h"
#include <Arduino.h>

Drive::Drive(Encoder* enc, Motor* motor, PID_settings_t* pid, void (Drive::**task_func_ptr)()) {
    _enc = enc;
    _motor = motor;

    _kp = pid->kp;
    _ki = pid->ki;
    _kd = pid->kd;

    controller = PID(&_vel_est, &_pwm_out, &_requested_speed, _kp, _ki, _kd, DIRECT);
}

void Drive::set_speed(int speed) {
    _requested_speed = constrain(speed,-MAX_SPEED_RPM, MAX_SPEED_RPM);    // constrain input to [-MAX_SPEED, MAX_SPEED]
}

void Drive::stop() {
    stopped = true;
}

void Drive::start() {
    stopped = false;
}

void Drive::control_loop() {
    if (stopped) {
        _motor->set_pwm_speed(0);
        return;
    }

    _vel_est = _enc->get_velocity();
    controller.Compute();
    _motor->set_pwm_speed(_pwm_out);

}