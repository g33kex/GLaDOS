#include "motion.h"
int main(void) {
    if(!motion_init())
        return -1;
    robot_move(1);
    return 0;
}
