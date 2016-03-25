#include <stdio.h>
#include "bigint.h"

#ifndef __EC_POINT_H_
#define __EC_POINT_H_

/* Describes a point on the elliptic curve. 
 * We represent the point at infinity by
 * byte-long flag */
typedef struct
{
	BigInt x;
	BigInt y;
	char is_at_infinity;

}Point;

void create_point(BigInt const* a, BigInt const* b, Point* p);

void create_point_inf(Point* p);

/* Addition of two points on a curve*/
Point ec_point_add(Point a, Point b, BigInt p);

/* Multiplication of a point on a curve by a scalar*/
Point ec_point_mul(Point a, BigInt k, BigInt p);

#endif 
