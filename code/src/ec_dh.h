#ifndef __EC_DH_H_
#define __EC_DH_H_
#include <stdio.h>
#include "bigint.h"
#include "ec_point_structure.h"
#include "ec_point_operations.h"
#include "ec_parameters.h"
#include "ec_point_utilities.h"

/* General representation of an ECDH */
typedef struct
{
	EllipticCurveParameter parameters; 
	Point pub_key; // public key generated from private key 
	BigInt priv_key;	
	BigInt sharedInfo; // Point.x
} ECDH;


void ec_create_ECDH(ECDH *ecdh,EllipticCurveParameter *parameters, Point *pub_key, BigInt priv_key, BigInt sharedInfo);

/*
*	ecdh_generate_key() performs the first step of a Diffie-Hellman key exchange by generating private and public DH values. By calling ecdh_generate_key(), these are combined with *	 the other party's public value to compute the shared key.
*	
*/

void ecdh_generate_public_key(Point *publicKey, BigInt d, const EllipticCurveParameter *parameters);

/*
*	ec_compute_key() computes the shared secret from the private ECDH value in dhU and the other party's public value in dhV and returns it shared secret.
*	
*	The return value should be 1 if succeed and 0 otherwise
*/

int ecdh_compute_shared_secret(BigInt sharedInfo, BigInt privateKey, const Point *publicKey, const EllipticCurveParameter *parameters);

/*
*	ecdh_verification() verifies if the two parties have the same sharedInfo and parameters
*
*	The return value should be 1 if the sharedInfo are matched and 0 otherwise
*/

int ecdh_verification(ECDH *dhU, ECDH *dhV);
#endif
