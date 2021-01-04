#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"
#include "motion.h"
#include "test_motion.h"
#include "vector.h"

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
//const Color const *color[] = { UNKNOW, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN  };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

int orientation_zero = 0;

bool sensor_init(void) {
    if(ev3_sensor_init()==-1){
      printf("PB AVEC INIT\n");
      return false;
    }

    if(!ev3_search_sensor_plugged_in(COMPASS_PORT, 0, &sn_compass, 0)){
      printf("PB AVEC COMPASS\n");
      return false;
    }

    if(!ev3_search_sensor_plugged_in(SONAR_PORT, 0, &sn_sonar, 0)){
      printf("PB AVEC SONAR\n");
      return false;
    }
    if(!ev3_search_sensor_plugged_in(GYRO_PORT, 0, &sn_gyro, 0)){
      printf("PB AVEC ACCELEROMETRE\n");
      return false;
    }
    if(!ev3_search_sensor_plugged_in(COLOR_PINCE_PORT, 0, &sn_color_pince, 0)){
      printf("PB AVEC PINCE\n");
      return false;
    }
    return true;
}



const char * get_color(){
  set_sensor_mode( sn_color_front, "COL-COLOR" );
  int val;
  if ( !get_sensor_value( 0, sn_color_front, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
      val = 0;
  }
  return color[ val ];
}



// int get_intensity(){
//   set_sensor_mode( sn_color_front, "COL-REFLECT" );
//   int value;
//   if ( !get_sensor_value( 0, sn_color_front, &value )) {
//       printf("[X]ERROR while reading intensity value\n");
//       value = 0;
//   }
//   fflush( stdout );
//   return value;
// }

int get_distance(){
  set_sensor_mode( sn_sonar, "US-DIST-CM" );

  int value;
  if ( !get_sensor_value(0,sn_sonar, &value )) {
    printf("[X]ERROR while reading distance value\n");
    value = 0;
  }
  printf("distance : %d\n", value );
  fflush( stdout );
  return (value);
}


void calibrate_compass() {
    printf("Calibrating compass...\n");
    set_sensor_command(sn_compass, "END-CAL");
    set_sensor_command(sn_compass, "BEGIN-CAL");

    set_tacho_duty_cycle_sp(left_wheel, -INITIAL_DUTY*2);
    set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY*2);

    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);

    Sleep ( 40000 );

    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
    set_sensor_command(sn_compass, "END-CAL");
}


int get_orientation(){

  int rot;
  if ( !get_sensor_value(0, sn_compass, &rot )) {
    printf("[X]ERROR while reading orientation value\n");
    rot = 0;
  }
  fflush( stdout );
  rot = rot - orientation_zero;
  if(rot < 0) {
    rot = rot + 360;
  }
  return rot==0?0:360-rot;
}

//  float value;
//  if (ev3_search_sensor(HT_NXT_COMPASS, &sn_compass,0)){
//      if ( !get_sensor_value0(sn_compass, &value )) {
//        value = 0;
//      }
//      fflush( stdout );
//      return (int) value;
//    }
//    return 0;
// }

bool set_orientation(int orientation){
  orientation_zero = orientation;
  return true;

}

int get_gyro(){
  set_sensor_mode( sn_gyro, "GYRO-ANG" );

  int value;
  if ( !get_sensor_value(0,sn_gyro, &value )) {
    printf("[X]ERROR while reading gyro value\n");
    value = 0;
  }
  printf("angle : %d\n", value );
  fflush( stdout );
  return (value);
}
