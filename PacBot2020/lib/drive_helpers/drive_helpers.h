
#ifndef DRIVE_HELPERS_H
#define DRIVE_HELPERS_H

#include "../../include/pins.h"

#include "../Drive/Drive.h"
#include "../Encoder/Encoder.h"
#include "../Motor/Motor.h"


// Defaults found by tuning motor 1 at 100RPM with no friction load
#define DEFAULT_VEL_CONTROLLER_KP   0.5     //0.225
#define DEFAULT_VEL_CONTROLLER_KI   0.05
#define DEFAULT_VEL_CONTROLLER_KD   0.0

#define WEIGHT_FACTOR_ST            2.0
#define WEIGHT_FACTOR_DY            1.0

#define DEFAULT_FRIC_COMP_ST_P      (35.0*WEIGHT_FACTOR_ST)
#define DEFAULT_FRIC_COMP_ST_N      (35.0*WEIGHT_FACTOR_ST)
#define DEFAULT_FRIC_COMP_DY_P      (0.005*WEIGHT_FACTOR_DY)
#define DEFAULT_FRIC_COMP_DY_N      (0.005*WEIGHT_FACTOR_DY)

#define LOOP_PERIOD_MS              10

/* bytes for each velocity controller's stack */
#define VEL_CONTROLLER_STACK_DEPTH  8192
#define PCA_DRIVER_STACK_DEPTH      4096

void setup_drive_system(Drive *maindrives[4]);
void set_CL_velocity(int motorNum, int speed);

void pcaDriver( void * parameter);

void IRAM_ATTR enc1a_change();
void IRAM_ATTR enc1b_change();
void drive_loop_1( void * parameter);

void IRAM_ATTR enc2a_change();
void IRAM_ATTR enc2b_change();
void drive_loop_2( void * parameter);

void IRAM_ATTR enc3a_change();
void IRAM_ATTR enc3b_change();
void drive_loop_3( void * parameter);

void IRAM_ATTR enc4a_change();
void IRAM_ATTR enc4b_change();
void drive_loop_4( void * parameter);

#endif
