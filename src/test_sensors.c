#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
#include "sensors.h"
#include "motion.h"
#include "grab.h"
#include "test_motion.h"
#include "test_sensors.h"

void tourner_un_peu();


// int testColor(){
//   printf("get_color function : %s\n",get_color());
//   return 0;
// }
//
// int testIntensity(){
//   printf("get_intensity function : %d\n",get_intensity());
//
//   return 0;
// }

int testDistance(){
  printf("get_distance function : %d \n", get_distance());
  return 0;
}

int testOrientation(){
  printf("get_orientation function :%d\n", get_orientation());

  return 0;
}


void test_sonar(){
  int i;
  for(i = 0 ; i < 35; ++i){
    rotate(10);
    sleep(5000);
    printf("%d\n",get_distance());

  }
}


int test_gyro(){
   printf("angle de get_gyro function : %d\n",get_gyro());
   return 0;
}
