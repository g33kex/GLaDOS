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
    if(ev3_sensor_init()==-1)
        return false;
    if(!ev3_search_sensor_plugged_in(COMPASS_PORT, 0, &sn_compass, 0))
        return false;
/*    if(!ev3_search_sensor_plugged_in(SONAR_PORT, 0, &sn_sonar, 0))
        return false;
    if(!ev3_search_sensor_plugged_in(COLOR_FRONT_PORT, 0, &sn_color_front, 0))
        return false;
    if(!ev3_search_sensor_plugged_in(COLOR_PINCE_PORT, 0, &sn_color_pince, 0))
        return false;
        */
    return true;
}



const char * get_color(){

  int val;
  if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color_front, 0 )) {
          printf( "COLOR sensor is found, reading COLOR...\n" );
          set_sensor_mode( sn_color_front, "COL-COLOR" );
          if ( !get_sensor_value( 0, sn_color_front, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
              val = 0;
          }
          return color[ val ];
    }
    else {
      printf("[X] unable to find the color sensor !");
      return color[0];
    }
}



int get_intensity(){
  return 0;
}

int get_distance(){
  float value;
  if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
      printf("SONAR found, reading sonar...\n");
      if ( !get_sensor_value0(sn_sonar, &value )) {
        value = 0;
      }
      fflush( stdout );
      return (int) value;
    }

  return 0;
}

int get_orientation(){
  float value;
  if (ev3_search_sensor(HT_NXT_COMPASS, &sn_compass,0)){
      printf("COMPASS found, reading compass...\n");
      if ( !get_sensor_value0(sn_compass, &value )) {
        value = 0;
      }
      fflush( stdout );
      return (int) value;
    }
    return 0;
}
