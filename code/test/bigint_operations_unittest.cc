
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

TEST(bigint_add_inplace, test_add_zero)
{
	BigInt a,b;
	bigint_from_uint64(&a, 0);
	bigint_from_uint32(&b, 4);
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &b));

	bigint_free(&a);
	bigint_free(&b);
}
TEST(bigint_add_inplace, test_add_size)
{
	BigInt a,b,c;
	bigint_from_hex_string(&a, "FF");
	bigint_from_hex_string(&b, "10000");
	bigint_from_hex_string(&c, "100FF");
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));
	ASSERT_EQ(a.significant_octets, 1);

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}
TEST(bigint_add_inplace, test_add_inversed)
{
	BigInt a,b,c;
	bigint_from_hex_string(&a, "FFFFFFFE");
	bigint_from_hex_string(&b, "0102");
	bigint_from_hex_string(&c, "100000100");
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));
	ASSERT_EQ(a.significant_octets, 5);

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}

TEST(bigint_add_inplace, test_add_mem)
{
	BigInt a,b;
	bigint_from_hex_string(&a, "FFFF");
	bigint_from_hex_string(&b, "1");
	
	ASSERT_EQ(a.significant_octets, 2);
	ASSERT_EQ(b.significant_octets, 1);

	bigint_add_inplace(&a,&b);
	ASSERT_EQ(a.significant_octets, 3);
	bigint_free(&a);
	bigint_free(&b);
}
TEST(bigint_add_inplace, test_add_mem2)
{
	BigInt a,b,c;
	bigint_from_hex_string(&a, "1FFAFF");
	bigint_from_hex_string(&b, "1");
	bigint_from_hex_string(&c, "1FFB00");

	ASSERT_EQ(a.significant_octets, 3);
	ASSERT_EQ(b.significant_octets, 1);
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a,&c));
	ASSERT_EQ(a.significant_octets, 3);
	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}
TEST(bigint_add_inplace, test_add_mem3)
{
	BigInt a,b,c;
	bigint_from_hex_string(&a, "1");
	bigint_from_hex_string(&b, "1FFAFF");
	bigint_from_hex_string(&c, "1FFB00");

	ASSERT_EQ(a.significant_octets, 1);
	ASSERT_EQ(b.significant_octets, 3);
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a,&c));
	ASSERT_EQ(a.significant_octets, 3);
	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}
TEST(bigint_add_inplace, test_add_mem4)
{

	BigInt a,b,c;
	bigint_from_hex_string(&a, "FAFF");
	bigint_from_hex_string(&b, "1");
	bigint_from_hex_string(&c, "FB00");

	ASSERT_EQ(a.significant_octets, 2);
	ASSERT_EQ(b.significant_octets, 1);
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a,&c));
	ASSERT_EQ(a.significant_octets, 2);
	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}
TEST(bigint_add_inplace, test_add_mem5)
{

	BigInt a,b,c;
	bigint_from_hex_string(&a, "FE");
	bigint_from_hex_string(&b, "1");
	bigint_from_hex_string(&c, "FF");

	ASSERT_EQ(a.significant_octets, 1);
	ASSERT_EQ(b.significant_octets, 1);
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a,&c));
	ASSERT_EQ(a.significant_octets, 1);
	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}
TEST(bigint_add_inplace, test_add_mem6)
{

	BigInt a,b,c;
	bigint_from_hex_string(&a, "1");
	bigint_from_hex_string(&b, "FF");
	bigint_from_hex_string(&c, "100");

	ASSERT_EQ(a.significant_octets, 1);
	ASSERT_EQ(b.significant_octets, 1);
	
	bigint_add_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a,&c));
	ASSERT_EQ(a.significant_octets, 2);
	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}
// Test BigInt sub
TEST(bigint_sub_inplace, test_sub)
{
    BigInt a1, b1, c1;	
	bigint_from_uint64(&a1,0);
	bigint_from_uint64(&b1,0);
	bigint_from_uint64(&c1,0);
    bigint_sub_inplace(&a1, &b1);
    int are_equal = bigint_are_equal(&a1, &c1);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a1);
    bigint_free(&b1);
	bigint_free(&c1);
	
	BigInt a2, b2, c2;	
	bigint_from_uint64(&a2,1);
	bigint_from_uint64(&b2,0);
	bigint_from_uint64(&c2,1);
    bigint_sub_inplace(&a2, &b2);
    are_equal = bigint_are_equal(&a2, &c2);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a2);
    bigint_free(&b2);
	bigint_free(&c2);
	
	
	BigInt a3, b3, c3;	
	bigint_from_hex_string(&a3, "FF");
	bigint_from_hex_string(&b3, "1");
	bigint_from_hex_string(&c3, "FE");
    bigint_sub_inplace(&a3, &b3);
    are_equal = bigint_are_equal(&a3, &c3);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a3);
    bigint_free(&b3);
	bigint_free(&c3);
	
	
	BigInt a4, b4, c4;	
	bigint_from_uint64(&a4,98349869483274);
	bigint_from_uint64(&b4,25213123210954);
	bigint_from_uint64(&c4,73136746272320);
    bigint_sub_inplace(&a4, &b4);
    are_equal = bigint_are_equal(&a4, &c4);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a4);
    bigint_free(&b4);
	bigint_free(&c4);
	
	
	BigInt a5, b5, c5;	
	bigint_from_hex_string(&a5, "100");
	bigint_from_hex_string(&b5, "1");
	bigint_from_hex_string(&c5, "FF");
    bigint_sub_inplace(&a5, &b5);
    are_equal = bigint_are_equal(&a5, &c5);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a5);
    bigint_free(&b5);
	bigint_free(&c5);
	
	
	BigInt a6, b6, c6;	
	bigint_from_hex_string(&a6, "200");
	bigint_from_hex_string(&b6, "100");
	bigint_from_hex_string(&c6, "100");
    bigint_sub_inplace(&a6, &b6);
    are_equal = bigint_are_equal(&a6, &c6);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a6);
    bigint_free(&b6);
	bigint_free(&c6);

	BigInt a7, b7, c7;	
	bigint_from_hex_string(&a7, "10000000000000");
	bigint_from_hex_string(&b7, "FF1");
	bigint_from_hex_string(&c7, "FFFFFFFFFF00F");
    bigint_sub_inplace(&a7, &b7);
    are_equal = bigint_are_equal(&a7, &c7);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a7);
    bigint_free(&b7);
	bigint_free(&c7);
	
	BigInt a8, b8, c8;		
	bigint_from_hex_string(&a8, "10000000000000");
	bigint_from_hex_string(&b8, "FFFFFFFFFFFFF");
	bigint_from_hex_string(&c8, "1");
    bigint_sub_inplace(&a8, &b8);
    are_equal = bigint_are_equal(&a8, &c8);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a8);
    bigint_free(&b8);
	bigint_free(&c8);
	
		
	BigInt a9, b9, c9;	
	bigint_from_hex_string(&a9, "10000000000000");
	bigint_from_hex_string(&b9, "1");
	bigint_from_hex_string(&c9, "FFFFFFFFFFFFF");
    bigint_sub_inplace(&a9, &b9);
    are_equal = bigint_are_equal(&a9, &c9);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a9);
    bigint_free(&b9);
	bigint_free(&c9);

	BigInt a, b, c;	
	bigint_from_hex_string(&a, "10000000000000");
	bigint_from_hex_string(&b, "FFFFFFFFFFFF");
	bigint_from_hex_string(&c, "F000000000001");
    bigint_sub_inplace(&a, &b);
    are_equal = bigint_are_equal(&a, &c);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a);
    bigint_free(&b);
	bigint_free(&c);

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
