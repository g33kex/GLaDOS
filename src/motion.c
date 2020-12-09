#include "motion.h"

#include "ev3.h"
#include "ev3_tacho.h"

#include <stdio.h>
#include <unistd.h>

#define Sleep( msec ) usleep(( msec ) * 1000 )

/* Private functions */

static void init_motor(uint8_t);
static void run_motor(uint8_t, int, int);

/* Functions implementation */

bool motion_init(void) {
    robot_pos = (Position) {{0,0},0};
    //int i;
    //char s[256];

    printf("Running tacho init\n");
    if(ev3_tacho_init()==-1)
        return false;
    /*for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
      printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
      printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
      printf("  port = %d %d\n", ev3_tacho_desc_port(i), ev3_tacho_desc_extport(i));
    }
  }*/
    printf("Searching for left motor\n");
    if(!ev3_search_tacho_plugged_in(LEFT_WHEEL_PORT, 0, &left_wheel, 0))
        return false;
    printf("Searching for right motor\n");
    if(!ev3_search_tacho_plugged_in(RIGHT_WHEEL_PORT, 0, &right_wheel, 0))
        return false;

    init_motor(left_wheel);
    init_motor(right_wheel);
    return true;
}


/** Move the robot by given distance
  * distance in centimeters
  * if distance is negative moves backward */
int robot_move(int distance) {
    int rot = (distance*3600)/WHEEL_CIRCUMFERENCE;
    printf("Running the motors %d degrees with speed %d\n", rot, moving_speed);
    run_motor(left_wheel, rot, moving_speed);
    run_motor(right_wheel, rot, moving_speed);

   Sleep ( 10000 );

   return 0;
}

void test_dynamic_wheel() {
    set_tacho_duty_cycle_sp(left_wheel, 30);
    set_tacho_duty_cycle_sp(right_wheel, 30);
    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);
    Sleep ( 1500 );
    set_tacho_duty_cycle_sp(left_wheel, 10);
    Sleep ( 1000 );
    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
}

void move_to(Point target) {
    robot_pos.rotation = get_rotation();
}

/** Run the motor by a given amount.
  * rot is in degrees **/
static void run_motor(uint8_t motor, int rot, int speed) {
    set_tacho_speed_sp(motor, speed);
    set_tacho_position_sp(motor, rot);
    set_tacho_command_inx(motor, TACHO_RUN_TO_REL_POS);
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

