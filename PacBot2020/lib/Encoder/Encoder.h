#ifndef ENCODER_H
#define ENCODER_H

#define NO_FILTERING_VELOCITY_ESTIMATOR 0
#define AVERAGING_VELOCITY_ESTIMATOR    1
#define FUTURE_FANCY_VELOCITY_ESTIMATOR 2

#define ESTIMATOR                       AVERAGING_VELOCITY_ESTIMATOR

#define NUM_TICK_TIMES  10

class Encoder {
    public:
        Encoder(int A, int B);
        void resetTicks();
        int get_ticks();

        void pin_change_a();
        void pin_change_b();

        double get_velocity();

    private:
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