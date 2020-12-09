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


const char * get_color(){
  uint8_t sn_color;

  int val;
  if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
          printf( "COLOR sensor is found, reading COLOR...\n" );
          set_sensor_mode( sn_color, "COL-COLOR" );
          if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
              val = 0;
          }
          return color[ val ];
    }
    else {
      printf("[X] unable to find the color sensor !");
      return color[0];
    }


}

int get_distance(){
  uint8_t sn_sonar;
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
  uint8_t sn_compass;
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
