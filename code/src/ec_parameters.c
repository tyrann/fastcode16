#include "ec_parameters.h"
#include "bigint.h"
#include "ec_point_utilities.h"
#include <stdlib.h>

void ec_generate_parameter(EllipticCurveParameter *parameter, const CurveParameter name)
{
    BigInt p, a, b, n, h;
    Point G;
    if(name == SECP192K1)
    {
	    p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
		a = bigint_from_uint64(BI_PARAMS_A_TAG, 0);
	    b = bigint_from_uint64(BI_PARAMS_B_TAG, 3);
	    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, BI_PARAMS_GZ_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", p);
	    n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
	    h = bigint_from_uint64(BI_PARAMS_H_TAG, 1);
    }
    else if(name == SECP224R1)
    {
	    p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
	    a = bigint_from_hex_string(BI_PARAMS_A_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFE");
	    b = bigint_from_hex_string(BI_PARAMS_B_TAG, "B4050A850C04B3ABF54132565044B0B7D7BFD8BA270B39432355FFB4");
	    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, BI_PARAMS_GZ_TAG, "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21", "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34", p);
	    n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29455C5C2A3D");
	    h = bigint_from_uint64(BI_PARAMS_H_TAG, 1);
    }
    else if(name == SECP256K1)
    {
	    p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
	    a = bigint_from_uint64(BI_PARAMS_A_TAG, 0);
	    b = bigint_from_uint64(BI_PARAMS_B_TAG, 7);
	    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, BI_PARAMS_GZ_TAG, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798", "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8", p);
	    n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141");
	    h = bigint_from_uint64(BI_PARAMS_H_TAG, 1);
    }
    else if(name == SECP384R1)
    {
	    p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
	    a = bigint_from_hex_string(BI_PARAMS_A_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFC");
	    b = bigint_from_hex_string(BI_PARAMS_B_TAG, "B3312FA7E23EE7E4988E056BE3F82D19181D9C6EFE8141120314088F5013875AC656398D8A2ED19D2A85C8EDD3EC2AEF");
	    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, BI_PARAMS_GZ_TAG, "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7", "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F", p);
	    n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973");
	    h = bigint_from_uint64(BI_PARAMS_H_TAG, 1);
    }
    else if(name == SECP521R1)
    {
	    p = bigint_from_hex_string(BI_PARAMS_P_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	    a = bigint_from_hex_string(BI_PARAMS_A_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC");
	    b = bigint_from_hex_string(BI_PARAMS_B_TAG, "0051953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00");
	    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, BI_PARAMS_GZ_TAG, "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66", "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650", p);
	    n = bigint_from_hex_string(BI_PARAMS_N_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409");
	    h = bigint_from_uint64(BI_PARAMS_H_TAG, 1);
    }
    else
    {
	fprintf(stderr, "Could not load parameters");
	exit(0);
    }
    ec_create_parameters(parameter, p, a, b, &G, n, h);
    __montgomery_init(p);
    precompute_points(parameter);
}

void ec_create_parameters(EllipticCurveParameter *ec, BigInt p, BigInt a, BigInt b, Point const *generator, BigInt n, BigInt h)
{
    ec->p = p;
    ec->a = a;
    ec->b = b;
    ec->n = n;
    ec->h = h;
	ec->generator.x = generator->x;
	ec->generator.y = generator->y;
	ec->generator.z = generator->z;
	ec->generator.is_at_infinity = generator->is_at_infinity;
	ec->two = bigint_from_uint64(BI_EC_PARAMS_TWO_TAG, 2);
	ec->three = bigint_from_uint64(BI_EC_PARAMS_THREE_TAG, 3);
	ec_parameter_convert_to_montgomery_space(ec);
}

void ec_parameter_convert_to_montgomery_space(EllipticCurveParameter *parameter)
{
	BigInt a = GET_BIGINT_PTR(BI_EC_PARAMETER_CONVERT_TO_MONTGOMERY_SPACE_A_TAG);
	BigInt b = GET_BIGINT_PTR(BI_EC_PARAMETER_CONVERT_TO_MONTGOMERY_SPACE_B_TAG);
	bigint_copy(a, parameter->a);
	bigint_copy(b, parameter->b);
	__montgomery_convert(parameter->a, a, parameter->p);
	__montgomery_convert(parameter->b, b, parameter->p);
	__montgomery_convert(parameter->two, bigint_two, parameter->p);
	__montgomery_convert(parameter->three, bigint_three, parameter->p);
}

void ec_parameter_revert_from_montgomery_space(EllipticCurveParameter *parameter)
{
	BigInt a = GET_BIGINT_PTR(BI_EC_PARAMETER_REVERT_FROM_MONTGOMERY_SPACE_A_TAG);
	BigInt b = GET_BIGINT_PTR(BI_EC_PARAMETER_REVERT_FROM_MONTGOMERY_SPACE_B_TAG);
	bigint_copy(a, parameter->a);
	bigint_copy(b, parameter->b);
	__montgomery_revert(parameter->a, a, parameter->p);
	__montgomery_revert(parameter->b, b, parameter->p);
	bigint_copy(parameter->two, bigint_two);
	bigint_copy(parameter->three, bigint_three);
}

