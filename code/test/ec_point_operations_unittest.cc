extern "C" {
    #include "ec_point.h"
    #include "bigint.h"
    #include "ec_parameters.h"
}
#include "gtest/gtest.h"

TEST(ec_point_add_inplace, inf_plus_inf)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    Point a, b, expected;
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0, params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    a.is_at_infinity = 1;
    b.is_at_infinity = 1;
    expected.is_at_infinity = 1;

    __montgomery_init(params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_add_inplace, a_plus_inf)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    Point a, b, expected;
    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "3cd61e370d02ca0687c0b5f7ebf6d0373f4dd0ccccb7cc2d", "2c4befd9b02f301eb4014504f0533aa7eb19e9ea56441f78", params.p);
    create_point_from_uint64(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, 0, 0, params.p);
    b.is_at_infinity = 1;
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "3cd61e370d02ca0687c0b5f7ebf6d0373f4dd0ccccb7cc2d", "2c4befd9b02f301eb4014504f0533aa7eb19e9ea56441f78", params.p);

    __montgomery_init(params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_add_inplace, inf_plus_b)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    Point a, b, expected;
    create_point_from_uint64(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, 0, 0, params.p);
    a.is_at_infinity = 1;
    create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "3cd61e370d02ca0687c0b5f7ebf6d0373f4dd0ccccb7cc2d", "2c4befd9b02f301eb4014504f0533aa7eb19e9ea56441f78", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "3cd61e370d02ca0687c0b5f7ebf6d0373f4dd0ccccb7cc2d", "2c4befd9b02f301eb4014504f0533aa7eb19e9ea56441f78", params.p);

    __montgomery_init(params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_add_inplace, a_plus_a_SECP384R1)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    Point a, b, expected;

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "58bd2b6271fc20698586408a2e4046756c10bd79f16891284754c4f7ff753c09f8660d44dc6d80545a0df9ac7de99965", "605bbfa2d44e310a9f1475c28e933c39e1a2ef5894e65b1db3182f21163cb52f2d71fdce9da9b14c965f04293103c1df", params.p);
    create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "58bd2b6271fc20698586408a2e4046756c10bd79f16891284754c4f7ff753c09f8660d44dc6d80545a0df9ac7de99965", "605bbfa2d44e310a9f1475c28e933c39e1a2ef5894e65b1db3182f21163cb52f2d71fdce9da9b14c965f04293103c1df", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "2799d1abc4cc6bb3de567e349365177e450be9d8456b7d7726fe0aa86f9dc070399e06703b470f2d30035084a4927bd7", "967182745025f4abd645c19a201bb6f4f15aad3a67aeb27c33b636ee7fd7b38853556fe2b9d49b3921ad1899995526cd", params.p);

    __montgomery_init(params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_add_inplace, a_plus_b__SECP384R1_rule4)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    Point a, b, expected;
    __montgomery_init(params.p);

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "1c5f07f1f82becd192f2ebc06790f6e30850d668a258b09e35cf31128dcaaabca5a56922caeca08aa598439598174296", "18be0cc698bee9a21db0a4494ad3faaf17752b8be15971a2788eae558a1fafdf8d313b46a8dee779e2aed8584074c1de", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "3dc2f080428a8e9e3878262882c1e8035393a4e80db6591471a28e2c0c92629ca8b614b6d8b915a95fd893e56bad50fc", "c1ec2ccaf1e3acccdc4ab8e1a5611030999af5f90c15786b3d32a19f5162a7add51113d7d3b18adfabaf782cde3e43e5", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "2f8ecde401eaf2edeb8f805a8366119622dcde7a502be5fdf326c03b38a5e96b0961c71f3389eb67b7865a6f6b04953c", "b738eb04481237b2a8abd8dddb6b669e3513e66d91a9f75fc033e506e66e3ac76c0effc653118bcb5aef3547e19fa5e3", params.p);
	expected.is_at_infinity = 0;
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "411eca0c5855c566a1debf8c4bbe58c53c96ec0574872e1d70b3042fbbbb6983f9ee5193e09d26dfc153f60c8e626d64", "c9fb2d94f3068d95cd62905508eebdfe6825dbc06f0a11ae2c0a6df73ae5c7b47c6514346beb8a71c8b2e570d67e12e7", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "cf28c3ce4673857cca6b8da8fb379c882ed9aa207e542a5fcb4e958ba17759abfec542590bc0a9ddd602f23fea8fb0fd", "78a8975ea48ffaec7832f5d8b5706cf03b68ba4dbd6d2d65c996648e8af12254598cf5f26c408681698ad7d57886cee1", params.p);
	create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "903c1ca2bf721c9086f1760f6627ae0b5d24ef187fccc345464d35eaca18d012890bd0076bafcb4a97711a9f0cb1d84", "d8ab2df43341f3196b5ab2638dcd2741c37b668a19680d545a3fbe15af0d27d8b1c119fb9c07e84c23d6c1cf712ea70d", params.p);
	expected.is_at_infinity = 0;
	ec_point_add_inplace(&a, &b, &params);
	ASSERT_TRUE(point_are_equal(&a, &expected));


    bigint_destroy_buffer();
}


TEST(ec_point_add_inplace, a_plus_b_inf)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    Point a, b, expected;
    __montgomery_init(params.p);

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "411eca0c5855c566a1debf8c4bbe58c53c96ec0574872e1d70b3042fbbbb6983f9ee5193e09d26dfc153f60c8e626d64", "c9fb2d94f3068d95cd62905508eebdfe6825dbc06f0a11ae2c0a6df73ae5c7b47c6514346beb8a71c8b2e570d67e12e7", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "411eca0c5855c566a1debf8c4bbe58c53c96ec0574872e1d70b3042fbbbb6983f9ee5193e09d26dfc153f60c8e626d64", "3604d26b0cf9726a329d6faaf711420197da243f90f5ee51d3f59208c51a384a839aebca9414758e374d1a902981ed18", params.p);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    ec_point_add_inplace(&a, &b, &params);
    expected.is_at_infinity = 1;
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_add_inplace, large_number)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    Point a, b, expected;
    __montgomery_init(params.p);

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5", params.p);
    ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    create_point_from_hex(&a, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D", params.p);
	create_point_from_hex(&b, BI_TESTS_BX_TAG, BI_TESTS_BY_TAG, "F091CF6331B1747684F5D2549CD1D4B3A8BED93B94F93CB6", "FD7AF42E1E7565A02E6268661C5E42E603DA2D98A18F2ED5", params.p);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "6E43B7DCAE2FD5E0BF2A1BA7615CA3B9065487C9A67B4583", "C48DCEA47AE08E84D5FEDC3D09E4C19606A290F7A19A6A58", params.p);
	ec_point_add_inplace(&a, &b, &params);
    ASSERT_TRUE(point_are_equal(&a, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_mul, zero_times_point)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    Point P, result, expected;
    __montgomery_init(params.p);

    create_point_from_hex(&P, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "411eca0c5855c566a1debf8c4bbe58c53c96ec0574872e1d70b3042fbbbb6983f9ee5193e09d26dfc153f60c8e626d64", "c9fb2d94f3068d95cd62905508eebdfe6825dbc06f0a11ae2c0a6df73ae5c7b47c6514346beb8a71c8b2e570d67e12e7", params.p);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 0);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_mul, one_times_point)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    Point P, result, expected;
    __montgomery_init(params.p);
    expected.x = GET_BIGINT_PTR(BI_TESTS_EXPECTEDX_TAG);
    expected.y = GET_BIGINT_PTR(BI_TESTS_EXPECTEDY_TAG);

    create_point_from_hex(&P, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "411eca0c5855c566a1debf8c4bbe58c53c96ec0574872e1d70b3042fbbbb6983f9ee5193e09d26dfc153f60c8e626d64", "c9fb2d94f3068d95cd62905508eebdfe6825dbc06f0a11ae2c0a6df73ae5c7b47c6514346beb8a71c8b2e570d67e12e7", params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 1);
    point_copy(&expected, &P);
    ec_point_mul(&result, d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_mul, two_times_point)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP384R1);
    Point P, result, expected;
    __montgomery_init(params.p);

    create_point_from_hex(&P, BI_TESTS_AX_TAG, BI_TESTS_AY_TAG, "411eca0c5855c566a1debf8c4bbe58c53c96ec0574872e1d70b3042fbbbb6983f9ee5193e09d26dfc153f60c8e626d64", "c9fb2d94f3068d95cd62905508eebdfe6825dbc06f0a11ae2c0a6df73ae5c7b47c6514346beb8a71c8b2e570d67e12e7", params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    BigInt d = bigint_from_uint64(BI_TESTS_D_TAG, 2);
    create_point_from_hex(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, "b98c882cfd67b8d7bb6b7ead9873358c5cf82249ab4c871296e567761e7f88c4db94172a198fc0fd1a6d4ad3c2c75413", "444bf5758ad51e9dc04200eec9277aacbe083d3704945175fdad5c65a49840c641b8675cb5cc2a75818fca646e23379a", params.p);
    ec_point_mul(&result, d, &P, &params);
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}


TEST(ec_point_mul, ultimate_test)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    __montgomery_init(params.p);
    
    Point P, result, expected;
    BigInt d = GET_BIGINT_PTR(BI_TESTS_D_TAG);
    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 0, 0, params.p);
    
    point_copy(&P, &params.generator);
    bigint_copy(d, params.n);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

TEST(ec_point_mul, ultimate_test_2)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP521R1);
    __montgomery_init(params.p);
   
    Point P, result, expected;   
    BigInt d = GET_BIGINT_PTR(BI_TESTS_D_TAG);
    create_point_from_uint64(&P, BI_TESTS_PX_TAG, BI_TESTS_PY_TAG, 188, 93, params.p);
   
    point_copy(&P, &params.generator);
    bigint_copy(d, params.n);
    create_point_from_uint64(&expected, BI_TESTS_EXPECTEDX_TAG, BI_TESTS_EXPECTEDY_TAG, 0, 0, params.p);
    create_point_from_uint64(&result, BI_TESTS_RESULTX_TAG, BI_TESTS_RESULTY_TAG, 0, 0, params.p);
    expected.is_at_infinity = 1;
    ec_point_mul(&result, d, &P, &params);
    
    ASSERT_TRUE(point_are_equal(&result, &expected));

    bigint_destroy_buffer();
}

