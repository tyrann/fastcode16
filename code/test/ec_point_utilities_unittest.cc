extern "C" {
    #include "ec_point.h"
    #include "bigint.h"
}
#include "gtest/gtest.h"

void create_parameters(EllipticCurveParameter *params)
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

TEST(create_point, create_point)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	create_parameters(&params);
    Point p;
    BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "FFCC");
    BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "CCFF");
    create_point(&p, x, y, params.p);

    ASSERT_TRUE(bigint_are_equal(p.x, x));
    ASSERT_TRUE(bigint_are_equal(p.y, y));
    ASSERT_FALSE(p.is_at_infinity);

	bigint_destroy_buffer();
}

TEST(create_point_from_hex, create_point_form_hex)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	create_parameters(&params);
    Point p, q;
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "FFCC");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "CCFF");
    create_point(&p, x, y, params.p);
    create_point_from_hex(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, "FFCC", "CCFF", params.p);

    ASSERT_TRUE(point_are_equal(&p, &q));

	bigint_destroy_buffer();
}

TEST(create_point_uint64, create_point_uint64)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	create_parameters(&params);
    Point p, q;
	BigInt x = bigint_from_uint64(BI_TESTS_X_TAG, 20000000);
	BigInt y = bigint_from_uint64(BI_TESTS_Y_TAG, 50000000);
    create_point(&p, x, y, params.p);
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 20000000, 50000000, params.p);

    ASSERT_TRUE(point_are_equal(&p, &q));

	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_inf)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    create_parameters(&params);
    __montgomery_init(params.p);

    Point p;
    create_point_from_uint64(&p, BI_TESTS_PINFX_TAG, BI_TESTS_PINFY_TAG, 2, 3, params.p);
    p.is_at_infinity = 1;
    
    ASSERT_TRUE(point_is_on_curve(&p, &params));

	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_on_curve_SECP192K1)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    __montgomery_init(params.p);

    ASSERT_TRUE(point_is_on_curve(&params.generator, &params));
    
	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_on_curve_SECP224R1)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP224R1);
    __montgomery_init(params.p);

    ASSERT_TRUE(point_is_on_curve(&params.generator, &params));

	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_on_curve_SECP256K1)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP256K1);
    __montgomery_init(params.p);

    ASSERT_TRUE(point_is_on_curve(&params.generator, &params));

	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_on_curve_SECP384R1)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    __montgomery_init(params.p);

    ASSERT_TRUE(point_is_on_curve(&params.generator, &params));

	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_on_curve_SECP521R1)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP521R1);
    __montgomery_init(params.p);

    ASSERT_TRUE(point_is_on_curve(&params.generator, &params));

	bigint_destroy_buffer();
}


TEST(point_is_on_curve, point_not_on_curve)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	ec_generate_parameter(&params, SECP521R1);
	__montgomery_init(params.p);

    Point q;
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 0, 0, params.p);
    ASSERT_FALSE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 17, 8, params.p);
    ASSERT_FALSE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 27, 21, params.p);
    ASSERT_FALSE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 1, 4, params.p);
    ASSERT_FALSE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 3, 12, params.p);
    ASSERT_FALSE(point_is_on_curve(&q, &params));
    
	bigint_destroy_buffer();
}

TEST(copy_point, copy_point)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	create_parameters(&params);
    Point p, q;
    create_point(&p,
        bigint_from_hex_string(BI_TESTS_PX_TAG, "FFCC"),
        bigint_from_hex_string(BI_TESTS_PY_TAG, "CCFF"),
        params.p);
    create_point(&q,
        bigint_from_uint64(BI_TESTS_QX_TAG, 0),
        bigint_from_uint64(BI_TESTS_QY_TAG, 0),
        params.p);
    point_copy(&q, &p);

    ASSERT_TRUE(bigint_are_equal(p.x, q.x));
    ASSERT_TRUE(bigint_are_equal(p.y, q.y));
    ASSERT_TRUE(p.is_at_infinity == q.is_at_infinity);

	bigint_destroy_buffer();
}

TEST(point_are_equal, different_x_coordinate)
{
	bigint_create_buffer();
 
	EllipticCurveParameter params;
	create_parameters(&params);
	Point p, q;
	BigInt x1 = bigint_from_hex_string(BI_TESTS_X1_TAG, "FFCC");
	BigInt x2 = bigint_from_hex_string(BI_TESTS_X2_TAG, "FFCCDDDDDDD");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "CCFF");
    
    create_point(&p, x1, y, params.p);
    create_point(&q, x2, y, params.p);
    ASSERT_FALSE(point_are_equal(&p, &q));

	bigint_destroy_buffer();
}

TEST(point_are_equal, different_y_coordinate)
{
	bigint_create_buffer();
	EllipticCurveParameter params;
	create_parameters(&params);
    Point p, q;
    BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "FFCC");
    BigInt y1 = bigint_from_hex_string(BI_TESTS_Y1_TAG, "FFCCDDDDDDD");
	BigInt y2 = bigint_from_hex_string(BI_TESTS_Y2_TAG, "CCFF");
    
    create_point(&p, x, y1, params.p);
    create_point(&q, x, y2, params.p);
    ASSERT_FALSE(point_are_equal(&p, &q));

	bigint_destroy_buffer();
}

TEST(point_are_equal, inf)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	create_parameters(&params);
    Point p, q;
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "FFCC");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "FFCCDDDDDDD");
    
    create_point(&p, x, y, params.p);
    create_point_from_uint64(&q, BI_TESTS_PINFX_TAG, BI_TESTS_PINFY_TAG, 34, 0, params.p);
    q.is_at_infinity = 1;
    
    ASSERT_FALSE(point_are_equal(&p, &q));

	bigint_destroy_buffer();
}

TEST(precompute_points, precompute_points_SECP384R1)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	ec_generate_parameter(&params, SECP384R1);
	__montgomery_init(params.p);

	Point P, expected;
	create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 0, 0, params.p);
	create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);

	precompute_points(&params);
	point_copy(&expected, &params.generator);
	get_precomputed_point(&P, 0);
	ASSERT_TRUE(point_are_equal(&P, &expected));


	create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "d5d89c3b5282369c5fbd88e2b231511a6b80dff0e5152cf6a464fa9428a8583bac8ebc773d157811a462b892401dafcf", "d815229de12906d241816d5e9a9448f1d41d4fc40e2a3bdb9caba57e440a7abad1210cb8f49bf2236822b755ebab3673", params.p);
	get_precomputed_point(&P, 4);
	ASSERT_TRUE(point_are_equal(&P, &expected));

	bigint_destroy_buffer();

}

TEST(precompute_points, precompute_points_SECP521R1)
{
	bigint_create_buffer();

	EllipticCurveParameter params;
	ec_generate_parameter(&params, SECP521R1);
	__montgomery_init(params.p);

	Point P, expected;
	create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 0, 0, params.p);
	create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);

	precompute_points(&params);
	point_copy(&expected, &params.generator);
	get_precomputed_point(&P, 0);
	ASSERT_TRUE(point_are_equal(&P, &expected));

	create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "183eca433e3fa652f4c77c39eb2c366d51fbb2c32c360a6a3099502d7f334de701988cdc5acdb6259b219ed502c27659be2b7e9a776c2856b1e171b622ab226efd9", "1fc825778a659888534128adff0dd2a6510750a2cb9560761ca969059f45b83446d7b1837b3de0175ede59a63707cd4b81b8cef9743dbb5a59d23aaf387a5bd54ca", params.p);
	get_precomputed_point(&P, 575);
	ASSERT_TRUE(point_are_equal(&P, &expected));

	bigint_destroy_buffer();

}
