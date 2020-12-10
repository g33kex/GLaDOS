#include "grab.h"

#include "ev3.h"
#include "ev3_tacho.h"

#include <stdio.h>

static void init_motor(uint8_t);
static void run_motor(uint8_t, int, int);


int main(void) {
	if(ev3_tacho_init()==-1)
		return -1;
	if ( ev3_search_tacho_plugged_in(67,0, &hand, 0 ) && ev3_search_tacho_plugged_in(66,0, &lever,0)) {
		init_motor(hand);
		init_motor(lever);
		lower();
		lift();
	} else {			
		printf( "LEGO_EV3_M_MOTOR is NOT found\n" );		    
	}
	return 0;
}

void open_hand(){
	run_motor(hand, 0, 400);
	sleep(1);
}

void close_hand(){
	run_motor(hand, 200, 400);
	sleep(1);
}

void lift(){
	run_motor(lever, 0, 400);
	sleep(3);
}

void lower(){
	run_motor(lever, 288, 400);
	sleep(3);
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
	set_tacho_stop_action_inx(motor, TACHO_BRAKE);
}
