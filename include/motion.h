#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "ev3.h"
#include "ev3_tacho.h"

#include "sensors.h"


/* Macros */
#define PI 3.14159265
#define abs(x) (x>=0?x:-(x))
#define sign(x) (x>=0?1:-1)
#define radians(x) ((PI*(x))/180)
#define degrees(x) ((180*(x))/PI)

/* Constants */
//Port A
#define LEFT_WHEEL_PORT 65
//Port D
#define RIGHT_WHEEL_PORT 68

#define INITIAL_DUTY 20
#define MAX_SPEED 1500
//Millimeters
#define WHEEL_CIRCUMFERENCE 173 

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

/** Motors parameters **/
static const int moving_speed = MAX_SPEED/10;


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

void test_dynamic_wheel(void);

/** Move to target in a straight-ish line 
  * Returns true if we think move was successful */
bool move_to(Point target);


#endif // MOTION_H
