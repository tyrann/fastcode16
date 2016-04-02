
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

TEST(bigint_greater_than, check_greater_than)
{
    BigInt a1;
	BigInt a2;

    bigint_from_uint32(&a1, 1);
    bigint_from_uint32(&a2, 3);

    ASSERT_FALSE(bigint_is_greater(&a1,&a2));
    bigint_free(&a1);
	bigint_free(&a2);

	BigInt a3;
	BigInt a4;

	bigint_from_uint32(&a3, 2836);
	bigint_from_uint32(&a4, 2835);

	ASSERT_TRUE(bigint_is_greater(&a3, &a4));
	
	bigint_free(&a3);
	bigint_free(&a4);

	BigInt b1;
	BigInt b2;

	bigint_from_hex_string(&b1, "FFFFFFFFFFFFFFFFF");
	bigint_from_hex_string(&b2, "FFFFFFFFFFFFFFFFA");

	ASSERT_TRUE(bigint_is_greater(&b1,&b2));

	bigint_free(&b1);
	bigint_free(&b2);
    

}
TEST(bigint_greater_than, check_greater_than_0)
{
    	
	BigInt a5;
	BigInt a6;
	bigint_from_uint32(&a5, 0);
	bigint_from_uint32(&a6, 0);

	ASSERT_FALSE(bigint_is_greater(&a5, &a6));
	bigint_free(&a5);
	bigint_free(&a6);
	
	BigInt a1;
	BigInt a2;

	bigint_from_hex_string(&a1, "FFFFFFFFFFFFFFFFF");
	bigint_from_hex_string(&a2, "0");

	ASSERT_TRUE(bigint_is_greater(&a1,&a2));

	bigint_free(&a1);
	bigint_free(&a2); 

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
