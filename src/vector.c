#include "vector.h"

#include <stdio.h>

Vector vector_from_polar(double magnitude, double angle) {
    double theta = radians(angle);
    return (Vector) {magnitude*cos(theta), magnitude*sin(theta)};
}

Vector vector_add(Vector v1, Vector v2) {
    return (Vector) {v1.x+v2.x, v1.y+v2.y};
}

Vector vector_sub(Vector v1, Vector v2) {
    return (Vector) {v1.x-v2.x, v1.y-v2.y};
}

double vector_dot(Vector v1, Vector v2) {
    return v1.x*v2.x+v1.y*v2.y;
}

double vector_det(Vector v1, Vector v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

double vector_magnitude(Vector v) {
    return sqrt(vector_dot(v,v));
}

double vector_angle2(Vector v1, Vector v2) {
    return degrees(atan2(vector_det(v1, v2), vector_dot(v1, v2)));
}

/*
static void test_update_position() {
    update_rotation();
    printf("Old position : (%d, %d)\n", robot_pos.p.x, robot_pos.p.y);
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
    printf("Crossed %d at rotation %d\n",meanDistance, robot_pos.rotation);
//      int odometry_theta = (r-l)*WHEEL_CIRCUMFERENCE/(360*WHEEL_DISTANCE);
    // Update robot position
    //Vector motion = {meanDistance*cos(radians(robot_pos.rotation)), meanDistance*sin(radians(robot_pos.rotation))};
    //It seems the position needs to be updated in reverse..
    Vector motion = {meanDistance*sin(radians(robot_pos.rotation)), meanDistance*cos(radians(robot_pos.rotation))};
    robot_pos.p = vector_add(robot_pos.p,motion);
    printf("New position : (%d, %d), rotation:%d\n", robot_pos.p.x, robot_pos.p.y, robot_pos.r
    */


void test_vector(void) {
    /*Vector target = {0, 500};
    Vector rpos = {-81, 34};
    int rrot = 53;*/
  //  Vector target = {0, 0};
   // Vector rpos = {153, 45};
   // int rrot = 254;
    Vector target = {-59, -128};
    Vector rpos = {-110, -45};
    int rrot = 185;
    Vector direction = vector_from_polar(100, rrot);
    printf("Direction : (%f,%f)\n", direction.x, direction.y);
    Vector second = vector_sub(target, rpos);
    printf("Second : (%f,%f)\n", second.x, second.y);
    double angle = vector_angle2(direction, second);
    printf("Angle : %f\n", angle);

}

