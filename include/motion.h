#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "ev3.h"
#include "ev3_tacho.h"

#include "vector.h"
#include "sensors.h"

/* Constants */
//Port A
#define LEFT_WHEEL_PORT 65
//Port D
#define RIGHT_WHEEL_PORT 68

#define INITIAL_DUTY 20
#define MAX_SPEED 1500
//Millimeters
#define WHEEL_CIRCUMFERENCE 173 
#define WHEEL_DISTANCE 40

/* Structures */
typedef struct {
    Vector p;
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

/** Move to target in a straight-ish line 
  * Returns true if we think move was successful */
bool move_to(Vector target);

/** Rotate the robot to face a given point */
bool rotate_to(Vector target);


#endif // MOTION_H
