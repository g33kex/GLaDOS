#include "grab.h"
#include "motion.h"
#include "sensors.h"

#include "ev3.h"
#include "ev3_tacho.h"

#include <stdio.h>

static void init_motor(uint8_t);
static void run_motor(uint8_t, int, int);


void open_hand(){
	run_motor(hand, OPENED_HAND, GRAB_SPEED);
	sleep(2);
}

void close_hand(){
	run_motor(hand, CLOSED_HAND, GRAB_SPEED);
	sleep(3);
}

void lift(){
	run_motor(lever, LEVER_UP, LEVER_SPEED);
	sleep(3);
}

void lower_half() {
	run_motor(lever, LEVER_MID, LEVER_SPEED);
	sleep(3);
}

void lower(){

	run_motor(lever, LEVER_DOWN, GRAB_SPEED);
	sleep(3);
}

void grab(){
	lower_half();
	sleep(1);
	open_hand();
	lower();
	close_hand();
}

void grab_with_retry(){
	grab();
	while (!is_ball_in_hand()){
		open_hand();
		lower_half();
		coup_vener();
		sleep(1);
		lower();
		close_hand();
	}
	lift();
}


static void run_motor(uint8_t motor, int rot, int speed) {
	set_tacho_speed_sp(motor, speed);
	set_tacho_position_sp(motor, rot);
	set_tacho_command_inx(motor, TACHO_RUN_TO_ABS_POS);
}

static void init_motor(uint8_t motor) {
	int count_per_rot;
	get_tacho_count_per_rot(motor, &count_per_rot);
	printf("Tacho count for motor %d = %d\n",motor,count_per_rot);
	//One tacho count is actuall one degree
	//set_tacho_speed_sp(motor, max_speed/10);
	set_tacho_ramp_up_sp(motor, 0);
	set_tacho_ramp_down_sp(motor, 0);
	set_tacho_stop_action_inx(motor, TACHO_HOLD);
}

bool grab_init() {
	if(ev3_tacho_init()==-1)
		return false;
	if(!ev3_search_tacho_plugged_in(HAND_PORT,0,&hand,0)){
		printf("PB AVEC MAIN\n");
		return false;
	}
	if(!ev3_search_tacho_plugged_in(LEVER_PORT,0,&lever,0)){
		printf("PB AVEC levier\n");
		return false;
	}

	init_motor(hand);
	init_motor(lever);

	return true;
}

bool grab_position_init() {
	set_tacho_position(hand, 0);
	set_tacho_position(lever, 0);

	return true;
}
