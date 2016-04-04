
extern "C" {
    #include "../src/bigint.h"
}
#include "gtest/gtest.h"

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
	ASSERT_EQ(a.significant_octets, 3);

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

TEST(bigint_add_inplace, large_number)
{
    BigInt a,b,c;
    bigint_from_hex_string(&a, "508E4AA1C1FE6527C419418CC50AA59CCDF2E5C4C0A1F3B2452A9DC01397D8D6BF88C311CCA797AEA6DA4AEA3C78808");
    bigint_from_hex_string(&b, "91BB5C22AE9EF6E7E1FAEED5C31F792082352CF807B7DFE9D300053895AFE1A1E24BBA4EE4092B18F868638C16A626");
    bigint_from_hex_string(&c, "59AA0063ECE854964238F07A213C9D2ED6163894411D71B0E25A9E139CF2D6F0DDAD7EB6BAE82A603660D122FDE2E2E");
	
    bigint_add_inplace(&a,&b);

    ASSERT_TRUE(bigint_are_equal(&a,&c));
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&c);
}

TEST(bigint_sub_inplace, sub_test_1)
{
	BigInt a5, b5, c5;	
	bigint_from_hex_string(&a5, "100");
	bigint_from_hex_string(&b5, "1");
	bigint_from_hex_string(&c5, "FF");
    bigint_sub_inplace(&a5, &b5);
    int are_equal = bigint_are_equal(&a5, &c5);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a5);
    bigint_free(&b5);
	bigint_free(&c5);
}

TEST(bigint_sub_inplace, sub_test_2)
{
	BigInt a5, b5, c5;	
	bigint_from_hex_string(&a5, "FF");
	bigint_from_hex_string(&b5, "FF");
	bigint_from_hex_string(&c5, "0");
    bigint_sub_inplace(&a5, &b5);
    int are_equal = bigint_are_equal(&a5, &c5);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a5);
    bigint_free(&b5);
	bigint_free(&c5);
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

TEST(bigint_sub_inplace, test_sub_large)
{
	BigInt a,b,c;
	bigint_from_hex_string(&a, "93FA234AFF0ACC23");
	bigint_from_hex_string(&b, "8AB44BEFCD89");	
	bigint_from_hex_string(&c, "93F99896B31AFE9A");
	
	bigint_sub_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}

TEST(bigint_sub_inplace, bad_memory_acces)
{
    BigInt a8, b8, c8;
    int are_equal;
    bigint_from_hex_string(&a8, "100000");
    bigint_from_hex_string(&b8, "FFFFF");
    bigint_from_hex_string(&c8, "1");
    bigint_sub_inplace(&a8, &b8);
    are_equal = bigint_are_equal(&a8, &c8);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a8);
    bigint_free(&b8);
    bigint_free(&c8);
}

TEST(bigint_sub_inplace, very_large_number)
{
    int are_equal;
    BigInt a1, b1, c1;
    bigint_from_hex_string(&a1, "2A94608F8D29FBB7AF52D1BC1667F505440CC75CABABDC5961BFCC9F54DADD1A4000000000000000000000000000");
    bigint_from_hex_string(&b1, "2A94608F8D29FBB7AF52D1BC1667F505440CC75CABABDC5961BFCC9F54DADD1A3FFFFFFFFFFFFFFFFFFFFFFFFFFF");
    bigint_from_hex_string(&c1, "1");
    bigint_sub_inplace(&a1, &b1);
    are_equal = bigint_are_equal(&a1, &c1);
    EXPECT_EQ(are_equal, 1);    
    bigint_free(&a1);
    bigint_free(&b1);
    bigint_free(&c1);
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

TEST(bigint_montgomery_convert, test_big_numbers)
{
    BigInt a, p, A, expected;
    bigint_from_hex_string(&a, "6d09acdef99ad700431e77edcd980a3a54594d6e79a6657a68c7b");
    bigint_from_hex_string(&p, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    bigint_from_hex_string(&expected, "f730a1cf9f75e49d796ab57b016187c97d23899d548bb4cd3c9243cb71b6b130");
    
    __montgomery_convert(&A, &a, &p);
    ASSERT_TRUE(bigint_are_equal(&A, &expected));
    
    bigint_free(&a);
    bigint_free(&p);
    bigint_free(&A);
    bigint_free(&expected);
    
    bigint_from_hex_string(&a, "19f7dd97453df6cb19aa8120882a211ee82d59a584e5b833e16968640");
    bigint_from_hex_string(&p, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    bigint_from_hex_string(&expected, "22975b43cd66ef93e142e006ab5bb9522981ab20121a661f432bc566544a9f61");
    
    __montgomery_convert(&A, &a, &p);
    ASSERT_TRUE(bigint_are_equal(&A, &expected));
    
    bigint_free(&a);
    bigint_free(&p);
    bigint_free(&A);
    bigint_free(&expected);
}

TEST(bigint_montgomery_revert, test_big_numbers)
{
    BigInt a, p, A, expected;
    bigint_from_hex_string(&expected, "6d09acdef99ad700431e77edcd980a3a54594d6e79a6657a68c7b");
    bigint_from_hex_string(&p, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    bigint_from_hex_string(&a, "f730a1cf9f75e49d796ab57b016187c97d23899d548bb4cd3c9243cb71b6b130");
    
    __montgomery_revert(&A, &a, &p);
    ASSERT_TRUE(bigint_are_equal(&A, &expected));
    
    bigint_free(&a);
    bigint_free(&p);
    bigint_free(&A);
    bigint_free(&expected);
    
    bigint_from_hex_string(&expected, "19f7dd97453df6cb19aa8120882a211ee82d59a584e5b833e16968640");
    bigint_from_hex_string(&p, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    bigint_from_hex_string(&a, "22975b43cd66ef93e142e006ab5bb9522981ab20121a661f432bc566544a9f61");
    
    __montgomery_revert(&A, &a, &p);
    ASSERT_TRUE(bigint_are_equal(&A, &expected));
    
    bigint_free(&a);
    bigint_free(&p);
    bigint_free(&A);
    bigint_free(&expected);
}
TEST(bigint_montgomery_mul, bigint_montgomery_mul_1)
{
	BigInt res, x, y, p, A, expected;
    bigint_from_hex_string(&expected, "e35f881473508854759637d8a77f8d1f94a5d0d2b54637193f6f8c070b15326f");
    bigint_from_hex_string(&p, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
    bigint_from_hex_string(&x, "6d09acdef99ad700431e77edcd980a3a54594d6e79a6657a68c7b");
    bigint_from_hex_string(&y, "19f7dd97453df6cb19aa8120882a211ee82d59a584e5b833e16968640");
	
	montgomery_mul(&res,&x,&y,&p); 
    __montgomery_revert(&A, &res, &p);
    ASSERT_TRUE(bigint_are_equal(&A, &expected));
    
    bigint_free(&x);
    bigint_free(&p);
    bigint_free(&A);
    bigint_free(&expected);
}

TEST(bigint_modulo_inplace, test_modulo_1)
{
	BigInt a,b,c;
	bigint_from_uint64(&a, 2);
	bigint_from_uint64(&b, 4);
	bigint_from_uint64(&c, 2);
	
	bigint_modulo_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}

TEST(bigint_modulo_inplace, test_modulo_2)
{
	BigInt a,b,c;
	bigint_from_uint64(&a, 3245475);
	bigint_from_uint64(&b, 2394);
	bigint_from_uint64(&c, 1605);
	
	bigint_modulo_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}

TEST(bigint_modulo_inplace, test_modulo_z)
{
	BigInt a,b,c;
	bigint_from_uint64(&a, 0);
	bigint_from_uint64(&b, 2394);
	bigint_from_uint64(&c, 0);
	
	bigint_modulo_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}

TEST(bigint_modulo_inplace, test_modulo_large_1)
{
	BigInt a,b,c;
	bigint_from_hex_string(&a, "93FA234AFF0ACC23");
	bigint_from_hex_string(&b, "8AB44BEFCD89");
	bigint_from_hex_string(&c, "27E3AAB16A9E");
	
	bigint_modulo_inplace(&a,&b);
	ASSERT_TRUE(bigint_are_equal(&a, &c));

	bigint_free(&a);
	bigint_free(&b);
	bigint_free(&c);
}

