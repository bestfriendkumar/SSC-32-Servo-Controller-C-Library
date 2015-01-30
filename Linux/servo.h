/**
 * 2014-2015 NC State University
 * High Powered Rocketry Team - Tacho Lycos
 * Author: Daniel Mahinthakumar
 * 
 * This API will allow a user to include "servo.h" and
 * interact with servos connected to the SSC-32 Servo Controller.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Do initialization to connect with com ports
 * and set default values
 */
void initializeController();

/**
 * Do initialization to connect with com ports
 * and set to SPECIFIED VALUES
 * @param port, port number of the device
 * @param baud, communication baud rate to serial
 */
void initializeControllerSpecific(char *port, char *baud);

/**
 * Sets the servos to their initial position and sets the active number of servos
 * @param num, the highest index of servos connected to the board
 */ 
void setServos(int num);

/**
 * Set what a specific servo should start at
 * @param idx, index of the servo
 * @param pw, pulse width
 */
void setServoStart(int idx, int pw);

/**
 * Set specific command
 * @param comm, string to send to device
 */
void sendCommand(char *comm);

/**
 * Set the position of a specific servo by sending pulse width
 * @param idx, index of the servo
 * @param pw, pulse width
 */
void setPos(int idx, int pw);

/**
 * Set the position of a specific servo by sending pulse width
 * ADDITIONAL SUPPORT FOR SPECIFIC SPEEDS
 * @param idx, index of the servo
 * @param pw, pulse width
 */
void setPosWithSpeed(int idx, int pw, int speed);

/**
 * Set global speed of all servos
 */
void setSpeed(int speed);

/**
 * Center the specified servo
 * @param idx, index of the servo
 */
void center(int idx);