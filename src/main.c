#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "motion.h"
#include "sensors.h"
#include "grab.h"

#include "test_motion.h"
#include "test_sensors.h"

void usage(void) {
    printf(
        "Usage : GLaDOS <command>\n"
        "List of commands:\n"
        "\tstop\t\tStop the robot\n"
        "\tcalibrate\tCalibrate the compass\n"
        "\tmove\t\tMove the robot to the origin cube\n"
        "\tgrab\t\tGrab a ball in front of the robot\n"
        "\ttest6\t\tSearch and got ot the random cube\n"
        "\ttest5\t\tput the ball in the pyramid\n"
        );
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
    if(!grab_init()){
    	printf("Failed to initialize hand!\n");
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

void rot() {
    test_rotation();
}

void grab() {
	lower_half();
	open_hand();
	lower();
	close_hand();
	lift();
}

void grab_val_init() {
	grab_position_init();
}

void move_random(){
    move_robot_to_random_cube(); //in test_sensors, need to be moved ?
}

void drop_ball(){
  drop_ball_in_pyramid();//in test_sensors, need to be moved ?
}

void vector() {
    test_vector();
}

int main(int argc, char **argv) {

    if(argc!=2) {
        usage();
        return 1;
    }
    char *command = argv[1];
    if(!strcmp("vector", command)) {
        vector();
        return 0;
    }

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
    else if(!strcmp("rot", command)) {
        rot();
    }
    else if(!strcmp("grab", command)) {
        grab();
    }
    else if(!strcmp("grab_val_init", command)) {
	grab_val_init();
    }

    else if(!strcmp("test5", command)){
      drop_ball();
    }
    else if(!strcmp("test6", command)){
      move_random();
    }
    else if(!strcmp("color", command)){
      printf("couleur : %s\n",get_color() );
    }
    else if(!strcmp("dist", command)){
      printf("distance : %d\n",get_distance() );
    }
    else if(!strcmp("distRound", command)){
      test_sonar();
    }
    else if(!strcmp("compass", command)){
      printf("orientation : %d\n",get_orientation() );
    }
    else if(!strcmp("gyro", command)){
      printf("angle du gyro : %d\n",get_gyro() );
    }
    else if(!strcmp("move_grab", command)){
      grab_ball_in_pyramid();
    }
    else if(!strcmp("lower", command)){
      lower();
    }
    else if(!strcmp("lift", command)){
      lift();
    }
    else if(!strcmp("lower_half", command)){
	    lower_half();
    }
    else if(!strcmp("open_hand", command)){
	    open_hand();
    }
    else if (!strcmp("close_hand", command)){
	    close_hand();
    }
    else if(!strcmp("foward", command)){
      int distance = 100;
      init_rotation();
      foward((double) distance);
    }




    return 0;
}
