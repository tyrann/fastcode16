extern "C" {
    #include "../src/ec_point.h"
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

void create_parameters(EllipticCurveParameter *params)
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

TEST(create_point, create_point)
{
    Point p;
    BigInt x;
    BigInt y;
    bigint_from_hex_string(&x, "FFCC");
    bigint_from_hex_string(&y, "CCFF");
    create_point(&p, &x, &y);

    ASSERT_TRUE(bigint_are_equal(&(p.x), &x));
    ASSERT_TRUE(bigint_are_equal(&(p.y), &y));
    ASSERT_FALSE(p.is_at_infinity);

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
}

TEST(create_point_from_hex, create_point_form_hex)
{
    Point p, q;
    BigInt x;
    BigInt y;
    bigint_from_hex_string(&x, "FFCC");
    bigint_from_hex_string(&y, "CCFF");
    create_point(&p, &x, &y);
    create_point_from_hex(&q, "FFCC", "CCFF");

    ASSERT_TRUE(point_are_equal(&p,&q));

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}

TEST(create_point_uint32, create_point_uint32)
{
    Point p, q;
    BigInt x;
    BigInt y;
    bigint_from_uint32(&x, 2000);
    bigint_from_uint32(&y, 5000);
    create_point(&p, &x, &y);
    create_point_from_uint32(&q, 2000, 5000);

    ASSERT_TRUE(point_are_equal(&p,&q));

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}

TEST(create_point_uint64, create_point_uint64)
{
    Point p, q;
    BigInt x;
    BigInt y;
    bigint_from_uint64(&x, 20000000);
    bigint_from_uint64(&y, 50000000);
    create_point(&p, &x, &y);
    create_point_from_uint64(&q, 20000000, 50000000);

    ASSERT_TRUE(point_are_equal(&p,&q));

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}

TEST(create_point_inf, create_point_inf)
{
    Point p;
    create_point_inf(&p);
    BigInt zero;
    bigint_from_uint32(&zero, 0);

    ASSERT_TRUE(bigint_are_equal(&(p.x), &(zero)));
    ASSERT_TRUE(bigint_are_equal(&(p.y), &(zero)));
    ASSERT_TRUE(p.is_at_infinity);

    bigint_free(&zero);
    point_free(&p);
}

TEST(point_is_on_curve, point_inf)
{
    EllipticCurveParameter params;
    create_parameters(&params);
    Point p;
    create_point_inf(&p);
    ASSERT_TRUE(point_is_on_curve(&p, &params));
    ec_free(&params);
    point_free(&p);
}

TEST(point_is_on_curve, point_on_curve)
{
    EllipticCurveParameter params;
    create_parameters(&params);
    Point p,q,r,s,t;
    create_point_from_uint32(&p, 16, 10);
    ASSERT_TRUE(point_is_on_curve(&p, &params));
    create_point_from_uint32(&q, 17, 7);
    ASSERT_TRUE(point_is_on_curve(&q, &params));
    create_point_from_uint32(&r, 27, 22);
    ASSERT_TRUE(point_is_on_curve(&r, &params));
    create_point_from_uint32(&s, 1, 8);
    ASSERT_TRUE(point_is_on_curve(&s, &params));
    create_point_from_uint32(&t, 3, 23);
    ASSERT_TRUE(point_is_on_curve(&t, &params));
    point_free(&p);
    point_free(&q);
    point_free(&r);
    point_free(&s);
    point_free(&t);
    ec_free(&params);
}

TEST(point_is_on_curve, point_not_on_curve)
{
    EllipticCurveParameter params;
    create_parameters(&params);
    Point p,q,r,s,t;
    create_point_from_uint32(&p, 0, 0);
    ASSERT_FALSE(point_is_on_curve(&p, &params));
    create_point_from_uint32(&q, 17, 8);
    ASSERT_FALSE(point_is_on_curve(&q, &params));
    create_point_from_uint32(&r, 27, 21);
    ASSERT_FALSE(point_is_on_curve(&r, &params));
    create_point_from_uint32(&s, 1, 4);
    ASSERT_FALSE(point_is_on_curve(&s, &params));
    create_point_from_uint32(&t, 3, 12);
    ASSERT_FALSE(point_is_on_curve(&t, &params));
    point_free(&p);
    point_free(&q);
    point_free(&r);
    point_free(&s);
    point_free(&t);
    ec_free(&params);
}

TEST(copy_point, copy_point)
{
    Point p, q;
    BigInt x;
    BigInt y;
    bigint_from_hex_string(&x, "FFCC");
    bigint_from_hex_string(&y, "CCFF");
    create_point(&p, &x, &y);
    point_copy(&q, &p);

    ASSERT_TRUE(bigint_are_equal(&(p.x), &(q.x)));
    ASSERT_TRUE(bigint_are_equal(&(p.y), &(q.y)));
    ASSERT_TRUE(p.is_at_infinity == q.is_at_infinity);

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}

TEST(point_are_equal, different_x_coordinate)
{
    Point p, q;
    BigInt x1;
    BigInt x2;
    BigInt y;
    bigint_from_hex_string(&x1, "FFCC");
    bigint_from_hex_string(&x2, "FFCCDDDDDDD");
    bigint_from_hex_string(&y, "CCFF");
    
    create_point(&p, &x1, &y);
    create_point(&q, &x2, &y);
    ASSERT_FALSE(point_are_equal(&p, &q));

    bigint_free(&x1);
    bigint_free(&x2);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}

TEST(point_are_equal, different_y_coordinate)
{
    Point p, q;
    BigInt x;
    BigInt y1;
    BigInt y2;
    bigint_from_hex_string(&x, "FFCC");
    bigint_from_hex_string(&y1, "FFCCDDDDDDD");
    bigint_from_hex_string(&y2, "CCFF");
    
    create_point(&p, &x, &y1);
    create_point(&q, &x, &y2);
    ASSERT_FALSE(point_are_equal(&p, &q));

    bigint_free(&x);
    bigint_free(&y1);
    bigint_free(&y2);
    point_free(&p);
    point_free(&q);
}

TEST(point_are_equal, inf)
{
    Point p, q;
    BigInt x;
    BigInt y;
    bigint_from_hex_string(&x, "FFCC");
    bigint_from_hex_string(&y, "FFCCDDDDDDD");
    
    create_point(&p, &x, &y);
    create_point_inf(&q);
    ASSERT_FALSE(point_are_equal(&p, &q));

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}
