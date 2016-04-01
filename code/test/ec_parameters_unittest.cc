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
