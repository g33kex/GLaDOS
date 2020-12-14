#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define PI 3.14159265
#define abs(x) (x>=0?x:-(x))
#define sign(x) (x>=0?1:-1)
#define radians(x) ((PI*((float)x))/180)
#define degrees(x) ((180*(x))/PI)

typedef struct {
    int x;
    int y;
} Vector;

Vector vector_from_polar(int, int);

Vector vector_add(Vector, Vector);
Vector vector_sub(Vector, Vector);
int vector_dot(Vector, Vector);
int vector_det(Vector, Vector);

int vector_magnitude(Vector);
/** Gives angle between two vectors in range [0, 360] **/
int vector_angle2(Vector, Vector);

void test_vector(void);
#endif // VECTOR_H
