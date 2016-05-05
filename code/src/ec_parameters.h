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

typedef enum {SECP192K1, SECP521R1} CurveParameter;

/*
This function generates parameters, that are often used in crypto

*/
void ec_generate_parameter(EllipticCurveParameter *parameter, const CurveParameter name);

void ec_free(EllipticCurveParameter *ec);

void ec_create_parameters(EllipticCurveParameter *ec, BigInt const *p, BigInt const *a, BigInt const *b, Point const *generator, BigInt const *n, BigInt const *h);

#endif
