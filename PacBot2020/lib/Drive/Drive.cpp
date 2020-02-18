#include "Drive.h"
#include "../Helpers/Helpers.h"
#include <Arduino.h>

bool Drive::stopped = true;

Drive::Drive(Encoder* enc, Motor* motor, pid_values_t pid_v, friction_vals_t fric, int id) {
    _id = id;
    _fric = fric;

    _enc = enc;
    _motor = motor;

    _kp = pid_v.kp;
    _ki = pid_v.ki;
    _kd = pid_v.kd;

    controller = new PID(&_vel_est, &_pid_out, &_requested_speed, _kp, _ki, _kd, P_ON_E, DIRECT);
    controller->SetOutputLimits(-MAX_SPEED_RPM, MAX_SPEED_RPM);
    controller->SetMode(AUTOMATIC);
}

/*
*   set_speed(int speed)
*   INPUTS: speed in RPM
*   OUTPUTS: None
*   SIDE EFFECTS: Adjusts Setpoint for CL Velocity Controller
*/
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


    ctr++;
    _vel_est = _enc->get_velocity();
    if (ctr % 5 == 0) Serial.printf("ID[%d]\t", _id);
    //if (ctr % 5 == 0) Serial.printf("V:%.3f, ", _vel_est);
    controller->Compute();
    //Serial.printf("E: %f\t", _requested_speed - _vel_est);
    //if (ctr % 5 == 0) Serial.printf("P:%.3f", _pid_out);
    _pwm_out = _pid_out + fric_comp(_vel_est);
    /*if ((_requested_speed < 0 && _pid_out-ADJUSTMENT_TOLERANCE < 0) || (_requested_speed > 0 && _pid_out+ADJUSTMENT_TOLERANCE > 0) || abs(_requested_speed) <= ADJUSTMENT_TOLERANCE) {
        
    } else {
        _pwm_out = fric_comp(_vel_est);
    }*/
    if (ctr % 5 == 0) Serial.printf("\tE:%.3f\n", _pwm_out);

    //Serial.printf("PWM:%f\n\n", _pwm_out);
    _motor->set_pwm_speed(_pwm_out*3);

}


double Drive::fric_comp(double w) {
    if (_requested_speed < FRIC_COMP_DEADBAND) return 0;

    if (_requested_speed > 0) {
        if (w > 0) return _fric.st_p + (w * _fric.dy_p);
        return 0;
    } else {
        if (w < 0) return -_fric.st_n + (w * _fric.dy_n);
        return 0;
    }
}