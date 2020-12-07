#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "color.h"

const Color const *color[] = { UNKNOW, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

Color get_color(){
  uint8_t sn_color;
  Color color;
  int val, i;
  if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
          printf( "COLOR sensor is found, reading COLOR...\n" );
          set_sensor_mode( sn_color, "COL-COLOR" );
          if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
              return UNKNOW;
          }
          return color[ val ];
    }
    else {
      printf("[X] unable to find the color sensor !");
    }


}
