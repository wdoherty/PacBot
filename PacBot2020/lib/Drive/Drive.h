#ifndef DRIVE_H
#define DRIVE_H

#include "../Encoder/Encoder.h"
#include "../Motor/Motor.h"
#include "../Helpers/Helpers.h"
#include "../PID/PID_v1.h"

/* max speed in RPM */
#define MAX_SPEED_RPM   300

#define ADJUSTMENT_TOLERANCE    15
#define FRIC_COMP_DEADBAND      5

typedef struct friction_vals {
    double st_p;
    double st_n;
    double dy_p;
    double dy_n;
} friction_vals_t;

typedef struct pid_values {
    double kp;
    double ki;
    double kd;
} pid_values_t;


class Drive {
    public:
        Drive(Encoder* enc, Motor* motor, pid_values_t pid_vals, friction_vals_t fric);

        void set_speed(int speed);

        static void stop();
        static void start();
        void control_loop();


        double _kp;
        double _ki;
        double _kd;
        
        friction_vals_t _fric;
        PID* controller;
    private:

        double fric_comp(double w);

        double _requested_speed = 0;
        double _vel_est = 0;
        double _pid_out = 0;
        double _pwm_out = 0;

        Encoder* _enc;
        Motor* _motor;





        static bool stopped;
    
};

#endif