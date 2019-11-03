

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
    public:
        Motor(int pin_a, int pin_b);
        void set_velocity(int speed)

    private:
        int requested_speed = 0;


}

#endif