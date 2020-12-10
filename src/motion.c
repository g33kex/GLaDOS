#include "motion.h"

#include <stdio.h>
#include <unistd.h>

#include "ev3_sensor.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

/* Private functions */

static void init_motor(uint8_t motor) {
    set_tacho_stop_action_inx(motor, TACHO_HOLD);
}

static void calibrate_compass() {
    set_sensor_command(sn_compass, "END-CAL");
    set_sensor_command(sn_compass, "BEGIN-CAL");

    set_tacho_duty_cycle_sp(left_wheel, -INITIAL_DUTY);
    set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY);

    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);

    Sleep ( 40000 );

    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
    set_sensor_command(sn_compass, "END-CAL");
}

// Return rotation of the robot in standard angle convention...
static int get_correct_orientation() {
    int rot = get_orientation();
    return rot==0?0:360-rot;
}

/*static int angle_to_point(Point target) {
        int deltax=target.x-robot_pos.p.x;
        int deltay=target.y-robot_pos.p.y;
        int robot_angle = robot_pos.rotation==0?0:360-robot_pos.rotation;
        int target_angle = (360+(int)degrees(atan2(deltax,deltay)))%360;
        int angle = (360+target_angle-robot_angle)%360;
        angle = angle>180?-angle+360:-angle;

        printf("robot_angle %d target_angle %d angle %d\n", robot_angle, target_angle, angle);
        printf("Angle = %d\n",angle);

  
        return angle;
}*/

/* Functions implementation */



bool move_to(Vector target) {

    /* Temporary */
    //set_orientation(0); //Temporary, should be relative to TP room
    robot_pos.rotation = 0;
    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);

    //calibrate_compass();
    //return false;
    Sleep ( 1000 );

    /* Rotate to face the target */
    //rotate_to(target);

    /* Move to the target */
    // Initialize previous wheel encoder pos
    set_tacho_position(left_wheel, 0);
    set_tacho_position(right_wheel, 0);
    int right_wheel_previous_pos=0;
    int left_wheel_previous_pos=0;

    // Start the motors
    set_tacho_duty_cycle_sp(left_wheel, INITIAL_DUTY);
    set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY);
    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);

    while(vector_magnitude(vector_sub(target, robot_pos.p))>=5) {
        printf("Distance : %d\n",vector_magnitude(vector_sub(target, robot_pos.p)));
        Sleep ( 400 );
        // Update rotation
        robot_pos.rotation = get_correct_orientation();

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

        //odometry_theta = (r-l)*WHEEL_CIRCUMFERENCE/(360*WHEEL_DISTANCE);

        // Update robot position
        Vector motion = {meanDistance*cos(radians(robot_pos.rotation)), meanDistance*sin(radians(robot_pos.rotation))};
        robot_pos.p = vector_add(robot_pos.p,motion);
        printf("New position : (%d, y:%d), rotation:%d\n", robot_pos.p.x, robot_pos.p.y, robot_pos.rotation);
        
        // Compute angle to target
        Vector direction = vector_from_polar(100, robot_pos.rotation);
        int angle = vector_angle2(direction, vector_sub(target, robot_pos.p));
        printf("Direction : (%d, %d)\n", direction.x, direction.y);
        printf("Angle : %d\n", angle);

        if(angle < 0) {
            set_tacho_duty_cycle_sp(left_wheel, INITIAL_DUTY);
            set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY/2);
        }
        else if(angle > 0) {
            set_tacho_duty_cycle_sp(left_wheel, INITIAL_DUTY/2);
            set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY);
        }
        else {
            set_tacho_duty_cycle_sp(left_wheel, INITIAL_DUTY);
            set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY);
        }

         
    }
    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
    return true;
}


bool rotate_to(Vector target) {
    int angle = 0;

    //angle = angle_to_point(target);
    if(angle>0) {
        set_tacho_duty_cycle_sp(left_wheel, -INITIAL_DUTY);
        set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY);
    } else if(angle<0) {
        set_tacho_duty_cycle_sp(left_wheel, INITIAL_DUTY);
        set_tacho_duty_cycle_sp(right_wheel, -INITIAL_DUTY);
    }
    else {
        return true;
    }

    set_tacho_command_inx(left_wheel, TACHO_RUN_DIRECT);
    set_tacho_command_inx(right_wheel, TACHO_RUN_DIRECT);

    while(angle!=0) {
        robot_pos.rotation=get_orientation();
        angle = 0;//angle_to_point(target);
        if(angle>0) {
            set_tacho_duty_cycle_sp(left_wheel, -INITIAL_DUTY);
            set_tacho_duty_cycle_sp(right_wheel, INITIAL_DUTY);
        } else if(angle<0) {
            set_tacho_duty_cycle_sp(left_wheel, INITIAL_DUTY);
            set_tacho_duty_cycle_sp(right_wheel, -INITIAL_DUTY);
        }
    }
    set_tacho_command_inx(left_wheel, TACHO_STOP);
    set_tacho_command_inx(right_wheel, TACHO_STOP);
    return true;
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
