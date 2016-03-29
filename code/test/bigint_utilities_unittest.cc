
extern "C" {
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

// Test bigint_free function
TEST(bigint_free_test, free_test)
{
    BigInt bigint = { 1, 1, (char*)malloc(1 * sizeof(char)) };
    bigint_free(&bigint);
    
    EXPECT_EQ(bigint.allocated_octets, 0);
    EXPECT_EQ(bigint.significant_octets, 0);
    EXPECT_EQ(bigint.octets, (char*)0);
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