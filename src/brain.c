#include "brain.h"

void run(void) {
    printf("Starting world domination sequence\n");
    Vector dir = (Vector) {500, 0};
    rotate_move_to(dir);
    dir = (Vector) {500, -200};
    rotate_to(dir);
    grab_ball_in_cube();
    dir = (Vector) {300, 0};
    rotate_move_to(dir);
    dir = (Vector) {300, 200};
    rotate_to(dir);
    drop_ball_in_pyramid();
    dir = (Vector) {500, 0};
    rotate_move_to(dir);
    dir = (Vector) {500, -200};
    rotate_to(dir);
    grab_ball_in_cube();
    Sleep(5000);
    dir = (Vector) {300, 0};
    rotate_move_to(dir);
    dir = (Vector) {300, 200};
    rotate_to(dir);
    drop_ball_in_pyramid();
}
