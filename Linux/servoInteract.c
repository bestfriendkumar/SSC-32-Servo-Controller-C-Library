#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "servo.h"
//#include "radio.h"

int main() {
   // printf("Initialization\n");
    initializeController(); // initalize the board
    //printf("Setting servos\n");
    setServos(1); // Initialize servo positions
    //printf("running...\n");
    
    //initializeControllerSpecific("/dev/ttyUSB0", "115200");
    //sendCommand("#7P2300S750<CR>");
    setPos(0, 2400); // Set servo at index 0 to position 1500
    //sleep(3);
    //center(0);
    setPos(0, 600);
    //sleep(3);
    //setPos(0, 1500);
    //setPosWithSpeed(0, 600, 1000);
    //setPosWithSpeed(0, 2000, 1000);
    center(0);
    
    setPos(1, 2400);
    setPos(1, 1000);
    center(1);
    //sleep(4); //wait # seconds
    //setPosWithSpeed(0, 2300, 1000);
}