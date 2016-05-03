#include "ec_dh.h"
#include "ec_point_operations.h"
#include "logging/logging.h"

void ec_create_ECDH(ECDH *ecdh, EllipticCurveParameter *parameters, Point *pub_key, BigInt *priv_key, BigInt *sharedInfo)
{
    ecdh->parameters = *parameters;
    point_copy(&(ecdh->pub_key), pub_key);
    bigint_copy(&(ecdh->priv_key), priv_key);
    bigint_copy(&(ecdh->sharedInfo), sharedInfo);
}

void ec_ECDHfree(ECDH *ecdh)
{
    point_free(&(ecdh->pub_key));
    bigint_free(&(ecdh->priv_key));
    bigint_free(&(ecdh->sharedInfo));
}

void ecdh_generate_public_key(Point *public_key, const BigInt *d, const EllipticCurveParameter *parameters)
{
    //Compute Q = dG 
    //void ec_point_mul(Point *result, const BigInt *d, const Point *P, const EllipticCurveParameter *p);
    //printf("After ecdh_generate_key dh priv_key = %s \n", bigint_to_hex_string(&(dh->priv_key)));
    
    ec_point_mul(public_key, d, &(parameters->generator), parameters);
}


int ecdh_compute_shared_secret(BigInt *shared_info, const BigInt *private_key, const Point *public_key, const EllipticCurveParameter *parameters)
{
	Point shared_point;

	// Compute the elliptic curve point P = (xP , yP ) = priv_keyU*pub_keyV
	ec_point_mul(&shared_point, private_key, public_key, parameters);
	
	// Check that P != O. If P = O, output “invalid” and stop
	char ret = shared_point.is_at_infinity;
	if(ret)
	{
	    assert("ecdh_compute_key, invalid shared Point");
	}
	else
	{		
	    bigint_copy(shared_info, &shared_point.x);
	}
	// printf("After ecdh_generate_key dh sharedPoint = %s \n", bigint_to_hex_string(&(sharedPoint.x)));
	point_free(&shared_point);
	return (int)!ret;
}


int ecdh_verification(ECDH *dhU, ECDH *dhV)
{
	// check if dhU.sharedIno == dhV.sharedIno
	int ret = bigint_are_equal(&(dhU->sharedInfo),&(dhV->sharedInfo));
	return ret;
}
