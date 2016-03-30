extern "C" {
    #include "../src/ec_point.h"
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

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
    ASSERT_FALSE(p.is_at_infinity);
    ASSERT_FALSE(q.is_at_infinity);

    bigint_free(&x);
    bigint_free(&y);
    point_free(&p);
    point_free(&q);
}

