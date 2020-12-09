#ifndef SENSORS_H
#define SENSORS_H

#include <stdbool.h>
#include <stdint.h>

//Port 0
#define COMPASS_PORT 49

// Port 1
#define SONAR_PORT 50

//Port 2
#define COLOR_FRONT_PORT 51

//Port 3
#define COLOR_PINCE_PORT 52


/* Structures*/
typedef enum Color Color;
enum Color
{
   UNKNOW, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN
};




/* Variables */
uint8_t sn_compass;
uint8_t sn_sonar;
uint8_t sn_color_front;
uint8_t sn_color_pince;



/* Functions */

/** Initializes the sensor system
  * Returns false in case of an error **/
bool sensor_init(void);


const char * get_color();

/** Gives the intensity of the light
  * Return intensity between 0 and 100%  **/
int get_intensity();
//const enum Color * get_color();

int get_distance();
int get_orientation();


#endif // SENSORS_H
