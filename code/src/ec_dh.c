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

int ecdh_generate_public_key(ECDH *dh, const BigInt *d)
{
	//Compute Q = dG 
	//void ec_point_mul(Point *result, const BigInt *d, const Point *P, const EllipticCurveParameter *p);
    //printf("After ecdh_generate_key dh priv_key = %s \n", bigint_to_hex_string(&(dh->priv_key)));
	
	
	ec_point_mul(&(dh->pub_key), d, &(dh->parameters.generator), &(dh->parameters));
	char ret = point_is_on_curve(&(dh->pub_key),&(dh->parameters)); 
	
	//printf("After ecdh_generate_key dh priv_key = %s \n", bigint_to_hex_string(&(dh->priv_key)));

	return (int)ret;
}


int ecdh_compute_shared_secret(ECDH *dhU, ECDH *dhV)
{
	Point sharedPoint;
	//create_point_from_hex(&sharedPoint, "0", "0");

	// Compute the elliptic curve point P = (xP , yP ) = priv_keyU*pub_keyV
	ec_point_mul(&sharedPoint, &(dhU->priv_key), &(dhV->pub_key), &(dhU->parameters));
	
	// Check that P != O. If P = O, output “invalid” and stop
	char ret = sharedPoint.is_at_infinity;
	if(ret)
	{
		assert("ecdh_compute_key, invalid shared Point");
	}
	else
	{		
		bigint_copy(&(dhU->sharedInfo),&sharedPoint.x);
	}
	// printf("After ecdh_generate_key dh sharedPoint = %s \n", bigint_to_hex_string(&(sharedPoint.x)));
    point_free(&sharedPoint);
	return (int)!ret;
}


int ecdh_verification(ECDH *dhU, ECDH *dhV)
{
	// check if dhU.sharedIno == dhV.sharedIno
	int ret = bigint_are_equal(&(dhU->sharedInfo),&(dhV->sharedInfo));
	return ret;
}
