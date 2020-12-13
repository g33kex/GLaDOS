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
  printf("researchPoint atteint !!!\n");
  bool cubeFound = false;
  int initialOrientation = robot_pos.rotation ; //should be 0 for the test6..
  int i;
  Vector target;
  for (i = 0; i < 35 && !cubeFound ; ++i  ) { //on lui fait faire 35 petites rotations sauf s'il trouve le cube avant
    printf("zizi %d\n",i);
    target = vector_add(vector_from_polar(50, i *10),researchPoint);
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

int drop_ball_in_pyramid(){
  int distance_to_pyramid = get_distance();
  int ecart_pince_US_sensor = 80; //à adapter
  int distance_a_atteindre = ecart_pince_US_sensor  - 40 - 40; //
  int current_distance = get_distance();
  int ecart_de_distance = current_distance - distance_a_atteindre;
  if(ecart_de_distance > 0){
    printf("il faut avancer le robot de %d mm\n",ecart_de_distance );
    //avancer_robot(ecart_de_distance);
  } else {
    printf("il faut avancer le robot de %d mm\n",ecart_de_distance );
    //reculer_robot( 0 - ecart_de_distance)
  }


  open_hand();
  close_hand();


  return 1;

}
