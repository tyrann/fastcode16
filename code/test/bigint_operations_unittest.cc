
extern "C" {
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

TEST(bigint_is_even, check_even)
{
    BigInt a1;
    bigint_from_uint32(&a1, 2);
    ASSERT_TRUE(bigint_is_even(&a1));
    bigint_free(&a1);
    
    bigint_from_uint32(&a1, 4);
    ASSERT_TRUE(bigint_is_even(&a1));
    bigint_free(&a1);

    bigint_from_hex_string(&a1, "7FFFFFFFFFFFFFFE");
    ASSERT_TRUE(bigint_is_even(&a1));
    bigint_free(&a1);
}

TEST(bigint_is_even, check_odd)
{
    BigInt a1;
    bigint_from_uint32(&a1, 1);
    ASSERT_FALSE(bigint_is_even(&a1));
    bigint_free(&a1);
    
    bigint_from_uint32(&a1, 3);
    ASSERT_FALSE(bigint_is_even(&a1));
    bigint_free(&a1);

    bigint_from_hex_string(&a1, "7FFFFFFFFFFFFFFD");
    ASSERT_FALSE(bigint_is_even(&a1));
    bigint_free(&a1);
}
