


#ifndef DRIVE_H
#define DRIVE_H

#include "../Encoder/Encoder.h"
#include "../Motor/Motor.h"
#include "../Helpers/Helpers.h"
#include "../PID/PID_v1.h"

/* max speed in RPM */
#define MAX_SPEED_RPM   100

class Drive {
    public:
        Drive(Encoder* enc, Motor* motor, PID_settings_t* pid, void (Drive::**task_func_ptr)());

        void set_speed(int speed);

        static void stop();
        static void start();

    private:
        void control_loop();

        double _requested_speed = 0;
        double _vel_est = 0;
        double _pwm_out = 0;
        
        Encoder* _enc;
        Motor* _motor;

        PID controller;

        double _kp;
        double _ki;
        double _kd;

        static bool stopped;
    
};

bool Drive::stopped = false;

#endif