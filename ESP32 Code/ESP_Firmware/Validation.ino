#ifdef VALIDATE

#if (CPU_FREQUENCY/TIMER_0_HZ > 65536)
#error INVALID PRESCLAER
#endif

#if (M0_IN1 >= 16 || M0_IN1 <= -1)
#error Invalid M0_IN1 Pin
#endif

#if (M0_IN2 >= 16 || M0_IN2 <= -1)
#error Invalid M0_IN2 Pin
#endif

#if (M1_IN1 >= 16 || M1_IN1 <= -1)
#error Invalid M1_IN1 Pin
#endif

#if (M1_IN2 >= 16 || M1_IN2 <= -1)
#error Invalid M1_IN2 Pin
#endif

#if (M2_IN1 >= 16 || M2_IN1 <= -1)
#error Invalid M2_IN1 Pin
#endif

#if (M2_IN2 >= 16 || M2_IN2 <= -1)
#error Invalid M2_IN2 Pin
#endif

#if (M3_IN1 >= 16 || M3_IN1 <= -1)
#error Invalid M3_IN1 Pin
#endif

#if (M3_IN2 >= 16 || M3_IN2 <= -1)
#error Invalid M3_IN2 Pin
#endif


#if ( M0_IN1 == M0_IN2 ) || ( M0_IN1 == M1_IN1 ) || ( M0_IN1 == M1_IN2 ) || ( M0_IN1 == M2_IN1 ) || ( M0_IN1 == M2_IN2 ) || ( M0_IN1 == M3_IN1 ) || ( M0_IN1 == M3_IN2 ) || ( M0_IN2 == M1_IN1 ) || ( M0_IN2 == M1_IN2 ) || ( M0_IN2 == M2_IN1 ) || ( M0_IN2 == M2_IN2 ) || ( M0_IN2 == M3_IN1 ) || ( M0_IN2 == M3_IN2 ) || ( M1_IN1 == M1_IN2 ) || ( M1_IN1 == M2_IN1 ) || ( M1_IN1 == M2_IN2 ) || ( M1_IN1 == M3_IN1 ) || ( M1_IN1 == M3_IN2 ) || ( M1_IN2 == M2_IN1 ) || ( M1_IN2 == M2_IN2 ) || ( M1_IN2 == M3_IN1 ) || ( M1_IN2 == M3_IN2 ) || ( M2_IN1 == M2_IN2 ) || ( M2_IN1 == M3_IN1 ) || ( M2_IN1 == M3_IN2 ) || ( M2_IN2 == M3_IN1 ) || ( M2_IN2 == M3_IN2 ) || ( M3_IN1 == M3_IN2 )
#error Motor Control Channel Conflict(s)
#endif


#if (SENSOR_SCALING != 1) && (SENSOR_SCALING != 2) && (SENSOR_SCALING != 3)
#error Invalid Sensor Scaling
#endif

#endif
