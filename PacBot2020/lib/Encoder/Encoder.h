#ifndef ENCODER_H
#define ENCODER_H

#include <mutex>
#include <FreeRTOS.h>
#include <Arduino.h>
#include "../Helpers/Helpers.h"

#define TICK_STEP_SIZE_MS       25      
#define NUM_TICK_STEPS          20
#define NUM_STEPS_TO_AVERAGE    10

typedef struct tick_hist {
    long tick_pos;
    unsigned long time;
} tick_hist_t;


class Encoder {
    public:
        Encoder(int A, int B, int reversed);
        void update();
        void resetTicks();
        long get_ticks();

        void pin_change_a();
        void pin_change_b();

        double get_velocity();

    private:
        int _rev;

        int get_time_step_index(int time_step);

        portMUX_TYPE tick_mux = portMUX_INITIALIZER_UNLOCKED;
        tick_hist_t history[NUM_TICK_STEPS];
        int last_hist_idx = NUM_TICK_STEPS-1;

        bool velocity_ready = false;

        int pin_A;
        int pin_B;
        long ticks;

        int A_state;
        int B_state;
        
};

#endif