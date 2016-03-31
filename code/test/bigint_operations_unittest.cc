
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

// Test BigInt add
TEST(bigint_add_inplace, test_add)
{
    BigInt a, b, c;	
	bigint_from_uint64(&a,98349869483274);
	bigint_from_uint64(&b,25213123210954);
	bigint_from_uint64(&c,123562992694228);
    bigint_add_inplace(&a, &b);
    int are_equal = bigint_are_equal(&a, &c);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a);
    bigint_free(&b);
	bigint_free(&c);
}
// Test BigInt sub
TEST(bigint_sub_inplace, test_sub)
{
    BigInt a, b, c;	
	bigint_from_uint64(&a,98349869483274);
	bigint_from_uint64(&b,25213123210954);
	bigint_from_uint64(&c,73136746272320);
    bigint_sub_inplace(&a, &b);
    int are_equal = bigint_are_equal(&a, &c);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a);
    bigint_free(&b);
	bigint_free(&c);
}