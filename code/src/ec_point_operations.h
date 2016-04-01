
#ifndef __EC_POINT_OPERATIONS_H_
#define __EC_POINT_OPERATIONS_H_

#include <stdio.h>
#include "ec_point_structure.h"
#include "ec_parameters.h"

/* Addition of two points on a curve*/
void ec_point_add(Point *result, const Point *a, const Point *b, const EllipticCurveParameter *p);

/* Multiplication of a point on a curve by a scalar*/
/* result = d*P */
void ec_point_mul(Point *result, const BigInt *d, const Point *P, const EllipticCurveParameter *p);

#endif 
