#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"



int testColor(){
  printf("get_color function : %s\n",get_color());
  return 0;
}

int testIntensity(){
  printf("get_intensity function : %d\n",get_intensity());

  return 0;
}

int testDistance(){
  printf("get_distance function : %d \n", get_distance());
  return 0;
}

int testOrientation(){
  printf("get_orientation function :%d\n", get_orientation());

  return 0;
}
