
extern "C" {
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

// Test conversion from uint32 to BigInt 
TEST(bigint_from_uint32_test, test_conversion)
{
    bigint_create_buffer();
    
    uint32_t num = 0x114499FF;
    BigInt bigint = bigint_from_uint32(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 4);
    EXPECT_EQ(((uint32_t*)bigint->octets)[0], num);
    
    bigint_destroy_buffer();
}

// Test conversion from uint64 to BigInt 
TEST(bigint_from_uint64_test, test_conversion)
{
    bigint_create_buffer();
    
    uint64_t num = 0x1F33B419AA3DF2C0ULL;
    BigInt bigint = bigint_from_uint64(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 8);
    EXPECT_EQ(((uint64_t*)bigint->octets)[0], num);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_uint64_test, test_zero_conversion)
{
    bigint_create_buffer();
    
    uint64_t num = 0x0ULL;
    BigInt bigint = bigint_from_uint64(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 1);
    EXPECT_EQ(*bigint->octets, 0);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_uint64_test, test_small_conversion)
{
    bigint_create_buffer();
    
    uint64_t num = 0x4FCD7B8A3ULL;
    BigInt bigint = bigint_from_uint64(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 5);
    EXPECT_EQ(bigint->octets[4], num >> (4 * 8));
    EXPECT_EQ(((uint32_t*)bigint->octets)[0], (uint32_t)(num & 0xFFFFFFFFULL));
    
    bigint_destroy_buffer();
}

// Test string to BigInt conversion
TEST(bigint_from_hex_string_test, test_conversion)
{
    bigint_create_buffer();
    
    char num[] = "F123456789ABCDEF0FEDCBA9876543210";
    BigInt bigint = bigint_from_hex_string(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 17);
    EXPECT_EQ(((uint64_t*)bigint->octets)[0], 0xFEDCBA9876543210ULL);
    EXPECT_EQ(((uint64_t*)bigint->octets)[1], 0x123456789ABCDEF0ULL);
    EXPECT_EQ(((char*)bigint->octets)[16], 0x0F);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_hex_string_test, test_zero_conversion)
{
    bigint_create_buffer();
    
    char num[] = "0";
    BigInt bigint = bigint_from_hex_string(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 1);
    EXPECT_EQ(*bigint->octets, 0);
    
    bigint_destroy_buffer();
}

TEST(bigint_from_hex_string_test, test_small_conversion)
{
    bigint_create_buffer();
    
    char num[] = "000A";
    BigInt bigint = bigint_from_hex_string(BI_TESTS_A_TAG, num);
    
    EXPECT_EQ(bigint->significant_octets, 1);
    EXPECT_EQ(bigint->octets[0], 0xA);
    
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
    bigint->significant_octets = 17;
    memcpy(bigint->octets, num_data, 17);
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
    bigint->significant_octets = 1;
    memcpy(bigint->octets, num_data, 1);
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
    bigint->significant_octets = 1;
    memcpy(bigint->octets, num_data, 1);
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
    bigint->significant_octets = 1;
    memcpy(bigint->octets, num_data, 1);
    char* num_string = bigint_to_hex_string(bigint);
    char expected_string[] = "2A";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    
    free(num_string);
    bigint_destroy_buffer();
}