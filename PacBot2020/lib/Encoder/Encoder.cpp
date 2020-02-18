#include "Encoder.h"

#define STEPS_PER_MINUTE        (60000 / TICK_STEP_SIZE_MS)
#define TICKS_PER_ROTATION      225
#define get_time_step()         ( millis() / (int)TICK_STEP_SIZE_MS )
#define TICK_PER_STEP_TO_RPM(x) ( (x) * STEPS_PER_MINUTE / TICKS_PER_ROTATION )


Encoder::Encoder(int A, int B, int reversed) {
    pin_A = A;
    pin_B = B;
    _rev = reversed;
    pinMode(pin_A, INPUT);
    pinMode(pin_B, INPUT);
    A_state = digitalRead(pin_A);
    B_state = digitalRead(pin_B);
    ticks = 0;
}

void Encoder::resetTicks() {
    ticks = 0;
}

long Encoder::get_ticks() {
    //Serial.printf("Y:%ld\n", ticks);
    if (_rev) return -ticks;
    return ticks;
}

void IRAM_ATTR Encoder::pin_change_a() {
    A_state = (A_state == 0) ? 1 : 0;
    if ( A_state != B_state ) {
        ticks++;
    } else {
        ticks--;
    }

    //DO LOCK
    portENTER_CRITICAL_ISR(&tick_mux);
    int time_step = get_time_step();
    last_hist_idx = get_time_step_index(time_step);
    history[last_hist_idx].tick_pos = ticks;
    history[last_hist_idx].time = time_step;
    if (last_hist_idx == 0) velocity_ready = true;
    portEXIT_CRITICAL_ISR(&tick_mux);
    //RELEASE LOCK
}

void IRAM_ATTR Encoder::pin_change_b() {
    B_state = (B_state == 0) ? 1 : 0;
}

double Encoder::get_velocity() {
    if (!velocity_ready) {
        //printf("ERR\n");
        return 0.0;
    }

    //DO LOCK
    portENTER_CRITICAL(&tick_mux);
    double vel_sum = 0.0;
    int vel_count = 0;

    for (int i = 0; i < NUM_STEPS_TO_AVERAGE; i++) {
        tick_hist_t end = history[(last_hist_idx - i + NUM_TICK_STEPS) % NUM_TICK_STEPS];
        int end_time = end.time;
        if (get_time_step() > end_time+NUM_STEPS_TO_AVERAGE) break;

        int j = 1;
        for (; j < NUM_STEPS_TO_AVERAGE - i - 1; j++) {
            if (end_time - history[(last_hist_idx - i - j + NUM_TICK_STEPS) % NUM_TICK_STEPS].time == j) break;
        }

        if (j == NUM_STEPS_TO_AVERAGE - i - 1) break;

        tick_hist_t start = history[(last_hist_idx - i - j + NUM_TICK_STEPS) % NUM_TICK_STEPS];
        vel_sum += (double)(end.tick_pos - start.tick_pos); /* velocity in terms of ticks per time step */
        //Serial.printf("D:%ld\n",(end.tick_pos - start.tick_pos) );

        vel_count += j;
        i += (j-1);
    }
    portEXIT_CRITICAL(&tick_mux);
    //RELEASE LOCK

    //Serial.printf("S:%f\tC:%d\n",vel_sum, vel_count);

    double velocity = (vel_count == 0) ? 0.0 : vel_sum / (double)vel_count;
    if (_rev) velocity *= -1;
    //printf("%f\n\n\n", velocity);
    return TICK_PER_STEP_TO_RPM(velocity);
}

int IRAM_ATTR Encoder::get_time_step_index(int time_step) {
    int delta_t = time_step - history[last_hist_idx].time;
    return (last_hist_idx + delta_t) % NUM_TICK_STEPS;
}