#include "test_motion.h"

#include "motion.h"
#include "sensors.h"

#include <stdio.h>
#include <unistd.h>

bool test_motion() {
    if(!motion_init() || !sensor_init()) {
        printf("test_motion failed at motion_init() or sensors_init()\n");
        return false;
    }
    //set_orientation(get_orientation());
    init_rotation();
   // robot_pos.p.x=153;
   // robot_pos.p.y=45;
//    rotate_to(target);
    //Vector target = (Vector) {200,0};
    //rotate_move_to(target);
    //Vector target = (Vector) {850, 1650};
    //Sleep ( 1000 );
    //target = (Vector) {0, 200};
    //rotate_move_to(target);
    //Vector target = (Vector) {100, 150}; 
    //rotate_move_to(target);

    /*Vector target = (Vector) {85,165};
    rotate_move_to(target);
    target = (Vector) {0,0};
    rotate_move_to(target);*/

    /*Vector target = (Vector) {0, 200};
    rotate_move_to(target);
    target = (Vector) {200,200};
    rotate_move_to(target);
    target = (Vector) {200,0};
    rotate_move_to(target);
    target = (Vector) {0,0};
    rotate_move_to(target);*/

    /** Go north and come back **/
    Vector target = (Vector) {200, 0};
    rotate_move_to(target);
    target = (Vector) {0, 0};
    rotate_move_to(target);


    printf("test_motion passed\n");
    return true;
}

bool test_rotation() {

    rotate(10);
    return true;
}
