#ifndef __EC_PARAMETERS_H_
#define __EC_PARAMETERS_H_
#include <stdio.h>
#include "bigint.h"
#include "ec_point_structure.h"

/* General representation of an elliptic curve*/
typedef struct
{
	BigInt p;
	BigInt a;
	BigInt b;
	Point generator;
	BigInt n;
	BigInt h;
} EllipticCurveParameter;


/*Elliptic Curve Domain Parameters over Fp Validation Primitive
 *
 * Input:
 * Elliptic curve domain parameters over Fp
 *Output:
 * An indication of whether the elliptic curve domain parameters are valid or not 
 * 
 * The return value should be 0 if invalid and 1 otherwise*/
int ec_validation(EllipticCurveParameter e, int security_level); 


/*Elliptic Curve Domain Parameters over Fp Generation Primitive
 *
 * Input:
 * The approximate security level in bits required from the elliptic curve domain parameters
 * this must be an integer t  in {  80  ,  112  ,  128  ,  192  ,  256  }  . Optionally, a seed value S
 *Output:
 *  Elliptic curve domain parameters over Fp
 * */
EllipticCurveParameter ec_generation(int security_level);

void ec_free(EllipticCurveParameter *ec);

void ec_create_parameters(EllipticCurveParameter *ec, BigInt const *p, BigInt const *a, BigInt const *b, Point const *generator, BigInt const *n, BigInt const *h);

#endif
