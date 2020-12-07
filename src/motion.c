#include "motion.h"

#include "ev3.h"
#include "ev3_tacho.h"

#include <stdio.h>

positon = { .p = {.x = 0, .y = 0}, .rotation = 0 };

bool motion_init(void) {
    if(ev3_tacho_init()==-1)
        return false;
    if(!ev3_search_tacho_plugged_in(LEFT_WHEEL_PORT, 0, &left_wheel, 0))
        return false;
    if(!ev3_search_tacho_plugged_in(RIGHT_WHEEL_PORT, 0, &right_wheel, 0))
        return false;
    return true;
}

int robot_move(int distance) {
   int max_speed;
   int sn = left_wheel;
      printf( "LEGO_EV3_M_MOTOR 1 is found, run for 5 sec...\n" );
      get_tacho_max_speed( sn, &max_speed );
      printf("  max speed = %d\n", max_speed );
      set_tacho_stop_action_inx( sn, TACHO_COAST );
      set_tacho_speed_sp( sn, max_speed * 2 / 3 );
      set_tacho_time_sp( sn, 5000 );
      set_tacho_ramp_up_sp( sn, 2000 );
      set_tacho_ramp_down_sp( sn, 2000 );
      set_tacho_command_inx( sn, TACHO_RUN_TIMED );
      /* Wait tacho stop */
      Sleep( 100 );
      do {
        get_tacho_state_flags( sn, &state );
      } while ( state );
      printf( "run to relative position...\n" );
      set_tacho_speed_sp( sn, max_speed / 2 );
      set_tacho_ramp_up_sp( sn, 0 );
      set_tacho_ramp_down_sp( sn, 0 );
      set_tacho_position_sp( sn, 90 );
      for ( i = 0; i < 8; i++ ) {
        set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
        Sleep( 500 );
      } 
}
