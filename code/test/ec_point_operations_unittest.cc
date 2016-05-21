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
    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, "0", "0", p);
    BigInt n = bigint_from_uint64(BI_PARAMS_N_TAG, 0);
    BigInt h = bigint_from_uint64(BI_PARAMS_H_TAG, 0);
    ec_create_parameters(params, p, a, b, &G, n, h);
}

void create_parameters_2(EllipticCurveParameter *params)
{
    Point G;
    BigInt p = bigint_from_uint64(BI_PARAMS_P_TAG, 7927);
	BigInt a = bigint_from_uint64(BI_PARAMS_A_TAG, 500);
	BigInt b = bigint_from_uint64(BI_PARAMS_B_TAG, 3);
    
    // This parameters are not relevant for the tests
    create_point_from_hex(&G, BI_PARAMS_GX_TAG, BI_PARAMS_GY_TAG, "0", "0", p);
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
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
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
    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 1, 8, params.p);
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0, params.p);
    b.is_at_infinity = 1;
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 1, 8, params.p);

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
    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 0, 0, params.p);
    a.is_at_infinity = 1;
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 1, 8, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 1, 8, params.p);

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

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 3, 4319, params.p);
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 3, 4319, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 6403, 191, params.p);
	ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 6, 2752, params.p);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 6, 2752, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 2925, 7203, params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 4, 5799, params.p);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 4, 5799, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 3453, 4904, params.p);
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

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 2, 3644, params.p);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 2, 4283, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
	expected.is_at_infinity = 1;
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 4, 2128, params.p);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 4, 5799, params.p);
	create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
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

    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 4, 5799, params.p);
	create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 3453, 4904, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 3432, 1280, params.p);
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

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5", params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "6E43B7DCAE2FD5E0BF2A1BA7615CA3B9065487C9A67B4583", "C48DCEA47AE08E84D5FEDC3D09E4C19606A290F7A19A6A58", params.p);
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

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 222, 3060, params.p);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 0);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
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

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 222, 3060, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
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

    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 222, 3060, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 2);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 7813, 2629, params.p);
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
    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 0, 0, params.p);
    
    point_copy(&P, &params.generator);
    bigint_copy(d, params.n);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
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
    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93, params.p);
   
    point_copy(&P, &params.generator);
    bigint_copy(d, params.n);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}
