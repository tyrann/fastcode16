#ifndef WIN32
#include <sys/time.h>
#include <inttypes.h>
#include "benchmark/benchmark.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef SYS_OSSL
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/crypto.h>
#else
#include "../lib/openssl/usr/include/openssl/ec.h"
#include "../lib/openssl/usr/include/openssl/bn.h"
#include "../lib/openssl/usr/include/openssl/crypto.h"
#endif
#include <stdlib.h>

#define NUM_RUNS 100
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 3.4e9
#define CALIBRATE

unsigned short int n;
extern uint64_t global_index_count; 
extern uint64_t mul_opcount;
extern uint64_t add_opcount;
extern uint64_t shift_opcount;
extern uint64_t avx_opcount;
EllipticCurveParameter get_parameter_by_key_length(int key_length)
{
    EllipticCurveParameter params;
    
    const char precompute = 1;

    switch(key_length) {
    case 192 :
	ec_generate_parameter(&params, SECP192K1, precompute);
        break;
    case 224 :
	ec_generate_parameter(&params, SECP224R1, precompute);
        break;
    case 256 :
	ec_generate_parameter(&params, SECP256K1, precompute);
        break;
    case 384 :
	ec_generate_parameter(&params, SECP384R1, precompute);
        break;
    case 521 :
	ec_generate_parameter(&params, SECP521R1, precompute);
        break;
    default :
	ec_generate_parameter(&params, SECP192K1, precompute);
    }

    return params;
}

void compute_ECDH(char* dURand, char* dVRand, int keyLength)
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

    EllipticCurveParameter params = get_parameter_by_key_length(keyLength);
    
    BigInt dU = bigint_from_hex_string(BI_ECDH_DU_TAG, dURand); // Random number between 0 and n 
    BigInt dV = bigint_from_hex_string(BI_ECDH_DV_TAG, dVRand); // Random number between 0 and n 

    ECDH uECDH;
    Point pub_keyU;
    pub_keyU.x = GET_BIGINT_PTR(BI_ECDH_PUBKEYUX_TAG);
    pub_keyU.y = GET_BIGINT_PTR(BI_ECDH_PUBKEYUY_TAG);
    pub_keyU.z = GET_BIGINT_PTR(BI_ECDH_PUBKEYUZ_TAG);
    BigInt sharedInfoU = GET_BIGINT_PTR(BI_ECDH_SHAREDU_TAG);
   
    ECDH vECDH;
    Point pub_keyV;
    pub_keyV.x = GET_BIGINT_PTR(BI_ECDH_PUBKEYVX_TAG);
    pub_keyV.y = GET_BIGINT_PTR(BI_ECDH_PUBKEYVY_TAG);
    pub_keyV.z = GET_BIGINT_PTR(BI_ECDH_PUBKEYVZ_TAG);
    BigInt sharedInfoV = GET_BIGINT_PTR(BI_ECDH_SHAREDV_TAG);
    
	__montgomery_init(params.p);

    start = start_tsc();
    
    mul_opcount = 0;
    add_opcount = 0;
    shift_opcount = 0;
    avx_opcount = 0;

    for(int i = 0; i < num_runs; i++)
    {
	    ecdh_generate_public_key(&pub_keyU, dU, &params);
	    ecdh_generate_public_key(&pub_keyV, dV, &params);

	    ecdh_compute_shared_secret(sharedInfoU, dU, &pub_keyV, &params);
	    ecdh_compute_shared_secret(sharedInfoV, dV, &pub_keyU, &params);
    }
    cycles = stop_tsc(start);

    mul_opcount = mul_opcount/num_runs;
    add_opcount = add_opcount/num_runs; 
    shift_opcount = shift_opcount/num_runs;
    avx_opcount = avx_opcount/num_runs;
    
	printf("mul_opcount = %" PRIu64 "\n", mul_opcount);
	printf("add_opcount = %" PRIu64 "\n", add_opcount);
	printf("shift_opcount = %" PRIu64 "\n", shift_opcount);
	printf("avx_opcount = %" PRIu64 "\n", avx_opcount);
    printf("global_index_count = %" PRIu64 "\n", global_index_count);

    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6); 
    BigInt sharedInfoU_conv = GET_BIGINT_PTR(BI_MAIN_SHAREDINFOU_CONV_TAG);
    BigInt sharedInfoV_conv = GET_BIGINT_PTR(BI_MAIN_SHAREDINFOV_CONV_TAG);
    __montgomery_revert(sharedInfoU_conv, sharedInfoU, params.p);
    __montgomery_revert(sharedInfoV_conv, sharedInfoV, params.p);
    char *infoU = bigint_to_hex_string(sharedInfoU_conv);
    char *infoV = bigint_to_hex_string(sharedInfoV_conv);
    printf("info u %s\ninfo v %s\n\n", infoU, infoV);
    free(infoU);
    free(infoV);

    ec_create_ECDH(&uECDH, &params, &pub_keyU, dU, sharedInfoU);
    ec_create_ECDH(&vECDH, &params, &pub_keyV, dV, sharedInfoV);
    
    assert(ecdh_verification(&uECDH, &vECDH) != 0);
}

void compute_ECDH_open_ssl(char* dURand, char* dVRand, int keyLength)
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

    EllipticCurveParameter params = get_parameter_by_key_length(keyLength);
    ec_parameter_revert_from_montgomery_space(&params);
    point_revert_from_montgomery_space(&(params.generator), params.p);

    char *p_hex = bigint_to_hex_string(params.p);
    char *a_hex = bigint_to_hex_string(params.a);
    char *b_hex = bigint_to_hex_string(params.b);
    char *g_x_hex = bigint_to_hex_string(params.generator.x);
    char *g_y_hex = bigint_to_hex_string(params.generator.y);
    char *n_hex = bigint_to_hex_string(params.n);
    
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *p = BN_new();
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    BIGNUM *n = BN_new();
    
    BIGNUM *dU = BN_new();
    BIGNUM *dV = BN_new();

    BIGNUM *sharedInfoU_x = BN_new();
    BIGNUM *sharedInfoU_y = BN_new();
    BIGNUM *sharedInfoV_x = BN_new();
    BIGNUM *sharedInfoV_y = BN_new();

    BN_hex2bn(&p, p_hex);
    BN_hex2bn(&a, a_hex);
    BN_hex2bn(&b, b_hex);
    BN_hex2bn(&x, g_x_hex);
    BN_hex2bn(&y, g_y_hex);
    BN_hex2bn(&n, n_hex);

    EC_GROUP * group_non_optimized = EC_GROUP_new_curve_GFp(p, a, b, ctx);
    EC_POINT *G = EC_POINT_new(group_non_optimized);
    EC_POINT_set_affine_coordinates_GFp(group_non_optimized, G, x, y, ctx);
    EC_GROUP_set_generator(group_non_optimized, G, n, NULL);
    
    BN_hex2bn(&dU, dURand);
    BN_hex2bn(&dV, dVRand);
    EC_POINT *public_keyU = EC_POINT_new(group_non_optimized);
    EC_POINT *public_keyV = EC_POINT_new(group_non_optimized);
    EC_POINT *resultU = EC_POINT_new(group_non_optimized);
    EC_POINT *resultV = EC_POINT_new(group_non_optimized);

    
    start = start_tsc();
    for(int i = 0; i < num_runs; i++)
    {
	EC_POINT_mul(group_non_optimized, public_keyU, dU, NULL, NULL, ctx);
	EC_POINT_mul(group_non_optimized, public_keyV, dV, NULL, NULL, ctx);
	EC_POINT_mul(group_non_optimized, resultU, NULL, public_keyV, dU, ctx);
	EC_POINT_mul(group_non_optimized, resultV, NULL, public_keyU, dV, ctx);
    }
    cycles = stop_tsc(start);	
    EC_POINT_get_affine_coordinates_GF2m(group_non_optimized, resultU, sharedInfoU_x, sharedInfoU_y, NULL);
    EC_POINT_get_affine_coordinates_GF2m(group_non_optimized, resultV, sharedInfoV_x, sharedInfoV_y, NULL);

    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
    
    char *infoU = BN_bn2hex(sharedInfoU_x);
    char *infoV = BN_bn2hex(sharedInfoV_x);
    printf("info u %s\ninfo v %s\n\n", infoU, infoV);
    free(infoU);
    free(infoV);
    free(p_hex);
    free(a_hex);
    free(b_hex);
    free(g_x_hex);
    free(g_y_hex);
    free(n_hex);
    BN_CTX_free(ctx);
    BN_free(p);
    BN_free(a);
    BN_free(b);
    BN_free(x);
    BN_free(y);
    BN_free(n);
    BN_free(dU);
    BN_free(dV);
    BN_free(sharedInfoU_x);
    BN_free(sharedInfoU_y);
    BN_free(sharedInfoV_x);
    BN_free(sharedInfoV_y);
    EC_POINT_free(G);
    EC_POINT_free(public_keyU);
    EC_POINT_free(public_keyV);
    EC_POINT_free(resultU);
    EC_POINT_free(resultV);
    EC_GROUP_free(group_non_optimized);
}

int main(){
    
    bigint_create_buffer();
    
    mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0; 
    // secp192
    printf("==========ECDH optimal secp192==========\n");
    compute_ECDH("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",192); 
    mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;
    global_index_count = 0;
	
    printf("==========ECDH open_ssl secp192==========\n");
    compute_ECDH_open_ssl("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",192); 
    mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;
    global_index_count = 0;
    // secp224
    printf("==========ECDH optimal secp224==========\n");
    compute_ECDH("FEFFFFFFFFFFFFFFFFFFFFFFFFFF61A2E0B8F03E13DD29455C5C2A3D","FEFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29545C5C2A3D",224); 
	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0;
    printf("==========ECDH open_ssl secp224==========\n");    
    compute_ECDH_open_ssl("FEFFFFFFFFFFFFFFFFFFFFFFFFFF61A2E0B8F03E13DD29455C5C2A3D","FEFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29545C5C2A3D", 224);  

	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;


    global_index_count = 0;   
    // secp256
    printf("==========ECDH optimal secp256==========\n");
    compute_ECDH("FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF84A03BBFD25E8CD0364141","FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0361441", 256); 
	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0;  
    printf("==========ECDH open_ssl secp256==========\n");     
    compute_ECDH_open_ssl("FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF84A03BBFD25E8CD0364141","FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0361441", 256); 
	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0;
    // secp384
    printf("==========ECDH optimal secp384==========\n");
    compute_ECDH("FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF851A0DB248B0A77AECEC196ACCC52973","FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F3472DDF581A0DB248B0A77AECEC196ACCC52973", 384);
	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0;
    printf("==========ECDH open_ssl secp384==========\n");  
    compute_ECDH_open_ssl("FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF851A0DB248B0A77AECEC196ACCC52973","FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F3472DDF581A0DB248B0A77AECEC196ACCC52973", 384);
	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0;
    // secp521
    printf("==========ECDH optimal secp521==========\n");
    compute_ECDH("01EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA15868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409","01EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868738BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409", 521);
	mul_opcount = 0;
	add_opcount = 0;
	shift_opcount = 0;
	avx_opcount = 0;

    global_index_count = 0;
    printf("==========ECDH open_ssl secp521==========\n");  
    compute_ECDH_open_ssl("01EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA15868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409","01EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868738BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409", 521);

    bigint_destroy_buffer();
  
    return 0;
}
