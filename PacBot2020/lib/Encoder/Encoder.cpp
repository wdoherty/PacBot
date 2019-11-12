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
    unsigned long start_time = ESP.getCycleCount();
    A_state = !A_state;
    if(A_state == B_state) {
        ticks++;
        return;
    } else {
        ticks--;
    }

    //DO LOCK
    portENTER_CRITICAL_ISR(&tick_mux);
    tick_time[tick_hist_idx] = start_time;
    tick_pos[(tick_hist_idx++ % NUM_TICK_TIMES)] = ticks;
    portEXIT_CRITICAL_ISR(&tick_mux);
    //RELEASE LOCK
}

void Encoder::pin_change_b() {
    unsigned long start_time = ESP.getCycleCount();
    B_state = !B_state;
    if(B_state == A_state) {
        ticks++;
        return;
    } else {
        ticks--;
    }

    //DO LOCK
    portENTER_CRITICAL_ISR(&tick_mux);
    tick_time[tick_hist_idx] = start_time;
    tick_pos[(tick_hist_idx++ % NUM_TICK_TIMES)] = ticks;
    portEXIT_CRITICAL_ISR(&tick_mux);
    //RELEASE LOCK
}

double Encoder::get_velocity() {
    double velocity = 0.0;
    double sum_instant_vel = 0.0;

    //DO LOCK
    portENTER_CRITICAL(&tick_mux);
    for (int i = 0; i < NUM_TICK_TIMES; i++) {
        sum_instant_vel += (tick_pos[(tick_hist_idx+1+i)%NUM_TICK_TIMES] - tick_pos[(tick_hist_idx+i)%NUM_TICK_TIMES]) / (tick_time[(tick_hist_idx+1+i)%NUM_TICK_TIMES] - tick_time[(tick_hist_idx+i)%NUM_TICK_TIMES]);
    }
    portEXIT_CRITICAL(&tick_mux);
    //RELEASE LOCK

    velocity = sum_instant_vel / (double)NUM_TICK_TIMES;
    return velocity;
}
