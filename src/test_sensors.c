#include <stdio.h>
#include <unistd.h>

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
  initialOrientation = robot_pos.rotation ;
  while (!cubeFound &&  ) {
    rotate_to
    update_rotation();
    if (!strcmp("BLUE", get_color())){
      cubeFound = true;
    }
  }
  if (cubeFound) {
    printf("CUBE FOUND ! Going to cube\n", );
    while(get_distance() > 50){ //50mm, peut être moi, peut être plus
      move_to()
    }
    printf("INCH WE ARE CLOSE TO THE RANDOM CUBE NOW\n", );
    return 1;
  } else {
    printf("CUBE NOT FOUND\n", );
    return 0;
  }

}
