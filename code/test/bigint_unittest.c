#include "../src/bigint.h"
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

// Test conversion from uint32 to BigInt 
TEST(bigint_from_uint32_test, test_conversion)
{
    uint32_t num = 0x114499FF;
    BigInt bigint;
    bigint_from_uint32(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 4);
    EXPECT_EQ(bigint.significant_octets, 4);
    EXPECT_EQ(((uint32_t*)bigint.octets)[0], num);
    
    bigint_free(&bigint);
}

// Test conversion from uint64 to BigInt 
TEST(bigint_from_uint64_test, test_conversion)
{
    uint64_t num = 0x1F33B419AA3DF2C0ULL;
    BigInt bigint;
    bigint_from_uint64(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 8);
    EXPECT_EQ(bigint.significant_octets, 8);
    EXPECT_EQ(((uint64_t*)bigint.octets)[0], num);
    
    bigint_free(&bigint);
}

TEST(bigint_from_uint64_test, test_zero_conversion)
{
    uint64_t num = 0x0ULL;
    BigInt bigint;
    bigint_from_uint64(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 1);
    EXPECT_EQ(bigint.significant_octets, 1);
    EXPECT_EQ(*bigint.octets, 0);
    
    bigint_free(&bigint);
}

TEST(bigint_from_uint64_test, test_small_conversion)
{
    uint64_t num = 0x4FCD7B8A3ULL;
    BigInt bigint;
    bigint_from_uint64(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 5);
    EXPECT_EQ(bigint.significant_octets, 5);
    EXPECT_EQ(bigint.octets[4], num >> (4 * 8));
    EXPECT_EQ(((uint32_t*)bigint.octets)[0], (uint32_t)(num & 0xFFFFFFFFULL));
    
    bigint_free(&bigint);
}

// Test string to BigInt conversion
TEST(bigint_from_hex_string_test, test_conversion)
{
    char num[] = "F123456789ABCDEF0FEDCBA9876543210";
    BigInt bigint;
    bigint_from_hex_string(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 17);
    EXPECT_EQ(bigint.significant_octets, 17);
    EXPECT_EQ(((uint64_t*)bigint.octets)[0], 0xFEDCBA9876543210ULL);
    EXPECT_EQ(((uint64_t*)bigint.octets)[1], 0x123456789ABCDEF0ULL);
    EXPECT_EQ(((char*)bigint.octets)[16], 0x0F);
    
    bigint_free(&bigint);
}

TEST(bigint_from_hex_string_test, test_zero_conversion)
{
    char num[] = "0";
    BigInt bigint;
    bigint_from_hex_string(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 1);
    EXPECT_EQ(bigint.significant_octets, 1);
    EXPECT_EQ(*bigint.octets, 0);
    
    bigint_free(&bigint);
}

TEST(bigint_from_hex_string_test, test_small_conversion)
{
    char num[] = "000A";
    BigInt bigint;
    bigint_from_hex_string(&bigint, num);
    
    EXPECT_EQ(bigint.allocated_octets, 1);
    EXPECT_EQ(bigint.significant_octets, 1);
    EXPECT_EQ(bigint.octets[0], 0xA);
    
    bigint_free(&bigint);
}

// Test BigInt to string conversion
TEST(bigint_to_hex_string_test, test_conversion)
{
    uint64_t num_data[] = {
        0xFEDCBA9876543220ULL,
        0x123456789ABCDEF0ULL,
        0xFULL
    };
    
    BigInt bigint = { 17, 17, (char*)num_data };
    char* num_string = bigint_to_hex_string(&bigint);
    char expected_string[] = "F123456789ABCDEF0FEDCBA9876543220";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    free(num_string);
}

TEST(bigint_to_hex_string_test, test_zero_conversion)
{
    char num_data[] = { 0x0 };
    
    BigInt bigint = { 1, 1, (char*)num_data };
    char* num_string = bigint_to_hex_string(&bigint);
    char expected_string[] = "0";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    free(num_string);
}

TEST(bigint_to_hex_string_test, test_small_odd_conversion)
{
    char num_data[] = { 0x0F };
    
    BigInt bigint = { 1, 1, (char*)num_data };
    char* num_string = bigint_to_hex_string(&bigint);
    char expected_string[] = "F";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    free(num_string);
}

TEST(bigint_to_hex_string_test, test_small_even_conversion)
{
    char num_data[] = { 0x2A };
    
    BigInt bigint = { 1, 1, (char*)num_data };
    char* num_string = bigint_to_hex_string(&bigint);
    char expected_string[] = "2A";
    
    EXPECT_EQ(strcmp(num_string, expected_string), 0);
    free(num_string);
}