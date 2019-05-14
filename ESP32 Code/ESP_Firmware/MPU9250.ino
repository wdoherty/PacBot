


MPU9250 IMU;
float mDirection, mX, mY, mZ;

void setup_IMU() {
  
  IMU.setWire(&Wire);
  //IMU.beginAccel();
  //IMU.beginGyro();
  IMU.beginMag();

  IMU.magXOffset = -50;
  IMU.magYOffset = -55;
  IMU.magZOffset = -10;
  
}

//need to pick out which value is the one we want
void update_Orientation_Angle() {
  IMU.magUpdate();
  
  mX = IMU.magX();
  mY = IMU.magY();
  mZ = IMU.magZ();
  
  mDirection = IMU.magHorizDirection();
}

