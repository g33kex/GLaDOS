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
  * Angle is between 0 and 360 
  * @author Virgile Retault **/
Vector vector_from_polar(double, double);

/** Add two vectors
  * @author Virgile Retault **/
Vector vector_add(Vector, Vector);
/** Substract two vectors
  * @author Virgile Retault **/ 
Vector vector_sub(Vector, Vector);
/** Returns the dot product of two vectors
  * @author Virgile Retault **/ 
double vector_dot(Vector, Vector);
/** Returns the determinant of two vectors
  * @author Virgile Retault **/ 
double vector_det(Vector, Vector);

/** Returns the magnitude of a vector
  * @author Virgile Retault **/ 
double vector_magnitude(Vector);
/** Gives angle between two vectors in range [-180, 180]
  * @author Virgile Retault **/
double vector_angle2(Vector, Vector);

/** Used to test some vector functions 
  * @author Virgile Retault **/ 
void test_vector(void);
#endif // VECTOR_H
