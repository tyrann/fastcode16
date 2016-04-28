#include "ec_parameters.h"
#include "bigint.h"
#include "ec_point_utilities.h"
#include "ec_dh.h"
#include "ec_parameters.h"

/* General representation of an ECDH */
typedef struct
{
	EllipticCurveParameter parameters; 
	BigInt pub_key; // public key generated from private key 
	BigInt priv_key;	
	BigInt sharedInfo;
} ECDH;


int ecdh_generate_key(ECDH *dh)
{
	return 0; 
}


BigInt ecdh_compute_key(ECDH *dhU, ECDH *dhV)
{
	BigInt ret;
	return ret;
}


int ecdh_verification(ECDH *dhU, ECDH *dhV)
{
	return 0;
}
