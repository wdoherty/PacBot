


#ifndef DRIVE_H
#define DRIVE_H

#include "../Encoder/Encoder.h"
#include "../Motor/Motor.h"
#include "../Settings/Settings.h"

class Drive {
    public:
    Drive(Encoder enc, Motor motor, PID_settings_t pid, void (Drive::**task_func_ptr)());

    void set_speed(int speed);

    static void stop();
    static void start();

    private:
    int requested_speed = 0;

}

#endif