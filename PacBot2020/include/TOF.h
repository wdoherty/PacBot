#ifndef TOF_h
#define TOF_h

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef VL6180X_h
#include "VL6180X.h"
#endif

#define NEW_DATA_WEIGHT (0.4)   //MUST BE LESS THAN OR EQUAL TO 1.0
#define MAX_CONVERGENCE_TIME 30
#define RANGE_UPDATE_PERIOD 50




class VL6180X_Envelope {
    public:
        void enableSensor() { digitalWrite(ShutdownPin, HIGH); }
        void disableSensor() { digitalWrite(ShutdownPin, LOW); }

        void init();
                
        uint16_t readSensorRange();

        VL6180X_Envelope(int shutdown, int interrupt, int i2cAddr, float scaling, int offset, int rangeMult);

        int ShutdownPin;
        int InterruptPin;
        int i2cAddress;
        float scalingFactor;
        int offset;
        int rangeMultiplier;

        portMUX_TYPE sensorMUX = portMUX_INITIALIZER_UNLOCKED;   

        VL6180X sensor;
        volatile bool ready = false;
};


//need to call startInterrupts when everything is initialized
class VL6180X_Group {
    public:
        uint16_t Distances[4] = { 0 };

        VL6180X_Group(VL6180X_Envelope* newSensors);
        void startInterrupts();
        void endInterrupts();

        void updateDistances();

        static void IRAM_ATTR sensor0Ready() { sensors[0].ready = true; }
        static void IRAM_ATTR sensor1Ready() { sensors[1].ready = true; }
        static void IRAM_ATTR sensor2Ready() { sensors[2].ready = true; }
        static void IRAM_ATTR sensor3Ready() { sensors[3].ready = true; }
        static VL6180X_Envelope* sensors;
        uint32_t previousRawDists[4] = { 0 };
};

#endif /* _TOF_H_ */