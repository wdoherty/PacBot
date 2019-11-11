#ifndef HELPERS_H

#define min(a,b)                        ( (a) < (b) ? (a) : (b) )
#define max(a,b)                        ( (a) > (b) ? (a) : (b) )
#define constrain(x, minimum, maximum)  ( min( max(x, minimum), maximum ) )
#define abs(x)                          ( (x) > 0 ? (x) : -1*(x) )


typedef struct PID_settings_t {
    double kp;
    double ki;
    double kd;
} PID_settings;

#endif