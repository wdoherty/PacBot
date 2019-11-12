#ifndef ENCODER_H
#define ENCODER_H

#include "portmacro.h"

// WARNING AS THIS INCREASES, ENCODER INTERRUPTS GET BLOCKED IN SPIN LOCK FOR LONGER
#define NUM_TICK_TIMES      10

class Encoder {
    public:
        Encoder(int A, int B);
        void resetTicks();
        int get_ticks();

        void pin_change_a();
        void pin_change_b();

        double get_velocity();

    private:
        portMUX_TYPE tick_mux = portMUX_INITIALIZER_UNLOCKED;
        long tick_pos[NUM_TICK_TIMES];
        long tick_time[NUM_TICK_TIMES];
        int tick_hist_idx = 0;

        int pin_A;
        int pin_B;
        long ticks;

        bool A_state;
        bool B_state;
};

#endif