/**
 * 2014-2015 NC State University
 * High Powered Rocketry Team - Tacho Lycos
 * Author: Daniel Mahinthakumar
 * 
 * This API will allow a user to include "servo.h" and
 * interact with servos connected to the SSC-32 Servo Controller.
 * 
 * KNOWN BUGS/ISSUES:
 * -Memory is not freed for each function
 * -Commands have a limited size
 * -Wait time is only measured in integer seconds, not decimal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "servo.h"

//Helper function prototypes
void fail(char *message);
int timeNeeded(int idx, int destination, int speed);
int getDistance(int idx, int destination);
int getPW(int idx);

//Constants
#define COMMAND_SIZE 100 //Max command size
#define PARTIAL_COMMAND_SIZE 60 //usual command size
#define MAX_IDX 31 //highest index size
#define MIN_PW 500 //lowest pw
#define MAX_PW 2500 //highest pw
#define CENTER_PW 1500 //pw for center position
#define DEFAULT_SLEEP_TIME 3//wait time for each servo at initialization

//Global Variables
char PORT[13] = "/dev/ttyUSB0 "; // USB Port ID
char BAUD[6] = "115200"; // Baud Rate
int SPEED = 500; // Servo speed
int NUM_ACTIVE_SERVOS;

//Keeps track of the last servo position
//                  0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    20    31
int servoPW[32] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};

/**
 * Do initialization to connect with com ports
 * and set default values
 */
void initializeController() {
    char command[COMMAND_SIZE];
    sprintf(command, "stty -F %s %s", PORT, BAUD);
    system(command);
}

/**
 * Do initialization to connect with com ports
 * and set to SPECIFIED VALUES
 * @param port, port number of the device
 * @param baud, communication baud rate to serial
 */
void initializeControllerSpecific(char *port, char *baud) {
    char command[COMMAND_SIZE];
    sprintf(command, "stty -F %s %s", port, baud);
    strcpy(PORT, port);
    strcpy(BAUD, baud);
    system(command);
}

/**
 * Sets the servos to their initial position and sets the active number of servos
 * @param num, the highest index of servos connected to the board
 */ 
void setServos(int num) {
    NUM_ACTIVE_SERVOS = num;
    for(int i = 0; i <= NUM_ACTIVE_SERVOS; i++) {
        char command[COMMAND_SIZE];
        char partialCommand[PARTIAL_COMMAND_SIZE];
        sprintf(partialCommand, "#%dP%dS%d<CR>", i, servoPW[i], SPEED);
        sprintf(command, "echo \"%s\" > %s", partialCommand, PORT);
        system(command);
        sleep(DEFAULT_SLEEP_TIME); //give each servo initial wait time
   }
}

/**
 * Set what a specific servo should start at
 * @param idx, index of the servo
 * @param pw, pulse width
 */
void setServoStart(int idx, int pw) {
    servoPW[idx] = pw;
}

/**
 * Set specific command
 * @param comm, string to send to device
 */
void sendCommand(char *comm) {
    if(sizeof(comm) > (COMMAND_SIZE - 2))
        fail("Command to large");
        
    char command[COMMAND_SIZE];
    sprintf(command, "echo \"%s\" > %s", comm, PORT);
    system(command);
}

/**
 * Set the position of a specific servo by sending pulse width
 * @param idx, index of the servo
 * @param pw, pulse width
 */
void setPos(int idx, int pw) {
    if((idx > MAX_IDX) || (pw < MIN_PW) || (pw > MAX_PW))
        fail("Invalid index or pw");
    char command[COMMAND_SIZE];
    char partialCommand[PARTIAL_COMMAND_SIZE];
    sprintf(partialCommand, "#%dP%dS%d<CR>", idx, pw, SPEED);
    sprintf(command, "echo \"%s\" > %s", partialCommand, PORT);
    system(command);
    sleep(timeNeeded(idx, pw, SPEED));
    servoPW[idx] = pw;
}

/**
 * Set the position of a specific servo by sending pulse width
 * ADDITIONAL SUPPORT FOR SPECIFIC SPEEDS
 * @param idx, index of the servo
 * @param pw, pulse width
 */
void setPosWithSpeed(int idx, int pw, int speed) {
    if((idx > MAX_IDX) || (pw < MIN_PW) || (pw > MAX_PW))
        fail("Invalid index or pw");
    char command[COMMAND_SIZE];
    char partialCommand[PARTIAL_COMMAND_SIZE];
    sprintf(partialCommand, "#%dP%dS%d<CR>", idx, pw, speed);
    sprintf(command, "echo \"%s\" > %s", partialCommand, PORT);
    system(command);
    sleep(timeNeeded(idx, pw, speed));
    servoPW[idx] = pw;
}

/**
 * Set global speed of all servos
 */
void setSpeed(int speed) {
    SPEED = speed;
}

/**
 * Center the specified servo
 * @param idx, index of the servo
 */
void center(int idx) {
    char command[COMMAND_SIZE];
    char partialCommand[PARTIAL_COMMAND_SIZE];
    sprintf(partialCommand, "#%dP%dS%d<CR>", idx, CENTER_PW, SPEED);
    sprintf(command, "echo \"%s\" > %s", partialCommand, PORT);
    system(command);
}

/**************************************************************
 **************************HELPER FUNCTIONS********************
 *************************************************************/
 
 /**
  * Failure mode
  * @param message, output message
  */
void fail(char *message) {
    printf("%s\n", message);
    exit(1);
}

/**
 * Gets the time needed to complete the movement
 * Time = Distance / Speed
 * @param idx, index of the servo
 * @param destination, destination pulse width
 * @param speed, the speed being used
 */
int timeNeeded(int idx, int destination, int speed) {
    int neededTime;
    int distance = getDistance(idx, destination);
    neededTime = distance / speed;
    return neededTime;   
}

/**
 * Gets the distance between the current position and the destination
 * @param idx, index of the servo
 * @param destination, destination pulse width
 */
int getDistance(int idx, int destination) {
    int distance = abs(getPW(idx) - destination);
    return distance;
}

/**
 * Get pulse width of specified servo
 * @param idx, index of the servo
 */
int getPW(int idx) {
   return servoPW[idx];
}