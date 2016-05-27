#include "ec_dh.h"
#include "ec_point_operations.h"
#include "logging/logging.h"

void ec_create_ECDH(ECDH *ecdh, EllipticCurveParameter *parameters, Point *pub_key, BigInt priv_key, BigInt sharedInfo)
{
    ecdh->parameters = *parameters;
    ecdh->priv_key = priv_key;
    ecdh->sharedInfo = sharedInfo;
	ecdh->pub_key.x = pub_key->x;
	ecdh->pub_key.y = pub_key->y;
	ecdh->pub_key.z = pub_key->z;
	ecdh->pub_key.is_at_infinity = pub_key->is_at_infinity;
}

void ecdh_generate_public_key(Point *public_key, BigInt d, const EllipticCurveParameter *parameters)
{
    //Compute Q = dG 
    //void ec_point_mul(Point *result, const BigInt *d, const Point *P, const EllipticCurveParameter *p);
    //printf("After ecdh_generate_key dh priv_key = %s \n", bigint_to_hex_string(&(dh->priv_key)));
	__montgomery_init(parameters->p);
    ec_point_mul_generator(public_key, d, parameters);
}

int ecdh_compute_shared_secret(BigInt shared_info, BigInt private_key, const Point *public_key, const EllipticCurveParameter *parameters)
{	
	Point shared_point;
	shared_point.x = shared_info;
	shared_point.y = GET_BIGINT_PTR(BI_ECDH_SHAREDSECRETY_TAG);
	shared_point.z = GET_BIGINT_PTR(BI_ECDH_SHAREDSECRETZ_TAG);
	
	// Compute the elliptic curve point P = (xP , yP ) = priv_keyU*pub_keyV
	__montgomery_init(parameters->p);
	ec_point_mul(&shared_point, private_key, public_key, parameters);
	point_convert_to_affine_coordinates(&shared_point, parameters);
	
	// Check that P != O. If P = O, output “invalid” and stop
	char ret = shared_point.is_at_infinity;
	if(ret)
	{
	    assert("ecdh_compute_key, invalid shared Point");
	}
	
	// printf("After ecdh_generate_key dh sharedPoint = %s \n", bigint_to_hex_string(&(sharedPoint.x)));
	return (int)!ret;
}

int ecdh_verification(ECDH *dhU, ECDH *dhV)
{
	// check if dhU.sharedIno == dhV.sharedIno
	int ret = bigint_are_equal(dhU->sharedInfo, dhV->sharedInfo);
	return ret;
}
