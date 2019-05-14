//include function prototypes for everything
#include "ESP_Firmware.h"

#include <Wire.h>

//START VL6180X Dependencies
#include <VL6180X.h>
//END VL6180X Dependencies

//START Drive Dependencies
#include <Adafruit_PWMServoDriver.h>
//END Drive Dependencies

//START IMU Dependencies
#include <MPU9250_asukiaaa.h>
//END IMU Dependencies

#define i2cClockFreq 1000000
#define SERIAL_BAUD 115200
#define CPU_FREQUENCY 80000000  //80 MHz
#define TIMER_0_HZ 1000  //1kHz
#define TIMER_1_HZ 20  //20Hz

//1000Hz Timer
hw_timer_t* timer0 = NULL;
portMUX_TYPE timer0_MUX = portMUX_INITIALIZER_UNLOCKED;
volatile bool checkSensors = false;

//20Hz Timer
hw_timer_t* timer1 = NULL;
portMUX_TYPE timer1_MUX = portMUX_INITIALIZER_UNLOCKED;
volatile bool readVoltage = false;


void setup() {
  Serial.begin(SERIAL_BAUD);
  Wire.begin();
  
  setup_Drivers();
  setup_Encoders();
  setup_VL6180X();

  timer0 = timerBegin(0, CPU_FREQUENCY/1000000, true);
  timerAttachInterrupt(timer0, &onTimer0, true);
  timerAlarmWrite(timer0, 1000000/TIMER_0_HZ, true);

  timer1 = timerBegin(1, CPU_FREQUENCY/1000000, true);
  timerAttachInterrupt(timer1, &onTimer1, true);
  timerAlarmWrite(timer1, 1000000/TIMER_1_HZ, true);

  startTimers();
}


void loop() {
  portENTER_CRITICAL(&timer0_MUX);
  if (checkSensors) update_VL6180X_Dists();
  portEXIT_CRITICAL(&timer0_MUX);




  portENTER_CRITICAL(&timer1_MUX);
  if (readVoltage) updateVoltage();
  portEXIT_CRITICAL(&timer1_MUX);
  
}


void startTimers() {
  timerAlarmEnable(timer0);
  timerAlarmEnable(timer1);
}

//1kHz
void IRAM_ATTR onTimer0() {
  portENTER_CRITICAL_ISR(&timer0_MUX);
  checkSensors = true;
  portEXIT_CRITICAL_ISR(&timer0_MUX);
}

//20Hz
void IRAM_ATTR onTimer1() {
  portENTER_CRITICAL_ISR(&timer1_MUX);
  readVoltage = true;
  portEXIT_CRITICAL_ISR(&timer1_MUX);
}
