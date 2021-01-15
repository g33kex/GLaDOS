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

/** Wheel circumference (mm) **/
#define WHEEL_CIRCUMFERENCE 173.0
/** Distance between the wheels (mm) **/
#define WHEEL_DISTANCE 40.0

#define GYRO_TRUST_RATIO 0.95

/* Parameters */
/** Duty of the motors (percentage of maximum speed)
    Goes between 0 and 100% **/
#define INITIAL_DUTY 30//15
/** Same but for rotation **/
#define ROTATE_DUTY 18//12
/** Amount substracted from INITIAL_DUTY when correcting trajectory **/
#define DELTA_DUTY 5
/** Precisision of the angle when rotating (in degrees) **/
#define ANGLE_PRECISION 5
/** Precision of the distance when moving to a point (in mm) **/
#define PRECISION 5

/** Amount of time we sleep before updating rotation again **/
#define SLEEP_ROTATION 200

/** Amount of time we sleep before updating position again **/
#define SLEEP_POSITION 50//100

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

/** Initialize rotation of the robot **/
void init_rotation(void);

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

/** Rotate the robot by given angle
  * Angle should be in [-180, 180] **/
void rotate(int angle);

/** Go forward by a given distance **/
void foward(double distance);



void aller_tout_droit(int time); //idem
void coup_vener();
#endif // MOTION_H
