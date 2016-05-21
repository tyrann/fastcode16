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

    Point p;
    create_point_from_uint64(&p, BI_TESTS_PINFX_TAG, BI_TESTS_PINFY_TAG, 2, 3, params.p);
    p.is_at_infinity = 1;
    
    ASSERT_TRUE(point_is_on_curve(&p, &params));

	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_on_curve)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    create_parameters(&params);

    Point q;
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 16, 10, params.p);
    ASSERT_TRUE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 17, 7, params.p);
    ASSERT_TRUE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 27, 22, params.p);
    ASSERT_TRUE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 1, 8, params.p);
    ASSERT_TRUE(point_is_on_curve(&q, &params));
    create_point_from_uint64(&q, BI_TESTS_QX_TAG, BI_TESTS_QY_TAG, 3, 23, params.p);
    ASSERT_TRUE(point_is_on_curve(&q, &params));
    
	bigint_destroy_buffer();
}

TEST(point_is_on_curve, point_not_on_curve)
{
	bigint_create_buffer();

    EllipticCurveParameter params;
    create_parameters(&params);

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
