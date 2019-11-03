
class encoder {
    public:
        encoder(int A, int B);
        void resetTicks();
        int get_ticks();

        void pin_change_a();
        void pin_change_b();

    private:
        int pin_A;
        int pin_B;
        int ticks;
        bool A_state;
        bool B_state;
};