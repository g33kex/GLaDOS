#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include <stdint.h>

//Port A
#define LEFT_WHEEL_PORT 64
//Port D
#define RIGHT_WHEEL_PORT 68

/* Structures */
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point p;
    int rotation;
} Position;

/* Variables */

/** Motors sequence numbers **/
uint8_t left_wheel;
uint8_t right_wheel;


/** Position of the robot **/
Position robot_pos;

/* Functions */

/** Initializes the motion systme
  * Returns false in case of an error **/ 
bool motion_init(void);

/** Move the robot by given distance
  * If distance < 0, moves backward
  * If distance > 0, moves forward
  * Returns the distance moved **/
int robot_move(int distance);

/** Rotate the robot by given angle
 ** Returns the actual rotation **/
int robot_rotate(int angle);


#endif // MOTION_H
