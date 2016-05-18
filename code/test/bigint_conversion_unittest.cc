
extern "C" {
    #include "bigint.h"
}
#include "gtest/gtest.h"


// Test conversion from uint64 to BigInt 
TEST(bigint_from_uint64_test, test_conversion)
{
    bigint_create_buffer();
    
    uint64_t num = 0x1F33B419AA3DF2C0ULL;
    BigInt bigint = bigint_from_uint64(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_blocks, 1);
    EXPECT_EQ(bigint->blocks[0], num);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_uint64_test, test_zero_conversion)
{
    bigint_create_buffer();
    
    uint64_t num = 0x0ULL;
    BigInt bigint = bigint_from_uint64(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_blocks, 1);
    EXPECT_EQ(bigint->blocks[0], 0);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_uint64_test, test_small_conversion)
{
    bigint_create_buffer();
    
    uint64_t num = 0x4FCD7B8A3ULL;
    BigInt bigint = bigint_from_uint64(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_blocks, 5);
    EXPECT_EQ(((uint32_t*)bigint->blocks)[0], (uint32_t)(num & 0xFFFFFFFFULL));
    EXPECT_EQ(((uint32_t*)bigint->blocks)[1], num >> (4 * 8));
    
    bigint_destroy_buffer();
}

// Test string to BigInt conversion
TEST(bigint_from_hex_string_test, test_conversion)
{
    bigint_create_buffer();
    
    char num[] = "F123456789ABCDEF0FEDCBA9876543210";
    BigInt bigint = bigint_from_hex_string(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_blocks, 3);
    EXPECT_EQ(bigint->blocks[0], 0xFEDCBA9876543210ULL);
    EXPECT_EQ(bigint->blocks[1], 0x123456789ABCDEF0ULL);
    EXPECT_EQ(bigint->blocks[2], 0x0FULL);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_hex_string_test, test_zero_conversion)
{
    bigint_create_buffer();
    
    char num[] = "0";
    BigInt bigint = bigint_from_hex_string(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_blocks, 1);
    EXPECT_EQ(*bigint->blocks, 0);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_hex_string_test, test_small_conversion)
{
    bigint_create_buffer();
    
    char num[] = "000A";
    BigInt bigint = bigint_from_hex_string(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_blocks, 1);
    EXPECT_EQ(bigint->blocks[0], 0xA);
    
    bigint_destroy_buffer();
}

// Test BigInt to string conversion
TEST(bigint_to_hex_string_test, test_conversion)
{
    bigint_create_buffer();
    
    uint64_t num_data[] = {
        0xFEDCBA9876543220ULL,
        0x123456789ABCDEF0ULL,
        0xFULL
    };
    
    BigInt bigint = GET_BIGINT_PTR(BI_TESTS_A_TAG);
    bigint->significant_blocks = 3;
    memcpy(bigint->blocks, num_data, 3*8);
    char* num_string = bigint_to_hex_string(bigint);
    char expected_string[] = "F123456789ABCDEF0FEDCBA9876543220";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    
    free(num_string);
    bigint_destroy_buffer();
}

TEST(bigint_to_hex_string_test, test_zero_conversion)
{
    bigint_create_buffer();
    
    char num_data[] = { 0x0 };
    
    BigInt bigint = GET_BIGINT_PTR(BI_TESTS_A_TAG);
    bigint->significant_blocks = 1;
    memcpy(bigint->blocks, num_data, 1);
    char* num_string = bigint_to_hex_string(bigint);
    char expected_string[] = "0";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    
    free(num_string);
    bigint_destroy_buffer();
}

TEST(bigint_to_hex_string_test, test_small_odd_conversion)
{
    bigint_create_buffer();
    
    char num_data[] = { 0x0F };
    
    BigInt bigint = GET_BIGINT_PTR(BI_TESTS_A_TAG);
    bigint->significant_blocks = 1;
    memcpy(bigint->blocks, num_data, 1);
    char* num_string = bigint_to_hex_string(bigint);
    char expected_string[] = "F";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    
    free(num_string);
    bigint_destroy_buffer();
}

TEST(bigint_to_hex_string_test, test_small_even_conversion)
{
    bigint_create_buffer();
    
    char num_data[] = { 0x2A };
    
    BigInt bigint = GET_BIGINT_PTR(BI_TESTS_A_TAG);
    bigint->significant_blocks = 1;
    memcpy(bigint->blocks, num_data, 1);
    char* num_string = bigint_to_hex_string(bigint);
    char expected_string[] = "2A";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    
    free(num_string);
    bigint_destroy_buffer();
}