#include <stdio.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"

int main( void )
{
	char s[ 256 ];
    	int val , n, i, ii;
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
