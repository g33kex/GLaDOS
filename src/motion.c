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


/** Update the rotation of the robot using compass and gyroscope **/
static void update_rotation() {
    double k = GYRO_TRUST_RATIO;
    int gyro_rot = get_gyro_delta();
    int compass_rot = get_orientation();
    robot_pos.rotation += gyro_rot;
    printf("Robot rotation = %d Compass rotation = %d\n", robot_pos.rotation, compass_rot);
    if((compass_rot - robot_pos.rotation) > 180 || (compass_rot - robot_pos.rotation) < -180 ){
      printf("[-] RECALIBRATING COMPASS AND GYRO\n");
      if(compass_rot > robot_pos.rotation) {
        robot_pos.rotation += 360;
      } else {
        compass_rot += 360;
      }
    }
    robot_pos.rotation = (robot_pos.rotation*k) + (compass_rot*(1.0-k));
    robot_pos.rotation = robot_pos.rotation%360;

}
/** Update the position of the robot using compass odometry **/
static void update_position() {
    update_rotation();
    printf("Old position : (%f, %f)\n", robot_pos.p.x, robot_pos.p.y);

    // Update encoder position and compute distance
    int l;
    int r;
    get_tacho_position(left_wheel, &l);
    get_tacho_position(right_wheel, &r);
    double SR = ((r-right_wheel_previous_pos)*WHEEL_CIRCUMFERENCE)/360.0;
    double LR = ((l-left_wheel_previous_pos)*WHEEL_CIRCUMFERENCE)/360.0;
    right_wheel_previous_pos = r;
    left_wheel_previous_pos = l;
    double meanDistance = (SR+LR)/2;


    //int odometry_theta = (r-l)*WHEEL_CIRCUMFERENCE/(360*WHEEL_DISTANCE);
    //robot_pos.rotation=(robot_pos.rotation+odometry_theta)%360;

    printf("Crossed %f at rotation %d\n",meanDistance, robot_pos.rotation);
    // Update robot position
    //Vector motion = {meanDistance*cos(radians(robot_pos.rotation)), meanDistance*sin(radians(robot_pos.rotation))};
    //It seems the position needs to be updated in reverse..
    Vector motion = {meanDistance*cos(radians(robot_pos.rotation)), meanDistance*sin(radians(robot_pos.rotation))};
    robot_pos.p = vector_add(robot_pos.p,motion);

    printf("New position : (%f, %f), rotation:%d\n", robot_pos.p.x, robot_pos.p.y, robot_pos.rotation);
}



/* Functions implementation */


void stop_robot() {
    stop_motors();
}

void rotate_move_to(Vector target) {
    rotate_to(target);
    Sleep(200);
    move_to(target);
}

void foward(double distance) {
  if(distance > 0){
    move_to(vector_add(robot_pos.p, vector_from_polar(distance, robot_pos.rotation)));
  } else {
    distance = -distance;
    rotate_move_to(vector_sub(robot_pos.p, vector_from_polar(distance, robot_pos.rotation)));
  }
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

    int ancienne_distance;
    bool distance_diminue = true;
    while(vector_magnitude(vector_sub(target, robot_pos.p))>=PRECISION  && distance_diminue) {
        printf("Distance : %f\n",vector_magnitude(vector_sub(target, robot_pos.p)));
        Sleep ( SLEEP_POSITION );


        ancienne_distance = vector_magnitude(vector_sub(target, robot_pos.p));
        // Update robot position using odometry and compass
        update_position();
        if(vector_magnitude(vector_sub(target, robot_pos.p)) > ancienne_distance){
          printf("[-] STOPPING ROBOT BECAUSE DISTANCE INCREASING\n");
          printf("Distance : %f\n",vector_magnitude(vector_sub(target, robot_pos.p)));
          distance_diminue = false;
        }

        // Compute angle to target
        Vector direction = vector_from_polar(100.0, robot_pos.rotation);
        double angle = vector_angle2(direction, vector_sub(target, robot_pos.p));
        printf("Direction : (%f, %f)\n", direction.x, direction.y);
        printf("Angle : %f\n", angle);

        if(angle < -ANGLE_PRECISION) { // Turn Right
            set_motors_duty(INITIAL_DUTY, INITIAL_DUTY-DELTA_DUTY);
            printf("TOURNE DROIT\n");
        }
        else if(angle > ANGLE_PRECISION) { // Turn Left
            set_motors_duty(INITIAL_DUTY-DELTA_DUTY, INITIAL_DUTY);
            printf("TOURNE GAUCHE\n");
        }
        else { // Go Straight
          printf("TOUT DROIT\n");
            set_motors_duty(INITIAL_DUTY, INITIAL_DUTY);
        }
    }
    stop_motors();
}


void rotate_to(Vector target) {
    set_motors_duty(0,0);
    start_motors();

    double angle;
    do {
        Sleep ( SLEEP_ROTATION );
        update_rotation();
        Vector direction = vector_from_polar(100.0, robot_pos.rotation);
        angle = vector_angle2(direction, vector_sub(target, robot_pos.p));
        printf("Robot angle : %d\n",robot_pos.rotation);
        printf("Direction : (%f, %f)\n", direction.x, direction.y);
        printf("Angle : %f\n", angle);

        if(angle>0) {
            set_motors_duty(-ROTATE_DUTY, ROTATE_DUTY);
        } else if(angle<0) {
            set_motors_duty(ROTATE_DUTY, -ROTATE_DUTY);
        }
    } while(abs(angle)>ANGLE_PRECISION);

    stop_motors();
}

void rotate(int angle) {
    printf("Angle=%d\n", angle);
    update_rotation();
    set_motors_duty(0,0);
    start_motors();

    do {
        Sleep ( SLEEP_ROTATION );
        int old_rotation = robot_pos.rotation;
        update_rotation();
        printf("Angle : %d, old_rotation: %d, rotation: %d\n", angle, old_rotation, robot_pos.rotation);
        angle=(angle-(robot_pos.rotation-old_rotation))%360;
        printf("Angle : %d, old_rotation: %d, rotation: %d\n", angle, old_rotation, robot_pos.rotation);

        if(angle>0) {
            set_motors_duty(-ROTATE_DUTY, ROTATE_DUTY);
        } else if(angle<0) {
            set_motors_duty(ROTATE_DUTY, -ROTATE_DUTY);
        }
    } while(abs(angle)>ANGLE_PRECISION);

    stop_motors();
}

void init_rotation(void) {
    robot_pos.rotation=get_orientation();
}

bool motion_init(void) {
    robot_pos = (Position) {{50,600},0};

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





void tourner_un_peu(){
  set_motors_duty(0,0);
  start_motors();
  Sleep ( 250 );
  update_rotation();
  set_motors_duty(-INITIAL_DUTY, INITIAL_DUTY);
  Sleep( 1000 );
  stop_motors();
}

void aller_tout_droit(int time ){

  // Initialize previous wheel encoder pos
  set_tacho_position(left_wheel, 0);
  set_tacho_position(right_wheel, 0);
  right_wheel_previous_pos=0;
  left_wheel_previous_pos=0;
  // Start the motors
  if(time > 0){
    set_motors_duty(INITIAL_DUTY, INITIAL_DUTY); //20 et 17

  } else {
    set_motors_duty(-INITIAL_DUTY, -INITIAL_DUTY);
    time = -time;
  }

  start_motors();

  Sleep ( time );

  // Update robot position using odometry and compass
  //update_position();
  //Sleep( time );

  stop_motors();
  update_position();
}

void coup_vener(){
  // Initialize previous wheel encoder pos
  set_tacho_position(left_wheel, 0);
  set_tacho_position(right_wheel, 0);
  right_wheel_previous_pos=0;
  left_wheel_previous_pos=0;

  // Start the motors

    set_motors_duty(-80 , -80);


  start_motors();

  Sleep ( 300 );

  // Update robot position using odometry and compass
  update_position();

  stop_motors();

}

void correct_rotation(){
  rotate(robot_pos.rotation - get_orientation());
  printf("ORIENTATION GYRO : %d  COMAPSS %d \n",robot_pos.rotation,get_orientation() );
}
