#include "SubsystemManager/SubsystemManager.h"
#include "TestSubsystem/TestSubsystem.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h"
#include "RobotVision/vision.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

// #define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

using namespace std;

// unsigned char feedback[10];
unsigned char* feedback;
unsigned char controller[8];
unsigned char data[8];

bool connection;
bool badPacket;
unsigned char x;
unsigned char packet_index;
unsigned char i;
unsigned char size1;
unsigned char checkSumTX;    // check sum for transmitting data
unsigned char checkSumRX;    // check sum for recieving data

unsigned long read_time;

//function for halting all motor output in case of comms loss
void failsafe(SubsystemManager* subsystems){
    // write the code below that you want to run
    // when the robot loses a signal here
    subsystems->failsafe();
    connection = false;
}

int main()
{
  //initializes digital IO
	wiringPiSetupGpio();

	int serialId = serialOpen("/dev/ttyS0", 9600);     //for RPi 3
    // int serialId = serialOpen("/dev/ttyAMA0", 9600);     //For previous RPi models

	memset(controller,0,sizeof(controller));
    // memset(feedback,0,sizeof(feedback));
    connection = true;

    // creates the subsystems for the robot and sets initial states
    SubsystemManager* Robot = new SubsystemManager();
    Robot->initializeSubsystems();
    //Vision *v = new Vision();

    //calls failsafe to stop output before comms are established
	failsafe(Robot);

  //initializes variables for packet reading
	read_time = millis();
	checkSumRX = 0;
	x = 0;
	packet_index = 0;

	cout << "init complete" << endl;

  //packet reading loop
	while(true)
	{
		/*if(v->checkBoard()){
			std::cout << "Found board." << std::endl;
			cout << v->analyzeBoard() << endl;
			usleep(3000000); //3 seconds
		}*/
        // try
        // {
            connection = false;
            //this loop discards any extra packets detected
            while(packet_index == 0 && serialDataAvail(serialId) >= 22){
                serialGetchar(serialId);
            }

            // size1 set to number of packets
            size1 = serialDataAvail(serialId);
            while(size1 > 0){
                if(packet_index == 0){
                    //checks for expected leading package (255), increments packet_index to proceed if correct
                    if(serialGetchar(serialId)==255){
                        packet_index++;
                    }
                }
                else if(packet_index < 9){
                    //stores information in data array, keeps a rolling sum of values to compare at end of packet (checkSum)
                    data[packet_index-1] = serialGetchar(serialId);
                    checkSumRX += data[packet_index-1];
                    packet_index++;
                }
                else if(packet_index == 9){
                  //if received checkSum equals expected checkSum, proceed to final validation check
                  //otherwise, repeat process
                    if(serialGetchar(serialId) == checkSumRX){
                        packet_index++;
                    }else{
                        packet_index=0;
                    }
                    checkSumRX = 0;
                }
                else if(packet_index == 10){
                    //checks for expected ending package
                    if(serialGetchar(serialId) == 240){
                        //if ending package is valid, then use the information
                        //as valid controller input
                        for(i=0; i<8; i++){
                            controller[i] = data[i];
                        }
                        connection = true;
                        read_time = millis();
                    }
                    packet_index=0;
                }
                size1--;
            }
            //if timeout, run failsafe
            if(connection && millis() - read_time >= time_out){
                failsafe(Robot);
            }

            if(connection){
                // write the code below that you want to run
                // when the robot recieves valid data of the xbox controller
                // basically all the motor control stuff
                //after getting valid input, execute main code
                feedback = Robot->runRobot(controller);

                // below is the code for sending feedback packet to the driver station
                serialPutchar(serialId, 255);
                checkSumTX = 0;
                for(i=0; i<10; i++){
                    serialPutchar(serialId, feedback[i]);
                    checkSumTX += feedback[i];
                }
                serialPutchar(serialId, checkSumTX);
                serialPutchar(serialId, 240);
            }
        // }
        // catch (...)
        // {
        //     cout << "failsafe" << endl;
        //     Robot->failsafe();
        // }
	}
}
