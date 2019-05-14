float battery_voltage = 0.0;


void updateVoltage() {
  battery_voltage = ((float)analogRead(VOLTAGE_SENSE_PIN)/4095.0)*((PULLUP_RESISTOR+PULLDOWN_RESISTOR) / PULLDOWN_RESISTOR);
}



