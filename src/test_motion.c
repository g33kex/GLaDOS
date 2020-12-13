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
   // robot_pos.p.x=153;
   // robot_pos.p.y=45;
    //Vector target = (Vector) {150,50};
//    rotate_to(target);
    //Vector target = (Vector) {200,0};
    //rotate_move_to(target);
    Vector target = (Vector) {850, 1650};
    rotate_move_to(target);
    Sleep ( 1000 );
    //target = (Vector) {0, 200};
    //rotate_move_to(target);
   // target = (Vector) {0,0};
   //rotate_move_to(target);
    //Vector target = (Vector) {100, 150}; 
    //rotate_move_to(target);

    printf("test_motion passed\n");
    return true;
}
