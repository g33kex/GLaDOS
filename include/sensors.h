#ifndef SENSORS_H
#define SENSORS_H

#include <stdbool.h>
#include <stdint.h>

//Port 0
#define COMPASS_PORT 52

// Port 1
#define SONAR_PORT 49

//Port 2
#define GYRO_PORT 50
#define COLOR_FRONT_PORT 50 //ne devrait plus être utilisé
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
uint8_t sn_color_front; //ne devrait plus être utilisé
uint8_t sn_color_pince;


/* Functions */

/** Initializes the sensor system
  * Returns false in case of an error **/
bool sensor_init(void);

/*give color [NE SERT PLUS]*/
const char * get_color();


/*check there is a ball in the hand*/
bool is_ball_in_hand();


/** Gives the intensity of the light
  * Return intensity between 0 and 100%  **/
int get_intensity();

/* give distance in mm*/
int get_distance();

/*gives orientation*/
int get_orientation();

/** Calibrate the compass **/
void calibrate_compass();

/** Initializes the compass such has current orientation is the new North
  * Returns false in case of an error **/
bool set_orientation(int orientation);

/* retourne la rotation totale du robot par rapport à l'angle initiale (lors de l'allumage)*/
int get_gyro();

/** Returns rotation of the gyroscope since last call of the function **/
int get_gyro_delta();


#endif // SENSORS_H
