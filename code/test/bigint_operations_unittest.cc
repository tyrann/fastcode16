
extern "C" {
    #include "bigint.h"
}
#include "gtest/gtest.h"

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
	BigInt b = bigint_from_uint32(BI_TESTS_B_TAG, 4);
	
	bigint_add_inplace(a,b);
	ASSERT_TRUE(bigint_are_equal(a, b));

    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "10000");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "100FF");
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 3);
    
    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_inversed)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FFFFFFFE");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "0102");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "100000100");
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 5);

    bigint_destroy_buffer();
}

TEST(bigint_add_inplace, test_add_mem)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFF");
	
	ASSERT_EQ(a->significant_octets, 1);
	ASSERT_EQ(b->significant_octets, 2);

	bigint_add_inplace(a, b);
	ASSERT_EQ(a->significant_octets, 3);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem2)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1FFAFF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1FFB00");

	ASSERT_EQ(a->significant_octets, 3);
	ASSERT_EQ(b->significant_octets, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 3);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem3)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1FFAFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1FFB00");

	ASSERT_EQ(a->significant_octets, 1);
	ASSERT_EQ(b->significant_octets, 3);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 3);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem4)
{
    bigint_create_buffer();

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FAFF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FB00");

	ASSERT_EQ(a->significant_octets, 2);
	ASSERT_EQ(b->significant_octets, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 2);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem5)
{
    bigint_create_buffer();

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FE");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FF");

	ASSERT_EQ(a->significant_octets, 1);
	ASSERT_EQ(b->significant_octets, 1);
	
	bigint_add_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 1);
	
    bigint_destroy_buffer();
}
TEST(bigint_add_inplace, test_add_mem6)
{
    bigint_create_buffer();

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "1");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "100");

	ASSERT_EQ(a->significant_octets, 1);
	ASSERT_EQ(b->significant_octets, 1);
	
	bigint_add_inplace(a, b);

	ASSERT_TRUE(bigint_are_equal(a, c));
	ASSERT_EQ(a->significant_octets, 2);
	
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

TEST(bigint_sub_inplace, sub_test_1)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FF");
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

// Test BigInt sub
TEST(bigint_sub_inplace, sub_test_3)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_uint64(BI_TESTS_A_TAG, 0);
	BigInt b = bigint_from_uint64(BI_TESTS_B_TAG, 0);
	BigInt c = bigint_from_uint64(BI_TESTS_C_TAG, 0);
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    ASSERT_EQ(a->significant_octets, 1);
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
    ASSERT_EQ(a->significant_octets, 1);
    
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
    ASSERT_EQ(a->significant_octets, 1);
    
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
    ASSERT_EQ(a->significant_octets, 6);
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_7)
{	
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "200");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "100");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "100");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_octets, 2);	
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_8)
{	
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FF1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FFFFFFFFFF00F");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_octets, 7);		
    
    bigint_destroy_buffer();
}
TEST(bigint_sub_inplace, sub_test_9)
{	
    bigint_create_buffer();
    			
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "10000000000000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFFFFFFFFFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);
    ASSERT_EQ(a->significant_octets, 1);	
    
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
    ASSERT_EQ(a->significant_octets, 7);
    
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
    ASSERT_EQ(a->significant_octets, 1);
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_12)
{	
    bigint_create_buffer();		
    	
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FE");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1); 
    ASSERT_EQ(a->significant_octets, 1);		
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, sub_test_13)
{	
    bigint_create_buffer();		
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "FB00");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "1");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "FAFF");
    bigint_sub_inplace(a, b);
    int are_equal = bigint_are_equal(a, c);
    EXPECT_EQ(are_equal, 1);    
    ASSERT_EQ(a->significant_octets, 2);	
    
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
    ASSERT_EQ(a->significant_octets, 7);		
    
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, test_sub_large)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "93FA234AFF0ACC23");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "8AB44BEFCD89");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "93F99896B31AFE9A");
	
	bigint_sub_inplace(a, b);
	ASSERT_TRUE(bigint_are_equal(a, c));
    ASSERT_EQ(a->significant_octets, 8);	
	
    bigint_destroy_buffer();
}

TEST(bigint_sub_inplace, bad_memory_acces)
{
    bigint_create_buffer();
    
    int are_equal;
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100000");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "FFFFF");
	BigInt c = bigint_from_hex_string(BI_TESTS_C_TAG, "1");
    bigint_sub_inplace(a, b);
    are_equal = bigint_are_equal(a, c);
    ASSERT_EQ(a->significant_octets, 1);	
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
    ASSERT_EQ(a->significant_octets, 1);	
    
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
    ASSERT_EQ(a->significant_octets, 1);
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "8");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "10");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "7F");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "FE");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 1);
    
	a = bigint_from_hex_string(BI_TESTS_A_TAG, "466962f6e91eaaf80e4803ffffffe003");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 16);
    
    bigint_destroy_buffer();
}

TEST(bigint_left_shift_inplace, test_different_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "80");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "100");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 2);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "1FE");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 2);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "119a58bdba47aabe039200fffffff800c");
    bigint_left_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 17);
    
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
    ASSERT_EQ(a->significant_octets, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "10");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "FF");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "7F");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc007");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "466962f6e91eaaf80e4803ffffffe003");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 16);
    
    bigint_destroy_buffer();
}

TEST(bigint_right_shift_inplace, test_different_size)
{
    bigint_create_buffer();
    
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "100");
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "80");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "1FF");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "FF");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 1);

	a = bigint_from_hex_string(BI_TESTS_A_TAG, "119a58bdba47aabe039200fffffff800c");
	expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
    bigint_right_shift_inplace(a);
    ASSERT_EQ(bigint_are_equal(a, expected), 1);
    ASSERT_EQ(a->significant_octets, 16);
    
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

TEST(bigint_montgomery_mul, bigint_montgomery_mul_1)
{
    bigint_create_buffer();
    
	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "e35f881473508854759637d8a77f8d1f94a5d0d2b54637193f6f8c070b15326f");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "6d09acdef99ad700431e77edcd980a3a54594d6e79a6657a68c7b");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "19f7dd97453df6cb19aa8120882a211ee82d59a584e5b833e16968640");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p); 
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));
    
	bigint_destroy_buffer();
}

TEST(bigint_montgomery_mul, bigint_montgomery_mul_2)
{
    bigint_create_buffer();
    
	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "8");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "2");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "4");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p); 
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));
    
	bigint_destroy_buffer();
}
TEST(bigint_montgomery_mul, bigint_montgomery_mul_3)
{
    bigint_create_buffer();
    
	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt expected = bigint_from_hex_string(BI_TESTS_EXPECTED_TAG, "10");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "4");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "4");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
	montgomery_mul(c, x_conv, y_conv, p); 
    __montgomery_revert(b, c, p);
    __montgomery_revert(b, c, p);
    ASSERT_TRUE(bigint_are_equal(b, expected));

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
