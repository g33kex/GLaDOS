#ifndef SENSORS_H
#define SENSORS_H

#include <stdbool.h>
#include <stdint.h>

#include "motion.h"
#include "grab.h"

//Port 0
#define COMPASS_PORT 52

// Port 1
#define SONAR_PORT 49
//Port 2
#define GYRO_PORT 50
#define COLOR_PORT 50 //unused
//Port 3
#define COLOR_PINCE_PORT 51


/* Structures*/
typedef enum Color Color;
enum Color
{
   UNKNOW, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN
};


/* Variables */
uint8_t sn_compass;
uint8_t sn_sonar;
uint8_t sn_gyro;
uint8_t sn_color_front; //unused
uint8_t sn_color_pince;


/* Functions */

/** Initializes the sensor system
  * Returns false in case of an error
  * @author Mathieu CHAMPION**/
bool sensor_init(void);

/** give color
  * @author Mathieu CHAMPION **/
const char * get_color();


/** check there is a ball in the hand
  * @author Mathieu CHAMPION **/
bool is_ball_in_hand();


/** Gives the intensity of the light
  * Return intensity between 0 and 100%
  * @author Mathieu CHAMPION**/
int get_intensity();

/** give distance in mm
  * @author Mathieu CHAMPION**/
int get_distance();

/**gives orientation relative to north
  * @author Mathieu CHAMPION**/
int get_orientation();

/** Calibrate the compass
  * @author Virgile Retault **/
void calibrate_compass();

/** Initializes the compass such has current orientation is the new North
  * Returns false in case of an error
  * @author Mathieu CHAMPION **/
bool set_orientation(int orientation);

/** gives the total rotation relative to the robot to start
  * @author Mathieu CHAMPION**/
int get_gyro();

/** Returns rotation of the gyroscope since last call of the function
  * @author Virgile Retault **/
int get_gyro_delta();

/** search the random cube and go to it (to find ball afterwards)
  * @author Mathieu CHAMPION **/
int move_robot_to_random_cube();

/** move close enough to the pyramid and drop the ball in it !
  * @author Mathieu CHAMPION **/
int drop_ball_in_pyramid();

/** move close enough to the cube and grab a ball in it
  * @author Mathieu CHAMPION **/
int grab_ball_in_cube();


#endif // SENSORS_H
