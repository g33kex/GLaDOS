#ifndef GRAB_H
#define GRAB_H

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>


/*variables*/
#define LEVER_PORT 66
#define HAND_PORT 67

#define GRAB_SPEED 100
#define LEVER_SPEED 250
#define CLOSED_HAND -20 //0 avant
#define OPENED_HAND 90
#define LEVER_UP -450
#define LEVER_MID -210
#define LEVER_DOWN 0


/*functions*/

/**brings the hand to the lowest position**/
void lower();

/**brings the hand at intermediate position (in the cube but above the balls)**/
void lower_half();

/**brings the hand at the highest position**/
void lift();

/**opens the hand**/
void open_hand();

/**closes the hand**/
void close_hand();

/**procedure that combines the previous functions to grab a ball when placed above the cube**/
void grab();

/**tries grabing a ball until it has one in hand**/
void grab_with_retry();

/*init functions*/

/**associates the motors to their ports**/
bool grab_init();

/**sets positions of the hand as lowest and closed (to execute only once at startup)**/
bool grab_position_init();

/*constants*/
uint8_t hand;
uint8_t lever;

#endif // GRAB_H
