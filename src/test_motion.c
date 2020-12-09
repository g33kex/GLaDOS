#include "test_motion.h"

#include "motion.h"
#include "sensors.h"

#include <stdio.h>

int main(void) {
    return test_motion();
}

bool test_motion() {
    if(!motion_init() || !sensor_init()) {
        printf("test_motion failed at motion_init() or sensors_init()\n");
        return false;
    }
    /*robot_move(100);
    robot_move(-100);
    robot_move(100);
    robot_move(-100);*/
    //test_dynamic_wheel();
    //robot_move(-10);
    //y + = NORTH
    Point target = (Point) {150,0};
    move_to(target);
    printf("test_motion passed\n");
    return true;
}
