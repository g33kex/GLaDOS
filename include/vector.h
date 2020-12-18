#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define PI 3.1415926535
#define abs(x) (x>=0?x:-(x))
#define sign(x) (x>=0?1:-1)
#define radians(x) ((PI*(x))/180.0)
#define degrees(x) ((180.0*(x))/PI)

typedef struct {
    double x;
    double y;
} Vector;

/** Returns a vector from polar coordinate
  * Angle is between 0 and 360 **/
Vector vector_from_polar(double, double);

Vector vector_add(Vector, Vector);
Vector vector_sub(Vector, Vector);
double vector_dot(Vector, Vector);
double vector_det(Vector, Vector);

double vector_magnitude(Vector);
/** Gives angle between two vectors in range [-180, 180] **/
double vector_angle2(Vector, Vector);

void test_vector(void);
#endif // VECTOR_H
