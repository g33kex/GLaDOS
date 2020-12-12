#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"
#include "motion.h"


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


int move_robot_to_random_cube(){
  Vector researchPoint = (Vector) {60,40};
  void move_to(researchPoint);
  bool cubeFound = false;
  initialOrientation = robot_pos.rotation ; //should be 0 for the test6..
  int i;
  Vector target;
  for (i = 0; i < 35 && !cubeFound ; ++i  ) { //on lui fait faire 35 petites rotations sauf s'il trouve le cube avant
    target = vector_add(vector_from_polar(50, i *10),researchPoint)
    rotate_to(target);
    if (!strcmp("BLUE", get_color())){
      cubeFound = true;
    }
  }
  if (cubeFound) {
    int angle = i * 10;
    printf("CUBE FOUND ! Going to cube\n");
    int magnitude = 150;
    while(get_distance() > 50){ //50mm, peut être moi, peut être plus
      target = vector_from_polar(magnitude,angle);
      move_to(target);
      magnitude = magnitude + 50;
    }
    printf("INCH WE ARE CLOSE TO THE RANDOM CUBE NOW\n");
    return 1;
  } else {
    printf("CUBE NOT FOUND\n");
    return 0;
  }

}
