#include <stdio.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_light.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "sensors.h"
#include "motion.h"
#include "test_motion.h"
#include "vector.h"

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
//const Color const *color[] = { UNKNOW, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN  };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

int orientation_zero = 0;
int last_gyro_rot = 0;

bool sensor_init(void) {
    if(ev3_sensor_init()==-1){
      printf("PB AVEC INIT\n");
      return false;
    }

    if(!ev3_search_sensor_plugged_in(COMPASS_PORT, 0, &sn_compass, 0)){
      printf("PB AVEC COMPASS\n");
      return false;
    }

    if(!ev3_search_sensor_plugged_in(SONAR_PORT, 0, &sn_sonar, 0)){
      printf("PB AVEC SONAR\n");
      return false;
    }
    if(!ev3_search_sensor_plugged_in(GYRO_PORT, 0, &sn_gyro, 0)){
      printf("PB AVEC ACCELEROMETRE\n");
      return false;
    }
    if(!ev3_search_sensor_plugged_in(COLOR_PINCE_PORT, 0, &sn_color_pince, 0)){
      printf("PB AVEC PINCE\n");
      return false;
    }
    last_gyro_rot=get_gyro();
    set_orientation(get_orientation());
    return true;
}



const char * get_color(){
  set_sensor_mode( sn_color_front, "COL-COLOR" );
  int val;
  if ( !get_sensor_value( 0, sn_color_front, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
      val = 0;
  }
  return color[ val ];
}


bool is_ball_in_hand(){
set_sensor_mode(sn_color_pince, "RGB-RAW" );

   int value;
   if ( !get_sensor_value( 0, sn_color_pince, &value )) {
       printf("[X]ERROR while reading intensity value\n");
       value = 0;
   }
   fflush( stdout );
   bool ballInHand = (bool) (value > 10);
   printf("Il y a une balle : %d, valeur = %d \n", ballInHand,value);
   return ballInHand;
}
// int get_intensity(){
//   set_sensor_mode( sn_color_front, "COL-REFLECT" );
//   int value;
//   if ( !get_sensor_value( 0, sn_color_front, &value )) {
//       printf("[X]ERROR while reading intensity value\n");
//       value = 0;
//   }
//   fflush( stdout );
//   return value;
// }

int get_distance(){
  set_sensor_mode( sn_sonar, "US-DIST-CM" );

  int value;
  if ( !get_sensor_value(0,sn_sonar, &value )) {
    printf("[X]ERROR while reading distance value\n");
    value = 0;
  }
  //printf("distance : %d\n", value );
  fflush( stdout );
  return (value);
}


void calibrate_compass() {
    printf("Calibrating compass...\n");
    set_sensor_command(sn_compass, "END-CAL");
    set_sensor_command(sn_compass, "BEGIN-CAL");

    set_tacho_duty_cycle_sp(left_wheel, 20);
    set_tacho_duty_cycle_sp(right_wheel, -20);

    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);

    Sleep ( 40000 );

    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
    set_sensor_command(sn_compass, "END-CAL");
}


int get_orientation(){

  int rot;
  if ( !get_sensor_value(0, sn_compass, &rot )) {
    printf("[X]ERROR while reading orientation value\n");
    rot = 0;
  }
  fflush( stdout );
//  printf("rot a la base %d\n",rot );
  rot = rot - orientation_zero;
  //printf("rot corrigé %d\n",rot );
  if(rot < 0) {
    rot = rot + 360;
  }
  //printf("rot recorrigé %d\n",rot );
  //printf("zero : %d, rot : %d\n",orientation_zero,rot);
  return rot==0?0:360-rot;
}

//  float value;
//  if (ev3_search_sensor(HT_NXT_COMPASS, &sn_compass,0)){
//      if ( !get_sensor_value0(sn_compass, &value )) {
//        value = 0;
//      }
//      fflush( stdout );
//      return (int) value;
//    }
//    return 0;
// }

bool set_orientation(int orientation){
  orientation_zero = (orientation==0?0:360-orientation);
  return true;

}

int get_gyro(){
  set_sensor_mode( sn_gyro, "GYRO-ANG" );

  int value;
  if ( !get_sensor_value(0,sn_gyro, &value )) {
    printf("[X]ERROR while reading gyro value\n");
    value = 0;
  }
  fflush( stdout );
  return  -value;
}

int get_gyro_delta() {
    int rot = get_gyro();
    int deltarot = rot - last_gyro_rot;
    last_gyro_rot = rot;
    return deltarot;
}



int move_robot_to_random_cube(){
  lift();
  int distance_attendue = 500; //a trouver par dichotomie
  bool cubeFound = false;
  int posRech[6][2] = {{0 , -400},
                       {0 , -200},
                       {0 , 200},
                       {0 , 400},
                       {20 , 60},
                       {10 , 60}};
 Vector newSpot;
 int i = 0;
  while(!cubeFound){
    //TODO prendre en compte que le cube random peut etre en haut de la zone de gauche
    //aller à (posRech[i][0],posRech[i][1]), direction sud
    printf("x : %d, y : %d\n", posRech[i][0],posRech[i][1]);

    newSpot = (Vector) {posRech[i][0],posRech[i][1]};
    printf("on move vers le new spot\n");
    rotate_move_to(newSpot);
    newSpot = (Vector) {100,posRech[i][1]};
    rotate_to(newSpot);



    printf("distance detectée : %d\n, distance attendue : %d",get_distance(), distance_attendue );
    Sleep(2000);
    if (get_distance() < distance_attendue){
      printf("CUBE FOUND !\n");
      cubeFound = true;
    }
    else {
      i++;
      if(i == 6){
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
  return 5;
}

int drop_ball_in_pyramid(){
  lift();
  close_hand();
  int distance_a_atteindre = 50; //
  int current_distance = get_distance();
  while(current_distance > distance_a_atteindre ||  current_distance < (distance_a_atteindre - 10)){
    if(current_distance == 2550) {break;} //pcq des fois y'a un bug
    printf("distance du cube : %d\n",current_distance );
    if(current_distance > distance_a_atteindre){
      if(current_distance - distance_a_atteindre < 20){break;}
      foward((double) (50));
    }else {
      aller_tout_droit(-500);
    }
    current_distance = get_distance();
    Sleep(500);
  }

  printf("distance du cube : %d\n",current_distance );

  open_hand();
  close_hand();
  //aller_tout_droit(-2000);
  //lower();
  return 1;

}

int grab_ball_in_cube(){
  lift();
  close_hand();
  int distance_a_atteindre = 50; //
  int current_distance = get_distance();
  while(current_distance > distance_a_atteindre && (current_distance - distance_a_atteindre > 20)  ){
    if(current_distance == 2550) {break;} //pcq des fois y'a un bug
    printf("distance du cube : %d\n",current_distance );
    foward((double) (current_distance - distance_a_atteindre));
    current_distance = get_distance();
    Sleep(500);
  }


  grab_with_retry();

  return 1;

}
