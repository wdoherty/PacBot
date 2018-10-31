#include "TankDrive.h"
#include <stdlib.h>
#include <math.h>
// #include <iostream>


TankDrive::TankDrive(PCA9685* PWM, int leftPin1, int leftPin2, int rightPin1, int rightPin2) : controller(PWM)
{
    _leftPin1 = leftPin1;
    _leftPin2 = leftPin2;
    _rightPin1 = rightPin1;
    _rightPin2 = rightPin2;
    left1 = new Victor(controller, _leftPin1);
    left2 = new Victor(controller, _leftPin2);
    right1 = new Victor(controller, _rightPin1);
    right2 = new Victor(controller, _rightPin2);
    headingMod = 1.6;
}

void TankDrive::failsafe()
{
    left1->setThrottle(2185);
    left2->setThrottle(2185);
    right1->setThrottle(2185);
    right2->setThrottle(2185);
}

unsigned char* TankDrive::updateDrive(unsigned char throttle, unsigned char reverse, unsigned char rStickX)
{
//scales input signa from
_throttle = (throttle >> 1);
_throttle *= 1650;
_throttle /= 100;

_reverse = (reverse >> 1);
_reverse *= 1650;
_reverse /= 100;

int throttleMag = _throttle - _reverse;
throttleMag += (1650/2);

_rStickX = rStickX;

_rStickX *= 1650;
_rStickX /= 200;

if(throttleMag > 743 && throttleMag < 907) throttleMag = 825;
if(_rStickX > 743 && _rStickX < 907) _rStickX = 825;
setThrottle(throttleMag, _rStickX);

return driveVals;
}

void TankDrive::setThrottle(int lStickY, int rStickX)
{
       double throttle = abs(lStickY-825) * (lStickY < 825 ? -1 : 1);    //// = magnitude & direction of throttle
       double heading = abs(rStickX-825) * (rStickX < 825 ? -1 : 1);    //// = magnitude and direction of heading

       double angularPower = fabs(throttle/825)*(heading)/(headingMod); //scales rotation by throttle value when not in quick turn

       setQuickTurn(throttle, heading);

   if(quickTurn)
   {
   lSpeed = throttle + heading + 825;
   rSpeed = throttle - heading + 825;
   }
   else
   {
   lSpeed = throttle + angularPower + 825;
   rSpeed = throttle - angularPower + 825;
   }

   //constrains motor values to within the PWM limits
if(lSpeed > 1650) lSpeed = 1650;
if(rSpeed > 1650) rSpeed = 1650;
if(lSpeed < 0) lSpeed = 0;
if(rSpeed < 0) rSpeed = 0;

//adjusts speed of one side of drive to compensate for uneven steering
// lSpeedMag = abs(90 - lSpeed);
// lSpeedMag *= 13;
// lSpeedMag /= 20;
// if(lSpeed > 90) lSpeed = 90 + lSpeedMag;
// else lSpeed = 90 - lSpeedMag;

//sends drive speeds back to DS
// feedback[0] = lSpeed;
// feedback[1] = rSpeed;

//optionally invert drive direction if electrical swap is difficult
lSpeed = 1650 - lSpeed;
// rSpeed = 1650 - rSpeed;

    //sends value to speed controller
    driveVals[0] = lSpeed;
    driveVals[1] = rSpeed;

    lSpeed += 1360;
    rSpeed += 1360;
	  // std::cout << lSpeed << std::endl;

      left1->setThrottle(lSpeed);
      left2->setThrottle(lSpeed);
      right1->setThrottle(rSpeed);
      right2->setThrottle(rSpeed);
}

void TankDrive::setQuickTurn(double throttle, double heading)
{
    if((fabs(throttle) < 82) && (fabs(heading) > 82)) quickTurn = true;
    else quickTurn = false;
}
