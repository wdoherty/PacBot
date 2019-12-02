#ifndef HELPERS_H
#define HELPERS_H

#define CYCLES_TO_MS(x)            ( (x) / ((double)240110.3) )

typedef struct PID_vals_t {
    double kp;
    double ki;
    double kd;
} PID_vals;

#endif