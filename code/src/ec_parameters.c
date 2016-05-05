#include "ec_parameters.h"
#include "bigint.h"
#include "ec_point_utilities.h"

void ec_generate_parameter(EllipticCurveParameter *parameter, const CurveParameter name)
{
    BigInt p, a, b, n, h;
    Point G;

    if(name == SECP192K1)
    {
	bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	bigint_from_uint32(&a, 0);
	bigint_from_uint32(&b, 3);
	create_point_from_hex(&G, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
	bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
	bigint_from_uint32(&h, 1);
	ec_create_parameters(parameter, &p, &a, &b, &G, &n, &h);
    }
    else if(name == SECP521R1)
    {
	bigint_from_hex_string(&p, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	bigint_from_hex_string(&a, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC");
	bigint_from_hex_string(&b, "0051953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00");
	create_point_from_hex(&G, "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66", "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650");
	bigint_from_hex_string(&n, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409");
	bigint_from_uint32(&h, 1);
    }
    
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

void ec_free(EllipticCurveParameter *ec)
{
    bigint_free(&(ec->p));
    bigint_free(&(ec->a));
    bigint_free(&(ec->b));
    point_free(&(ec->generator));
    bigint_free(&(ec->n));
    bigint_free(&(ec->h));
}

void ec_create_parameters(EllipticCurveParameter *ec, BigInt const *p, BigInt const *a, BigInt const *b, Point const *generator, BigInt const *n, BigInt const *h)
{
    bigint_copy(&(ec->p), p);
    bigint_copy(&(ec->a), a);
    bigint_copy(&(ec->b), b);
    point_copy(&(ec->generator), generator);
    bigint_copy(&(ec->n), n);
    bigint_copy(&(ec->h), h);
}


