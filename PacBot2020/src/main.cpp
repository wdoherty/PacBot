#include <Arduino.h>

#include "drive_helpers.h"

Drive *main_drives[4];

void setup() {
  Serial.begin(1000000);
  setup_drive_system(main_drives);
  delay(100);

  //server = new Pacbot_Server("pacbot", "irobotics", main_drives);
  
  //set_CL_velocity(2, -60);
  //set_CL_velocity(4, 60);
  //set_CL_velocity(3, 60);
  //Drive::start();
}

void loop() {
  delay(10);
}
