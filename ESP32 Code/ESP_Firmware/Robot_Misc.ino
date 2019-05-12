float battery_voltage = 0.0;


void updateVoltage() {
  battery_voltage = analogRead(VOLTAGE_SENSE_PIN)*((PULLUP_RESISTOR+PULLDOWN_RESISTOR) / PULLDOWN_RESISTOR);
}



