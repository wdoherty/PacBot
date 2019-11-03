

#ifndef ENCODER_H
#define ENCODER_H

class encoder {
    public:
        encoder(int pin_A, int pin_B);
        void resetTicks();
        int get_ticks();

        void pin_change_a();
        void pin_change_b();

        int get_pin_a() { return pin_A; }
        int get_pin_b() { return pin_B; }

    private:
        int pin_A;
        int pin_B;
        int ticks;
}

#endif