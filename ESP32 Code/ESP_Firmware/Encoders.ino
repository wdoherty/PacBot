volatile long ticks[4] = { 0, 0, 0, 0 };

volatile byte last_GPIO_M1 = -1;
volatile byte last_GPIO_M2 = -1;
volatile byte last_GPIO_M3 = -1;
volatile byte last_GPIO_M4 = -1;

volatile byte M0A_High = 0;
volatile byte M0B_High = 0;

volatile byte M1A_High = 0;
volatile byte M1B_High = 0;

volatile byte M2A_High = 0;
volatile byte M2B_High = 0;

volatile byte M3A_High = 0;
volatile byte M3B_High = 0;

void IRAM_ATTR M0A_Change() {
  M0A_High = !M0A_High;
  if (M0B_High && M0A_High) ticks[0]++;
  last_GPIO_M1 = 'a';
}

void IRAM_ATTR M0B_Change() {
  M0B_High = !M0B_High;
  if (M0A_High && M0B_High) ticks[0]--;
  last_GPIO_M1 = 'b';
}

void IRAM_ATTR M1A_Change() {
  M1A_High = !M1A_High;
  if (M1B_High && M1A_High) ticks[1]++;
  last_GPIO_M2 = 'a';
}

void IRAM_ATTR M1B_Change() {
  M1B_High = !M1B_High;
  if (M1A_High && M1B_High) ticks[1]--;
  last_GPIO_M2 = 'b';
}

void IRAM_ATTR M2A_Change() {
  M2A_High = !M2A_High;
  if (M2B_High && M2A_High) ticks[2]++;
  last_GPIO_M3 = 'a';
}

void IRAM_ATTR M2B_Change() {
  M2B_High = !M2B_High;
  if (M2A_High && M2B_High) ticks[2]--;
  last_GPIO_M3 = 'b';
}

void IRAM_ATTR M3A_Change() {
  M3A_High = !M3A_High;
  if (M3B_High && M3A_High) ticks[3]++;
  last_GPIO_M4 = 'a';
}

void IRAM_ATTR M3B_Change() {
  M3B_High = !M3B_High;
  if (M3A_High && M3B_High) ticks[3]--;
  last_GPIO_M4 = 'b';
}


void zero_Encoders() {
  for (int i = 0; i < 4; i++) ticks[i] = 0;
}

void setup_Encoders() {
  pinMode(interrupt_M0A, INPUT);
  pinMode(interrupt_M0A, INPUT);
  
  pinMode(interrupt_M1A, INPUT);
  pinMode(interrupt_M1B, INPUT);
  
  pinMode(interrupt_M2A, INPUT);
  pinMode(interrupt_M2B, INPUT);
  
  pinMode(interrupt_M3A, INPUT);
  pinMode(interrupt_M3B, INPUT);

  M0A_High = digitalRead(interrupt_M0A);
  M0B_High = digitalRead(interrupt_M0B); 

  M0A_High = digitalRead(interrupt_M0A);
  M0B_High = digitalRead(interrupt_M0B); 

  M0A_High = digitalRead(interrupt_M0A);
  M0B_High = digitalRead(interrupt_M0B); 

  M0A_High = digitalRead(interrupt_M0A);
  M0B_High = digitalRead(interrupt_M0B);  

  if (AUTOSTART_ENCODERS) {
    start_Encoder_Interrupts();
  }
}

void start_Encoder_Interrupts() {
  attachInterrupt(digitalPinToInterrupt(interrupt_M0A), M0A_Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt_M0B), M0B_Change, CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(interrupt_M1A), M1A_Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt_M1B), M1B_Change, CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(interrupt_M2A), M2A_Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt_M2B), M2B_Change, CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(interrupt_M3A), M3A_Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt_M3B), M3B_Change, CHANGE);
}

void stop_Encoder_Interrupts() {
  detachInterrupt(digitalPinToInterrupt(interrupt_M0A));
  detachInterrupt(digitalPinToInterrupt(interrupt_M0A));
  
  detachInterrupt(digitalPinToInterrupt(interrupt_M1A));
  detachInterrupt(digitalPinToInterrupt(interrupt_M1B));
  
  detachInterrupt(digitalPinToInterrupt(interrupt_M2A));
  detachInterrupt(digitalPinToInterrupt(interrupt_M2A));
  
  detachInterrupt(digitalPinToInterrupt(interrupt_M3A));
  detachInterrupt(digitalPinToInterrupt(interrupt_M3B));
}



