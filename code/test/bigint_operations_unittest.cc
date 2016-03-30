
extern "C" {
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

// Test bigint_is_even funciton
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

// Test left shift
TEST(bigint_left_shift_inplace, test_same_size)
{
    BigInt a, expected;
    bigint_from_hex_string(&a, "0");
    bigint_from_hex_string(&expected, "0");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 1);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "8");
    bigint_from_hex_string(&expected, "10");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 1);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "7F");
    bigint_from_hex_string(&expected, "FE");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 1);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "466962f6e91eaaf80e4803ffffffe003");
    bigint_from_hex_string(&expected, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 16);
    ASSERT_EQ(a.significant_octets, 16);
    bigint_free(&a);
    bigint_free(&expected);
}

TEST(bigint_left_shift_inplace, test_different_size)
{
    BigInt a, expected;
    bigint_from_hex_string(&a, "80");
    bigint_from_hex_string(&expected, "100");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 2);
    ASSERT_EQ(a.significant_octets, 2);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "FF");
    bigint_from_hex_string(&expected, "1FE");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 2);
    ASSERT_EQ(a.significant_octets, 2);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_from_hex_string(&expected, "119a58bdba47aabe039200fffffff800c");
    bigint_left_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 17);
    ASSERT_EQ(a.significant_octets, 17);
    bigint_free(&a);
    bigint_free(&expected);
}

// Test right shift
TEST(bigint_right_shift_inplace, test_same_size)
{
    BigInt a, expected;
    bigint_from_hex_string(&a, "0");
    bigint_from_hex_string(&expected, "0");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 1);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "10");
    bigint_from_hex_string(&expected, "8");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 1);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "FF");
    bigint_from_hex_string(&expected, "7F");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 1);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "8cd2c5edd23d55f01c9007ffffffc007");
    bigint_from_hex_string(&expected, "466962f6e91eaaf80e4803ffffffe003");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 16);
    ASSERT_EQ(a.significant_octets, 16);
    bigint_free(&a);
    bigint_free(&expected);
}

TEST(bigint_right_shift_inplace, test_different_size)
{
    BigInt a, expected;
    bigint_from_hex_string(&a, "100");
    bigint_from_hex_string(&expected, "80");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 2);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "1FF");
    bigint_from_hex_string(&expected, "FF");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 2);
    ASSERT_EQ(a.significant_octets, 1);
    bigint_free(&a);
    bigint_free(&expected);

    bigint_from_hex_string(&a, "119a58bdba47aabe039200fffffff800c");
    bigint_from_hex_string(&expected, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_right_shift_inplace(&a);
    ASSERT_EQ(bigint_are_equal(&a, &expected), 1);
    ASSERT_EQ(a.allocated_octets, 17);
    ASSERT_EQ(a.significant_octets, 16);
    bigint_free(&a);
    bigint_free(&expected);
}