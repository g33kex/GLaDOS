#include "brain.h"

void run(void) {
    printf("Starting world domination sequence\n");
    lift();
    pick_and_place_normal();
    pick_and_place_normal();
    pick_and_place_normal();
    pick_and_place_normal();



    // Vector dir = (Vector) {500, 0};
    // rotate_move_to(dir);
    // dir = (Vector) {500, -200};
    // rotate_to(dir);
    // grab_ball_in_cube();
    // dir = (Vector) {300, 0};
    // rotate_move_to(dir);
    // dir = (Vector) {300, 200};
    // rotate_to(dir);
    // drop_ball_in_pyramid();
    // dir = (Vector) {500, 0};
    // rotate_move_to(dir);
    // dir = (Vector) {500, -200};
    // rotate_to(dir);
    // grab_ball_in_cube();
    // Sleep(5000);
    // dir = (Vector) {300, 0};
    // rotate_move_to(dir);
    // dir = (Vector) {300, 200};
    // rotate_to(dir);
    // drop_ball_in_pyramid();
}

void pick_and_place_normal(){

  Vector dir = (Vector) {1725, 600};
  rotate_move_to(dir);
  dir = (Vector) {1725, 350};
  rotate_to(dir);


  grab_ball_in_cube();
  dir = (Vector) {875, 600};
  rotate_move_to(dir);
  Sleep(5000);
  dir = (Vector) {875, 850};
  rotate_to(dir);
  Sleep(5000);
  correct_rotation();
  printf("ROTATE CORRIGE\n");
  drop_ball_in_pyramid();
}

void pick_and_place_random(){
  //TODO
}
