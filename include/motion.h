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

#define GYRO_TRUST_RATIO 1;

/* Parameters */
/** Duty of the motors (percentage of maximum speed)
    Goes between 0 and 100% **/
#define INITIAL_DUTY 60//35
/** Same but for rotation **/
#define ROTATE_DUTY 27//18
/** Amount substracted from INITIAL_DUTY when correcting trajectory **/
#define DELTA_DUTY 8  //5
/** Precisision of the angle when rotating (in degrees) **/
#define ANGLE_PRECISION 1 //5
/** Precision of the distance when moving to a point (in mm) **/
#define PRECISION 5

/** Amount of time we sleep before updating rotation again **/
#define SLEEP_ROTATION 25 //200

/** Amount of time we sleep before updating position again **/
#define SLEEP_POSITION 20//100

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

/** Initialize rotation of the robot
  * @author Virgile Retault **/
void init_rotation(void);

/** Initializes the motion systme
  * Returns false in case of an error
  * @author Virgile Retault **/
bool motion_init(void);

/** Stop the robot
  * @author Virgile Retault **/
void stop_robot(void);

/** Rotate to target then move to target in a straight-ish line
  * @author Virgile Retault **/
void rotate_move_to(Vector target);

/** Move to target in a straight-ish line
  * @author Virgile Retault **/
void move_to(Vector target);

/** Rotate the robot to face a given point
  * @author Virgile Retault **/
void rotate_to(Vector target);

/** Rotate the robot by given angle
  * Angle should be in [-180, 180]
  * @author Virgile Retault **/
void rotate(int angle);

/** Go forward by a given distance
  * @author Virgile Retault **/
void foward(double distance);


/* @author Mathieu CHAMPION */
void aller_tout_droit(int time);
void coup_vener(void);
void correct_rotation(void);
#endif // MOTION_H
