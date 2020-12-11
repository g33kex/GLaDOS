#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "motion.h"
#include "sensors.h"

#include "test_motion.h"

void usage(void) {
    printf("Usage : GLaDOS <command>\nList of commands:\n\tstop\t\tStop the robot\n\tcalibrate\tCalibrate the compass\n\tmove\t\tMove the robot to the origin cube\n\tgrab\t\tGrab a ball in front of the robot\n");
}

bool init() {
    if(!motion_init()) {
        printf("Failed to initialize motors!\n");
        return false;
    }
    if(!sensor_init()) {
        printf("Failed to initialize sensors!\n");
        return false;
    }
    return true;
}

void stop() {
    stop_robot();
}

void calibrate() {
    calibrate_compass();
}

void move() {
    test_motion();
}

void grab() {

}

int main(int argc, char **argv) {

    if(argc!=2) {
        usage();
        return 1;
    }
    char *command = argv[1];

    /* Tests that require initialization */
    if(!init())
        return -1;

    if(strcmp("stop", command)) {
        stop();
    }
    else if(strcmp("calibrate", command)) {
        calibrate();
    }
    else if(strcmp("move", command)) {
        move();
    }
    else if(strcmp("grab", command)) {
        grab();
    }
    return 0;
}
