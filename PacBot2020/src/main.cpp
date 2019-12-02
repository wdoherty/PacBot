#include <Arduino.h>
#include "Pacbot_Server.h"
#include "drive_helpers.h"

Drive *main_drives[4];
Pacbot_Server *server;

void setup() {
  Serial.begin(1000000);
  setup_drive_system(&main_drives);
  for (int i = 5; i > 0; i--) {
    delay(1000);
    Serial.println(i);
  }

  server = new Pacbot_Server("pacbot", "irobotics", main_drives);

  set_CL_velocity(1, 100);
  set_CL_velocity(3, 100);
}

void loop() {
  delay(10);
}



