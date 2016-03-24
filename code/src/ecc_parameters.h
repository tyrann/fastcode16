#include <stdio.h>
#include "bigint.h"

#ifndef __ECC_PARAMETERS_H_
#define __ECC_PARAMETERS_H_
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

/* General representation of an elliptic curve*/
typedef struct
{
	BigInt p;
	BigInt a;
	BigInt b;
	Point generator;
	BigInt n;
	BigInt h;

}EllipticCurve;

/* Addition of two points on a curve*/
Point ecc_points_add(Point p, Point q);

/* Multiplication of two points on a curve*/
Point ecc_points_mul(Point p, Point q);

/*Elliptic Curve Domain Parameters over Fp Validation Primitive
 *
 * Input:
 * Elliptic curve domain parameters over Fp
 *Output:
 * An indication of whether the elliptic curve domain parameters are valid or not 
 * 
 * The return value should be 0 if invalid and 1 otherwise*/
int ecc_validation(EllipticCurve e); 


/*Elliptic Curve Domain Parameters over Fp Generation Primitive
 *
 * Input:
 * The approximate security level in bits required from the elliptic curve domain parameters
 * this must be an integer t  in {  80  ,  112  ,  128  ,  192  ,  256  }  . Optionally, a seed value S
 *Output:
 *  Elliptic curve domain parameters over Fp
 * */
EllipticCurve ecc_generation(int security_level);
