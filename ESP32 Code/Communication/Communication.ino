
void sendFailedMSG(int i) {
  Serial.print("Bad");
  Serial.println(i);
  return;
}
void sendSuccessMSG() {
  Serial.println("Good");
  return;
}

void setup() {
  delay(1000);
  Serial1.begin(38400);
  Serial.begin(115200);
  Serial.println("ESP STARTING");
}

#define MSG_TIMEOUT 1000 //ms
#define START_BYTE 0x38

#define COMMAND_1 0x12
#define COMMAND_2 0x25
#define COMMAND_3 0x27
#define COMMAND_4 0x31



bool idle = true;
unsigned long startRead;
unsigned int lenRead = 256;
byte currentByte;

byte* messageData;
unsigned int messageLength;

bool newMessageReady = false;


void ParseMessage() {
  if (messageLength > 0) {
    switch(messageData[0]) {
      case(COMMAND_1):  //3 data bytes
        Serial.println("Command 1");
        if (messageLength != 4) {
          sendFailedMSG(3);
        } else {
          Serial.print("A: ");
          Serial.println(messageData[1]);
          Serial.print("B: ");
          Serial.println(messageData[2]);
          Serial.print("C: ");
          Serial.println(messageData[3]);
        }        
        break;
      case(COMMAND_2):  //3 data bytes
        Serial.println("Command 2");
        if (messageLength != 4) {
          sendFailedMSG(4);
        } else {
          Serial.print("A: ");
          Serial.println(messageData[1]);
          Serial.print("B: ");
          Serial.println(messageData[2]);
          Serial.print("C: ");
          Serial.println(messageData[3]);
          
        }        
        break;
      case(COMMAND_3):  //3 data bytes
        Serial.println("Command 3");
        if (messageLength != 4) {
          sendFailedMSG(5);
        } else {
          Serial.print("A: ");
          Serial.println(messageData[1]);
          Serial.print("B: ");
          Serial.println(messageData[2]);
          Serial.print("C: ");
          Serial.println(messageData[3]);
          
        }        
        break;
      case(COMMAND_4):  //2 data bytes
        Serial.println("Command 4");
        if (messageLength != 3) {
          sendFailedMSG(6);
        } else {
          Serial.print("A: ");
          Serial.println(messageData[1]);
          Serial.print("B: ");
          Serial.println(messageData[2]);
          
        }        
        break;
      default:
         Serial.println("Invalid command byte");
         sendFailedMSG(7);
         break;
    }
  }
  

  delete[] messageData;
  newMessageReady = false;
}



void loop() {
  if (idle) {
    if (Serial1.available() >= 2 && newMessageReady == false) {
      currentByte = Serial1.read();
      if (currentByte == START_BYTE) {
        startRead = millis();
        lenRead = (unsigned int)Serial1.read();  //length in bytes including the start byte, length byte and checksum byte
        idle = false;
        Serial.println(lenRead);
      }
    }
  } else {
    if (Serial1.available() >= lenRead-2) {  //already read 2 bytes: start byte and length byte
      idle = true;
      
      messageData = new byte[lenRead-3];
      
      byte sum = 0;
      byte checksum;
      for (int i = 0; i < lenRead-3; i++) {
        byte tmp = Serial1.read();
        messageData[i] = tmp;
        sum += tmp;
      }
      messageLength = lenRead-3;
      
      checksum = Serial1.read();
      if (sum != checksum) {
        Serial.println(sum);
        sendFailedMSG(1);
        newMessageReady = false;
      } else {
        sendSuccessMSG();
        newMessageReady = true;
      }

    } else if (millis() > startRead + MSG_TIMEOUT) {
      idle = true;
      sendFailedMSG(2);
      newMessageReady = false;
    }
  }

  if (newMessageReady) {
    ParseMessage();
  }
}

