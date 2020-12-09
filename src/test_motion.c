#include "test_motion.h"

#include "motion.h"

#include <stdio.h>

int main(void) {
    return test_motion();
}

bool test_motion() {
    if(!motion_init()) {
        printf("test_motion failed at motion_init()\n");
        return false;
    }
    /*robot_move(100);
    robot_move(-100);
    robot_move(100);
    robot_move(-100);*/
    test_dynamic_wheel();
    printf("test_motion passed\n");
    return true;
}
