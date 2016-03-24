#include <stdio.h>
#include "bigint.h"
#include "ec_point.h"

#ifndef __EC_PARAMETERS_H_
#define __EC_PARAMETERS_H_
#endif

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


/*Elliptic Curve Domain Parameters over Fp Validation Primitive
 *
 * Input:
 * Elliptic curve domain parameters over Fp
 *Output:
 * An indication of whether the elliptic curve domain parameters are valid or not 
 * 
 * The return value should be 0 if invalid and 1 otherwise*/
int ec_validation(EllipticCurve e); 


/*Elliptic Curve Domain Parameters over Fp Generation Primitive
 *
 * Input:
 * The approximate security level in bits required from the elliptic curve domain parameters
 * this must be an integer t  in {  80  ,  112  ,  128  ,  192  ,  256  }  . Optionally, a seed value S
 *Output:
 *  Elliptic curve domain parameters over Fp
 * */
EllipticCurve ec_generation(int security_level);
