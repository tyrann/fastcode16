
extern "C" {
    #include "bigint.h"
	#include "logging/logging.h"
}
#include "gtest/gtest.h"
#include <inttypes.h>

// Test BigInt add
TEST(bigint_add_inplace, test_add)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 98349869483274);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 25213123210954);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 123562992694228);
    bigint_add_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    
    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_zero)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 0);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 4);
	
	bigint_add_inplace(a,b);
	ASSERT_TRUE(bigint_are_equal(a, b));

    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF00000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1000000000000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "100FF00000000000000");
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 2);
    
    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_inversed)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFE00000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "010200000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "10000010000000000");
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 2);

    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_mem)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFFFFFFFFFFFFF");
	
	ASSERT_EQ(a->significant_blocks, 1);
	ASSERT_EQ(b->significant_blocks, 1);

	bigint_add_inplace(a, b);
	ASSERT_EQ(a->significant_blocks, 2);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem2)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1FFAFF0000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "10000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1FFB000000000000");

	ASSERT_EQ(a->significant_blocks, 1);
	ASSERT_EQ(b->significant_blocks, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 1);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem3)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1FFAFF0000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1FFB000000000000");

	ASSERT_EQ(a->significant_blocks, 1);
	ASSERT_EQ(b->significant_blocks, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 1);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem4)
{
    bigint_create_buffer();

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FAFF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FB00");

	ASSERT_EQ(a->significant_blocks, 1);
	ASSERT_EQ(b->significant_blocks, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 1);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem5)
{
    bigint_create_buffer();

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FE00000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "100000000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FF00000000000000");

	ASSERT_EQ(a->significant_blocks, 1);
	ASSERT_EQ(b->significant_blocks, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 1);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem6)
{
    bigint_create_buffer();

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FF00000000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "10000000000000000");

	ASSERT_EQ(a->significant_blocks, 1);
	ASSERT_EQ(b->significant_blocks, 1);
	
	bigint_add_inplace(a, b);

	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_blocks, 2);
	
    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, large_number)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "508E4AA1C1FE6527C419418CC50AA59CCDF2E5C4C0A1F3B2452A9DC01397D8D6BF88C311CCA797AEA6DA4AEA3C78808");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "91BB5C22AE9EF6E7E1FAEED5C31F792082352CF807B7DFE9D300053895AFE1A1E24BBA4EE4092B18F868638C16A626");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "59AA0063ECE854964238F07A213C9D2ED6163894411D71B0E25A9E139CF2D6F0DDAD7EB6BAE82A603660D122FDE2E2E");
	
    bigint_add_inplace(a, b);

    ASSERT_TRUE(bigint_are_equal(a, c));
    
    bigint_destroy_buffer();
}

// Test BigInt sub
TEST(bigint_sub_inplace, sub_test_1)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FFFFFFFFFFFFFFFF");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
	
	bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_2)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "0");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);    
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_3)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 0);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 0);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 0);
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    ASSERT_EQ(a->significant_blocks, 1);
    EXPECT_EQ(are_equal, 1);    
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_4)
{	
    bigint_create_buffer();
    	
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 1);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 0);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 1);
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_5)
{	
    bigint_create_buffer();	
	
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FE");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_6)
{		
    bigint_create_buffer();
		
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 98349869483274);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 25213123210954);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 73136746272320);
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_7)
{	
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "2000000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1000000000000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1000000000000000000");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 2);	
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_8)
{	
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FF1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FFFFFFFFFFFFF00F");
    ASSERT_EQ(a->significant_blocks, 2);
	bigint_sub_inplace(a, b);	
	int are_equal = bigint_are_equal(a, c);
	EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);		
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_9)
{	
    bigint_create_buffer();
    			
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFFFFFFFFFFFFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);	
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_10)
{	
    bigint_create_buffer();
    			
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FFFFFFFFFFFFF");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);   
    ASSERT_EQ(a->significant_blocks, 1);
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_11)
{	
    bigint_create_buffer();
    			
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FF");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_12)
{	
    bigint_create_buffer();		
    	
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFFFFFFFFFF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FFFFFFFFFFFFFFFE");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1); 
    ASSERT_EQ(a->significant_blocks, 1);		
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_13)
{	
    bigint_create_buffer();		
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FB0000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "100000000000000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FAFF00000000000000");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);    
    ASSERT_EQ(a->significant_blocks, 2);	
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, test_sub)
{	
    bigint_create_buffer();
    	
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFFFFFFFFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "F000000000001");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_blocks, 1);		
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, test_sub_large1)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "93FA234AFF0ACC23");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "8AB44BEFCD89");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "93F99896B31AFE9A");
	
	bigint_sub_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
    ASSERT_EQ(a->significant_blocks, 1);	
	
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, test_sub_large2)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_B_TAG, "ffffdec387488efce9de90a977ecfe981262fd3651");
	BigInt b = bigint_from_hex_string(BI_TESTS_A_TAG,    "234787dca89873478efc3487dc2398a0000398d");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "fffdaa4b097e0575b565a0e62f6f3c5e8862fcfcc4");
	
	bigint_sub_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
    ASSERT_EQ(a->significant_blocks, 3);	
	
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, test_sub_large3)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "23878e732f3ecfcfdf392facf912321998fceabbbc0");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "23878e732f3ecfcfdf392f23487f7777cc87009840f");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "89b092baa1cc75ea237b1");
	
	bigint_sub_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
    ASSERT_EQ(a->significant_blocks, 2);	
	
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, bad_memory_acces)
{
    bigint_create_buffer();
    
    int are_equal;
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1000000000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFFFFFFFFFFFFFFFFFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1");
    bigint_sub_inplace(a, b);
    are_equal = bigint_are_equal(a, c);
    ASSERT_EQ(a->significant_blocks, 1);	
    EXPECT_EQ(are_equal, 1);    
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, very_large_number)
{
    bigint_create_buffer();
    
    int are_equal;
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "2A94608F8D29FBB7AF52D1BC1667F505440CC75CABABDC5961BFCC9F54DADD1A4000000000000000000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "2A94608F8D29FBB7AF52D1BC1667F505440CC75CABABDC5961BFCC9F54DADD1A3FFFFFFFFFFFFFFFFFFFFFFFFFFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1");
    bigint_sub_inplace(a, b);
    are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);    
    ASSERT_EQ(a->significant_blocks, 1);	
    
    bigint_destroy_buffer();
}

// Test left shift
TEST(bigint_left_shift_inplace, test_same_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "0");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "0");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "8");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "10");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "7F");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "FE");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "466962f6e91eaaf80e4803ffffffe003");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 2);
    
    bigint_destroy_buffer();
}

TEST(bigint_left_shift_inplace, test_different_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "80");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "100");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFFFFFFFFFF");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "1FFFFFFFFFFFFFFFE");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 2);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "119a58bdba47aabe039200fffffff800c");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 3);
    
    bigint_destroy_buffer();
}

// Test right shift
TEST(bigint_right_shift_inplace, test_same_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "0");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "0");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "10");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFFFFFFFFFF");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "7FFFFFFFFFFFFFFF");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc007");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "466962f6e91eaaf80e4803ffffffe003");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 2);
    
    bigint_destroy_buffer();
}

TEST(bigint_right_shift_inplace, test_different_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "80");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "1FFFFFFFFFFFFFFFF");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "FFFFFFFFFFFFFFFF");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "119a58bdba47aabe039200fffffff800c");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_blocks, 2);
    
    bigint_destroy_buffer();
}

TEST(bigint_montgomery_convert, test_big_numbers_1)
{
    bigint_create_buffer();
    
    BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "6d09acdef99ad700431e77edcd980a3a54594d6e79a6657a68c7b");
    BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "f730a1cf9f75e49d796ab57b016187c97d23899d548bb4cd3c9243cb71b6b130");
    
    __montgomery_convert(b, a, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "19f7dd97453df6cb19aa8120882a211ee82d59a584e5b833e16968640");
	p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "22975b43cd66ef93e142e006ab5bb9522981ab20121a661f432bc566544a9f61");
    
    __montgomery_convert(b, a, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));
    
    bigint_destroy_buffer();
}

TEST(bigint_montgomery_revert, test_big_numbers_2)
{
    bigint_create_buffer();
    
	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "6d09acdef99ad700431e77edcd980a3a54594d6e79a6657a68c7b");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "f730a1cf9f75e49d796ab57b016187c97d23899d548bb4cd3c9243cb71b6b130");
    
    __montgomery_revert(b, a, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "22975b43cd66ef93e142e006ab5bb9522981ab20121a661f432bc566544a9f61");
	p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "19f7dd97453df6cb19aa8120882a211ee82d59a584e5b833e16968640");
    
    __montgomery_revert(b, a, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));
    
    bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP192K1_0)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "0");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "0");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "118427b3b4a05bc8a8a4de8459867fffffffffff");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
    __montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP192K1_1)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "118427b3b4a05bc8a8a4de8459867fffffffffff");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "1");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "118427b3b4a05bc8a8a4de8459867fffffffffff");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP192K1)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "fc43c1fd4b39ad4a13be38a5e95f6237fd79726838ad5a2a");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "c1d420185df71b4d6473d45a552a4de2c476d2653ec8c699");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "118427b3b4a05bc8a8a4de8459867fffffffffff");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP224R1)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "810f29bd7ac72fb7f6de8d43d2b00327f9d77c50ad490fd9ef9d9208");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "c1d420185df71b4d6473d45a552a4de2c476d2653ec8c699");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "118427b3b4a05bc8a8a4de8459867fffffffffff");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);

    ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP256K1)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "cacdeaeb50e91372ecda1308802be761726d3a3410fd888205126ea8a4aaf126");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "fa2c4119aa6706576f4e45b29dbd1a41fb90d7a9d4b797b5251868f7ff1f304c");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "1d39528e9b55885f473cf2e28ef905737e940892f00a6842263c39f23f17206");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);

    ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP384R1)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "27324cd17ba42220938b6b05507048c101d9e52fa7264e7ca33f8d0d2de59e4099ff53c1e560c64f0a2f7733ef3b153b");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "5bd7a6692433aa9391f2480bf5aeb6f335a7d64f435e4a308825082f63d029641ccae28f449f7eea926320c4b07fde71");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "6780202797a27886abe780242d8e919613947b782b08b749218f33fea919267cbdb6983a91dc011c5ae14849e1bbc2c9");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));

    expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "f743802591af86f812e6e3a051a2be73cadebd46f007ef58e612c956dd0bd7f1873169ae609c0b3a362ce22b9c840ce7");
	x = bigint_from_hex_string(BI_TESTS_X_TAG, "a7c12ab7308fd7a8064cf68ac5e0ea2698f4e9c25002a51da206431cf45947fad7bb2339cadeae68bcb9a0b9898159a2");
	y = bigint_from_hex_string(BI_TESTS_Y_TAG, "3");
	x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
	__montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));

    expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "c0b77f45a89c62153e28eb851d267873c345deb129ccb63b66305e422c796a5e5ae3fb9d3b5362992cbe0852620783be");
	x = bigint_from_hex_string(BI_TESTS_X_TAG, "605bbfa2d44e310a9f1475c28e933c39e1a2ef5894e65b1db3182f21163cb52f2d71fdce9da9b14c965f04293103c1df");
	y = bigint_from_hex_string(BI_TESTS_Y_TAG, "2");
	x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
	__montgomery_revert(b, c, p);
	ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_SECP521R1)
{
    bigint_create_buffer();

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "1e943c184b0c3984b3b6e5237e81784e69a01e10a8a8b9a9499703033cf290b9ec473086865fce3c42f099c2f6e7d1abb87ed8dd1a283ce144e4a2d6cfcf557aeeb");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "19618f0a082355abbcbba19e7d471340bffa6e60da7b7ed6cbcff54a8f7ad044ebb479479f20046c8c73fd45f627d509129cbbdfe0edf38c2f8ea2933499c770454");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "10d5478c921ddfc4117a9fd80c7222fe43ed73dc3d10ff568b14ce3181ce3e6db0d0ed487a170309bc836906d6894389d38b8ac75cbe7222de29e50488ffd82916e");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p);
    __montgomery_revert(b, c, p);

    ASSERT_TRUE(bigint_are_equal(b, expected));

	bigint_destroy_buffer();
}

TEST(bigint_multiplication, bigint_multiplication_zero)
{
    bigint_create_buffer();

	uint64_t b = 0;
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FFAA7777777777777");
	BigInt expected = bigint_from_uint64(BI_TESTS_EXPECTED_TAG, 0);

	bigint_multiply_inplace(a, b);
    ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_multiplication, bigint_multiplication)
{
    bigint_create_buffer();

	uint64_t b = (uint64_t)1 << (63);
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, b);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "40000000000000000000000000000000");
	bigint_multiply_inplace(a, b);
    ASSERT_TRUE(bigint_are_equal(a, expected));


    b = 23486345345;
	a = bigint_from_uint64(BI_TESTS_A_TAG, 892349889234);
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "470233319ce1c7183d2");
	bigint_multiply_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, expected));

	b = 23486345345;
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "21195e6b6401aa7f9d224b7468817646d2288ba3641f62048ac9827ff9");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "b4ff44f3c512471a9cacd1cb42aad26cc33f727651ed10d4d6b49cbace3b7e2c79");
	bigint_multiply_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_multiplication, bigint_multiplication_large)
{
    bigint_create_buffer();

	uint64_t b = 123123123;
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "37900b3819a5d49e0a355fb44e75b48372b7ac48e88af780ba692c47681fd3246a87e6456b9eb9d9effa1eb798ee7e5adfb40bf41b3a45930cb949e8330eef8edfee7b7df9b020bd3fedac73c552b6acc9d494ef52c3b570097747fd7969cdb4677e5ad6daec42bb5ffcfaadee09e63e1a36a2016ab6715286928660d3b8a63d0990249defb076dc82a7ac3e550aa662888b2eb3e");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "197c221ff32a8e1eda64b44f4b3fa065139b76ef216eed88480925987ae4c033baee2bbd4189608de297eebfa772f137cbdac846817b069a1aef51514366906a4f044b81f361caf499fac15d766fc3e8b8e8301009a80904205851211c63b3ebcda9b3f17bd6e35a8f34db8f3107d897c4a32bd6b231dd3ef17ccbf7bc797f91b698bdd38499d6e52137e9979495dd694ebae787ce41525a");
	bigint_multiply_inplace(a, b);
    ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_multiplication, bigint_multiplication_carry)
{
    bigint_create_buffer();

	uint64_t b = 0xffffffffffffffff;
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000002");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "10000000000000000fffffffffffffffe");
	bigint_multiply_inplace(a, b);
    ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_right_shift_inplace_64, bigint_right_shift_inplace_64_0)
{
    bigint_create_buffer();

    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "0");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "0");
	bigint_right_shift_inplace_64(a);
    ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_right_shift_inplace_64, bigint_right_shift_inplace_64_1)
{
    bigint_create_buffer();

    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "000000000000000070000000000000006000000000000000500000000000000040000000000000003000000000000000200000000000000010000000000000000");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "00000000000000007000000000000000600000000000000050000000000000004000000000000000300000000000000020000000000000001");
	bigint_right_shift_inplace_64(a);
    ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_right_shift_inplace_64, bigint_right_shift_inplace_64_2)
{
    bigint_create_buffer();

    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100000000000000000000000000000000");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "10000000000000000");
	bigint_right_shift_inplace_64(a);
	char * a_str = bigint_to_hex_string(a);
	free(a_str);
    ASSERT_TRUE(bigint_are_equal(a, expected));

    bigint_destroy_buffer();
}

TEST(bigint_modulo_inplace, test_modulo_0)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 11600);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 29);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 0);
	
	bigint_modulo_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));

	bigint_destroy_buffer();
}

TEST(bigint_modulo_inplace, test_modulo_1)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 2);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 4);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 2);
	
	bigint_modulo_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));

	bigint_destroy_buffer();
}

TEST(bigint_modulo_inplace, test_modulo_2)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 3245475);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 2394);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 1605);
	
	bigint_modulo_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));

	bigint_destroy_buffer();
}

TEST(bigint_modulo_inplace, test_modulo_z)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 0);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 2394);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 0);
	
	bigint_modulo_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));

	bigint_destroy_buffer();
}

TEST(bigint_modulo_inplace, test_modulo_large_1)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "93FA234AFF0ACC23");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "8AB44BEFCD89");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "27E3AAB16A9E");
	
	bigint_modulo_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));

	bigint_destroy_buffer();
}

TEST(bigint_division, test_simple)
{
    bigint_create_buffer();
    
	BigInt x = GET_BIGINT_PTR(BI_TESTS_X_TAG);
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "2");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "6");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "3");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "7");
    
	bigint_divide(x, b, a, p);
	ASSERT_TRUE(bigint_are_equal(x, c));
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "635A");
	b = bigint_from_hex_string(BI_TESTS_B_TAG, "161F0A");
	c = bigint_from_hex_string(BI_TESTS_C_TAG, "39");
	p = bigint_from_hex_string(BI_TESTS_P_TAG, "29F6CF");
    
	bigint_divide(x, b, a, p);
	ASSERT_TRUE(bigint_are_equal(x, c));

	bigint_destroy_buffer();
}

TEST(bigint_division, test_field)
{
    bigint_create_buffer();
    
	BigInt x = GET_BIGINT_PTR(BI_TESTS_X_TAG);
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "4");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "2");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "7");
    
	bigint_divide(x, b, a, p);
	ASSERT_TRUE(bigint_are_equal(x, c));
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "272CC2");
	b = bigint_from_hex_string(BI_TESTS_B_TAG, "207416");
	c = bigint_from_hex_string(BI_TESTS_C_TAG, "F0053");
	p = bigint_from_hex_string(BI_TESTS_P_TAG, "2A13BB");
    
	bigint_divide(x, b, a, p);
	ASSERT_TRUE(bigint_are_equal(x, c));

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "7cd73b6fc007dfee34a23caf363ae67e8bb8782600000000032accceb");
	b = bigint_from_hex_string(BI_TESTS_B_TAG, "c69d8b898f0e43b4643a018e7b0569de6f8cf328e0bf6d59ace4e3bc2ca28d10");
	c = bigint_from_hex_string(BI_TESTS_C_TAG, "1f7b09f4cadaeba016af3426bfe4b53533e054f6f9646f000000000031e9d354");
	p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    
	bigint_divide(x, b, a, p);
	
	ASSERT_TRUE(bigint_are_equal(x, c));

	bigint_destroy_buffer();
}
