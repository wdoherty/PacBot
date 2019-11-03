#include "Encoder.h"

encoder::encoder(int A, int B) {
    pin_A = A;
    pin_B = B;
    ticks = 0;
}

void encoder::resetTicks() {
    ticks = 0;
}

int encoder::get_ticks() {

}

void encoder::pin_change_a() {

}

void encoder::pin_change_b() {

}