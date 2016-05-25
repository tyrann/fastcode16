extern "C" {
#include "ec_point.h"
#include "bigint.h"
#include "ec_parameters.h"
#include "ec_dh.h"
#include "ec_point_operations.h"

}
#include "gtest/gtest.h"

TEST(ec_dh, ecdh_compute_shared_secret)
{
    bigint_create_buffer();
    
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    __montgomery_init(params.p);
 
    BigInt dU = bigint_from_hex_string(BI_TESTS_DU_TAG, "FFFFFFFFFFFFFFFFFFFFFFF"); // Random number between 0 and n 
    BigInt dV = bigint_from_hex_string(BI_TESTS_DV_TAG, "26F2FC170F69466A74DEFD8"); // Random number between 0 and n 

    ECDH uECDH;
    Point pub_keyU;
    create_point_from_uint64(&pub_keyU, BI_TESTS_PUBKEYUX_TAG, BI_TESTS_PUBKEYUY_TAG, BI_TESTS_PUBKEYUZ_TAG, 0, 0, params.p);
    BigInt sharedInfoU = GET_BIGINT_PTR(BI_TESTS_SHAREDU_TAG);
   
    ECDH vECDH;
    Point pub_keyV;
    create_point_from_uint64(&pub_keyV, BI_TESTS_PUBKEYVX_TAG, BI_TESTS_PUBKEYVY_TAG, BI_TESTS_PUBKEYVZ_TAG, 0, 0, params.p);
    BigInt sharedInfoV = GET_BIGINT_PTR(BI_TESTS_SHAREDV_TAG);
	
    ecdh_generate_public_key(&pub_keyU, dU, &params);
    ecdh_generate_public_key(&pub_keyV, dV, &params);

    ASSERT_TRUE(ecdh_compute_shared_secret(sharedInfoU, dU, &pub_keyV, &params));
    ASSERT_TRUE(ecdh_compute_shared_secret(sharedInfoV, dV, &pub_keyU, &params));

    ec_create_ECDH(&uECDH, &params, &pub_keyU, dU, sharedInfoU);
    ec_create_ECDH(&vECDH, &params, &pub_keyV, dV, sharedInfoV);

    ASSERT_TRUE(ecdh_verification(&uECDH, &vECDH));
    
    bigint_destroy_buffer();
}

