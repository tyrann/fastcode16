extern "C" {
    #include "../src/ec_point.h"
    #include "../src/bigint.h"
    #include "../src/ec_parameters.h"
    #include "../src/ec_dh.h"
	#include "../src/ec_point_operations.h"

}
#include "gtest/gtest.h"

// secp192k1
void create_parameters_ECDH(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
    bigint_from_uint32(&a, 0);
    bigint_from_uint32(&b, 3);
    create_point_from_hex(&G, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

TEST(ec_dh, ecdh_generate_key)
{
    EllipticCurveParameter params;
    create_parameters_ECDH(&params);
	BigInt d;
	bigint_from_hex_string(&d, "1"); // Randome number between 0 and n 

	ECDH uECDH;
    Point pub_key;
    create_point_inf(&pub_key);
	BigInt sharedInfo;
	bigint_from_uint32(&sharedInfo, 0);
	ec_create_ECDH(&uECDH, &params, &pub_key, &d, &sharedInfo);
	ASSERT_TRUE(ecdh_generate_key(&uECDH, &d));
	
	ec_free(&params);
	bigint_free(&d);

    point_free(&pub_key);
	bigint_free(&sharedInfo);
	ec_ECDHfree(&uECDH);
}

TEST(ec_dh, ecdh_compute_key)
{
    EllipticCurveParameter params;
    create_parameters_ECDH(&params);
	BigInt dU;
	bigint_from_hex_string(&dU, "FFFFFFFFFFFFFFFFFFFFFFF"); // Randome number between 0 and n 
	
	BigInt dV;
	bigint_from_hex_string(&dV, "26F2FC170F69466A74DEFD8"); // Randome number between 0 and n 

	ECDH uECDH;
    Point pub_keyU;
    create_point_inf(&pub_keyU);
	BigInt sharedInfoU;
	bigint_from_uint32(&sharedInfoU, 0);
	ec_create_ECDH(&uECDH, &params, &pub_keyU, &dU, &sharedInfoU);
	
	
	ECDH vECDH;
    Point pub_keyV;
    create_point_inf(&pub_keyV);
	BigInt sharedInfoV;
	bigint_from_uint32(&sharedInfoV, 1);
	ec_create_ECDH(&vECDH, &params, &pub_keyV, &dV, &sharedInfoV);
	
	ecdh_generate_key(&uECDH, &dU);
	ecdh_generate_key(&vECDH, &dV);
	
	ASSERT_TRUE(ecdh_compute_key(&uECDH, &vECDH));
	ASSERT_TRUE(ecdh_verification(&uECDH, &vECDH));

	
	ec_free(&params);
	bigint_free(&dU);
	bigint_free(&dV);

    point_free(&pub_keyU);
	bigint_free(&sharedInfoU);
	ec_ECDHfree(&uECDH);

	
	point_free(&pub_keyV);
	bigint_free(&sharedInfoV);
	ec_ECDHfree(&vECDH);	
}


TEST(ec_dh, ecdh_compute_keySharedInfoCheck)
{
    EllipticCurveParameter params;
    create_parameters_ECDH(&params);
	BigInt dU;
	bigint_from_hex_string(&dU, "FFFFFFFFFFFFFFFFFFFFFFF"); // Randome number between 0 and n 
	
	BigInt dV;
	bigint_from_hex_string(&dV, "26F2FC170F69466A74DEFD8"); // Randome number between 0 and n 

	ECDH uECDH;
    Point pub_keyU;
    create_point_inf(&pub_keyU);
	BigInt sharedInfoU;
	bigint_from_uint32(&sharedInfoU, 0);
	ec_create_ECDH(&uECDH, &params, &pub_keyU, &dU, &sharedInfoU);
	
	
	ECDH vECDH;
    Point pub_keyV;
    create_point_inf(&pub_keyV);
	BigInt sharedInfoV;
	bigint_from_uint32(&sharedInfoV, 1);
	ec_create_ECDH(&vECDH, &params, &pub_keyV, &dV, &sharedInfoV);
	
	ecdh_generate_key(&uECDH, &dU);
	ecdh_generate_key(&vECDH, &dV);
	
	
	ASSERT_TRUE(ecdh_compute_key(&uECDH, &vECDH));
	ASSERT_TRUE(ecdh_verification(&uECDH, &vECDH));

	BigInt uToV, vToU;
	bigint_copy(&uToV,&(uECDH.sharedInfo));
	
	ASSERT_TRUE(ecdh_compute_key(&vECDH, &uECDH));
	bigint_copy(&vToU,&(uECDH.sharedInfo));
	
	
	ASSERT_TRUE(bigint_are_equal(&uToV,&vToU));	
	
	ec_free(&params);
	bigint_free(&dU);
	bigint_free(&dV);

    point_free(&pub_keyU);
	bigint_free(&sharedInfoU);
	ec_ECDHfree(&uECDH);

	
	point_free(&pub_keyV);
	bigint_free(&sharedInfoV);
	ec_ECDHfree(&vECDH);

	bigint_free(&uToV);
	bigint_free(&vToU);
	
}