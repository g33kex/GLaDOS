#include "vector.h"

#include <stdio.h>

Vector vector_from_polar(int magnitude, int angle) {
    float theta = radians(angle);
    return (Vector) {magnitude*cos(theta), magnitude*sin(theta)};
}

Vector vector_add(Vector v1, Vector v2) {
    return (Vector) {v1.x+v2.x, v1.y+v2.y};
}

Vector vector_sub(Vector v1, Vector v2) {
    return (Vector) {v1.x-v2.x, v1.y-v2.y};
}

int vector_dot(Vector v1, Vector v2) {
    return v1.x*v2.x+v1.y*v2.y;
}

int vector_det(Vector v1, Vector v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

int vector_magnitude(Vector v) {
    return sqrt(vector_dot(v,v));
}

int vector_angle2(Vector v1, Vector v2) {
    return degrees(atan2(vector_det(v1, v2), vector_dot(v1, v2)));
}

void test_vector(void) {
/*    Vector target = {0, 500};
    Vector rpos = {-81, 34};
    int rrot = 53;*/
    Vector target = {0, 0};
    Vector rpos = {153, 45};
    int rrot = 254;
    Vector direction = vector_from_polar(100, rrot);
    printf("Direction : (%d,%d)\n", direction.x, direction.y);
    Vector second = vector_sub(target, rpos);
    printf("Second : (%d,%d)\n", second.x, second.y);
    int angle = vector_angle2(direction, second);
    printf("Angle : %d\n", angle);
}
