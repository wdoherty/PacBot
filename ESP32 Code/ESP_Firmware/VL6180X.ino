/*
MUST CALL setup_VL6180X to initialize sensors; 
IF NOT AUTOSTART INTERRUPTS - MUST CALL start_VL6180X_Interrupts before data will be updated

MUST SET PIN ARRAYS BELOW

MUST SET I2C ADDRESSES BELOW

MUST CALL update_VL6180X_Dists to update distances in loop() -> may add to a timer interrupt in the future

*/
//DATA
uint16_t VL6180X_Distances[4] = { -1, -1, -1, -1 };

uint16_t rawData[4][SENSOR_BUFFER_SIZE];
int lastIndex[4] = { 0, 0, 0, 0 };

volatile bool sensor_Ready[4] = { false, false, false, false };

VL6180X sensors[4];

void IRAM_ATTR sensor_0_Ready() {
  sensor_Ready[0] = true;
}
void IRAM_ATTR sensor_1_Ready() {
  sensor_Ready[1] = true;
}
void IRAM_ATTR sensor_2_Ready() {
  sensor_Ready[2] = true;
}
void IRAM_ATTR sensor_3_Ready() {
  sensor_Ready[3] = true;
}

void setup_VL6180X() {  
  for (int i = 0; i < 4; i++) {
    pinMode(sensor_SHUTDOWN[i], OUTPUT);
    pinMode(sensor_INTERRUPT[i], INPUT);

    for (int j = 0; j < SENSOR_BUFFER_SIZE; j++) { rawData[i][j] = 0; }
    
    digitalWrite(sensor_SHUTDOWN[i], LOW);
  }
  
  for (int index = 0; index < 4; index++) {

    digitalWrite(sensor_SHUTDOWN[index], HIGH);
    
    VL6180X& sensor = sensors[index];
    sensor.init();
    sensor.configureDefault();
    sensor.setAddress(sensor_Address[index]);
    sensor.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, MAX_CONVERGENCE_TIME);

    sensor.setTimeout(300);
    sensor.stopContinuous();
    delay(300);
    
    sensor.writeReg(VL6180X::SYSTEM__MODE_GPIO1, 0x10);
    sensor.writeReg(VL6180X::SYSTEM__INTERRUPT_CLEAR, 0x03);

    sensor.startRangeContinuous(RANGE_UPDATE_PERIOD);
  }

  if (AUTOSTART_VL6180X) start_VL6180X_Interrupts();
}

void start_VL6180X_Interrupts() {
  attachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[0]), sensor_0_Ready, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[1]), sensor_1_Ready, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[2]), sensor_2_Ready, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[3]), sensor_3_Ready, FALLING);
}

void stop_VL6180X_Interrupts() {
  detachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[0]));
  detachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[1]));
  detachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[2]));
  detachInterrupt(digitalPinToInterrupt(sensor_INTERRUPT[3]));
}

uint16_t read_Sensor_Range(int index) {
  VL6180X& sensor = sensors[index];
  
  uint8_t range = sensor.readReg(VL6180X::RESULT__RANGE_VAL);
  sensor.writeReg(VL6180X::SYSTEM__INTERRUPT_CLEAR, 0x01);

  return (range * (uint16_t)sensor.getScaling() * sensor_scaling_factor[index]) + sensor_offset[index];
}


void update_VL6180X_Dists() {
  for (int index = 0; index < 4; index++) {
    if (sensor_Ready[index]) {
      sensor_Ready[index] = false;
      rawData[index][lastIndex[index]] = read_Sensor_Range(index);
      lastIndex[index] = (lastIndex[index]+1) % SENSOR_BUFFER_SIZE;

      float sum = 0.0;
      for (int i = 0; i < SENSOR_BUFFER_SIZE; i++) sum += rawData[index][i];
      
      VL6180X_Distances[index] = sum / (float)SENSOR_BUFFER_SIZE;
    }
  }
}





