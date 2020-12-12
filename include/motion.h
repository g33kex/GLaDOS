#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "ev3.h"
#include "ev3_tacho.h"

#include "vector.h"
#include "sensors.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

/* Constants */

/** Port for the left wheel motor (A) **/
#define LEFT_WHEEL_PORT 65
/** Port for the right wheel motor (D) **/
#define RIGHT_WHEEL_PORT 68

/** Starting duty of the motors **/
#define INITIAL_DUTY 20
/** Wheel circumference (mm) **/
#define WHEEL_CIRCUMFERENCE 173
/** Distance between the wheels (mm) **/
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

/** Position of the robot **/
Position robot_pos;

/* Functions */

/** Initializes the motion systme
  * Returns false in case of an error **/
bool motion_init(void);

/** Stop the robot **/
void stop_robot(void);

/** Rotate to target then move to target in a straight-ish line **/
void rotate_move_to(Vector target);

/** Move to target in a straight-ish line **/
void move_to(Vector target);

/** Rotate the robot to face a given point **/
void rotate_to(Vector target);


#endif // MOTION_H
