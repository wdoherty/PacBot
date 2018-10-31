#include "SubsystemManager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// intitalizes the subsystem manager and all global objects
SubsystemManager::SubsystemManager()
{
// declares new instance of PWM driver at default I2C address
    PWM1 = new PCA9685(0x40);
    controller = new Controller(controllerArray);
}

// calls all subsystem failsafes
void SubsystemManager::failsafe()
{
    simonSays->failsafe();
    intake->failsafe();
    driveTrain->failsafe();
    foamArm->failsafe();
}

// creates a new instance of each robot subsystem
// passes a pointer to the PWM driver, motor PWM pins, and solenoid GPIO pins

void SubsystemManager::initializeSubsystems()
{
    simonSays = new SimonSays(PWM1, 6, 17, 27, 22, 23); //Arm pin 6, GPIO 17, 27, 22, 23 for pistons (Pi 11, 13, 15, 16)
    intake = new Intake(PWM1, 4, 5, 26); //Foam intake pin 4, soccer intake pin 5, digital pin GPIO 26 (Pi 37)
    driveTrain = new TankDrive(PWM1, 0, 1, 2, 3); //Left drive on pins 0 & 1, Right drive on pins 2 & 3
    foamArm = new Arm(PWM1, 7, 8, 24, 21); //foam arm on pwm 7, wheel on pwm 8, clamp piston GPIO 24, door GPIO 5 (Pi 18,29)
    soccer = new SoccerOutput(6, 13); //Soccer finger GPIO 6, Soccer door GPIO 13 (Pi 31,33)
}

// looping function
// distributes controller inputs to subsystems for handling
// returns an array of values sent back to driver station with state data
unsigned char* SubsystemManager::runRobot(unsigned char controllerIn[8])
{
    //NOTE: For the motor speeds, full reverse is a value of 1360, neutral is between 2160 and 2210, and full forward is 3010
    //These values are from testing on a talon that wasn't accepting a new calibration with output 0-4095
     controllerArray = controllerIn;
     memset(returnValues,0,sizeof(returnValues));

     // start = 1 & (controller[0] >> 6); (start)
     //
     // driveThrottleRight = controller[7]; (right trigger)
     // driveThrottleLeft = controller[6]; (left trigger)
     // driveHeading = controller[4]; (right stick X)
     //
     // SimonSaysArm = controller[2]; (left stick X)
     // SimonSays_UpperLeft = 1 & controller[1]; (D-Up - DS Button)
     // SimonSays_UpperRight = 1 & (controller[1] >> 3); (D-Right - DS Button)
     // SimonSays_LowerLeft = 1 & (controller[1] >> 2); (D-Left - DS Button)
     // SimonSays_LowerRight = 1 & (controller[1] >> 1);(D-Down - DS Button)
     //
     // doorReset = 1 & (controller[1] >> 5); (R3 - DS Button)
     //
     // FoamIntake = 1 & (controller[0] >> 5); (RB)
     // SoccerIntake = 1 & (controller[0] >> 4); (LB)
     //
     // FoamArm = controller[3]; (left stick Y)
     // RopeClamp = 1 & (controller[0] >> 2); (X)
     // Wheel = 1 & (controller[0] >> 3); (Y)
     // FoamDoor = 1 & (controller[1] >> 6); (select)
     //
     // FingerPosition = 1 & (controller[0] >> 1); (B)
     // SoccerDoor = 1 & (controller[0]); (A)

     // assigns values of XBox controller to specific functions
      driveThrottleRight = controller->RTrigger();
      driveThrottleLeft = controller->LTrigger();
      driveHeading = controller->RightStickX();

      SimonSaysArm = controller->LeftStickX();
      SimonSays_UpperLeft = controller->DPadUp();
      SimonSays_UpperRight = controller->DPadRight();
      SimonSays_LowerLeft = controller->DPadLeft();
      SimonSays_LowerRight = controller->DPadDown();

      doorReset = controller->Rstick();

      FoamIntake = controller->RB();
      SoccerIntake = controller->LB();

      FoamArm = controller->LeftStickY();
      RopeClamp = controller->X();
      Wheel = controller->Y();
      FoamDoor = controller->select();

      FingerPosition = controller->B();
      SoccerDoor = controller->A();

     // passes controller values to subsystems, sets outputs based on commands, and sends feedback to DS
     returnValues[3] += simonSays->updateSimonSays(SimonSaysArm, SimonSays_UpperLeft, SimonSays_UpperRight,
                                SimonSays_LowerLeft, SimonSays_LowerRight);
     returnValues[2] += intake->updateIntake(FoamIntake, SoccerIntake, doorReset);
     driveVals = driveTrain->updateDrive(driveThrottleRight, driveThrottleLeft, driveHeading);
     returnValues[0] = driveVals[0];
     returnValues[1] = driveVals[1];
     returnValues[2] += foamArm->updateArm(FoamArm, RopeClamp, FoamDoor, Wheel);
     returnValues[2] += soccer->updateSoccerOutput(FingerPosition, SoccerDoor);

     return returnValues;
}
