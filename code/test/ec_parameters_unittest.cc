extern "C" {
    #include "../src/ec_parameters.h"
    #include "../src/ec_point.h"
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

TEST(ec_create_parameters, ec_create_parameters)
{
    EllipticCurveParameter parameter;
    BigInt p, a, b, n, h, x, y;
    Point g;
    bigint_from_hex_string(&p, "1111");
    bigint_from_hex_string(&a, "2222");
    bigint_from_hex_string(&b, "3333");
    bigint_from_hex_string(&n, "4444");
    bigint_from_hex_string(&h, "5555");
    bigint_from_hex_string(&x, "6666");
    bigint_from_hex_string(&y, "7777");
    create_point(&g, &x, &y);

    ec_create_parameters(&parameter, &p, &a, &b, &g, &n, &h);

    ASSERT_TRUE(bigint_are_equal(&(parameter.p), &p));
    ASSERT_TRUE(bigint_are_equal(&(parameter.a), &a));
    ASSERT_TRUE(bigint_are_equal(&(parameter.b), &b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(&(parameter.n), &n));
    ASSERT_TRUE(bigint_are_equal(&(parameter.h), &h));

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    point_free(&g);
    ec_free(&parameter);
}

TEST(ec_generate_parameter, SECP192K1)
{
    EllipticCurveParameter parameter;
    BigInt p, a, b, n, h, x, y;
    Point g;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
    bigint_from_hex_string(&a, "000000000000000000000000000000000000000000000000");
    bigint_from_hex_string(&b, "000000000000000000000000000000000000000000000003");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
    bigint_from_hex_string(&h, "01");
    bigint_from_hex_string(&x, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D");
    bigint_from_hex_string(&y, "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    create_point(&g, &x, &y);

    ec_generate_parameter(&parameter, SECP192K1);

    ASSERT_TRUE(bigint_are_equal(&(parameter.p), &p));
    ASSERT_TRUE(bigint_are_equal(&(parameter.a), &a));
    ASSERT_TRUE(bigint_are_equal(&(parameter.b), &b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(&(parameter.n), &n));
    ASSERT_TRUE(bigint_are_equal(&(parameter.h), &h));

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    point_free(&g);
    ec_free(&parameter);
}

TEST(ec_generate_parameter, SECP224R1)
{
    EllipticCurveParameter parameter;
    BigInt p, a, b, n, h, x, y;
    Point g;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
    bigint_from_hex_string(&a, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFE");
    bigint_from_hex_string(&b, "B4050A850C04B3ABF54132565044B0B7D7BFD8BA270B39432355FFB4");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29455C5C2A3D");
    bigint_from_hex_string(&h, "01");
    bigint_from_hex_string(&x, "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21");
    bigint_from_hex_string(&y, "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34");
    create_point(&g, &x, &y);

    ec_generate_parameter(&parameter, SECP224R1);

    ASSERT_TRUE(bigint_are_equal(&(parameter.p), &p));
    ASSERT_TRUE(bigint_are_equal(&(parameter.a), &a));
    ASSERT_TRUE(bigint_are_equal(&(parameter.b), &b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(&(parameter.n), &n));
    ASSERT_TRUE(bigint_are_equal(&(parameter.h), &h));

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    point_free(&g);
    ec_free(&parameter);
}

TEST(ec_generate_parameter, SECP256K1)
{
    EllipticCurveParameter parameter;
    BigInt p, a, b, n, h, x, y;
    Point g;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    bigint_from_hex_string(&a, "0000000000000000000000000000000000000000000000000000000000000000");
    bigint_from_hex_string(&b, "0000000000000000000000000000000000000000000000000000000000000007");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141");
    bigint_from_hex_string(&h, "01");
    bigint_from_hex_string(&x, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
    bigint_from_hex_string(&y, "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");
    create_point(&g, &x, &y);

    ec_generate_parameter(&parameter, SECP256K1);

    ASSERT_TRUE(bigint_are_equal(&(parameter.p), &p));
    ASSERT_TRUE(bigint_are_equal(&(parameter.a), &a));
    ASSERT_TRUE(bigint_are_equal(&(parameter.b), &b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(&(parameter.n), &n));
    ASSERT_TRUE(bigint_are_equal(&(parameter.h), &h));

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    point_free(&g);
    ec_free(&parameter);
}


TEST(ec_generate_parameter, SECP384R1)
{
    EllipticCurveParameter parameter;
    BigInt p, a, b, n, h, x, y;
    Point g;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
    bigint_from_hex_string(&a, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFC");
    bigint_from_hex_string(&b, "B3312FA7E23EE7E4988E056BE3F82D19181D9C6EFE8141120314088F5013875AC656398D8A2ED19D2A85C8EDD3EC2AEF");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973");
    bigint_from_hex_string(&h, "01");
    bigint_from_hex_string(&x, "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7");
    bigint_from_hex_string(&y, "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F");
    create_point(&g, &x, &y);

    ec_generate_parameter(&parameter, SECP384R1);

    ASSERT_TRUE(bigint_are_equal(&(parameter.p), &p));
    ASSERT_TRUE(bigint_are_equal(&(parameter.a), &a));
    ASSERT_TRUE(bigint_are_equal(&(parameter.b), &b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(&(parameter.n), &n));
    ASSERT_TRUE(bigint_are_equal(&(parameter.h), &h));

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    point_free(&g);
    ec_free(&parameter);
}

TEST(ec_generate_parameter, SECP521R1)
{
    EllipticCurveParameter parameter;
    BigInt p, a, b, n, h, x, y;
    Point g;
    bigint_from_hex_string(&p, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    bigint_from_hex_string(&a, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC");
    bigint_from_hex_string(&b, "0051953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00");
    bigint_from_hex_string(&n, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409");
    bigint_from_hex_string(&h, "01");
    bigint_from_hex_string(&x, "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66");
    bigint_from_hex_string(&y, "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650");
    create_point(&g, &x, &y);

    ec_generate_parameter(&parameter, SECP521R1);

    ASSERT_TRUE(bigint_are_equal(&(parameter.p), &p));
    ASSERT_TRUE(bigint_are_equal(&(parameter.a), &a));
    ASSERT_TRUE(bigint_are_equal(&(parameter.b), &b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(&(parameter.n), &n));
    ASSERT_TRUE(bigint_are_equal(&(parameter.h), &h));

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    point_free(&g);
    ec_free(&parameter);
}
