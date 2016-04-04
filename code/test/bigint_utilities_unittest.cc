
extern "C" {
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

// Test bigint_free function
TEST(bigint_free_test, free_test)
{
    BigInt bigint = { 1, 1, (uchar*)malloc(1 * sizeof(uchar)) };
    bigint_free(&bigint);
    
    EXPECT_EQ(bigint.allocated_octets, 0);
    EXPECT_EQ(bigint.significant_octets, 0);
    EXPECT_EQ(bigint.octets, (uchar*)0);
}


// Test equality for BigInts
TEST(bigint_equality_test, test_equality)
{
    BigInt a, b;
    bigint_from_hex_string(&a, "000123837483928ABCDEF7678EDBAC76EF67BA768D");
    bigint_from_hex_string(&b, "123837483928ABCDEF7678EDBAC76EF67BA768D");
    
    int are_equal = bigint_are_equal(&a, &b);
    
    EXPECT_EQ(are_equal, 1);
    
    bigint_free(&a);
    bigint_free(&b);
}

TEST(bigint_equality_test, test_inequality)
{
    BigInt a, b;
    bigint_from_hex_string(&a, "123837483928ABCDEF7678EDBAC76EF67BA768D");
    bigint_from_hex_string(&b, "123837483928ABCDE27678EDBAC76EF67BA768D");
    
    int are_equal = bigint_are_equal(&a, &b);
    
    EXPECT_EQ(are_equal, 0);
    
    bigint_free(&a);
    bigint_free(&b);
}

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

// Test BigInt copy
TEST(bigint_copy_test, test_copy)
{
    BigInt a, b;
    bigint_from_hex_string(&a, "AB76C87D5FE78DB789A789D8CDFFE7EFD89CAB876A");
    bigint_copy(&b, &a);
    
    int are_equal = bigint_are_equal(&a, &b);
    EXPECT_EQ(are_equal, 1);
    
    bigint_free(&a);
    bigint_free(&b);
}

// Test BigInt greater than
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