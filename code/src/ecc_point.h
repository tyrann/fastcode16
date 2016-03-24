#include <stdio.h>
#include "bigint.h"

#ifndef __ECC_POINT_H_
#define __ECC_POINT_H_
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
Point ecc_points_add(Point p, Point q);

/* Multiplication of two points on a curve*/
Point ecc_points_mul(Point p, Point q);



