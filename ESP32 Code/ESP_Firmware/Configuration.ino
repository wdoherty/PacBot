//#define VALIDATE

//Drive Config
#define PCA_I2C_ADDR 0x40
#define MOTOR_PWM_DEADBAND 5

//!! CHANNEL ON THE PCA IC - NOT ESP32!!
#define M0_IN1 -1
#define M0_IN2 -1

#define M1_IN1 -1
#define M1_IN2 -1

#define M2_IN1 -1
#define M2_IN2 -1

#define M3_IN1 -1
#define M3_IN2 -1

bool reverseMotor[4] = { false, false, false, false };




//Encoders Config
#define AUTOSTART_ENCODERS 1

//pins
#define interrupt_M0A -1
#define interrupt_M0B -1

#define interrupt_M1A -1
#define interrupt_M1B -1

#define interrupt_M2A -1
#define interrupt_M2B -1

#define interrupt_M3A -1
#define interrupt_M3B -1


//MPU9250 Config
#define MPU9250_ADDR 0x68



//Robot Misc Config
#define VOLTAGE_SENSE_PIN -1
#define PULLUP_RESISTOR 300000
#define PULLDOWN_RESISTOR 100000

#define CLEAR_BUFFER_PIN -1

//Serial Communication Config

#define MSG_TIMEOUT 250 //ms
#define START_BYTE 0x38 //arbitrary

#define COMMAND_1 0x12
#define COMMAND_2 0x25
#define COMMAND_3 0x27
#define COMMAND_4 0x31




//VL6180X Config
#define SENSOR_BUFFER_SIZE 5
#define RANGE_UPDATE_PERIOD 50  //ms
#define MAX_CONVERGENCE_TIME 30 //ms
#define AUTOSTART_VL6180X 1     //1 - true; 0 - false
#define SENSOR_SCALING 1        //Sensor range scale (1, 2, or 3)

//SENSOR CALIBRATION
uint8_t sensor_offset[4] =        { 0,    0,    0,    0 };
float sensor_scaling_factor[4] =  { 1.0,  1.0,  1.0,  1.0 };

//PINS
int sensor_INTERRUPT[4] = { -1, -1, -1, -1 };
int sensor_SHUTDOWN[4] = { -1, -1, -1, -1 };

//I2C ADDRESSES
const uint8_t sensor_Address[4] = { 0x30, 0x31, 0x32, 0x33 };
