#include "TOF.h"


VL6180X_Envelope::VL6180X_Envelope(int shutdown, int interrupt, int i2cAddr, float scalingDist, int offsetDist, int rangeMult) {
    ShutdownPin = shutdown;
    InterruptPin = interrupt;
    i2cAddress = i2cAddr;
    scalingFactor = scalingDist;
    offset = offsetDist;
    rangeMultiplier = rangeMult;

    pinMode(ShutdownPin, OUTPUT);
    pinMode(InterruptPin, INPUT);
}

void VL6180X_Envelope::init() {
    sensor.init();
    sensor.configureDefault();
    sensor.setAddress(i2cAddress);

    sensor.setScaling(rangeMultiplier);

    sensor.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, MAX_CONVERGENCE_TIME);

    sensor.setTimeout(300);
    sensor.stopContinuous();
    delay(300);

    sensor.writeReg(VL6180X::SYSTEM__MODE_GPIO1, 0x10);
    sensor.writeReg(VL6180X::SYSTEM__INTERRUPT_CLEAR, 0x03);

    sensor.startRangeContinuous(RANGE_UPDATE_PERIOD);
}
uint16_t VL6180X_Envelope::readSensorRange() {
    uint8_t range = sensor.readReg(VL6180X::RESULT__RANGE_VAL);
    sensor.writeReg(VL6180X::SYSTEM__INTERRUPT_CLEAR, 0x01);

    return (range * (uint16_t)sensor.getScaling() * scalingFactor) + offset;
}


VL6180X_Group::VL6180X_Group(VL6180X_Envelope* Sensors) {
    for (int i  = 0; i < 4; i++) {
        sensors = Sensors;
        sensors[i].disableSensor();
    }

    for (int i  = 0; i < 4; i++) {
        sensors[i].enableSensor();
        sensors[i].init();
    }
}

void VL6180X_Group::startInterrupts() {
    attachInterrupt(digitalPinToInterrupt(sensors[0].InterruptPin), sensor0Ready, FALLING);
    attachInterrupt(digitalPinToInterrupt(sensors[1].InterruptPin), sensor1Ready, FALLING);
    attachInterrupt(digitalPinToInterrupt(sensors[2].InterruptPin), sensor2Ready, FALLING);
    attachInterrupt(digitalPinToInterrupt(sensors[3].InterruptPin), sensor3Ready, FALLING);
}

void VL6180X_Group::endInterrupts() {
    detachInterrupt(digitalPinToInterrupt(sensors[0].InterruptPin));
    detachInterrupt(digitalPinToInterrupt(sensors[1].InterruptPin));
    detachInterrupt(digitalPinToInterrupt(sensors[2].InterruptPin));
    detachInterrupt(digitalPinToInterrupt(sensors[3].InterruptPin));
}

void VL6180X_Group::updateDistances() {
    for (int i = 0; i < 4; i++) {
        if (sensors[i].ready) {
            portENTER_CRITICAL(&sensors[i].sensorMUX);
            sensors[i].ready = false;
            portEXIT_CRITICAL(&sensors[i].sensorMUX);

            uint16_t dist = sensors[i].readSensorRange();

            Distances[i] = NEW_DATA_WEIGHT*dist + (1-NEW_DATA_WEIGHT)*previousRawDists[i];
            previousRawDists[i] = dist;
        }
    }
}