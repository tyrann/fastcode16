
extern "C" {
    #include "bigint.h"
}
#include "gtest/gtest.h"

// Test bigint_clear function
TEST(bigint_clear_test, clear_test)
{
    bigint_create_buffer();
    
    BigInt bigint = GET_BIGINT_PTR(BI_TESTS_A_TAG);
    bigint->significant_octets = 2;
    bigint->octets[0] = 0xF4;
    bigint->octets[1] = 0x23;
    bigint_clear(bigint);
    
    EXPECT_EQ(bigint->significant_octets, 1);
    EXPECT_EQ(bigint->octets[0], 0);
    
    bigint_destroy_buffer();
}


// Test equality for BigInts
TEST(bigint_equality_test, test_equality)
{
    bigint_create_buffer();
    
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "000123837483928ABCDEF7678EDBAC76EF67BA768D");
    BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "123837483928ABCDEF7678EDBAC76EF67BA768D");
    
    int are_equal = bigint_are_equal(a, b);
    
    EXPECT_EQ(are_equal, 1);
    
    bigint_destroy_buffer();
}

TEST(bigint_equality_test, test_inequality)
{
    bigint_create_buffer();
    
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "123837483928ABCDEF7678EDBAC76EF67BA768D");
    BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "123837483928ABCDE27678EDBAC76EF67BA768D");
    
    int are_equal = bigint_are_equal(a, b);
    
    EXPECT_EQ(are_equal, 0);
    
    bigint_destroy_buffer();
}

// Test bigint_is_even funciton
TEST(bigint_is_even, check_even)
{
    bigint_create_buffer();
    
    BigInt a1 = bigint_from_uint32(BI_TESTS_A_TAG, 2);
    ASSERT_TRUE(bigint_is_even(a1));
    
    a1 = bigint_from_uint32(BI_TESTS_A_TAG, 4);
    ASSERT_TRUE(bigint_is_even(a1));

    a1 = bigint_from_hex_string(BI_TESTS_A_TAG, "7FFFFFFFFFFFFFFE");
    ASSERT_TRUE(bigint_is_even(a1));
    
    bigint_create_buffer();
}

TEST(bigint_is_even, check_odd)
{
    bigint_create_buffer();
    
    BigInt a1 = bigint_from_uint32(BI_TESTS_A_TAG, 1);
    ASSERT_FALSE(bigint_is_even(a1));
    
    a1 = bigint_from_uint32(BI_TESTS_A_TAG, 3);
    ASSERT_FALSE(bigint_is_even(a1));
    
    a1 = bigint_from_hex_string(BI_TESTS_A_TAG, "7FFFFFFFFFFFFFFD");
    ASSERT_FALSE(bigint_is_even(a1));
    
    bigint_destroy_buffer();
}

// Test BigInt copy
TEST(bigint_copy_test, test_copy)
{
    bigint_create_buffer();
    
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "AB76C87D5FE78DB789A789D8CDFFE7EFD89CAB876A");
    BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
    bigint_copy(b, a);
    
    int are_equal = bigint_are_equal(a, b);
    EXPECT_EQ(are_equal, 1);
    
    bigint_destroy_buffer();
}

// Test BigInt greater than
TEST(bigint_greater_than, check_greater_than)
{
    bigint_create_buffer();
    
    BigInt a1 = bigint_from_uint32(BI_TESTS_A_TAG, 1);
    BigInt a2 = bigint_from_uint32(BI_TESTS_B_TAG, 3);

    ASSERT_FALSE(bigint_is_greater(a1,a2));

	a1 = bigint_from_uint32(BI_TESTS_A_TAG, 2836);
	a2 = bigint_from_uint32(BI_TESTS_B_TAG, 2835);

	ASSERT_TRUE(bigint_is_greater(a1, a2));
	
    a1 = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFFFFFFFFFFF");
	a2 = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFFFFFFFFFFFFFA");

	ASSERT_TRUE(bigint_is_greater(a1,a2));

	bigint_destroy_buffer();
}

TEST(bigint_greater_than, check_greater_than_0)
{
    bigint_create_buffer();
    
	BigInt a1 = bigint_from_uint32(BI_TESTS_A_TAG, 0);
	BigInt a2 = bigint_from_uint32(BI_TESTS_B_TAG, 0);

	ASSERT_FALSE(bigint_is_greater(a1, a2));
	
    a1 = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFFFFFFFFFFF");
	a2 = bigint_from_hex_string(BI_TESTS_B_TAG, "0");

	ASSERT_TRUE(bigint_is_greater(a1, a2));

    bigint_destroy_buffer();
}