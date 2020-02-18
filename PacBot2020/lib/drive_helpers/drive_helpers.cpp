#include "drive_helpers.h"

Adafruit_PWMServoDriver *pwm;

Encoder *enc1, *enc2, *enc3, *enc4;
Motor *mot1, *mot2, *mot3, *mot4;
friction_vals_t fric_1, fric_2, fric_3, fric_4;
pid_values_t pid_1, pid_2, pid_3, pid_4;

Drive *drive1, *drive2, *drive3, *drive4;
Drive *Drives[4] = { drive1, drive2, drive3, drive4 };

QueueHandle_t pca_queue;

void setup_drive_system(Drive *maindrives[4]) {
  pwm = new Adafruit_PWMServoDriver(0x48);
  pwm->begin();
  pwm->setPWMFreq(500);  // This is the maximum PWM frequency

  pca_queue = xQueueCreate(10, sizeof(motor_val_t));

  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);
  pinMode(ENC2A, INPUT);
  pinMode(ENC2B, INPUT);
  pinMode(ENC3A, INPUT);
  pinMode(ENC3B, INPUT);
  pinMode(ENC4A, INPUT);
  pinMode(ENC4B, INPUT);

  enc1 = new Encoder(ENC1A, ENC1B, 0);
  enc2 = new Encoder(ENC2A, ENC2B, 0);
  enc3 = new Encoder(ENC3A, ENC3B, 0);
  enc4 = new Encoder(ENC4A, ENC4B, 0);

  mot1 = new Motor(PCA_1A, PCA_1B, pwm, 0, &pca_queue);
  mot2 = new Motor(PCA_2A, PCA_2B, pwm, 0, &pca_queue);
  mot3 = new Motor(PCA_3A, PCA_3B, pwm, 0, &pca_queue);
  mot4 = new Motor(PCA_4A, PCA_4B, pwm, 0, &pca_queue);

  // FRICTION COMPENSATION VALUES (ALL SHOULD ALWAYS BE POSITIVE)
  fric_1.st_n = DEFAULT_FRIC_COMP_ST_N;
  fric_1.st_p = DEFAULT_FRIC_COMP_ST_P;
  fric_1.dy_n = DEFAULT_FRIC_COMP_DY_N;
  fric_1.dy_p = DEFAULT_FRIC_COMP_DY_P;
  
  fric_2.st_n = DEFAULT_FRIC_COMP_ST_N;
  fric_2.st_p = DEFAULT_FRIC_COMP_ST_P;
  fric_2.dy_n = DEFAULT_FRIC_COMP_DY_N;
  fric_2.dy_p = DEFAULT_FRIC_COMP_DY_P;
    
  fric_3.st_n = DEFAULT_FRIC_COMP_ST_N;
  fric_3.st_p = DEFAULT_FRIC_COMP_ST_P;
  fric_3.dy_n = DEFAULT_FRIC_COMP_DY_N;
  fric_3.dy_p = DEFAULT_FRIC_COMP_DY_P;
   
  fric_4.st_n = DEFAULT_FRIC_COMP_ST_N;
  fric_4.st_p = DEFAULT_FRIC_COMP_ST_P;
  fric_4.dy_n = DEFAULT_FRIC_COMP_DY_N;
  fric_4.dy_p = DEFAULT_FRIC_COMP_DY_P;


  // PID VALUES FOR VELOCITY CONTROLLER 
  pid_1.kp = DEFAULT_VEL_CONTROLLER_KP;
  pid_1.ki = DEFAULT_VEL_CONTROLLER_KI;
  pid_1.kd = DEFAULT_VEL_CONTROLLER_KD; // LEAVE THIS 0 MOST LIKELY

  pid_2.kp = DEFAULT_VEL_CONTROLLER_KP;
  pid_2.ki = DEFAULT_VEL_CONTROLLER_KI;
  pid_2.kd = DEFAULT_VEL_CONTROLLER_KD;
  
  pid_3.kp = DEFAULT_VEL_CONTROLLER_KP;
  pid_3.ki = DEFAULT_VEL_CONTROLLER_KI;
  pid_3.kd = DEFAULT_VEL_CONTROLLER_KD;
  
  pid_4.kp = DEFAULT_VEL_CONTROLLER_KP;
  pid_4.ki = DEFAULT_VEL_CONTROLLER_KI;
  pid_4.kd = DEFAULT_VEL_CONTROLLER_KD;

  drive1 = new Drive(enc1, mot1, pid_1, fric_1, 1);
  drive2 = new Drive(enc2, mot2, pid_2, fric_2, 2);
  drive3 = new Drive(enc3, mot3, pid_3, fric_3, 3);
  drive4 = new Drive(enc4, mot4, pid_4, fric_4, 4);

  maindrives[0] = drive1;
  maindrives[1] = drive2;
  maindrives[2] = drive3;
  maindrives[3] = drive4;

  drive1->set_speed(0);
  drive2->set_speed(0);
  drive3->set_speed(0);
  drive4->set_speed(0);

  attachInterrupt(ENC1A, enc1a_change, CHANGE);
  attachInterrupt(ENC1B, enc1b_change, CHANGE);
  attachInterrupt(ENC2A, enc2a_change, CHANGE);
  attachInterrupt(ENC2B, enc2b_change, CHANGE);
  attachInterrupt(ENC3A, enc3a_change, CHANGE);
  attachInterrupt(ENC3B, enc3b_change, CHANGE);
  attachInterrupt(ENC4A, enc4a_change, CHANGE);
  attachInterrupt(ENC4B, enc4b_change, CHANGE);

  //xTaskCreatePinnedToCore(drive_loop_1, "Vel_Controller_1", VEL_CONTROLLER_STACK_DEPTH, NULL, 10, NULL, 1);
  xTaskCreatePinnedToCore(drive_loop_2, "Vel_Controller_2", VEL_CONTROLLER_STACK_DEPTH, NULL, 10, NULL, 1);
  //xTaskCreatePinnedToCore(drive_loop_3, "Vel_Controller_3", VEL_CONTROLLER_STACK_DEPTH, NULL, 10, NULL, 1);
  xTaskCreatePinnedToCore(drive_loop_4, "Vel_Controller_4", VEL_CONTROLLER_STACK_DEPTH, NULL, 10, NULL, 1);

  xTaskCreatePinnedToCore(pcaDriver, "PCA_DRIVER", PCA_DRIVER_STACK_DEPTH, NULL, 10, NULL, 1);

}

void pcaDriver( void * parameter) {
  motor_val_t voltage;

  for ( ; ; ) {
        // continually check if there are status' to be shown, and read them off the queue and display them if any exist
        if (xQueueReceive(pca_queue, &voltage, 0) == pdTRUE) {
          pwm->setPWM(voltage.pin_a, voltage.pin_a_val);
          pwm->setPWM(voltage.pin_b, voltage.pin_b_val);
          Serial.println("UPDATED PCA\n");
        }

        // waiting after each check based on the software configs
        vTaskDelay(10.0 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


/*
*   set_CL_velocity(int motorNum, int speed)
*   INPUTS: drive number of [1,2,3,4] and speed in RPM
*   OUTPUTS: None
*   SIDE EFFECTS: Adjusts Setpoint for specified CL Velocity Controller
*/
void set_CL_velocity(int motorNum, int speed) {
  if (motorNum-1 < 0 || motorNum-1 > 3) return;
  // Array doesn't work for some reason (throws exception)
  switch (motorNum) {
    case(1):
      drive1->set_speed(speed);
      break;
    case(2):
      drive2->set_speed(speed);
      break;
    case(3):
      drive3->set_speed(speed);
      break;
    case(4):
      drive4->set_speed(speed);
      break;
    default:
      break;
  }
}


// DRIVE 1 HELPERS
void IRAM_ATTR enc1a_change() {
  enc1->pin_change_a();
}
void IRAM_ATTR enc1b_change() {
  enc1->pin_change_b();
}

void drive_loop_1( void * parameter) {
  drive1->start();
  while (1) {
    vTaskDelay(LOOP_PERIOD_MS / portTICK_PERIOD_MS);
    drive1->control_loop();
    //Serial.println("LOOP 1");
  }
}


// DRIVE 2 HELPERS
void IRAM_ATTR enc2a_change() {
  enc2->pin_change_a();
}
void IRAM_ATTR enc2b_change() {
  enc2->pin_change_b();
}

void drive_loop_2( void * parameter) {
  drive2->start();
  uint32_t idx = 0;
  while (1) {
    idx++;
    vTaskDelay(LOOP_PERIOD_MS / portTICK_PERIOD_MS);
    drive2->control_loop();
    //Serial.println("LOOP 2");
    if (idx % 250 == 0) Serial.printf("SIZE[2]: %u", uxTaskGetStackHighWaterMark(NULL));
  }
}

// DRIVE 3 HELPERS
void IRAM_ATTR enc3a_change() {
  enc3->pin_change_a();
}
void IRAM_ATTR enc3b_change() {
  enc3->pin_change_b();
}

void drive_loop_3( void * parameter) {
  drive3->start();
  while (1) {
    vTaskDelay(LOOP_PERIOD_MS / portTICK_PERIOD_MS);
    drive3->control_loop();
    //Serial.println("LOOP 3");
  }
}


// DRIVE 4 HELPERS
void IRAM_ATTR enc4a_change() {
  enc4->pin_change_a();
}
void IRAM_ATTR enc4b_change() {
  enc4->pin_change_b();
}

void drive_loop_4( void * parameter) {
  drive4->start();
  while (1) {
    vTaskDelay(LOOP_PERIOD_MS / portTICK_PERIOD_MS);
    drive4->control_loop();
    //Serial.println("LOOP 4");
  }
}
