#include <stdio.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

int main( void )
{
	char s[ 256 ];
    	int val , n, i, ii;
	uint8_t sn_color;
	printf( "Hello, OS!\n" );

	ev3_init();
	printf("initializing sensors..\n");
	ev3_sensor_init();
	printf( "Found sensors:\n" );
    	for ( i = 0; i < DESC_LIMIT; i++ ) {
       		if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
            		printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
            		printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
            		if ( get_sensor_mode( i, s, sizeof( s ))) {
                		printf( "  mode = %s\n", s );
            		}		
            		if ( get_sensor_num_values( i, &n )) {
                		for ( ii = 0; ii < n; ii++ ) {
                    			if ( get_sensor_value( ii, i, &val )) {
                        			printf( "  value%d = %d\n", ii, val );
                    			}	
                		}
            		}
        	}
    	}
	if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        	printf( "COLOR sensor is found, reading COLOR...\n" );
        	set_sensor_mode( sn_color, "COL-COLOR" );
        	for ( i = 0  ; i < 5 ; i++ ) {
            		if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
                		val = 0;
            		}		
            		printf( "%s \n", color[ val ]);
            		// fflush( stdout ); useless ?
                        sleep( 200 );
       		}
   	}

	switch ( get_light( LIT_LEFT )) {

	case LIT_GREEN:
		set_light( LIT_LEFT, LIT_RED );
		break;

	case LIT_RED:
		set_light( LIT_LEFT, LIT_AMBER );
		break;

	default:
		set_light( LIT_LEFT, LIT_GREEN );
		break;
	}
	ev3_uninit();

	return 0;
}
