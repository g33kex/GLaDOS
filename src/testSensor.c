#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"



int testColor(){
  printf("testing the get_color function\n");
  printf("%s\n",get_color());
  return 0;
}

int testIntensity(){
  printf("testing the get_intensity function\n");
  printf("%s\n",get_intensity());
  return 0;
}

int testDistance(){
  printf("testing the get_color function\n");
  printf( "%d \n", get_distance());
  return 0;
}

int testOrientation(){
  printf("testing the get_orientation function\n");
  printf("%d\n", get_orientation());

  return 0;
}
