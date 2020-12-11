#include "test_motion.h"

#include "motion.h"
#include "sensors.h"

#include <stdio.h>

bool test_motion() {
    if(!motion_init() || !sensor_init()) {
        printf("test_motion failed at motion_init() or sensors_init()\n");
        return false;
    }
    Vector target = (Vector) {0,500};
    move_to(target);
    printf("test_motion passed\n");
    return true;
}
