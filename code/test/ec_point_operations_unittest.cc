extern "C" {
    #include "ec_point.h"
    #include "bigint.h"
    #include "ec_parameters.h"
}
#include "gtest/gtest.h"

void create_parameters_1(EllipticCurveParameter *params)
{
    Point G;
    BigInt p = bigint_from_uint64(BI_PARAMS_P_TAG, 29);
	BigInt a = bigint_from_uint64(BI_PARAMS_A_TAG, 2);
	BigInt b = bigint_from_uint64(BI_PARAMS_B_TAG, 3);
    
    // This parameters are not relevant for the tests
    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, "0", "0");
    BigInt n = bigint_from_uint64(BI_PARAMS_N_TAG, 0);
    BigInt h = bigint_from_uint64(BI_PARAMS_H_TAG, 0);
    ec_create_parameters(params, p, a, b, &G, n, h);
}

void create_parameters_2(EllipticCurveParameter *params)
{
    Point G;
    BigInt p = bigint_from_uint64(BI_PARAMS_P_TAG, 7927);
	BigInt a = bigint_from_uint64(BI_PARAMS_A_TAG, 500);
	BigInt b = bigint_from_uint64(BI_PARAMS_B_TAG, 0);
    
    // This parameters are not relevant for the tests
    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, "0", "0");
    BigInt n = bigint_from_uint64(BI_PARAMS_N_TAG, 0);
    BigInt h = bigint_from_uint64(BI_PARAMS_H_TAG, 0);
    ec_create_parameters(params, p, a, b, &G, n, h);
}

TEST(ec_point_add_inplace, inf_plus_inf)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_1(&params);
    Point a, b, expected;
    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 0, 0);
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0);
    a.is_at_infinity = 1;
    b.is_at_infinity = 1;
    expected.is_at_infinity = 1;

    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_add_inplace, a_plus_inf)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_1(&params);
    Point a, b, expected;
    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 1, 8);
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0);
    b.is_at_infinity = 1;
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 1, 8);

    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_add_inplace, inf_plus_b)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_1(&params);
    Point a, b, expected;
    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 0, 0);
    a.is_at_infinity = 1;
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 1, 8);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 1, 8);

    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_add_inplace, a_plus_a_curve1)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point a, b, expected;

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 188, 93);
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 188, 93);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 2505, 3126);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 692, 150);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 692, 150);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 6111, 95);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 6026, 210);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 6026, 210);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 3075, 6164);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_add_inplace, a_plus_b)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point a, b, expected;

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 2, 2903);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 2, 5024);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0);
	expected.is_at_infinity = 1;
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 0, 0);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0);
	create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0);
	expected.is_at_infinity = 1;
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_add_inplace, a_plus_b_rule4)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point a, b, expected;

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 6026, 210);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 2, 2903);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 4555, 1855);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 4, 5017);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 475, 2499);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 6563, 6553);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_add_inplace, large_number)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    Point a, b, expected;

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5");
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5");
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "6E43B7DCAE2FD5E0BF2A1BA7615CA3B9065487C9A67B4583", "C48DCEA47AE08E84D5FEDC3D09E4C19606A290F7A19A6A58");
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, zero_times_point)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point P, result, expected;

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 0);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, one_times_point)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point P, result, expected;
    expected.x = GET_BIGINT_PTR(BI_TESTS_EXPECTEDX_TAG);
    expected.y = GET_BIGINT_PTR(BI_TESTS_EXPECTEDY_TAG);

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 1);
    point_copy(&expected, &P);
    ec_point_mul(&result, d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, two_times_point)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point P, result, expected;

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 2);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 2505, 3126);
    ec_point_mul(&result, d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, multiple_tests)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    create_parameters_2(&params);
    Point P, result, expected;
    BigInt d;

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    d = bigint_from_uint64(BI_TESTS_D_TAG, 3);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 6452, 1971);
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    d = bigint_from_uint64(BI_TESTS_D_TAG, 4);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 3124, 272);
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    d = bigint_from_uint64(BI_TESTS_D_TAG, 10);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 3025, 1344);
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    d = bigint_from_uint64(BI_TESTS_D_TAG, 1000);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 2945, 4676);
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, ultimate_test)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    
    Point P, result, expected;
    BigInt d = GET_BIGINT_PTR(BI_TESTS_D_TAG);
    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 0, 0);
    
    point_copy(&P, &params.generator);
    bigint_copy(d, params.n);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);

    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, ultimate_test_2)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP521R1);
   
    Point P, result, expected;   
    BigInt d = GET_BIGINT_PTR(BI_TESTS_D_TAG);
    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93);
   
    point_copy(&P, &params.generator);
    bigint_copy(d, params.n);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}
