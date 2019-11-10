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
    A_state = !A_state;
    if(A_state == B_state) {
        ticks++;
        return;
    } else {
        ticks--;
    }
    
}

void Encoder::pin_change_b() {
    B_state = !B_state;
    if(B_state == A_state) {
        ticks++;
        return;
    } else {
        ticks--;
    }
}