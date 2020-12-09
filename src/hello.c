#include <stdio.h>
#include <unistd.h>
#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "hello.h"
#include "test.h"
#include "testSensor.h"

int main( void )
{
	printf( "Hello, OS!\n" );

	ev3_init();
	ev3_sensor_init();
	printf( "Found sensors:\n" );
	int i, ii, val, n;
	char s[ 256 ];

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


if(sensor_init(void)){
	printf("YESSAI CA MARCHE\n", );
}
	// int j;
	// for(j = 0 ; j < 100 ; j++){
	// 	testColor();
	// 	testOrientation();
	// 	testDistance();
	// 	sleep(1);
	// }



	ev3_uninit();


	return test();
}

void print_hello() {
	printf("Hello, world!\n");
}
