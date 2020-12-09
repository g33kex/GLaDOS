#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
//const Color const *color[] = { UNKNOW, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN  };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

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
    if(!ev3_search_sensor_plugged_in(COLOR_FRONT_PORT, 0, &sn_color_front, 0)){
      printf("PB AVEC FRONT\n");
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



int get_intensity(){
  set_sensor_mode( sn_color_front, "COL-AMBIENT" );
  int value;
  if ( !get_sensor_value( 0, sn_color_front, &value )) {
      value = 0;
  }
  fflush( stdout );
  return value;
}

int get_distance(){
  float value;
  if ( !get_sensor_value0(sn_sonar, &value )) {
    value = 0;
  }
  fflush( stdout );
  printf("%f\n",value );
  return (int) value;
}

int get_orientation(){
  float value;
  if ( !get_sensor_value0(sn_compass, &value )) {
    value = 0;
  }
  fflush( stdout );
  return (int) value;
}
