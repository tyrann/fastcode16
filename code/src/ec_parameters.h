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
	BigInt two;
	BigInt three;
} EllipticCurveParameter;

typedef enum {SECP192K1, SECP224R1, SECP256K1, SECP384R1, SECP521R1} CurveParameter;

/*
This function generates parameters, that are often used in crypto
The values are taken from

SEC 2: Recommended Elliptic Curve Domain Parameters
Certicom Research
January 27, 2010
Version 2.0

*/
void ec_generate_parameter(EllipticCurveParameter *parameter, const CurveParameter name);

void ec_create_parameters(EllipticCurveParameter *ec, BigInt p, BigInt a, BigInt b, Point const *generator, BigInt n, BigInt h);

void ec_parameter_convert_to_montgomery_space(EllipticCurveParameter *parameter);

#endif
