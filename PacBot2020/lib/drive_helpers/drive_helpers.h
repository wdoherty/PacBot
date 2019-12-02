
#ifndef DRIVE_HELPERS_H
#define DRIVE_HELPERS_H

#include "../../include/pins.h"

#include "../Drive/Drive.h"
#include "../Encoder/Encoder.h"
#include "../Motor/Motor.h"

#define LOOP_PERIOD_MS              4

/* bytes for each velocity controller's stack */
#define VEL_CONTROLLER_STACK_DEPTH  4096

void setup_drive_system(Drive* (*maindrives)[4]);
void set_CL_velocity(int motorNum, int speed);

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
