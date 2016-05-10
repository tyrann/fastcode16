extern "C" {
#include "../src/ec_point.h"
#include "../src/bigint.h"
#include "../src/ec_parameters.h"
#include "../src/ec_dh.h"
#include "../src/ec_point_operations.h"

}
#include "gtest/gtest.h"

TEST(ec_dh, ecdh_compute_shared_secret)
{
    EllipticCurveParameter params;
    ec_generate_parameter(&params, SECP192K1);
    BigInt dU;
    bigint_from_hex_string(&dU, "FFFFFFFFFFFFFFFFFFFFFFF"); // Random number between 0 and n 
	
    BigInt dV;
    bigint_from_hex_string(&dV, "26F2FC170F69466A74DEFD8"); // Random number between 0 and n 

    ECDH uECDH;
    Point pub_keyU;
    BigInt sharedInfoU;
   
    ECDH vECDH;
    Point pub_keyV;
    BigInt sharedInfoV;
	
    ecdh_generate_public_key(&pub_keyU, &dU, &params);
    ecdh_generate_public_key(&pub_keyV, &dV, &params);

    ASSERT_TRUE(ecdh_compute_shared_secret(&sharedInfoU, &dU, &pub_keyV, &params));
    ASSERT_TRUE(ecdh_compute_shared_secret(&sharedInfoV, &dV, &pub_keyU, &params));

    ec_create_ECDH(&uECDH, &params, &pub_keyU, &dU, &sharedInfoU);
    ec_create_ECDH(&vECDH, &params, &pub_keyV, &dV, &sharedInfoV);

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

/*TEST(ec_dh, ecdh_compute_keySharedInfoCheck)
{
    EllipticCurveParameter params;
    create_parameters_ECDH(&params);
    BigInt dU;
    bigint_from_hex_string(&dU, "FFFFFFFFFFFFFFFFFFFFFFF"); // Randome number between 0 and n 
	
    BigInt dV;
    bigint_from_hex_string(&dV, "26F2FC170F69466A74DEFD8"); // Randome number between 0 and n 

    ECDH uECDH;
    Point pub_keyU;
    BigInt sharedInfoU;    

    ECDH vECDH;
    Point pub_keyV;
    BigInt sharedInfoV;
	
    ecdh_generate_public_key(&pub_keyU, &dU);
    ecdh_generate_public_key(&pub_keyV, &dV);

    ASSERT_TRUE(ecdh_compute_shared_secret(&sharedInfoU, &dU, &pub_keyV, &params));
    ASSERT_TRUE(ecdh_compute_shared_secret(&sharedInfoV, &dV, &pub_keyU, &params));

    ASSERT_TRUE(ecdh_verification(&uECDH, &vECDH));

    BigInt uToV, vToU;
    bigint_copy(&uToV,&(uECDH.sharedInfo));
	
    ec_create_ECDH(&uECDH, &params, &pub_keyU, &dU, &sharedInfoU);
    ec_create_ECDH(&vECDH, &params, &pub_keyV, &dV, &sharedInfoV);
    ASSERT_TRUE(ecdh_compute_shared_secret(&vECDH, &uECDH));
    bigint_copy(&vToU,&(uECDH.sharedInfo));	
    ASSERT_TRUE(ecdh_verification(&uECDH, &vECDH));		
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
	
    }*/

