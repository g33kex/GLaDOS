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
  // Vector researchPoint = (Vector) {60,40};
  // void move_to(researchPoint);
  //aller_tout_droit( 5000 );
  printf("researchPoint atteint !!!\n");
  bool cubeFound = false;
  int i;
  //Vector target;
  for (i = 0; i < 35 && !cubeFound ; ++i  ) { //on lui fait faire 35 petites rotations sauf s'il trouve le cube avant
    printf("rotation number %d\n",i);
    // target = vector_add(vector_from_polar(50, i *10),researchPoint);
    // rotate_to(target);
    tourner_un_peu();
    printf("couleur detectée : %s\n",get_color() );
    printf("distance detectée : %d\n",get_distance() );
    if (!strcmp("BLUE", get_color()) || get_distance() < 100){
      cubeFound = true;
    }
  }
  if (cubeFound) {
    //int angle = i * 10;
    printf("CUBE FOUND ! Going to cube\n");
    //int magnitude = 150;
    while(get_distance() > 80){ //100mm, peut être moi, peut être plus
      // target = vector_from_polar(magnitude,angle);
      // move_to(target);
      // magnitude = magnitude + 50;
      aller_tout_droit(1500);
      printf("distance du cube : %d\n",get_distance() );
    }
    printf("INCH WE ARE CLOSE TO THE RANDOM CUBE NOW\n");
    return 1;
  } else {
    printf("CUBE NOT FOUND\n");
    return 0;
  }

}

int drop_ball_in_pyramid(){
  //int distance_to_pyramid = get_distance();
  int ecart_pince_US_sensor = 80; //à adapter
  int distance_a_atteindre = ecart_pince_US_sensor  - 40 - 40; //
  int current_distance = get_distance();
  int ecart_de_distance = current_distance - distance_a_atteindre;
  printf("distance du cube : %d\n",get_distance() );
  if(ecart_de_distance > 0){
    printf("il faut avancer le robot de %d mm\n",ecart_de_distance );
    aller_tout_droit(ecart_de_distance * 10 + 200);
    printf("distance du cube : %d\n",get_distance() );
  } else {
    printf("il faut reculer le robot de %d mm\n",ecart_de_distance );
    //reculer_robot( 0 - ecart_de_distance)
  }


  open_hand();
  close_hand();


  return 1;

}



void test_sonar(){
  int i;
  for(i = 0 ; i < 35; ++i){
    rotate(10);
    sleep(500);
    printf("%d\n",get_distance());

  }
}
