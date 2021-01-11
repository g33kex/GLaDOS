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


int move_robot_to_random_cube(){
  int distance_attendue = 20000; //a trouver par dichotomie
  bool cubeFound = false;
  int posRech[6][2] = {{110 , 80},
                       {100 , 80},
                       {90 , 80},
                       {30 , 60},
                       {20 , 60},
                       {10 , 60}};
 int i = 0;
  while(!cubeFound){
    //TODO prendre en compte que le cube random peut etre en haut de la zone de gauche
    //aller à (posRech[i][0],posRech[i][1]), direction sud
    printf("distance detectée : %d\n, distance attendue : %d",get_distance(), distance_attendue );
    if (get_distance() < distance_attendue){
      printf("CUBE FOUND !\n");
      cubeFound = true;
    }
    else {
      if(i = 6){
      printf("CUBE NOT FOUND !\n");
      return 0;
      }
    }
  }

  //une fois qu'il a trouvé le cube, il va sur le téco pour bien trouver l'autre position ?


  if (cubeFound) {
    //s'approcher du cube
    //tourner pour detecter le coin
    //setRandomCubePosition(.....)

    return 1;
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
    aller_tout_droit(ecart_de_distance * 10 + 200); //idemit(ecart_de_distance * 10 + 200);
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
    sleep(5000);
    printf("%d\n",get_distance());

  }
}


int test_gyro(){
   printf("angle de get_gyro function : %d\n",get_gyro());
   return 0;
}
