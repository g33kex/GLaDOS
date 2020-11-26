#include <stdio.h>

#include "ev3.h"
#include "ev3_light.h"

#include "hello.h"
#include "test.h"

int main( void )
{
	printf( "Hello, OS!\n" );

	ev3_init();
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

	print_hello();

	return test();
}

void print_hello() {
	printf("Hello, world!\n");
}
