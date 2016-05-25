extern "C" {
    #include "ec_parameters.h"
    #include "ec_point.h"
    #include "bigint.h"
}
#include "gtest/gtest.h"

TEST(ec_create_parameters, ec_create_parameters)
{
	bigint_create_buffer();
    EllipticCurveParameter parameter;
    Point g;

    BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "1111");
	BigInt a = bigint_from_hex_string(BI_PARAMS_A_TAG, "2222");
	BigInt b = bigint_from_hex_string(BI_PARAMS_B_TAG, "3333");
	BigInt n = bigint_from_hex_string(BI_PARAMS_N_TAG, "4444");
	BigInt h = bigint_from_hex_string(BI_PARAMS_H_TAG, "5555");
	BigInt x = bigint_from_hex_string(BI_PARAMS_GX_TAG, "6666");
	BigInt y = bigint_from_hex_string(BI_PARAMS_GY_TAG, "7777");
	BigInt z = bigint_from_hex_string(BI_PARAMS_GZ_TAG, "8888");
    create_point(&g, x, y, z, p);

    ec_create_parameters(&parameter, p, a, b, &g, n, h);

    ASSERT_TRUE(bigint_are_equal(parameter.p, p));
    ASSERT_TRUE(bigint_are_equal(parameter.a, a));
    ASSERT_TRUE(bigint_are_equal(parameter.b, b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(parameter.n, n));
    ASSERT_TRUE(bigint_are_equal(parameter.h, h));

	bigint_destroy_buffer();
}

TEST(ec_generate_parameter, SECP192K1)
{
	bigint_create_buffer();
    EllipticCurveParameter parameter;
    Point g;

	BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	BigInt a = bigint_from_hex_string(BI_PARAMS_A_TAG, "000000000000000000000000000000000000000000000000");
	BigInt b = bigint_from_hex_string(BI_PARAMS_B_TAG, "000000000000000000000000000000000000000000000003");
	BigInt n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
	BigInt h = bigint_from_hex_string(BI_PARAMS_H_TAG, "01");
	BigInt x = bigint_from_hex_string(BI_PARAMS_GX_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D");
	BigInt y = bigint_from_hex_string(BI_PARAMS_GY_TAG, "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
	BigInt z = bigint_from_hex_string(BI_PARAMS_GZ_TAG, "1");
	create_point(&g, x, y, z, p);

	char precompute = 0;
	ec_generate_parameter(&parameter, SECP192K1, precompute);

    ASSERT_TRUE(bigint_are_equal(parameter.p, p));
    ASSERT_TRUE(bigint_are_equal(parameter.a, a));
    ASSERT_TRUE(bigint_are_equal(parameter.b, b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(parameter.n, n));
    ASSERT_TRUE(bigint_are_equal(parameter.h, h));
	
	bigint_destroy_buffer();
}

TEST(ec_generate_parameter, SECP224R1)
{
	bigint_create_buffer();
    EllipticCurveParameter parameter;
    Point g;

	BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
	BigInt a = bigint_from_hex_string(BI_PARAMS_A_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFE");
	BigInt b = bigint_from_hex_string(BI_PARAMS_B_TAG, "B4050A850C04B3ABF54132565044B0B7D7BFD8BA270B39432355FFB4");
	BigInt n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29455C5C2A3D");
	BigInt h = bigint_from_hex_string(BI_PARAMS_H_TAG, "01");
	BigInt x = bigint_from_hex_string(BI_PARAMS_GX_TAG, "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21");
	BigInt y = bigint_from_hex_string(BI_PARAMS_GY_TAG, "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34");
	BigInt z = bigint_from_hex_string(BI_PARAMS_GZ_TAG, "1");
	create_point(&g, x, y, z, p);

	char precompute = 0;
	ec_generate_parameter(&parameter, SECP224R1, precompute);

    ASSERT_TRUE(bigint_are_equal(parameter.p, p));
    ASSERT_TRUE(bigint_are_equal(parameter.a, a));
    ASSERT_TRUE(bigint_are_equal(parameter.b, b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(parameter.n, n));
    ASSERT_TRUE(bigint_are_equal(parameter.h, h));

	bigint_destroy_buffer();
}

TEST(ec_generate_parameter, SECP256K1)
{
	bigint_create_buffer();
    EllipticCurveParameter parameter;
    Point g;

	BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
	BigInt a = bigint_from_hex_string(BI_PARAMS_A_TAG, "0000000000000000000000000000000000000000000000000000000000000000");
	BigInt b = bigint_from_hex_string(BI_PARAMS_B_TAG, "0000000000000000000000000000000000000000000000000000000000000007");
	BigInt n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141");
	BigInt h = bigint_from_hex_string(BI_PARAMS_H_TAG, "01");
	BigInt x = bigint_from_hex_string(BI_PARAMS_GX_TAG, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
	BigInt y = bigint_from_hex_string(BI_PARAMS_GY_TAG, "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");
	BigInt z = bigint_from_hex_string(BI_PARAMS_GZ_TAG, "1");
	create_point(&g, x, y, z, p);

	char precompute = 0;
	ec_generate_parameter(&parameter, SECP256K1, precompute);

    ASSERT_TRUE(bigint_are_equal(parameter.p, p));
    ASSERT_TRUE(bigint_are_equal(parameter.a, a));
    ASSERT_TRUE(bigint_are_equal(parameter.b, b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(parameter.n, n));
    ASSERT_TRUE(bigint_are_equal(parameter.h, h));

	bigint_destroy_buffer();
}


TEST(ec_generate_parameter, SECP384R1)
{
	bigint_create_buffer();
    EllipticCurveParameter parameter;
    Point g;

	BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
	BigInt a = bigint_from_hex_string(BI_PARAMS_A_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFC");
	BigInt b = bigint_from_hex_string(BI_PARAMS_B_TAG, "B3312FA7E23EE7E4988E056BE3F82D19181D9C6EFE8141120314088F5013875AC656398D8A2ED19D2A85C8EDD3EC2AEF");
	BigInt n = bigint_from_hex_string(BI_PARAMS_N_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973");
	BigInt h = bigint_from_hex_string(BI_PARAMS_H_TAG, "01");
	BigInt x = bigint_from_hex_string(BI_PARAMS_GX_TAG, "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7");
	BigInt y = bigint_from_hex_string(BI_PARAMS_GY_TAG, "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F");
	BigInt z = bigint_from_hex_string(BI_PARAMS_GZ_TAG, "1");
	create_point(&g, x, y, z, p);

	char precompute = 0;
	ec_generate_parameter(&parameter, SECP384R1, precompute);

    ASSERT_TRUE(bigint_are_equal(parameter.p, p));
    ASSERT_TRUE(bigint_are_equal(parameter.a, a));
    ASSERT_TRUE(bigint_are_equal(parameter.b, b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(parameter.n, n));
    ASSERT_TRUE(bigint_are_equal(parameter.h, h));

	bigint_destroy_buffer();
}

TEST(ec_generate_parameter, SECP521R1)
{
	bigint_create_buffer();
    EllipticCurveParameter parameter;
    Point g;

	BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	BigInt a = bigint_from_hex_string(BI_PARAMS_A_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC");
	BigInt b = bigint_from_hex_string(BI_PARAMS_B_TAG, "0051953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00");
	BigInt n = bigint_from_hex_string(BI_PARAMS_N_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409");
	BigInt h = bigint_from_hex_string(BI_PARAMS_H_TAG, "01");
	BigInt x = bigint_from_hex_string(BI_PARAMS_GX_TAG, "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66");
	BigInt y = bigint_from_hex_string(BI_PARAMS_GY_TAG, "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650");
	BigInt z = bigint_from_hex_string(BI_PARAMS_GZ_TAG, "1");
	create_point(&g, x, y, z, p);

	char precompute = 0;
	ec_generate_parameter(&parameter, SECP521R1, precompute);

    ASSERT_TRUE(bigint_are_equal(parameter.p, p));
    ASSERT_TRUE(bigint_are_equal(parameter.a, a));
    ASSERT_TRUE(bigint_are_equal(parameter.b, b));
    ASSERT_TRUE(point_are_equal(&(parameter.generator), &g));
    ASSERT_TRUE(bigint_are_equal(parameter.n, n));
    ASSERT_TRUE(bigint_are_equal(parameter.h, h));

	bigint_destroy_buffer();
}
