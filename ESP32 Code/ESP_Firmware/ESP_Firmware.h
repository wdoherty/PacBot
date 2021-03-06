//File: Configuration.ino

//File: Drive.ino
void setup_Drivers();
void set_Motor_Speed(int index, int pwm_val);
void PCA_analogWrite(int channel, int val);

//File: Encoders.ino
void IRAM_ATTR M0A_Change();
void IRAM_ATTR M0B_Change();
void IRAM_ATTR M1A_Change();
void IRAM_ATTR M1B_Change();
void IRAM_ATTR M2A_Change();
void IRAM_ATTR M2B_Change();
void IRAM_ATTR M3A_Change();
void IRAM_ATTR M3B_Change();
void zero_Encoders();
void setup_Encoders();
void start_Encoder_Interrupts();
void stop_Encoder_Interrupts();

//File: ESP_Firmware.ino
void setup();
void loop();
void startTimers();
void IRAM_ATTR onTimer0();
void IRAM_ATTR onTimer1();

//File: Robot_Misc.ino
void updateVoltage();

//File: Validation.ino

//File: VL6180X.ino
void IRAM_ATTR sensor_0_Ready();
void IRAM_ATTR sensor_1_Ready();
void IRAM_ATTR sensor_2_Ready();
void IRAM_ATTR sensor_3_Ready();
void setup_VL6180X();
void start_VL6180X_Interrupts();
void stop_VL6180X_Interrupts();
uint16_t read_Sensor_Range(int index);
void update_VL6180X_Dists();

