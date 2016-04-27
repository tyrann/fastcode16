extern "C" {
    #include "../src/ec_point.h"
    #include "../src/bigint.h"
    #include "../src/ec_parameters.h"
}
#include "gtest/gtest.h"

void create_parameters_1(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_uint32(&p, 29);
    bigint_from_uint32(&a, 2);
    bigint_from_uint32(&b, 3);
    // This parameters are not relevant for the tests
    create_point_from_hex(&G, "0", "0");
    bigint_from_uint32(&n, 0);
    bigint_from_uint32(&h, 0);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

void create_parameters_2(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_uint32(&p, 7927);
    bigint_from_uint32(&a, 500);
    bigint_from_uint32(&b, 0);
    // This parameters are not relevant for the tests
    create_point_from_hex(&G, "0", "0");
    bigint_from_uint32(&n, 0);
    bigint_from_uint32(&h, 0);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

// secp192k1
void create_parameters_3(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
    bigint_from_uint32(&a, 0);
    bigint_from_uint32(&b, 3);
    create_point_from_hex(&G, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

TEST(ec_point_add, inf_plus_inf)
{
    EllipticCurveParameter params;
    create_parameters_1(&params);
    Point a, b, result, expected;
    create_point_inf(&a);
    create_point_inf(&b);
    create_point_inf(&expected);

    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);
    ec_free(&params);
}

TEST(ec_point_add, a_plus_inf)
{
    EllipticCurveParameter params;
    create_parameters_1(&params);
    Point a, b, result, expected;
    create_point_from_uint32(&a, 1, 8);
    create_point_inf(&b);
    create_point_from_uint32(&expected, 1, 8);

    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);
    ec_free(&params);
}

TEST(ec_point_add, inf_plus_b)
{
    EllipticCurveParameter params;
    create_parameters_1(&params);
    Point a, b, result, expected;
    create_point_inf(&a);
    create_point_from_uint32(&b, 1, 8);
    create_point_from_uint32(&expected, 1, 8);

    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);
    ec_free(&params);
}

TEST(ec_point_add, a_plus_a_curve1)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point a, b, result, expected;

    create_point_from_uint32(&a, 188, 93);
    create_point_from_uint32(&b, 188, 93);
    create_point_from_uint32(&expected, 2505, 3126);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&a, 692, 150);
    create_point_from_uint32(&b, 692, 150);
    create_point_from_uint32(&expected, 6111, 95);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&a, 6026, 210);
    create_point_from_uint32(&b, 6026, 210);
    create_point_from_uint32(&expected, 3075, 6164);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_add, a_plus_b)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point a, b, result, expected;

    create_point_from_uint32(&a, 2, 2903);
    create_point_from_uint32(&b, 2, 5024);
    create_point_inf(&expected);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&a, 0, 0);
    create_point_from_uint32(&b, 0, 0);
    create_point_inf(&expected);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_add, a_plus_b_rule4)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point a, b, result, expected;

    create_point_from_uint32(&a, 6026, 210);
    create_point_from_uint32(&b, 2, 2903);
    create_point_from_uint32(&expected, 4555, 1855);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&a, 4, 5017);
    create_point_from_uint32(&b, 475, 2499);
    create_point_from_uint32(&expected, 6563, 6553);
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_add, large_number)
{
    EllipticCurveParameter params;
    create_parameters_3(&params);
    Point a, b, result, expected;

    create_point_from_hex(&a, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    create_point_from_hex(&b, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    create_point_from_hex(&expected, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5");
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    create_point_from_hex(&a, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    create_point_from_hex(&b, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5");
    create_point_from_hex(&expected, "6E43B7DCAE2FD5E0BF2A1BA7615CA3B9065487C9A67B4583", "C48DCEA47AE08E84D5FEDC3D09E4C19606A290F7A19A6A58");
    ec_point_add(&result, &a, &b, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    point_free(&a);
    point_free(&b);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_mul, zero_times_point)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    BigInt d;
    Point P, result, expected;

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 0);
    create_point_inf(&expected);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_mul, one_times_point)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    BigInt d;
    Point P, result, expected;

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 1);
    point_copy(&expected, &P);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_mul, two_times_point)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    BigInt d;
    Point P, result, expected;

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 2);
    create_point_from_uint32(&expected, 2505, 3126);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_mul, multiple_tests)
{
    EllipticCurveParameter params;
    create_parameters_2(&params);
    BigInt d;
    Point P, result, expected;

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 3);
    create_point_from_uint32(&expected, 6452, 1971);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 4);
    create_point_from_uint32(&expected, 3124, 272);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 10);
    create_point_from_uint32(&expected, 3025, 1344);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    create_point_from_uint32(&P, 188, 93);
    bigint_from_uint32(&d, 1000);
    create_point_from_uint32(&expected, 2945, 4676);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}

TEST(ec_point_mul, ultimate_test)
{
    EllipticCurveParameter params;
    create_parameters_3(&params);
    BigInt d;
    Point P, result, expected;

    point_copy(&P, &(params.generator));
    bigint_copy(&d, &(params.n));
    create_point_inf(&expected);
    ec_point_mul(&result, &d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));
    bigint_free(&d);
    point_free(&P);
    point_free(&result);
    point_free(&expected);

    ec_free(&params);
}
