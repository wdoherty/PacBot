#ifndef TOF_h
#define TOF_h

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef VL6180X_h
#include "VL6180X.h"
#endif

#define NUM_SENSORS 4

typedef struct TOF_Specs {
    int ReadyPin;
    int InterruptPin;
    int i2cAddress;
};



class VL6180X_Group {
    public:
        uint32_t Distances[NUM_SENSORS] = { 0, 0, 0, 0 };

        VL6180X_Group(TOF_Specs* SensorSpecs);
        void startInterrupts();
        void endInterrupts();

    private:
        bool ready[NUM_SENSORS];
        uint32_t previousRawDists[NUM_SENSORS] = { 0 };




};


#endif /* _TOF_H_ */