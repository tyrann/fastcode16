#ifndef __EC_PARAMETERS_H_
#define __EC_PARAMETERS_H_
#include <stdio.h>
#include "bigint.h"
#include "ec_point_structure.h"
#include "ec_point_operations.h"

/* General representation of an ECDH */
typedef struct
{
	EllipticCurveParameter parameters; 
	BigInt pub_key; // public key generated from private key 
	BigInt priv_key;	
	BigInt sharedInfo;
} ECDH;

/*
	ecdh_generate_key() performs the first step of a Diffie-Hellman key exchange by generating private and public DH values. By calling ecdh_generate_key(), these are combined with the other party's public value to compute the shared key.
	
	The return value should be 1 if succeed and 0 otherwise
*/
int ecdh_generate_key(DH *dh);
/*
	ec_compute_key() computes the shared secret from the private ECDH value in dhU and the other party's public value in dhV and returns it shared secret.
	
	The return value should be the sharedInfo
*/

BigInt ecdh_compute_key(ECDH *dhU, ECDH *dhV);

/*
	ecdh_verification() verifies if the two parties have the same sharedInfo and parameters

	The return value should be 1 if the sharedInfo are matched and 0 otherwise
*/
int ecdh_verification(ECDH *dhU, ECDH *dhV);
#endif
