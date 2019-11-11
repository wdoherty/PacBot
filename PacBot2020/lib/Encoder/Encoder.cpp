#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(int A, int B) {
    pin_A = A;
    pin_B = B;
    A_state = digitalRead(pin_A);
    B_state = digitalRead(pin_B);
    ticks = 0;
}

void Encoder::resetTicks() {
    ticks = 0;
}

int Encoder::get_ticks() {
    return ticks;
}

void Encoder::pin_change_a() {
    tick_time[tick_hist_idx] = ESP.getCycleCount();
    A_state = !A_state;
    if(A_state == B_state) {
        ticks++;
        return;
    } else {
        ticks--;
    }
    tick_pos[(tick_hist_idx++ % NUM_TICK_TIMES)] = ticks;
}

void Encoder::pin_change_b() {
    tick_time[tick_hist_idx] = ESP.getCycleCount();
    B_state = !B_state;
    if(B_state == A_state) {
        ticks++;
        return;
    } else {
        ticks--;
    }
    tick_pos[(tick_hist_idx++ % NUM_TICK_TIMES)] = ticks;
}

double Encoder::get_velocity() {
    double velocity = 0.0;
#if (ESTIMATOR == NO_FILTERING_VELOCITY_ESTIMATOR)

#endif
#if (ESTIMATOR == AVERAGING_VELOCITY_ESTIMATOR)
    double sum_instant_vel = 0.0;

    for (int i = 0; i < NUM_TICK_TIMES; i++) {
        sum_instant_vel += (tick_pos[(tick_hist_idx+1+i)%NUM_TICK_TIMES] - tick_pos[(tick_hist_idx+i)%NUM_TICK_TIMES]) / (tick_time[(tick_hist_idx+1+i)%NUM_TICK_TIMES] - tick_time[(tick_hist_idx+i)%NUM_TICK_TIMES]);
    }
    
    velocity = sum_instant_vel / (double)NUM_TICK_TIMES;

#endif 
#if (ESTIMATOR == FUTURE_FANCY_VELOCITY_ESTIMATOR)

#endif
return velocity;
}
