#include "motion.h"

#include <stdio.h>
#include <unistd.h>

#include "ev3_sensor.h"

/* Private variables */
static int right_wheel_previous_pos = 0;
static int left_wheel_previous_pos = 0;

/* Private functions */

static void init_motor(uint8_t motor) {
    set_tacho_stop_action_inx(motor, TACHO_HOLD);
}

static void start_motors() {
    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);
}

static void stop_motors() {
    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
}

static void set_motors_duty(int duty_left, int duty_right) {
    set_tacho_duty_cycle_sp(left_wheel, duty_left);
    set_tacho_duty_cycle_sp(right_wheel, duty_right);
}


// Return rotation of the robot in standard angle convention...
static int get_correct_orientation() {
    int rot = get_orientation();
    return rot==0?0:360-rot;
}

/** Update the rotation of the robot using compass **/
static void update_rotation() {
    robot_pos.rotation = get_correct_orientation();

}
/** Update the position of the robot using compass odometry **/
static void update_position() {
    update_rotation();

    // Update encoder position and compute distance
    int l;
    int r;
    get_tacho_position(left_wheel, &l); 
    get_tacho_position(right_wheel, &r);
    int SR = (r-right_wheel_previous_pos)*WHEEL_CIRCUMFERENCE/360;
    int LR = (l-left_wheel_previous_pos)*WHEEL_CIRCUMFERENCE/360;
    right_wheel_previous_pos = r;
    left_wheel_previous_pos = l;
    int meanDistance = (SR+LR)/2;

//      int odometry_theta = (r-l)*WHEEL_CIRCUMFERENCE/(360*WHEEL_DISTANCE);

    // Update robot position
    //Vector motion = {meanDistance*cos(radians(robot_pos.rotation)), meanDistance*sin(radians(robot_pos.rotation))};
    //It seems the position needs to be updated in reverse..
    Vector motion = {meanDistance*sin(radians(robot_pos.rotation)), meanDistance*cos(radians(robot_pos.rotation))};
    robot_pos.p = vector_add(robot_pos.p,motion);

    printf("New position : (%d, y:%d), rotation:%d\n", robot_pos.p.x, robot_pos.p.y, robot_pos.rotation);
}



/* Functions implementation */
void calibrate_compass() {
    printf("Calibrating compass...\n");
    set_sensor_command(sn_compass, "END-CAL");
    set_sensor_command(sn_compass, "BEGIN-CAL");

    set_tacho_duty_cycle_sp(left_wheel, -INITIAL_DUTY*2);
    set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY*2);

    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);

    Sleep ( 40000 );

    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
    set_sensor_command(sn_compass, "END-CAL");
}

void stop_robot() {
    stop_motors();
}

void rotate_move_to(Vector target) {
    rotate_to(target);
    move_to(target);
}

void move_to(Vector target) {
    // Initialize previous wheel encoder pos
    set_tacho_position(left_wheel, 0);
    set_tacho_position(right_wheel, 0);
    right_wheel_previous_pos=0;
    left_wheel_previous_pos=0;

    // Start the motors
    set_motors_duty(INITIAL_DUTY, INITIAL_DUTY);
    start_motors();

    while(vector_magnitude(vector_sub(target, robot_pos.p))>=50) {
        printf("Distance : %d\n",vector_magnitude(vector_sub(target, robot_pos.p)));
        Sleep ( 100 );
        
        // Update robot position using odometry and compass
        update_position();

        // Compute angle to target
        Vector direction = vector_from_polar(100, robot_pos.rotation);
        int angle = vector_angle2(direction, vector_sub(target, robot_pos.p));
        printf("Direction : (%d, %d)\n", direction.x, direction.y);
        printf("Angle : %d\n", angle);

        if(angle < 0) { // Turn Right
            set_motors_duty(INITIAL_DUTY, INITIAL_DUTY-2);
        }
        else if(angle > 0) { // Turn Left
            set_motors_duty(INITIAL_DUTY-2, INITIAL_DUTY);
        }
        else { // Go Straight
            set_motors_duty(INITIAL_DUTY, INITIAL_DUTY);
        }
    }
    stop_motors();
}


void rotate_to(Vector target) {
    set_motors_duty(0,0);
    start_motors();

    int angle;
    do {
        Sleep ( 200 );
        update_rotation();
        Vector direction = vector_from_polar(100, robot_pos.rotation);
        angle = vector_angle2(direction, vector_sub(target, robot_pos.p));
        printf("Robot angle : %d\n",robot_pos.rotation);
        printf("Direction : (%d, %d)\n", direction.x, direction.y);
        printf("Angle : %d\n", angle);

        if(angle>0) {
            set_motors_duty(-INITIAL_DUTY, INITIAL_DUTY);
        } else if(angle<0) {
            set_motors_duty(INITIAL_DUTY, -INITIAL_DUTY);
        }
    } while(abs(angle)>10);

    stop_motors();
}


bool motion_init(void) {
    robot_pos = (Position) {{0,0},0};

    printf("Running tacho init\n");
    if(ev3_tacho_init()==-1)
        return false;
    printf("Searching for left motor\n");
    if(!ev3_search_tacho_plugged_in(LEFT_WHEEL_PORT, 0, &left_wheel, 0))
        return false;
    printf("Searching for right motor\n");
    if(!ev3_search_tacho_plugged_in(RIGHT_WHEEL_PORT, 0, &right_wheel, 0))
        return false;

    init_motor(left_wheel);
    init_motor(right_wheel);
    return true;
}
