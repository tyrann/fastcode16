#include <stdio.h>
#include "bigint.h"

#ifndef __EC_POINT_H_
#define __EC_POINT_H_
#endif

/* Describes a point on the elliptic curve. 
 * We represent the point at infinity by
 * byte-long flag */
typedef struct
{
	BigInt x;
	BigInt y;
	char point_at_inf;

}Point;

/* Addition of two points on a curve*/
Point ec_points_add(Point p, Point q);

/* Multiplication of a pointon a curve by a scalar*/
Point ec_point_mul(Point p, BigInt k);




