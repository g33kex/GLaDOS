#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "motion.h"
#include "sensors.h"

#include "test_motion.h"
#include "test_sensors.h"

void usage(void) {
    printf("Usage : GLaDOS <command>\nList of commands:\n\tstop\t\tStop the robot\n\tcalibrate\tCalibrate the compass\n\tmove\t\tMove the robot to the origin cube\n\tgrab\t\tGrab a ball in front of the robot\n\ttest6\t\tSearch and got ot the random cube\n");
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

void move_random(){
    move_robot_to_random_cube(); //in test_sensors, need to be moved ?
}

void drop_ball(){
  drop_ball_in_pyramid();//in test_sensors, need to be moved ?
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

    if(!strcmp("stop", command)) {
        stop();
    }
    else if(!strcmp("calibrate", command)) {
        calibrate();
    }
    else if(!strcmp("move", command)) {
        move();
    }
    else if(!strcmp("grab", command)) {
        grab();
    }

    else if(!strcmp("test5", command)){
      drop_ball();
    }
    else if(!strcmp("test6", command)){
      move_random();
    }

    return 0;
}
