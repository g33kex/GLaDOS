#include "vector.h"

#include <stdio.h>

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

int main(void) {
    Vector v1 = {15, 0};
    Vector v2 = {-15, 0};
    int angle = vector_angle2(v1, v2);
    printf("Angle = %d\n", angle);

    return 0;
}
