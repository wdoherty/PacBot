//MESSAGE FORMAT:
// [MSG_START]  [MSG_LEN] [MSG_0][MSG_1]...[MSG_N]  [CHECKSUM]
//    1 BYTE      1 BYTE   -- -- N BYTES --  --  -    1 BYTE 

bool serialIdle = true;
unsigned long startRead;
unsigned int lenRead = 255;
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
          sendFailedMSG();
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
          sendFailedMSG();
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
          sendFailedMSG();
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
          sendFailedMSG();
        } else {
          Serial.print("A: ");
          Serial.println(messageData[1]);
          Serial.print("B: ");
          Serial.println(messageData[2]);
          
        }        
        break;
      default:
         Serial.println("Invalid command byte");
         sendFailedMSG();
         break;
    }
  }
  

  delete[] messageData;
  newMessageReady = false;
}


void sendFailedMSG() {
  Serial.print("Bad");
  return;
}
void sendSuccessMSG() {
  Serial.println("Good");
  return;
}


void handle_Communication() {
  if (serialIdle) {
    if (Serial1.available() >= 2 && newMessageReady == false) {
      currentByte = Serial1.read();
      if (currentByte == START_BYTE) {
        startRead = millis();
        lenRead = (unsigned int)Serial1.read();  //length in bytes including the start byte, length byte and checksum byte
        serialIdle = false;
      }
    }
  } else {
    if (Serial1.available() >= lenRead-2) {  //already read 2 bytes: start byte and length byte
      serialIdle = true;
      
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
        sendFailedMSG();
        newMessageReady = false;
      } else {
        sendSuccessMSG();
        newMessageReady = true;
      }

    } else if (millis() > startRead + MSG_TIMEOUT) {
      serialIdle = true;
      sendFailedMSG();
      newMessageReady = false;
    }
  }

  if (newMessageReady) {
    ParseMessage();
  }
}
